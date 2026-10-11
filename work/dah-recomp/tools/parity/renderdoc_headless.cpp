// Console-only RenderDoc v1.43 target control and offline replay helper.
// No Qt or preview outputs. Launch mode only injects a newly created suspended
// xemu child on an explicitly named inactive desktop, never an existing PID.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define RENDERDOC_PLATFORM_WIN32
#include <windows.h>
#include <delayimp.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include "renderdoc_replay.h"

REPLAY_PROGRAM_MARKER()

static FARPROC WINAPI load_renderdoc(unsigned notification, PDelayLoadInfo info)
{
    if (notification == dliNotePreLoadLibrary && !_stricmp(info->szDll, "renderdoc.dll")) {
        HMODULE module = LoadLibraryExW(L"C:\\Program Files\\RenderDoc\\renderdoc.dll", nullptr,
            LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!module) {
            std::fprintf(stderr, "Cannot load installed RenderDoc: Windows error %lu\n", GetLastError());
            ExitProcess(10);
        }
        return reinterpret_cast<FARPROC>(module);
    }
    return nullptr;
}
extern "C" const PfnDliHook __pfnDliNotifyHook2 = load_renderdoc;

static const char *expected_commit = "286e07140d96bf3acda4059e085e8f5eb0e92608";

static std::string json(const char *value)
{
    std::string out = "\"";
    for (const unsigned char *p = reinterpret_cast<const unsigned char *>(value); *p; ++p) {
        if (*p == '\\' || *p == '"') { out += '\\'; out += char(*p); }
        else if (*p < 32) { char b[7]; std::snprintf(b, sizeof(b), "\\u%04x", *p); out += b; }
        else out += char(*p);
    }
    return out + "\"";
}

static uint32_t number(const char *s, uint32_t maximum)
{
    char *end = nullptr;
    unsigned long long n = std::strtoull(s, &end, 10);
    if (!s[0] || s[0] == '-' || !end || *end || !n || n > maximum)
        throw std::runtime_error(std::string("Invalid positive integer: ") + s);
    return uint32_t(n);
}

struct ReplayLifetime {
    ReplayLifetime() {
        GlobalEnvironment env;
        env.enumerateGPUs = false;
        RENDERDOC_InitialiseReplay(env, {});
    }
    ~ReplayLifetime() { RENDERDOC_ShutdownReplay(); }
};

template<typename T> struct Handle {
    T *value = nullptr;
    ~Handle() { if (value) value->Shutdown(); }
    T *operator->() const { return value; }
};

static void check(const ResultDetails &result)
{
    if (!result.OK()) throw std::runtime_error(result.internal_msg ? result.internal_msg->c_str() :
        (std::string("RenderDoc result code ") + std::to_string(unsigned(result.code))));
}

// Keep ResourceId opaque. Tokens are indices into this capture's texture list,
// never guessed integer representations of RenderDoc's private ID storage.
static std::string token(IReplayController *controller, ResourceId resource)
{
    const auto &textures = controller->GetTextures();
    for (size_t i = 0; i < textures.size(); ++i)
        if (textures[i].resourceId == resource) return "texture:" + std::to_string(i);
    return "none";
}

static void show_capture(const NewCaptureData &c, const char *kind)
{
    std::printf("{\"kind\":%s,\"captureId\":%u,\"hostFrame\":%u,\"timestamp\":%llu,"
        "\"local\":%s,\"api\":%s,\"path\":%s,\"title\":%s}\n", json(kind).c_str(),
        c.captureId, c.frameNumber, static_cast<unsigned long long>(c.timestamp),
        c.local ? "true" : "false", json(c.api.c_str()).c_str(), json(c.path.c_str()).c_str(),
        json(c.title.c_str()).c_str());
    std::fflush(stdout);
}

static void capture(uint32_t ident, uint32_t expected_pid, uint32_t timeout_ms,
                    bool trigger, uint32_t inventory_ms = 1000)
{
    Handle<ITargetControl> target{RENDERDOC_CreateTargetControl("localhost", ident,
                                                              "DAH headless parity", false)};
    if (!target.value || !target->Connected()) throw std::runtime_error("Target unavailable or busy");
    if (target->GetPID() != expected_pid) throw std::runtime_error("Target PID mismatch; capture not requested");
    std::printf("{\"kind\":\"target\",\"pid\":%u,\"ident\":%u,\"api\":%s}\n",
        expected_pid, ident, json(target->GetAPI().c_str()).c_str());
    // Receive the existing capture inventory before requesting one new capture.
    // Listen mode accepts an already available app-API capture and does not trigger.
    std::set<std::string> known;
    auto capture_key = [](const NewCaptureData &c) {
        return std::to_string(c.captureId) + ":" + std::to_string(c.frameNumber) + ":" +
               std::to_string(static_cast<unsigned long long>(c.timestamp)) + ":" + c.path.c_str();
    };
    // Target control replays its complete capture inventory when a client
    // connects.  Wait for an actual quiet interval after the last inventory
    // record instead of assuming every record arrives inside one fixed window.
    ULONGLONG last_inventory_message = GetTickCount64();
    ULONGLONG inventory_deadline = last_inventory_message +
        (std::max)(5000ull, static_cast<ULONGLONG>(inventory_ms) * 20ull);
    while (GetTickCount64() < inventory_deadline && target->Connected()) {
        auto m = target->ReceiveMessage(nullptr);
        if (m.type == TargetControlMessageType::NewCapture) {
            if (!trigger) { show_capture(m.newCapture, "available_capture"); return; }
            known.insert(capture_key(m.newCapture));
            last_inventory_message = GetTickCount64();
            show_capture(m.newCapture, "existing_capture");
        }
        if (GetTickCount64() - last_inventory_message >= inventory_ms) break;
    }
    if (!target->Connected()) throw std::runtime_error("Target disconnected before trigger");
    if (trigger) target->TriggerCapture(1);
    ULONGLONG until = GetTickCount64() + timeout_ms;
    while (GetTickCount64() < until && target->Connected()) {
        auto m = target->ReceiveMessage(nullptr);
        if (m.type == TargetControlMessageType::NewCapture && !known.count(capture_key(m.newCapture))) {
            show_capture(m.newCapture, "new_capture");
            return;
        }
    }
    throw std::runtime_error("No new capture received before timeout/disconnection");
}

static std::wstring wide(const char *value)
{
    int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value, -1, nullptr, 0);
    if (!size) throw std::runtime_error("Invalid UTF-8 launch argument");
    std::wstring result(size, L'\0');
    MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value, -1, result.data(), size);
    result.pop_back();
    return result;
}

static std::wstring desktop_name(HDESK desktop)
{
    wchar_t name[256] = {};
    DWORD needed = 0;
    if (!GetUserObjectInformationW(desktop, UOI_NAME, name, sizeof(name), &needed))
        throw std::runtime_error("Cannot verify desktop name");
    return name;
}

struct WindowSearch { DWORD pid; unsigned windows = 0; };
static BOOL CALLBACK count_target_window(HWND window, LPARAM param)
{
    auto *search = reinterpret_cast<WindowSearch *>(param);
    DWORD pid = 0;
    GetWindowThreadProcessId(window, &pid);
    if (pid == search->pid) ++search->windows;
    return TRUE;
}

static void launch_xemu(const char *app, const char *cwd, const char *command,
                        const char *prefix, const char *desktop)
{
    std::string desktop_arg(desktop), app_arg(app);
    if (desktop_arg.rfind("DAHRenderdoc_", 0) != 0 || desktop_arg.size() > 80 ||
        desktop_arg.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-") != std::string::npos)
        throw std::runtime_error("Launch requires a unique DAHRenderdoc_ desktop name");
    size_t slash = app_arg.find_last_of("/\\");
    if (_stricmp(app_arg.substr(slash == std::string::npos ? 0 : slash + 1).c_str(), "xemu.exe"))
        throw std::runtime_error("Launch mode accepts only an explicitly provided xemu.exe");
    if (std::string(command).find("-snapshot") == std::string::npos ||
        std::string(command).find("-config_path") == std::string::npos)
        throw std::runtime_error("Launch requires isolated config and snapshot arguments");
    auto name = wide(desktop), application = wide(app), working = wide(cwd);
    HDESK input = OpenInputDesktop(0, FALSE, DESKTOP_READOBJECTS);
    if (!input) throw std::runtime_error("Cannot verify the input desktop; refusing launch");
    bool is_input = false;
    try { is_input = !_wcsicmp(desktop_name(input).c_str(), name.c_str()); }
    catch (...) { CloseDesktop(input); throw; }
    CloseDesktop(input);
    if (is_input) throw std::runtime_error("Refusing to launch on the input desktop");
    HDESK prior = OpenDesktopW(name.c_str(), 0, FALSE, DESKTOP_READOBJECTS);
    if (prior) { CloseDesktop(prior); throw std::runtime_error("Desktop already exists; choose a new run name"); }
    if (GetLastError() != ERROR_FILE_NOT_FOUND)
        throw std::runtime_error("Cannot establish that the requested desktop name is unused");
    HDESK hidden = CreateDesktopW(name.c_str(), nullptr, nullptr, 0, GENERIC_ALL, nullptr);
    if (!hidden) throw std::runtime_error("Cannot create inactive desktop");
    PROCESS_INFORMATION process = {};
    HANDLE setup_job = nullptr;
    HANDLE output = INVALID_HANDLE_VALUE, error = INVALID_HANDLE_VALUE, nullin = INVALID_HANDLE_VALUE;
    bool child_ready = false;
    try {
        // A timed-out launcher must not leave a suspended orphan. Release this
        // kill-on-close guard only once our new child has passed verification.
        setup_job = CreateJobObjectW(nullptr, nullptr);
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits = {};
        limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        if (!setup_job || !SetInformationJobObject(setup_job, JobObjectExtendedLimitInformation,
                &limits, sizeof(limits)))
            throw std::runtime_error("Cannot create child setup job");
        SECURITY_ATTRIBUTES inherited = {sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE};
        output = CreateFileW((working + L"\\xemu.stdout.log").c_str(), GENERIC_WRITE, FILE_SHARE_READ,
            &inherited, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
        error = CreateFileW((working + L"\\xemu.stderr.log").c_str(), GENERIC_WRITE, FILE_SHARE_READ,
            &inherited, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
        nullin = CreateFileW(L"NUL", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
            &inherited, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (output == INVALID_HANDLE_VALUE || error == INVALID_HANDLE_VALUE || nullin == INVALID_HANDLE_VALUE)
            throw std::runtime_error("Cannot exclusively create child log handles");
        STARTUPINFOW startup = {};
        startup.cb = sizeof(startup);
        startup.lpDesktop = name.data();
        startup.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW | STARTF_FORCEOFFFEEDBACK;
        startup.wShowWindow = SW_SHOWNOACTIVATE;
        startup.hStdOutput = output; startup.hStdError = error; startup.hStdInput = nullin;
        std::wstring arguments = L"\"" + application + L"\" " + wide(command);
        if (!CreateProcessW(application.c_str(), arguments.data(), nullptr, nullptr, TRUE,
                CREATE_SUSPENDED | CREATE_NO_WINDOW | BELOW_NORMAL_PRIORITY_CLASS,
                nullptr, working.c_str(), &startup, &process))
            throw std::runtime_error("Cannot create suspended xemu on inactive desktop");
        if (!AssignProcessToJobObject(setup_job, process.hProcess))
            throw std::runtime_error("Cannot guard newly created child during startup");
        std::printf("{\"kind\":\"child_created_suspended\",\"pid\":%lu,\"desktop\":%s}\n",
            process.dwProcessId, json(desktop).c_str()); std::fflush(stdout);
        CaptureOptions options = {};
        RENDERDOC_GetDefaultCaptureOptions(&options);
        options.allowFullscreen = false;
        options.hookIntoChildren = false;
        // Equivalent to ExecuteAndInject's suspended startup injection, with
        // an explicit desktop that its internal CreateProcess does not supply.
        auto injected = RENDERDOC_InjectIntoProcess(process.dwProcessId, {}, prefix, options, false);
        check(injected.result);
        if (!injected.ident) throw std::runtime_error("Startup injection returned no target ident");
        Handle<ITargetControl> target{RENDERDOC_CreateTargetControl("localhost", injected.ident,
                                                                   "DAH isolated startup", false)};
        if (!target.value || !target->Connected() || target->GetPID() != process.dwProcessId)
            throw std::runtime_error("Fresh target PID/ident could not be verified");
        if (ResumeThread(process.hThread) == DWORD(-1)) throw std::runtime_error("Cannot resume newly injected child");
        WindowSearch windows{process.dwProcessId};
        auto until = GetTickCount64() + 15000;
        while (GetTickCount64() < until && target->Connected()) {
            windows.windows = 0;
            if (!EnumDesktopWindows(hidden, count_target_window, reinterpret_cast<LPARAM>(&windows)))
                throw std::runtime_error("Cannot verify child's desktop windows");
            if (windows.windows && !target->GetAPI().empty()) break;
            target->ReceiveMessage(nullptr);
            Sleep(20);
        }
        if (!windows.windows) throw std::runtime_error("No new xemu window found on requested desktop");
        limits.BasicLimitInformation.LimitFlags = 0;
        if (!SetInformationJobObject(setup_job, JobObjectExtendedLimitInformation, &limits, sizeof(limits)))
            throw std::runtime_error("Cannot release child setup job");
        child_ready = true;
        std::printf("{\"kind\":\"launched\",\"pid\":%lu,\"ident\":%u,\"api\":%s,"
            "\"desktop\":%s,\"windowsOnExpectedDesktop\":%u,\"snapshot\":true,"
            "\"priority\":\"below-normal\",\"capturePrefix\":%s}\n",
            process.dwProcessId, injected.ident, json(target->GetAPI().c_str()).c_str(),
            json(desktop).c_str(), windows.windows, json(prefix).c_str()); std::fflush(stdout);
    } catch (...) {
        // This handle was obtained only from our CreateProcess call. Never
        // accept an external PID here or terminate a pre-existing emulator.
        if (process.hProcess && !child_ready) TerminateProcess(process.hProcess, 10);
        if (process.hThread) CloseHandle(process.hThread);
        if (process.hProcess) CloseHandle(process.hProcess);
        if (output != INVALID_HANDLE_VALUE) CloseHandle(output);
        if (error != INVALID_HANDLE_VALUE) CloseHandle(error);
        if (nullin != INVALID_HANDLE_VALUE) CloseHandle(nullin);
        if (setup_job) CloseHandle(setup_job);
        CloseDesktop(hidden);
        throw;
    }
    CloseHandle(process.hThread); CloseHandle(process.hProcess);
    CloseHandle(output); CloseHandle(error); CloseHandle(nullin);
    CloseHandle(setup_job);
    CloseDesktop(hidden);
}

static void actions(IReplayController *controller, const rdcarray<ActionDescription> &items,
                    unsigned depth = 0)
{
    if (depth > 128) throw std::runtime_error("Action tree exceeds depth limit");
    for (const auto &a : items) {
        auto name = a.GetName(controller->GetStructuredFile());
        std::printf("{\"kind\":\"action\",\"event\":%u,\"depth\":%u,\"name\":%s,"
            "\"flags\":%u,\"numIndices\":%u,\"numInstances\":%u,\"vertexOffset\":%u,"
            "\"indexOffset\":%u,\"baseVertex\":%d,"
            "\"outputs\":[", a.eventId, depth,
            json(name.c_str()).c_str(), unsigned(a.flags), a.numIndices, a.numInstances,
            a.vertexOffset, a.indexOffset, a.baseVertex);
        for (size_t i = 0; i < a.outputs.size(); ++i)
            std::printf("%s%s", i ? "," : "", json(token(controller, a.outputs[i]).c_str()).c_str());
        std::printf("],\"copyDestination\":%s}\n", json(token(controller, a.copyDestination).c_str()).c_str());
        actions(controller, a.children, depth + 1);
    }
}

static bool event_exists(const rdcarray<ActionDescription> &items, uint32_t event, unsigned depth = 0)
{
    if (depth > 128) return false;
    for (const auto &a : items)
        if (a.eventId == event || event_exists(a.children, event, depth + 1)) return true;
    return false;
}

static const ActionDescription *find_action(const rdcarray<ActionDescription> &items,uint32_t event,unsigned depth=0)
{
    if(depth>128)return nullptr;
    for(const auto &a:items){if(a.eventId==event)return &a;if(const auto *found=find_action(a.children,event,depth+1))return found;}
    return nullptr;
}

static void offline(const char *path, uint32_t event, const char *resource, const char *output)
{
    Handle<ICaptureFile> file{RENDERDOC_OpenCaptureFile()};
    if (!file.value) throw std::runtime_error("OpenCaptureFile returned null");
    check(file->OpenFile(path, "", nullptr));
    if (file->LocalReplaySupport() != ReplaySupport::Supported)
        throw std::runtime_error("Capture does not support local replay");
    auto opened = file->OpenCapture(ReplayOptions(), nullptr);
    check(opened.first);
    Handle<IReplayController> controller{opened.second};
    if (!controller.value) throw std::runtime_error("OpenCapture returned null");
    auto info = controller->GetFrameInfo();
    std::printf("{\"kind\":\"frame\",\"hostFrame\":%u}\n", info.frameNumber);
    if (!output) {
        actions(controller.value, controller->GetRootActions());
        for (const auto &t : controller->GetTextures())
            std::printf("{\"kind\":\"texture\",\"resource\":%s,\"width\":%u,\"height\":%u,"
                "\"depth\":%u,\"mips\":%u,\"samples\":%u,\"format\":%s}\n",
                json(token(controller.value, t.resourceId).c_str()).c_str(), t.width, t.height, t.depth, t.mips,
                t.msSamp, json(t.format.Name().c_str()).c_str());
        return;
    }
    if (!event_exists(controller->GetRootActions(), event)) throw std::runtime_error("Unknown action event");
    if (GetFileAttributesA(output) != INVALID_FILE_ATTRIBUTES) throw std::runtime_error("Output already exists");
    ResourceId selected;
    for (const auto &t : controller->GetTextures())
        if (token(controller.value, t.resourceId) == resource) { selected = t.resourceId; break; }
    if (selected == ResourceId::Null()) throw std::runtime_error("Unknown texture resource token");
    controller->SetFrameEvent(event, true);
    TextureSave save;
    save.resourceId = selected;
    save.destType = FileType::PNG;
    save.mip = 0;
    save.slice.sliceIndex = 0;
    save.alpha = AlphaMapping::Preserve;
    check(controller->SaveTexture(save, output));
    std::printf("{\"kind\":\"export\",\"event\":%u,\"resource\":%s,\"path\":%s}\n",
        event, json(resource).c_str(), json(output).c_str());
}

static void export_series(const char *path, const char *resource,
                          const char *prefix, int count, char **events)
{
    if (count < 1 || count > 512) throw std::runtime_error("Export series requires 1..512 events");
    Handle<ICaptureFile> file{RENDERDOC_OpenCaptureFile()};
    if (!file.value) throw std::runtime_error("OpenCaptureFile returned null");
    check(file->OpenFile(path, "", nullptr));
    if (file->LocalReplaySupport() != ReplaySupport::Supported)
        throw std::runtime_error("Capture does not support local replay");
    auto opened = file->OpenCapture(ReplayOptions(), nullptr); check(opened.first);
    Handle<IReplayController> controller{opened.second};
    if (!controller.value) throw std::runtime_error("OpenCapture returned null");
    ResourceId selected;
    for (const auto &t : controller->GetTextures())
        if (token(controller.value, t.resourceId) == resource) { selected = t.resourceId; break; }
    if (selected == ResourceId::Null()) throw std::runtime_error("Unknown texture resource token");
    TextureSave save; save.resourceId = selected; save.destType = FileType::PNG;
    save.mip = 0; save.slice.sliceIndex = 0; save.alpha = AlphaMapping::Preserve;
    for (int i = 0; i < count; ++i) {
        uint32_t event = number(events[i], UINT32_MAX);
        if (!event_exists(controller->GetRootActions(), event)) throw std::runtime_error("Unknown action event");
        std::string output = std::string(prefix) + "-" + std::to_string(event) + ".png";
        if (GetFileAttributesA(output.c_str()) != INVALID_FILE_ATTRIBUTES)
            throw std::runtime_error("Series output already exists");
        controller->SetFrameEvent(event, true); check(controller->SaveTexture(save, output.c_str()));
        std::printf("{\"kind\":\"export\",\"event\":%u,\"resource\":%s,\"path\":%s}\n",
            event, json(resource).c_str(), json(output.c_str()).c_str()); std::fflush(stdout);
    }
}

// Offline IA bytes, not post-VS positions or visible-fragment evidence. Match
// the proven OutputVertex/FVFUP prefix only after validating actual IA inputs.
static std::string buffer_token(IReplayController *c,ResourceId id)
{
    const auto &buffers=c->GetBuffers();
    for(size_t i=0;i<buffers.size();++i)if(buffers[i].resourceId==id)return "buffer:"+std::to_string(i);
    return "none";
}
static std::string hex_bytes(const byte *p,size_t size)
{
    static const char digits[]="0123456789abcdef";std::string out;out.reserve(size*2);
    for(size_t i=0;i<size;++i){out+=digits[p[i]>>4];out+=digits[p[i]&15];}return out;
}
static uint32_t vertex_word(const byte *p){uint32_t value;std::memcpy(&value,p,4);return value;}
static float vertex_float(const byte *p){float value;std::memcpy(&value,p,4);return value;}
static void json_float(float value){if(std::isfinite(value))std::printf("%.9g",double(value));else std::printf("null");}
static bool vertex_attribute(const VertexInputAttribute &a,const char *name,const char *alternate,
                             uint32_t offset,unsigned count,unsigned width,CompType type)
{
    return (!std::strcmp(a.name.c_str(),name)||!std::strcmp(a.name.c_str(),alternate))&&
        a.vertexBuffer==0&&!a.perInstance&&!a.genericEnabled&&a.byteOffset==offset&&
        a.format.type==ResourceFormatType::Regular&&a.format.compCount==count&&
        a.format.compByteWidth==width&&a.format.compType==type&&!a.format.BGRAOrder();
}
// PipeState's cross-API convenience methods are not exported from the pinned
// Windows DLL. Use its public virtual D3D11 state API and exact documented IA
// fields instead; no private ResourceId or pipeline-object layout is guessed.
static std::vector<BoundVBuffer> d3d11_vbuffers(const D3D11Pipe::State &state)
{
    std::vector<BoundVBuffer> result;
    for(const auto &raw:state.inputAssembly.vertexBuffers){BoundVBuffer b;
        b.resourceId=raw.resourceId;b.byteOffset=raw.byteOffset;b.byteStride=raw.byteStride;b.byteSize=0xffffffffu;
        result.push_back(b);
    }return result;
}
static std::vector<VertexInputAttribute> d3d11_vertex_inputs(const D3D11Pipe::State &state)
{
    std::vector<VertexInputAttribute> result;
    for(const auto &raw:state.inputAssembly.layouts){VertexInputAttribute v={};
        auto name=std::string(raw.semanticName.c_str())+std::to_string(raw.semanticIndex);v.name=name.c_str();
        v.vertexBuffer=int(raw.inputSlot);v.byteOffset=raw.byteOffset;v.perInstance=raw.perInstance;
        v.instanceRate=int(raw.instanceDataStepRate);v.format=raw.format;v.used=false;
        if(state.vertexShader.reflection)for(const auto &sig:state.vertexShader.reflection->inputSignature)
            if(!_stricmp(sig.semanticName.c_str(),raw.semanticName.c_str())&&sig.semanticIndex==raw.semanticIndex)v.used=sig.channelUsedMask!=0;
        result.push_back(v);
    }return result;
}
static void native_vertex_draw(IReplayController *c,const ActionDescription &a,unsigned ordinal)
{
    c->SetFrameEvent(a.eventId,true);
    const auto *pipeline=c->GetD3D11PipelineState();if(!pipeline)throw std::runtime_error("D3D11 pipeline state unavailable");
    auto buffers=d3d11_vbuffers(*pipeline);auto inputs=d3d11_vertex_inputs(*pipeline);
    if(buffers.size()>32||inputs.size()>64)throw std::runtime_error("IA metadata exceeds inspection limit");
    bool pos=false,color=false,uv=false,uv1=false,uv2=false,uv3=false;
    for(const auto &v:inputs){
        pos|=vertex_attribute(v,"POSITION","POSITION0",0,4,4,CompType::Float);
        color|=vertex_attribute(v,"COLOR","COLOR0",16,4,1,CompType::UNorm);
        uv|=vertex_attribute(v,"TEXCOORD","TEXCOORD0",20,2,4,CompType::Float);
        uv1|=vertex_attribute(v,"TEXCOORD1","TEXCOORD1",28,2,4,CompType::Float);
        uv2|=vertex_attribute(v,"TEXCOORD2","TEXCOORD2",36,2,4,CompType::Float);
        uv3|=vertex_attribute(v,"TEXCOORD3","TEXCOORD3",44,2,4,CompType::Float);
    }
    bool indexed=(uint32_t(a.flags)&uint32_t(ActionFlags::Indexed))!=0;
    std::printf("{\"kind\":\"native_vertices\",\"event\":%u,\"drawOrdinal\":%u,\"numIndices\":%u,"
        "\"numInstances\":%u,\"indexed\":%s,\"vertexOffset\":%u,\"indexOffset\":%u,\"baseVertex\":%d,\"outputs\":[",
        a.eventId,ordinal,a.numIndices,a.numInstances,indexed?"true":"false",a.vertexOffset,a.indexOffset,a.baseVertex);
    for(size_t i=0;i<a.outputs.size();++i)std::printf("%s%s",i?",":"",json(token(c,a.outputs[i]).c_str()).c_str());
    const auto &blend_state=pipeline->outputMerger.blendState;
    const ColorBlend *blend=blend_state.blends.empty()?nullptr:&blend_state.blends[0];
    const auto &accesses=c->GetDescriptorAccess();
    const auto &depth_stencil=pipeline->outputMerger.depthStencilState;
    const auto &stencil_front=depth_stencil.frontFace;
    std::printf("],\"pipeline\":{\"pixelShaderEntry\":%s,\"descriptorAccesses\":%zu,"
        "\"depthEnable\":%s,\"depthWrites\":%s,\"stencilEnable\":%s,"
        "\"stencilFunction\":%u,\"stencilReference\":%u,\"stencilCompareMask\":%u,"
        "\"stencilWriteMask\":%u,\"stencilFail\":%u,\"stencilDepthFail\":%u,\"stencilPass\":%u,"
        "\"blendEnabled\":%s,\"writeMask\":%u,"
        "\"colorBlend\":[%u,%u,%u],\"alphaBlend\":[%u,%u,%u]}",
        pipeline->pixelShader.reflection?json(pipeline->pixelShader.reflection->entryPoint.c_str()).c_str():"null",
        accesses.size(),
        pipeline->outputMerger.depthStencilState.depthEnable?"true":"false",
        pipeline->outputMerger.depthStencilState.depthWrites?"true":"false",
        depth_stencil.stencilEnable?"true":"false",unsigned(stencil_front.function),
        stencil_front.reference,stencil_front.compareMask,stencil_front.writeMask,
        unsigned(stencil_front.failOperation),unsigned(stencil_front.depthFailOperation),
        unsigned(stencil_front.passOperation),
        blend&&blend->enabled?"true":"false",blend?unsigned(blend->writeMask):0u,
        blend?unsigned(blend->colorBlend.source):0u,blend?unsigned(blend->colorBlend.destination):0u,
        blend?unsigned(blend->colorBlend.operation):0u,
        blend?unsigned(blend->alphaBlend.source):0u,blend?unsigned(blend->alphaBlend.destination):0u,
        blend?unsigned(blend->alphaBlend.operation):0u);
    std::printf(",\"descriptorBindings\":[");
    for(size_t i=0;i<accesses.size();++i){
        const auto &access=accesses[i];rdcarray<DescriptorRange> ranges;
        ranges.push_back(DescriptorRange(access));
        auto descriptors=c->GetDescriptors(access.descriptorStore,ranges);
        const Descriptor *descriptor=descriptors.empty()?nullptr:&descriptors[0];
        std::printf("%s{\"stage\":%u,\"type\":%u,\"index\":%u,\"arrayElement\":%u,"
            "\"staticallyUnused\":%s,\"resource\":%s,\"secondary\":%s,\"format\":%s,"
            "\"byteOffset\":%llu,\"byteSize\":%llu,\"rawDataHex\":",
            i?",":"",unsigned(access.stage),unsigned(access.type),unsigned(access.index),
            access.arrayElement,access.staticallyUnused?"true":"false",
            json(descriptor?token(c,descriptor->resource).c_str():"none").c_str(),
            json(descriptor?token(c,descriptor->secondary).c_str():"none").c_str(),
            descriptor?json(descriptor->format.Name().c_str()).c_str():"null",
            descriptor?(unsigned long long)descriptor->byteOffset:0ull,
            descriptor?(unsigned long long)descriptor->byteSize:0ull);
        if(descriptor&&descriptor->type==DescriptorType::ConstantBuffer&&
           descriptor->resource!=ResourceId::Null()){
            /* Vertex programs use 192 float4 constants (3072 bytes). Keep the
             * complete block so native/xemu UV and animation constants can be
             * compared offline without another instrumented game run. */
            uint64_t length=std::min<uint64_t>(descriptor->byteSize,4096u);
            bytebuf raw=c->GetBufferData(descriptor->resource,descriptor->byteOffset,length);
            std::printf("%s",json(hex_bytes(raw.data(),raw.size()).c_str()).c_str());
        }else std::printf("null");
        std::printf("}");
    }
    std::printf("],\"bindings\":[");
    for(size_t i=0;i<buffers.size();++i){const auto &b=buffers[i];
        std::printf("%s{\"slot\":%zu,\"resource\":%s,\"stride\":%u,\"offset\":%llu,\"size\":%llu}",
            i?",":"",i,json(buffer_token(c,b.resourceId).c_str()).c_str(),b.byteStride,
            (unsigned long long)b.byteOffset,(unsigned long long)b.byteSize);
    }
    std::printf("],\"inputs\":[");
    for(size_t i=0;i<inputs.size();++i){const auto &v=inputs[i];
        std::printf("%s{\"name\":%s,\"slot\":%d,\"offset\":%u,\"format\":%s,\"used\":%s,\"perInstance\":%s,\"generic\":%s}",
            i?",":"",json(v.name.c_str()).c_str(),v.vertexBuffer,v.byteOffset,json(v.format.Name().c_str()).c_str(),
            v.used?"true":"false",v.perInstance?"true":"false",v.genericEnabled?"true":"false");
    }
    // PostVertex in nv2a_pgraph_d3d11.c has the same prefix plus four float2
    // UV sets (52 bytes). Validate all four inputs before accepting that form.
    bool schema=!buffers.empty()&&(buffers[0].byteStride==28||buffers[0].byteStride==48||
        (buffers[0].byteStride==52&&uv1&&uv2&&uv3))&&pos&&color&&uv;
    std::printf("],\"schema\":%s",schema?"\"native-xyzrhw-bgra-uv-prefix\"":"null");
    std::string reason;bytebuf data;std::vector<uint32_t> indices;uint64_t start=0;uint32_t minimum=0;
    uint32_t sample_count=std::min(a.numIndices,a.numIndices<=512?512u:4u);
    if(buffers.empty()||buffers[0].resourceId==ResourceId::Null())reason="primary vertex buffer unavailable";
    else if(!buffers[0].byteStride||buffers[0].byteStride>256)reason="primary stride outside 1..256 byte bound";
    else if(!sample_count)reason="draw has no vertices";
    else{
        if(indexed){
            auto ib=pipeline->inputAssembly.indexBuffer;
            if(ib.resourceId==ResourceId::Null()||(ib.byteStride!=2&&ib.byteStride!=4))reason="unsupported index binding";
            else if(ib.byteOffset>UINT64_MAX-uint64_t(a.indexOffset)*ib.byteStride)reason="index offset overflow";
            else{
                auto raw=c->GetBufferData(ib.resourceId,ib.byteOffset+uint64_t(a.indexOffset)*ib.byteStride,uint64_t(sample_count)*ib.byteStride);
                if(raw.size()!=size_t(sample_count)*ib.byteStride)reason="short index read";
                else for(unsigned i=0;i<sample_count;++i){
                    uint32_t v=0;std::memcpy(&v,raw.data()+size_t(i)*ib.byteStride,ib.byteStride);
                    int64_t final=int64_t(v)+a.baseVertex;
                    if(final<0||final>UINT32_MAX){reason="index plus baseVertex outside uint32";break;}
                    indices.push_back(uint32_t(final));
                }
            }
        }else if(uint64_t(a.vertexOffset)+sample_count>uint64_t(UINT32_MAX)+1)reason="vertex offset overflow";
        else for(unsigned i=0;i<sample_count;++i)indices.push_back(a.vertexOffset+i);
        if(reason.empty()){
            minimum=*std::min_element(indices.begin(),indices.end());uint32_t maximum=*std::max_element(indices.begin(),indices.end());
            const auto &b=buffers[0];uint64_t offset=uint64_t(minimum)*b.byteStride;
            uint64_t length=(uint64_t(maximum)-minimum+1)*b.byteStride;
            if(length>65536)reason="vertex span exceeds 65536 byte bound";
            else if(b.byteOffset>UINT64_MAX-offset||b.byteOffset+offset>UINT64_MAX-length)reason="vertex byte offset overflow";
            else{
                start=b.byteOffset+offset;data=c->GetBufferData(b.resourceId,start,length);
                if(data.size()!=length)reason="short vertex read";
            }
        }
    }
    std::printf(",\"readOffset\":%llu,\"readBytes\":%zu,\"sampledVertices\":%zu,\"rawPrefixHex\":%s",
        (unsigned long long)start,data.size(),indices.size(),json(hex_bytes(data.data(),std::min(size_t(64),data.size())).c_str()).c_str());
    std::printf(",\"rawVerticesHex\":[");
    if(reason.empty())for(size_t i=0;i<std::min(size_t(4),indices.size());++i){
        const byte *p=data.data()+size_t(indices[i]-minimum)*buffers[0].byteStride;
        std::printf("%s%s",i?",":"",json(hex_bytes(p,buffers[0].byteStride).c_str()).c_str());
    }
    std::printf("]");
    std::printf(",\"vertices\":[");
    float xmin=0,ymin=0,xmax=0,ymax=0;unsigned cmin[4]={255,255,255,255},cmax[4]={0,0,0,0};
    bool finite=true,bounds=false;
    if(schema&&reason.empty())for(size_t i=0;i<indices.size();++i){
        const byte *p=data.data()+size_t(indices[i]-minimum)*buffers[0].byteStride;
        float x=vertex_float(p),y=vertex_float(p+4);finite&=std::isfinite(x)&&std::isfinite(y);
        if(std::isfinite(x)&&std::isfinite(y)){
            if(!bounds){xmin=xmax=x;ymin=ymax=y;bounds=true;}
            else{xmin=std::min(xmin,x);xmax=std::max(xmax,x);ymin=std::min(ymin,y);ymax=std::max(ymax,y);}
        }
        for(unsigned k=0;k<4;++k){cmin[k]=std::min(cmin[k],unsigned(p[16+k]));cmax[k]=std::max(cmax[k],unsigned(p[16+k]));}
        if(i<4){
            std::printf("%s{\"index\":%u,\"xyzrhw\":[",i?",":"",indices[i]);
            for(unsigned k=0;k<4;++k){if(k)std::printf(",");json_float(vertex_float(p+4*k));}
            std::printf("],\"xyzrhwBits\":[%u,%u,%u,%u],\"bgra\":[%u,%u,%u,%u],\"colorWord\":%u,\"uv\":[",
                vertex_word(p),vertex_word(p+4),vertex_word(p+8),vertex_word(p+12),p[16],p[17],p[18],p[19],vertex_word(p+16));
            json_float(vertex_float(p+20));std::printf(",");json_float(vertex_float(p+24));
            std::printf("],\"uvBits\":[%u,%u]}",vertex_word(p+20),vertex_word(p+24));
        }
    }
    bool full_bounds=bounds&&finite&&a.numIndices<=512&&indices.size()==a.numIndices&&reason.empty();
    std::printf("],\"boundsComplete\":%s,\"xyBounds\":",full_bounds?"true":"false");
    if(full_bounds){std::printf("[");json_float(xmin);std::printf(",");json_float(ymin);std::printf(",");json_float(xmax);std::printf(",");json_float(ymax);std::printf("]");}
    else std::printf("null");
    std::printf(",\"bgraRange\":");
    if(full_bounds)std::printf("[[%u,%u],[%u,%u],[%u,%u],[%u,%u]]",cmin[0],cmax[0],cmin[1],cmax[1],cmin[2],cmax[2],cmin[3],cmax[3]);
    else std::printf("null");
    bool hud_candidate=full_bounds&&xmin>=420&&xmax<=545&&ymin>=55&&ymax<=80&&cmax[2]>150&&cmax[3]>100;
    std::printf(",\"farmHudBarCandidate\":%s,\"reason\":%s}\n",hud_candidate?"true":"false",reason.empty()?"null":json(reason.c_str()).c_str());
    std::fflush(stdout);
}
static void native_vertex_actions(IReplayController *c,const rdcarray<ActionDescription> &items,
                                 uint32_t first,uint32_t last,unsigned &visited,unsigned &draws,unsigned depth=0)
{
    if(depth>128)throw std::runtime_error("Action tree exceeds depth limit");
    for(const auto &a:items){
        if(++visited>65536)throw std::runtime_error("Action tree exceeds 65536 item limit");
        if(a.eventId>=first&&a.eventId<=last&&(uint32_t(a.flags)&uint32_t(ActionFlags::Drawcall))){
            if(draws==4096)throw std::runtime_error("Inspection exceeds 4096 draw limit");
            native_vertex_draw(c,a,++draws);
        }
        native_vertex_actions(c,a.children,first,last,visited,draws,depth+1);
    }
}
static void inspect_native_vertices(const char *path,uint32_t first,uint32_t last)
{
    if(first>last)throw std::runtime_error("First event exceeds last event");
    Handle<ICaptureFile> file{RENDERDOC_OpenCaptureFile()};if(!file.value)throw std::runtime_error("OpenCaptureFile returned null");
    check(file->OpenFile(path,"",nullptr));
    if(file->LocalReplaySupport()!=ReplaySupport::Supported)throw std::runtime_error("Capture does not support local replay");
    auto opened=file->OpenCapture(ReplayOptions(),nullptr);check(opened.first);
    Handle<IReplayController> controller{opened.second};if(!controller.value)throw std::runtime_error("OpenCapture returned null");
    if(controller->GetAPIProperties().pipelineType!=GraphicsAPI::D3D11)throw std::runtime_error("Native vertex inspection requires a D3D11 capture");
    std::printf("{\"kind\":\"native_vertex_inspection\",\"firstEvent\":%u,\"lastEvent\":%u,\"drawLimit\":4096,\"boundsVertexLimit\":512,\"vertexSpanByteLimit\":65536,\"offline\":true}\n",first,last);
    unsigned visited=0,draws=0;native_vertex_actions(controller.value,controller->GetRootActions(),first,last,visited,draws);
    std::printf("{\"kind\":\"native_vertex_summary\",\"visitedActions\":%u,\"inspectedDraws\":%u,\"complete\":true}\n",visited,draws);
}

static void inspect_gl_shaders(const char *path,uint32_t event)
{
    Handle<ICaptureFile> file{RENDERDOC_OpenCaptureFile()};if(!file.value)throw std::runtime_error("OpenCaptureFile returned null");
    check(file->OpenFile(path,"",nullptr));
    if(file->LocalReplaySupport()!=ReplaySupport::Supported)throw std::runtime_error("Capture does not support local replay");
    auto opened=file->OpenCapture(ReplayOptions(),nullptr);check(opened.first);
    Handle<IReplayController> controller{opened.second};if(!controller.value)throw std::runtime_error("OpenCapture returned null");
    if(controller->GetAPIProperties().pipelineType!=GraphicsAPI::OpenGL)throw std::runtime_error("GL shader inspection requires an OpenGL capture");
    if(!event_exists(controller->GetRootActions(),event))throw std::runtime_error("Unknown action event");
    controller->SetFrameEvent(event,true);
    const auto *pipeline=controller->GetGLPipelineState();if(!pipeline)throw std::runtime_error("OpenGL pipeline state unavailable");
    const auto &depth=pipeline->depthState;
    const auto &stencil=pipeline->stencilState;
    const auto &sf=stencil.frontFace;
    const auto &sb=stencil.backFace;
    std::printf("{\"kind\":\"gl_depth_stencil\",\"event\":%u,\"depthEnable\":%s,\"depthWrites\":%s,\"depthFunction\":%u,"
        "\"stencilEnable\":%s,\"front\":{\"function\":%u,\"reference\":%u,\"compareMask\":%u,\"writeMask\":%u,"
        "\"fail\":%u,\"depthFail\":%u,\"pass\":%u},\"back\":{\"function\":%u,\"reference\":%u,"
        "\"compareMask\":%u,\"writeMask\":%u,\"fail\":%u,\"depthFail\":%u,\"pass\":%u}}\n",
        event,depth.depthEnable?"true":"false",depth.depthWrites?"true":"false",unsigned(depth.depthFunction),
        stencil.stencilEnable?"true":"false",unsigned(sf.function),sf.reference,sf.compareMask,sf.writeMask,
        unsigned(sf.failOperation),unsigned(sf.depthFailOperation),unsigned(sf.passOperation),
        unsigned(sb.function),sb.reference,sb.compareMask,sb.writeMask,unsigned(sb.failOperation),
        unsigned(sb.depthFailOperation),unsigned(sb.passOperation));
    const GLPipe::Shader *stages[]={&pipeline->vertexShader,&pipeline->fragmentShader};
    const char *names[]={"vertex","fragment"};
    for(unsigned i=0;i<2u;++i){
        const auto *stage=stages[i];
        std::printf("{\"kind\":\"gl_shader\",\"event\":%u,\"stage\":%s,\"entry\":%s,\"encoding\":%u,\"files\":[",
            event,json(names[i]).c_str(),stage->reflection?json(stage->reflection->entryPoint.c_str()).c_str():"null",
            stage->reflection?unsigned(stage->reflection->encoding):0u);
        if(stage->reflection)for(size_t j=0;j<stage->reflection->debugInfo.files.size();++j){
            const auto &source=stage->reflection->debugInfo.files[j];
            std::printf("%s{\"name\":%s,\"contents\":%s}",j?",":"",json(source.filename.c_str()).c_str(),json(source.contents.c_str()).c_str());
        }
        std::printf("],\"disassembly\":%s}\n",stage->reflection?
            json(controller->DisassembleShader(stage->programResourceId,stage->reflection,"").c_str()).c_str():"null");
    }
    const auto &accesses=controller->GetDescriptorAccess();
    for(const auto &access:accesses){
        rdcarray<DescriptorRange> ranges;ranges.push_back(DescriptorRange(access));
        auto descriptors=controller->GetDescriptors(access.descriptorStore,ranges);
        auto samplers=controller->GetSamplerDescriptors(access.descriptorStore,ranges);
        const Descriptor *descriptor=descriptors.empty()?nullptr:&descriptors[0];
        const SamplerDescriptor *sampler=samplers.empty()?nullptr:&samplers[0];
        std::printf("{\"kind\":\"gl_descriptor\",\"event\":%u,\"stage\":%u,\"type\":%u,\"index\":%u,"
            "\"resource\":%s,\"secondary\":%s,\"sampler\":%s}",event,unsigned(access.stage),unsigned(access.type),
            unsigned(access.index),json(descriptor?token(controller.value,descriptor->resource).c_str():"none").c_str(),
            json(descriptor?token(controller.value,descriptor->secondary).c_str():"none").c_str(),sampler?"true":"false");
        if(sampler)std::printf(" address=%u,%u,%u unnormalized=%s lod=%g..%g bias=%g",unsigned(sampler->addressU),
            unsigned(sampler->addressV),unsigned(sampler->addressW),sampler->unnormalized?"true":"false",
            double(sampler->minLOD),double(sampler->maxLOD),double(sampler->mipBias));
        std::printf("\n");
    }
}

static void inspect_gl_all_shaders(const char *path)
{
    Handle<ICaptureFile> file{RENDERDOC_OpenCaptureFile()};if(!file.value)throw std::runtime_error("OpenCaptureFile returned null");
    check(file->OpenFile(path,"",nullptr));
    if(file->LocalReplaySupport()!=ReplaySupport::Supported)throw std::runtime_error("Capture does not support local replay");
    auto opened=file->OpenCapture(ReplayOptions(),nullptr);check(opened.first);
    Handle<IReplayController> controller{opened.second};if(!controller.value)throw std::runtime_error("OpenCapture returned null");
    if(controller->GetAPIProperties().pipelineType!=GraphicsAPI::OpenGL)throw std::runtime_error("GL shader inventory requires an OpenGL capture");
    unsigned shaders=0,entries=0;
    for(const auto &resource:controller->GetResources()){
        if(resource.type!=ResourceType::Shader)continue;
        ++shaders;
        auto entrypoints=controller->GetShaderEntryPoints(resource.resourceId);
        for(const auto &entry:entrypoints){
            const ShaderReflection *reflection=controller->GetShader(ResourceId::Null(),resource.resourceId,entry);
            std::printf("{\"kind\":\"gl_shader_resource\",\"resource\":%s,\"name\":%s,\"entry\":%s,\"encoding\":%u,\"files\":[",
                json(token(controller.value,resource.resourceId).c_str()).c_str(),json(resource.name.c_str()).c_str(),
                reflection?json(reflection->entryPoint.c_str()).c_str():"null",reflection?unsigned(reflection->encoding):0u);
            if(reflection)for(size_t j=0;j<reflection->debugInfo.files.size();++j){
                const auto &source=reflection->debugInfo.files[j];
                std::printf("%s{\"name\":%s,\"contents\":%s}",j?",":"",json(source.filename.c_str()).c_str(),json(source.contents.c_str()).c_str());
            }
            std::printf("]}\n");
            ++entries;
        }
    }
    std::printf("{\"kind\":\"gl_shader_resource_summary\",\"shaders\":%u,\"entries\":%u}\n",shaders,entries);
}

static void print_shader_variable(const ShaderVariable &v,unsigned depth)
{
    if(depth>8)return;
    std::printf("{\"kind\":\"shader_variable\",\"depth\":%u,\"name\":%s,\"rows\":%u,\"columns\":%u,"
        "\"f32\":[%.9g,%.9g,%.9g,%.9g],\"u32\":[%u,%u,%u,%u],\"members\":%zu}\n",depth,
        json(v.name.c_str()).c_str(),unsigned(v.rows),unsigned(v.columns),double(v.value.f32v[0]),double(v.value.f32v[1]),
        double(v.value.f32v[2]),double(v.value.f32v[3]),v.value.u32v[0],v.value.u32v[1],v.value.u32v[2],v.value.u32v[3],v.members.size());
    for(const auto &member:v.members)print_shader_variable(member,depth+1u);
}

static void inspect_gl_vertex(const char *path,uint32_t event)
{
    Handle<ICaptureFile> file{RENDERDOC_OpenCaptureFile()};if(!file.value)throw std::runtime_error("OpenCaptureFile returned null");
    check(file->OpenFile(path,"",nullptr));auto opened=file->OpenCapture(ReplayOptions(),nullptr);check(opened.first);
    Handle<IReplayController> controller{opened.second};if(!controller.value)throw std::runtime_error("OpenCapture returned null");
    if(controller->GetAPIProperties().pipelineType!=GraphicsAPI::OpenGL)throw std::runtime_error("GL vertex inspection requires an OpenGL capture");
    const auto *action=find_action(controller->GetRootActions(),event);if(!action)throw std::runtime_error("Unknown action event");
    controller->SetFrameEvent(event,true);const auto *pipeline=controller->GetGLPipelineState();if(!pipeline)throw std::runtime_error("OpenGL pipeline state unavailable");
    uint32_t index=action->vertexOffset;
    if((uint32_t(action->flags)&uint32_t(ActionFlags::Indexed))!=0){
        const auto &vi=pipeline->vertexInput;if(vi.indexBuffer==ResourceId::Null()||(vi.indexByteStride!=1&&vi.indexByteStride!=2&&vi.indexByteStride!=4))throw std::runtime_error("Unsupported GL index binding");
        auto raw=controller->GetBufferData(vi.indexBuffer,uint64_t(action->indexOffset)*vi.indexByteStride,vi.indexByteStride);
        if(raw.size()!=vi.indexByteStride)throw std::runtime_error("Short GL index read");index=0;std::memcpy(&index,raw.data(),vi.indexByteStride);
        int64_t adjusted=int64_t(index)+action->baseVertex;if(adjusted<0||adjusted>UINT32_MAX)throw std::runtime_error("GL index plus base vertex outside uint32");index=uint32_t(adjusted);
    }
    ShaderDebugTrace *trace=controller->DebugVertex(0,0,index,0);if(!trace||!trace->debugger)throw std::runtime_error("GL vertex debugging unavailable");
    std::printf("{\"kind\":\"gl_vertex_debug\",\"event\":%u,\"numIndices\":%u,\"index\":%u,\"inputs\":%zu,\"constantBlocks\":%zu}\n",
        event,action->numIndices,index,trace->inputs.size(),trace->constantBlocks.size());
    for(const auto &v:trace->inputs)print_shader_variable(v,0);
    for(const auto &v:trace->constantBlocks)print_shader_variable(v,0);
    controller->FreeTrace(trace);
}

int main(int argc, char **argv)
{
    // No windows or graphics initialization are needed for probe/usage.
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    try {
        if (argc == 1) {
            std::puts("renderdoc_headless probe | capture IDENT PID TIMEOUT_MS [INVENTORY_MS] | listen IDENT PID TIMEOUT_MS | inspect FILE.rdc | inspect-native-vertices FILE.rdc [FIRST_EVENT [LAST_EVENT]] | inspect-gl-shaders FILE.rdc EVENT | inspect-gl-all-shaders FILE.rdc | inspect-gl-vertex FILE.rdc EVENT | export FILE.rdc EVENT RESOURCE_TOKEN OUT.png | export-series FILE.rdc RESOURCE_TOKEN OUT_PREFIX EVENT... | launch-xemu APP WORKDIR COMMANDLINE CAPTURE_PREFIX DESKTOP");
            return 0;
        }
        const char *commit = RENDERDOC_GetCommitHash();
        if (std::strcmp(commit, expected_commit)) throw std::runtime_error("Installed RenderDoc commit differs from pinned API headers");
        if (argc == 2 && !std::strcmp(argv[1], "probe")) {
            std::printf("{\"kind\":\"probe\",\"commit\":%s,\"replayInitialized\":false,\"processControlled\":false}\n", json(commit).c_str());
            return 0;
        }
        ReplayLifetime replay;
        if (argc == 7 && !std::strcmp(argv[1], "launch-xemu"))
            launch_xemu(argv[2], argv[3], argv[4], argv[5], argv[6]);
        else if ((argc == 5 || argc == 6) && !std::strcmp(argv[1], "capture"))
            capture(number(argv[2], 65535), number(argv[3], UINT32_MAX),
                number(argv[4], 60000), true,
                argc == 6 ? number(argv[5], 1000) : 1000);
        else if (argc == 5 && !std::strcmp(argv[1], "listen"))
            capture(number(argv[2], 65535), number(argv[3], UINT32_MAX), number(argv[4], 60000), false);
        else if (argc == 3 && !std::strcmp(argv[1], "inspect")) offline(argv[2], 0, nullptr, nullptr);
        else if (argc>=3&&argc<=5&&!std::strcmp(argv[1],"inspect-native-vertices"))
            inspect_native_vertices(argv[2],argc>=4?number(argv[3],UINT32_MAX):1,
                argc==5?number(argv[4],UINT32_MAX):(argc==4?number(argv[3],UINT32_MAX):UINT32_MAX));
        else if(argc==4&&!std::strcmp(argv[1],"inspect-gl-shaders"))
            inspect_gl_shaders(argv[2],number(argv[3],UINT32_MAX));
        else if(argc==3&&!std::strcmp(argv[1],"inspect-gl-all-shaders"))
            inspect_gl_all_shaders(argv[2]);
        else if(argc==4&&!std::strcmp(argv[1],"inspect-gl-vertex"))
            inspect_gl_vertex(argv[2],number(argv[3],UINT32_MAX));
        else if (argc == 6 && !std::strcmp(argv[1], "export"))
            offline(argv[2], number(argv[3], UINT32_MAX), argv[4], argv[5]);
        else if (argc >= 6 && argc <= 517 && !std::strcmp(argv[1], "export-series"))
            export_series(argv[2], argv[3], argv[4], argc - 5, argv + 5);
        else throw std::runtime_error("Invalid arguments; run without arguments for usage");
        return 0;
    } catch (const std::exception &error) {
        std::fprintf(stderr, "%s\n", error.what());
        return 1;
    }
}
