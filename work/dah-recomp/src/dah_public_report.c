#include "dah_public_report.h"
#include "dah_run_evidence.h"

#include <bcrypt.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint64_t report_build_hash;
static ULONGLONG report_started_tick;
static char report_id[33];
static char report_path[MAX_PATH];
static int report_initialized;
static int report_finalized;
static int consent_crashes;
static int consent_sessions;

static void write_all(HANDLE file, const char *text)
{
    DWORD remaining = (DWORD)strlen(text);
    while (remaining) {
        DWORD wrote = 0;
        if (!WriteFile(file, text, remaining, &wrote, NULL) || !wrote) return;
        text += wrote;
        remaining -= wrote;
    }
}

static void ensure_directory(const char *path)
{
    if (!CreateDirectoryA(path, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
        fprintf(stderr, "[DAH-REPORT] could not create %s error=%lu\n", path,
                GetLastError());
}

static void write_settings_file(int crashes, int sessions)
{
    char settings[768];
    HANDLE file = CreateFileA("reporting-settings.json", GENERIC_WRITE,
                              FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    sprintf_s(settings, sizeof(settings),
        "{\r\n"
        "  \"schema\": 1,\r\n"
        "  \"sendCrashReports\": %s,\r\n"
        "  \"sendSessionReports\": %s,\r\n"
        "  \"notice\": \"Only sanitized public reports are eligible for submission. Raw logs, dumps, saves, paths, memory and game assets remain local.\"\r\n"
        "}\r\n",
        crashes ? "true" : "false", sessions ? "true" : "false");
    if (file != INVALID_HANDLE_VALUE) {
        write_all(file, settings);
        FlushFileBuffers(file);
        CloseHandle(file);
    }
}

static void load_settings(void)
{
    char buffer[4097];
    DWORD got = 0;
    HANDLE file;
    DWORD attributes = GetFileAttributesA("reporting-settings.json");
    consent_crashes = 0;
    consent_sessions = 0;
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        const char *internal = getenv("DAH_INTERNAL_RUN");
        int accepted = 0;
        if (!(internal && !strcmp(internal, "1"))) {
            accepted = MessageBoxA(NULL,
                "Help improve Destroy All Humans! Recomp?\n\n"
                "The Debug-Reporter edition can prepare anonymous crash and "
                "play-session reports. Reports contain only game/build IDs, "
                "crash signatures, timing and anomaly counters.\n\n"
                "It will never include your name, computer name, paths, saves, "
                "inputs, screenshots, logs, memory, game files or assets. "
                "You can inspect every report and change this choice later.\n\n"
                "Choose Yes to opt in, or No to keep all reports local.",
                "Destroy All Humans! Debug-Reporter",
                MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES;
        }
        consent_crashes = accepted;
        consent_sessions = accepted;
        write_settings_file(consent_crashes, consent_sessions);
    }
    file = CreateFileA("reporting-settings.json", GENERIC_READ,
                       FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return;
    if (ReadFile(file, buffer, sizeof(buffer) - 1u, &got, NULL)) {
        buffer[got] = 0;
        consent_crashes = strstr(buffer, "\"sendCrashReports\": true") != NULL;
        consent_sessions = strstr(buffer, "\"sendSessionReports\": true") != NULL;
    }
    CloseHandle(file);
}

int dah_public_report_set_consent(int crash_reports, int session_reports)
{
    consent_crashes = crash_reports != 0;
    consent_sessions = session_reports != 0;
    write_settings_file(consent_crashes, consent_sessions);
    return GetFileAttributesA("reporting-settings.json") != INVALID_FILE_ATTRIBUTES;
}

void dah_public_report_get_consent(int *crash_reports, int *session_reports)
{
    if (crash_reports) *crash_reports = consent_crashes;
    if (session_reports) *session_reports = consent_sessions;
}

static uint64_t summary_value(const char *name)
{
    char path[MAX_PATH];
    char buffer[16385];
    char needle[96];
    char *match;
    FILE *file;
    size_t got;
    if (!dah_run_evidence_path(path, sizeof(path), "summary.json")) return 0;
    file = fopen(path, "rb");
    if (!file) return 0;
    got = fread(buffer, 1, sizeof(buffer) - 1u, file);
    fclose(file);
    buffer[got] = 0;
    sprintf_s(needle, sizeof(needle), "\"%s\"", name);
    match = strstr(buffer, needle);
    if (!match || !(match = strchr(match + strlen(needle), ':'))) return 0;
    return _strtoui64(match + 1, NULL, 10);
}

static const char *safe_status(const char *status)
{
    static const char *const allowed[] = {
        "completed", "closed", "quit", "manual"
    };
    unsigned i;
    for (i = 0; i < sizeof(allowed) / sizeof(allowed[0]); ++i)
        if (status && !strcmp(status, allowed[i])) return allowed[i];
    return "quit";
}

static void select_report_path(int eligible_to_send)
{
    const char *directory = eligible_to_send ?
        "reports\\pending" : "reports\\local";
    ensure_directory("reports");
    ensure_directory("reports\\local");
    ensure_directory("reports\\pending");
    sprintf_s(report_path, sizeof(report_path), "%s\\report-%s.json",
              directory, report_id);
}

static void offer_previous_crash(void)
{
    WIN32_FIND_DATAA found;
    HANDLE search;
    const char *internal = getenv("DAH_INTERNAL_RUN");
    if (internal && !strcmp(internal, "1")) return;
    search = FindFirstFileA("reports\\pending\\report-*.json", &found);
    if (search == INVALID_HANDLE_VALUE) return;
    do {
        char path[MAX_PATH];
        char body[4097];
        DWORD got = 0;
        HANDLE file;
        if (found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        sprintf_s(path, sizeof(path), "reports\\pending\\%s", found.cFileName);
        file = CreateFileA(path, GENERIC_READ,
                           FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file == INVALID_HANDLE_VALUE) continue;
        if (!ReadFile(file, body, sizeof(body) - 1u, &got, NULL)) got = 0;
        CloseHandle(file);
        body[got] = 0;
        if (!strstr(body, "\"kind\": \"crash\"")) continue;
        FindClose(search);
        if (MessageBoxA(NULL,
                "The Debug-Reporter edition saved a sanitized crash report "
                "from the previous run.\n\nOpen the GitHub report form and "
                "reports folder now? You can inspect the JSON before attaching it.",
                "Destroy All Humans! Crash Report",
                MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON1) == IDYES) {
            ShellExecuteA(NULL, "open",
                "https://github.com/Zippingrocks/Destroy-All-Humans-2005-Static-Recompilation/issues/new?template=bug_report.yml&title=%5BCrash+report%5D+DAH+Debug-Reporter",
                NULL, NULL, SW_SHOWNORMAL);
            ShellExecuteA(NULL, "open", "reports\\pending", NULL, NULL,
                          SW_SHOWNORMAL);
        }
        return;
    } while (FindNextFileA(search, &found));
    FindClose(search);
}

static void write_session_report(const char *status)
{
    char json[4096];
    HANDLE file;
    uint64_t duration = (GetTickCount64() - report_started_tick) / 1000u;
    select_report_path(consent_sessions);
    sprintf_s(json, sizeof(json),
        "{\r\n"
        "  \"schema\": 1,\r\n"
        "  \"privacySchema\": 1,\r\n"
        "  \"reportId\": \"%s\",\r\n"
        "  \"kind\": \"session\",\r\n"
        "  \"buildFnv1a64\": \"%016llX\",\r\n"
        "  \"status\": \"%s\",\r\n"
        "  \"durationSeconds\": %llu,\r\n"
        "  \"events\": %llu,\r\n"
        "  \"anomalies\": %llu,\r\n"
        "  \"droppedEvents\": %llu,\r\n"
        "  \"frameBudgetMisses\": %llu,\r\n"
        "  \"sceneVisibilityFlashes\": %llu,\r\n"
        "  \"playerRenderLosses\": %llu,\r\n"
        "  \"hudCinematicOverlaps\": %llu,\r\n"
        "  \"worstFrameUs\": %llu,\r\n"
        "  \"containsPaths\": false,\r\n"
        "  \"containsMemory\": false,\r\n"
        "  \"containsGameAssets\": false\r\n"
        "}\r\n",
        report_id, (unsigned long long)report_build_hash, safe_status(status),
        (unsigned long long)duration,
        (unsigned long long)summary_value("events"),
        (unsigned long long)summary_value("anomalies"),
        (unsigned long long)summary_value("droppedEvents"),
        (unsigned long long)summary_value("frame-budget-miss"),
        (unsigned long long)summary_value("scene-visibility-flash"),
        (unsigned long long)summary_value("player-render-loss"),
        (unsigned long long)summary_value("hud-cinematic-overlap"),
        (unsigned long long)summary_value("worstFrameUs"));
    file = CreateFileA(report_path, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return;
    write_all(file, json);
    FlushFileBuffers(file);
    CloseHandle(file);
}

void dah_public_report_initialize(uint64_t executable_hash)
{
    unsigned char random_bytes[16];
    unsigned i;
    if (report_initialized) return;
    memset(random_bytes, 0, sizeof(random_bytes));
    if (BCryptGenRandom(NULL, random_bytes, sizeof(random_bytes),
                        BCRYPT_USE_SYSTEM_PREFERRED_RNG) < 0) {
        ULONGLONG fallback = GetTickCount64() ^ executable_hash;
        memcpy(random_bytes, &fallback, sizeof(fallback));
        fallback = (ULONGLONG)(uintptr_t)&report_initialized;
        memcpy(random_bytes + 8, &fallback, sizeof(fallback));
    }
    for (i = 0; i < sizeof(random_bytes); ++i)
        sprintf_s(report_id + i * 2u, sizeof(report_id) - i * 2u,
                  "%02x", random_bytes[i]);
    report_build_hash = executable_hash;
    report_started_tick = GetTickCount64();
    report_initialized = 1;
    load_settings();
    if (consent_crashes) offer_previous_crash();
    select_report_path(0);
    fprintf(stderr,
        "[DAH-REPORT] privacy-schema=1 crash-consent=%d session-consent=%d id=%s\n",
        consent_crashes, consent_sessions, report_id);
}

void dah_public_report_session(const char *status)
{
    if (!report_initialized || report_finalized) return;
    write_session_report(status);
    if (!strcmp(safe_status(status), "completed") ||
        !strcmp(safe_status(status), "closed"))
        report_finalized = 1;
}

void dah_public_report_shutdown(void)
{
    if (report_initialized && !report_finalized) write_session_report("quit");
}

void dah_public_report_crash(const char *signature, DWORD exception_code,
                             uint64_t host_rva, ULONG_PTR access,
                             uint32_t guest_return)
{
    char json[2048];
    HANDLE file;
    uint64_t duration;
    if (!report_initialized || !signature || strncmp(signature, "DAH-", 4))
        return;
    duration = (GetTickCount64() - report_started_tick) / 1000u;
    select_report_path(consent_crashes);
    sprintf_s(json, sizeof(json),
        "{\r\n"
        "  \"schema\": 1,\r\n"
        "  \"privacySchema\": 1,\r\n"
        "  \"reportId\": \"%s\",\r\n"
        "  \"kind\": \"crash\",\r\n"
        "  \"buildFnv1a64\": \"%016llX\",\r\n"
        "  \"durationSeconds\": %llu,\r\n"
        "  \"crashSignature\": \"%.20s\",\r\n"
        "  \"exceptionCode\": \"%08lX\",\r\n"
        "  \"hostRva\": \"%016llX\",\r\n"
        "  \"accessType\": %llu,\r\n"
        "  \"guestReturn\": \"%08X\",\r\n"
        "  \"containsPaths\": false,\r\n"
        "  \"containsMemory\": false,\r\n"
        "  \"containsGameAssets\": false\r\n"
        "}\r\n",
        report_id, (unsigned long long)report_build_hash,
        (unsigned long long)duration, signature, exception_code,
        (unsigned long long)host_rva, (unsigned long long)access,
        guest_return);
    file = CreateFileA(report_path, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        write_all(file, json);
        FlushFileBuffers(file);
        CloseHandle(file);
    }
    report_finalized = 1;
}

const char *dah_public_report_path(void)
{
    return report_path;
}

int dah_public_report_open_issue(void)
{
    char url[1024];
    HINSTANCE opened;
    if (!report_initialized) return 0;
    dah_public_report_session("manual");
    sprintf_s(url, sizeof(url),
        "https://github.com/Zippingrocks/Destroy-All-Humans-2005-Static-Recompilation/issues/new?template=bug_report.yml&title=%%5BReport%%5D+DAH+bug+%s",
        report_id);
    opened = ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    ShellExecuteA(NULL, "open", "reports", NULL, NULL, SW_SHOWNORMAL);
    return (INT_PTR)opened > 32;
}
