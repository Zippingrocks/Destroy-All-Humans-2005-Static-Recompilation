#include "dah_crashlog.h"

#include <dbghelp.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
#define DAH_CRASH_TLS __declspec(thread)
#else
#define DAH_CRASH_TLS _Thread_local
#endif

extern DAH_CRASH_TLS uint32_t g_eax, g_ecx, g_edx, g_esp;
extern DAH_CRASH_TLS uint32_t g_ebx, g_esi, g_edi, g_ebp;
extern ptrdiff_t xbox_GetMemoryOffset(void);

static char g_runtime_log[MAX_PATH] = "recomp.log";
static volatile LONG g_recording;

static uint32_t safe_u32(const uint8_t *base, uint32_t address, int *valid)
{
#if defined(_MSC_VER)
    __try {
        uint32_t value;
        if (!base || address > 0x07FFFFFCu) return 0;
        value = *(const uint32_t *)(base + address);
        *valid = 1;
        return value;
    } __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
#else
    (void)base; (void)address; (void)valid;
    return 0;
#endif
}

static uint64_t hash64(uint64_t hash, uint64_t value)
{
    unsigned i;
    for (i = 0; i < 8; ++i) {
        hash ^= (uint8_t)(value >> (i * 8));
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}

static const char *fix_hint(DWORD code, ULONG_PTR access)
{
    if (code == EXCEPTION_ACCESS_VIOLATION || code == EXCEPTION_IN_PAGE_ERROR) {
        if (access == 8) return "Invalid execute target: resolve the host RVA and guest return, then inspect the callback/vtable target.";
        if (access == 1) return "Invalid write: resolve the host RVA and inspect the destination object's lifetime and bounds.";
        return "Invalid read: resolve the host RVA and inspect the source pointer, object lifetime, and missing original callback.";
    }
    if (code == EXCEPTION_ILLEGAL_INSTRUCTION) return "Resolve the host RVA and inspect the generated or manually lifted instruction path.";
    if (code == EXCEPTION_INT_DIVIDE_BY_ZERO || code == EXCEPTION_FLT_DIVIDE_BY_ZERO) return "Resolve the host RVA and trace the divisor back to its original game state.";
    if (code == EXCEPTION_STACK_OVERFLOW) return "Inspect recursion and guest/host stack ownership near the recorded site.";
    if (code == EXCEPTION_BREAKPOINT) return "Inspect the deliberate breakpoint or assertion at the recorded host RVA.";
    return "Resolve the host RVA with DestroyAllHumans.map and trace the recorded guest stack and runtime-log tail.";
}

static void write_all(HANDLE file, const void *data, DWORD bytes)
{
    const uint8_t *cursor = (const uint8_t *)data;
    while (bytes) {
        DWORD wrote = 0;
        if (!WriteFile(file, cursor, bytes, &wrote, NULL) || !wrote) return;
        cursor += wrote;
        bytes -= wrote;
    }
}

static void append_text(const char *path, const char *text)
{
    HANDLE file = CreateFileA(path, FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        write_all(file, text, (DWORD)strlen(text));
        FlushFileBuffers(file);
        CloseHandle(file);
    }
}

static int catalog_has_signature(const char *signature)
{
    HANDLE file = CreateFileA("crashlog\\unique-crashes.jsonl", GENERIC_READ,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    char buffer[65536 + 1];
    DWORD got;
    int found = 0;
    if (file == INVALID_HANDLE_VALUE) return 0;
    while (ReadFile(file, buffer, 65536, &got, NULL) && got) {
        buffer[got] = 0;
        if (strstr(buffer, signature)) { found = 1; break; }
    }
    CloseHandle(file);
    return found;
}

static void append_runtime_tail(HANDLE report)
{
    HANDLE source = CreateFileA(g_runtime_log, GENERIC_READ,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    LARGE_INTEGER size;
    char buffer[8192];
    DWORD got;
    if (source == INVALID_HANDLE_VALUE || !GetFileSizeEx(source, &size)) {
        if (source != INVALID_HANDLE_VALUE) CloseHandle(source);
        return;
    }
    if (size.QuadPart > 65536) {
        LARGE_INTEGER start;
        start.QuadPart = size.QuadPart - 65536;
        SetFilePointerEx(source, start, NULL, FILE_BEGIN);
    }
    write_all(report, "\r\n[runtime-log-tail]\r\n", 22);
    while (ReadFile(source, buffer, sizeof(buffer), &got, NULL) && got) write_all(report, buffer, got);
    CloseHandle(source);
}

void dah_crashlog_initialize(const char *runtime_log_path)
{
    const char *readme =
        "Destroy All Humans! crashlog\r\n"
        "================================\r\n"
        "events.jsonl records every crash occurrence. unique-crashes.jsonl records one row per stable signature.\r\n"
        "Each crash-*.txt contains host and guest registers, stack data, a fix hint, and the runtime log tail.\r\n"
        "The first occurrence of each signature also gets a matching .dmp for debugger inspection.\r\n"
        "This crash-only archive is separate from furonlog.log and recomp_crash.log; neither is replaced.\r\n";
    HANDLE readme_file;
    ULONG guarantee = 64 * 1024;
    if (runtime_log_path && *runtime_log_path)
        strncpy_s(g_runtime_log, sizeof(g_runtime_log), runtime_log_path, _TRUNCATE);
    CreateDirectoryA("crashlog", NULL);
    readme_file = CreateFileA("crashlog\\README.txt", GENERIC_WRITE, FILE_SHARE_READ,
                              NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (readme_file != INVALID_HANDLE_VALUE) {
        write_all(readme_file, readme, (DWORD)strlen(readme));
        CloseHandle(readme_file);
    }
    SetThreadStackGuarantee(&guarantee);
    SetUnhandledExceptionFilter(dah_crashlog_unhandled);
}

LONG WINAPI dah_crashlog_unhandled(EXCEPTION_POINTERS *info)
{
    SYSTEMTIME now;
    uintptr_t module_base;
    uintptr_t exception_address;
    uint64_t host_rva;
    uint8_t *guest_base;
    uint32_t guest_return = 0;
    int guest_return_valid = 0;
    DWORD code, pid, tid;
    ULONG_PTR access = 0, target = 0;
    uint64_t fingerprint;
    char signature[40], stamp[64], report_name[MAX_PATH], dump_name[MAX_PATH];
    char line[4096], exe[MAX_PATH];
    HANDLE report;
    int first_unique;
    unsigned i;

    if (!info || !info->ExceptionRecord || !info->ContextRecord ||
        InterlockedCompareExchange(&g_recording, 1, 0) != 0)
        return EXCEPTION_CONTINUE_SEARCH;

    code = info->ExceptionRecord->ExceptionCode;
    if (code == 0x40010006u || code == 0x4001000Au || code == 0x406D1388u) {
        InterlockedExchange(&g_recording, 0);
        return EXCEPTION_CONTINUE_SEARCH;
    }
    pid = GetCurrentProcessId(); tid = GetCurrentThreadId();
    module_base = (uintptr_t)GetModuleHandleA(NULL);
    exception_address = (uintptr_t)info->ExceptionRecord->ExceptionAddress;
    host_rva = exception_address >= module_base ? (uint64_t)(exception_address - module_base) : UINT64_MAX;
    if (info->ExceptionRecord->NumberParameters > 0) access = info->ExceptionRecord->ExceptionInformation[0];
    if (info->ExceptionRecord->NumberParameters > 1) target = info->ExceptionRecord->ExceptionInformation[1];
    guest_base = (uint8_t *)(uintptr_t)xbox_GetMemoryOffset();
    guest_return = safe_u32(guest_base, g_esp, &guest_return_valid);

    fingerprint = UINT64_C(1469598103934665603);
    fingerprint = hash64(fingerprint, code);
    fingerprint = hash64(fingerprint, guest_return_valid && guest_return >= 0x10000u && guest_return < 0x04000000u ? guest_return : host_rva);
    fingerprint = hash64(fingerprint, access);
    sprintf_s(signature, sizeof(signature), "DAH-%016llX", (unsigned long long)fingerprint);
    GetSystemTime(&now);
    sprintf_s(stamp, sizeof(stamp), "%04u%02u%02uT%02u%02u%02u.%03uZ",
              now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds);
    sprintf_s(report_name, sizeof(report_name), "crashlog/crash-%s-p%lu-t%lu-%s.txt", stamp, pid, tid, signature);
    sprintf_s(dump_name, sizeof(dump_name), "crashlog/crash-%s-p%lu-t%lu-%s.dmp", stamp, pid, tid, signature);
    first_unique = !catalog_has_signature(signature);
    GetModuleFileNameA(NULL, exe, MAX_PATH);

    sprintf_s(line, sizeof(line),
        "{\"time\":\"%s\",\"signature\":\"%s\",\"exception\":\"%08lX\",\"host_rva\":\"%016llX\",\"access\":%llu,\"target\":\"%016llX\",\"guest_esp\":\"%08X\",\"guest_return\":\"%08X\",\"pid\":%lu,\"tid\":%lu,\"report\":\"%s\",\"first_unique\":%s}\r\n",
        stamp, signature, code, (unsigned long long)host_rva, (unsigned long long)access,
        (unsigned long long)target, g_esp, guest_return, pid, tid, report_name, first_unique ? "true" : "false");
    append_text("crashlog\\events.jsonl", line);
    if (first_unique) {
        sprintf_s(line, sizeof(line),
            "{\"signature\":\"%s\",\"first_seen\":\"%s\",\"exception\":\"%08lX\",\"host_rva\":\"%016llX\",\"access\":%llu,\"guest_return\":\"%08X\",\"report\":\"%s\",\"fix_hint\":\"%s\"}\r\n",
            signature, stamp, code, (unsigned long long)host_rva, (unsigned long long)access,
            guest_return, report_name, fix_hint(code, access));
        append_text("crashlog\\unique-crashes.jsonl", line);
    }

    report = CreateFileA(report_name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (report != INVALID_HANDLE_VALUE) {
        sprintf_s(line, sizeof(line),
            "Destroy All Humans! crash occurrence\r\n"
            "time=%s\r\nsignature=%s\r\nfirst_unique=%d\r\nexception=%08lX\r\n"
            "exception_address=%p\r\nmodule_base=%p\r\nhost_rva=%016llX\r\n"
            "access=%llu target=%016llX parameters=%lu\r\npid=%lu tid=%lu\r\n"
            "executable=%s\r\nbuild=%s %s\r\nruntime_log=%s\r\nfix_hint=%s\r\n"
            "guest_regs eax=%08X ecx=%08X edx=%08X ebx=%08X esi=%08X edi=%08X ebp=%08X esp=%08X return=%08X valid=%d\r\n",
            stamp, signature, first_unique, code, (void *)exception_address, (void *)module_base,
            (unsigned long long)host_rva, (unsigned long long)access, (unsigned long long)target,
            info->ExceptionRecord->NumberParameters, pid, tid, exe, __DATE__, __TIME__, g_runtime_log,
            fix_hint(code, access), g_eax, g_ecx, g_edx, g_ebx, g_esi, g_edi, g_ebp, g_esp,
            guest_return, guest_return_valid);
        write_all(report, line, (DWORD)strlen(line));
        for (i = 0; i < info->ExceptionRecord->NumberParameters; ++i) {
            sprintf_s(line, sizeof(line), "parameter[%u]=%016llX\r\n", i,
                      (unsigned long long)info->ExceptionRecord->ExceptionInformation[i]);
            write_all(report, line, (DWORD)strlen(line));
        }
#if defined(_M_X64)
        sprintf_s(line, sizeof(line),
            "host_context rip=%016llX rsp=%016llX rbp=%016llX rax=%016llX rbx=%016llX rcx=%016llX rdx=%016llX rsi=%016llX rdi=%016llX r8=%016llX r9=%016llX r10=%016llX r11=%016llX r12=%016llX r13=%016llX r14=%016llX r15=%016llX eflags=%08lX\r\n",
            info->ContextRecord->Rip, info->ContextRecord->Rsp, info->ContextRecord->Rbp,
            info->ContextRecord->Rax, info->ContextRecord->Rbx, info->ContextRecord->Rcx,
            info->ContextRecord->Rdx, info->ContextRecord->Rsi, info->ContextRecord->Rdi,
            info->ContextRecord->R8, info->ContextRecord->R9, info->ContextRecord->R10,
            info->ContextRecord->R11, info->ContextRecord->R12, info->ContextRecord->R13,
            info->ContextRecord->R14, info->ContextRecord->R15, info->ContextRecord->EFlags);
        write_all(report, line, (DWORD)strlen(line));
#endif
        write_all(report, "guest_stack:\r\n", 14);
        for (i = 0; i < 32; ++i) {
            int valid = 0;
            uint32_t value = safe_u32(guest_base, g_esp + i * 4u, &valid);
            sprintf_s(line, sizeof(line), "  +%02X %s%08X\r\n", i * 4u, valid ? "" : "INVALID ", value);
            write_all(report, line, (DWORD)strlen(line));
        }
        append_runtime_tail(report);
        FlushFileBuffers(report);
        CloseHandle(report);
    }

    if (first_unique) {
        HANDLE dump = CreateFileA(dump_name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (dump != INVALID_HANDLE_VALUE) {
            MINIDUMP_EXCEPTION_INFORMATION mei;
            mei.ThreadId = tid; mei.ExceptionPointers = info; mei.ClientPointers = FALSE;
            MiniDumpWriteDump(GetCurrentProcess(), pid, dump,
                (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithDataSegs | MiniDumpWithHandleData |
                                MiniDumpWithThreadInfo | MiniDumpWithUnloadedModules | MiniDumpWithCodeSegs),
                &mei, NULL, NULL);
            FlushFileBuffers(dump);
            CloseHandle(dump);
        }
    }
    InterlockedExchange(&g_recording, 0);
    return EXCEPTION_EXECUTE_HANDLER;
}
