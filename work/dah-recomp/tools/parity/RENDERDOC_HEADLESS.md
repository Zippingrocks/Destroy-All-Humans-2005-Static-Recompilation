# Background RenderDoc capture and replay

The console helper builds against the exact installed RenderDoc v1.43 commit,
`286e07140d96bf3acda4059e085e8f5eb0e92608`. Public MIT-licensed headers and their
SHA-256/source URLs are under `vendor/renderdoc-v1.43/PROVENANCE.json`. The helper
loads only `C:\Program Files\RenderDoc\renderdoc.dll`, checks its commit, and
exports RenderDoc's replay-program marker. It contains no Qt or preview window.
Its isolated launch mode can inject only an xemu process that it creates
suspended itself, with an explicit inactive desktop.

Build and API-only probe were verified with the installed MSVC toolchain.
Offline replay/inspection/export were subsequently validated on the first
explicit native capture, with exact equality between its final swapchain and
presentable RGBA exports. Live target-control capture/listen remain untested.
No existing game or emulator process was connected to, injected into, or
controlled during helper implementation. The probe does not initialize replay
or enumerate GPUs. See `MENU_RENDERDOC_CHECKPOINT_20260926.md` for evidence.

Use the Python runner, which enforces `CREATE_NO_WINDOW` and a 120-second helper
timeout. Do not execute qrenderdoc for this workflow. Although `--python` scripts
can exit before its main UI, qrenderdoc creates its UI context and can show
configuration/analytics dialogs before the script runs. This installation has
no Qt offscreen platform plugin.

## Fresh isolated xemu startup

`launch_renderdoc_xemu.py` defaults to a read-only plan. Its `--start` switch
creates a fresh, paused reference; it never accepts an existing PID. Run it only
when the reference owner is ready. This mode was compiled and dry-planned;
actual xemu startup, SDL3/OpenGL capture, and paused host presentation remain
unverified until the first explicitly scheduled run.

```powershell
python tools/parity/launch_renderdoc_xemu.py --run-name farm-renderdoc-001
# The owner performs this actual start only after reviewing the plan:
python tools/parity/launch_renderdoc_xemu.py --run-name farm-renderdoc-001 --start
```

Defaults are GDB `127.0.0.1:1237` and QMP `127.0.0.1:4447`. A read-only Windows
TCP listener query verifies availability without connecting to any emulator.
The dry plan checks the exact retail XBE hash; actual startup additionally
requires the known full XISO hash. `--verify-media` includes that large read in a
dry plan. The run directory is exclusive, under
`build-parity-xemu/renderdoc-runs/<name>`. It holds copied xemu/EEPROM files,
config, logs, captures and private APPDATA/LOCALAPPDATA/TEMP/TMP. Source media
remain untouched; `-snapshot` keeps HDD writes in a temporary overlay.

The helper creates a unique `DAHRenderdoc_<name>` desktop without switching to
it, supplies that desktop through `STARTUPINFO.lpDesktop`, creates the new child
with `CREATE_SUSPENDED | CREATE_NO_WINDOW | BELOW_NORMAL_PRIORITY_CLASS`, then
injects RenderDoc before resuming its primary thread. This follows RenderDoc's
startup-injection sequence but supplies the explicit desktop that its
`ExecuteAndInject` wrapper does not expose. It verifies the new PID against
RenderDoc's target ident and checks its windows belong to that inactive
desktop. A temporary kill-on-close job guards only the new child during setup;
successful setup releases that guard so the child survives the launcher.

Host audio is muted, fullscreen is disabled, NVIDIA profile setup is disabled,
and networking is disabled. Physical controllers cannot auto-bind. Every
keyboard-controller mapping is SDL_SCANCODE_UNKNOWN (0); the neutral virtual
pad remains connected so the existing logical XInputGetState adapter works.
The frontend runs OpenGL at surface scale 1. The guest begins with `-S` and
needs the owner's existing QMP/GDB workflow to boot. No qrenderdoc is launched.

Future runs explicitly use a 640x480 host window, `aspect_ratio = '4x3'`, and
`fit = 'scale'`; these settings are also recorded in the launch plan. Earlier
Farm references 002/003/004 used forced `16x9` in a 640x480 window. xemu's
`ui/xui/gl-helpers.cc:RenderFramebuffer` therefore scaled the game vertically
to 360 pixels and cleared the remaining 60-pixel top/bottom bands. Those bands
are a host presentation artifact and must not be copied into the game renderer.
The unchanged 640x480 game display texture is the geometry comparison source;
the host texture additionally includes the DAC gamma/display pass. Equal
dimensions alone do not establish equal color-processing stages. See
`FARM_CINEMATIC_EVIDENCE_20260927.md` for capture events and timing limitations.

Review `launch-result.json` for PID, target ident, API and desktop verification.
An empty reported API means API detection remains unverified. A successful
launch is not proof of graphics capture: request one host capture only with
that recorded PID/ident, inspect its actions offline, and identify the post-DAC
gamma game output before xemu/RenderDoc overlays. Correlate it with guest PC,
loop, FIFO/scanout stability and RAM observations; never equate its RenderDoc
host frame number with a retail loop counter. Neither the launcher nor a
successful host capture proves GPU completion at a selected retail boundary.

Implementation references: xemu `config_spec.yml` for settings,
`ui/xemu-input.c:xemu_input_update_sdl_kbd_controller_state` for neutral key
mapping, and `ui/xemu.c` for SDL window creation. Windows documents the explicit
desktop assignment in [thread connection to a desktop](https://learn.microsoft.com/en-us/windows/win32/winstation/thread-connection-to-a-desktop).
The startup injection sequence is in the pinned
[RenderDoc Win32 process implementation](https://github.com/baldurk/renderdoc/blob/286e07140d96bf3acda4059e085e8f5eb0e92608/renderdoc/os/win32/win32_process.cpp).

```powershell
python tools/parity/build_renderdoc_helper.py
python tools/parity/run_renderdoc_helper.py probe
python tools/parity/run_renderdoc_helper.py inspect 'path/to/frame.rdc'
python tools/parity/run_renderdoc_helper.py export 'path/to/frame.rdc' 123 'texture:17' 'path/to/output.png'
```

`inspect` emits JSONL actions (event, output texture tokens, copy destination,
marker names) and texture metadata. `export` requires an actual action event
and a texture token from the same capture, selects that event, and saves mip 0,
slice 0 as PNG. It refuses to overwrite an existing output. Resource IDs remain
opaque: `texture:N` indexes the capture's returned texture list. No preview
output is created. PNG export preserves alpha but RenderDoc can convert complex
formats; retain the `.rdc` and format metadata when assessing exact pixels.

## Offline native vertex inspection

```powershell
python tools/parity/run_renderdoc_helper.py inspect-native-vertices 'frame.rdc'
python tools/parity/run_renderdoc_helper.py inspect-native-vertices 'frame.rdc' 13797
python tools/parity/run_renderdoc_helper.py inspect-native-vertices 'frame.rdc' 13797 13857
```

This D3D11-only command visits actual draw actions, selects each frame event,
and reads its captured input-assembler buffers. Optional event bounds are
inclusive; a single event argument inspects that event alone. It creates no
target connection, replay output window, Qt process, or game process. It is
bounded to 4,096 draws, 65,536 action nodes, depth 128, 512 sampled vertices per
small draw, and a 65,536-byte vertex span plus at most 2,048 index bytes per
draw. Larger draws report their first four input vertices without full bounds.
The existing Python runner retains its 120-second timeout.

The pinned Windows DLL does not export `PipeState::GetVBuffers`,
`GetVertexInputs`, or `GetIBuffer`. The helper therefore reads the documented
public `GetD3D11PipelineState()->inputAssembly` fields directly, including
layout semantics, formats, offsets, vertex/index bindings and shader input
signature use masks. Resource IDs stay opaque `buffer:N` tokens. Vertex and
index offsets, signed base-vertex offsets, range overflow, short reads and
unavailable bindings are handled explicitly.

XYZRHW/BGRA/UV decoding requires actual POSITION0 float4 at byte 0, COLOR0
R8G8B8A8_UNORM at byte 16, TEXCOORD0 float2 at byte 20, all in slot zero and
at vertex rate. Accepted strides are 28 bytes for the FVF prefix and 48 bytes
for `OutputVertex`. The 52-byte `PostVertex` form additionally requires float2
TEXCOORD1/2/3 at offsets 28/36/44. These structures are defined in
`third_party/xboxrecomp/src/nv2a/nv2a_pgraph_d3d11.c`; the matching input layout
and color `.bgra` shader swizzle are in `src/d3d/d3d8_shaders.c` under the same
library. Colors are reported in their actual stored BGRA byte order, with
the original packed word. Float values also retain original integer bits;
nonfinite formatted values are JSON null, never NaN or Infinity.

Each JSONL draw includes bindings, layout, output textures, action count,
read offset/span, up to four decoded vertices and their full raw hex bytes.
Unknown layouts retain bounded raw bytes with a null schema. For complete
draws of at most 512 vertices, `xyBounds` and `bgraRange` cover all referenced
input vertices. `farmHudBarCandidate` is only a search hint for a red rectangle
near (431,64)..(531,70); it is not proof of raster coverage or a final pixel.
Input data alone does not prove visibility after shaders, clipping, depth,
blending or texturing. Validate output bytes with
`python tools/parity/test_renderdoc_native_vertices.py inspection.jsonl`.

Farm016 capture validation (`parity-farm-hud-20260927-016_capture.rdc`):
470 action nodes / 458 draws inspected, all layout prefixes validated, no
short or unavailable buffer reads. The resulting
`build-parity-xemu/native-farm016-vertex-inspection-20260927-002.jsonl` contains
1,832 raw/decoded vertex pairs checked for exact bit/color agreement and 27
small draws whose full bounds were independently recomputed from raw bytes.
374 draws have full bounds; 84 large draws retain only four sample vertices.
All draws after event 13000 fit the full-bound limit. The four 52-byte draws
are screen postprocess quads at (0,0)..(320,240) or (0,0)..(640,480).
No fully inspected draw matches the red shield-bar candidate rectangle.
This locates evidence before final pixel composition but does not establish
why a bar is missing or exclude geometry inside the earlier large draws.
Single-event and three-event range output matched the same full-inspection
rows exactly; reversed bounds were rejected. All replay remained offline.

## Capturing a future diagnostic target

RenderDoc must be loaded **before the graphics API is initialized**. Official
RenderDoc documentation says injecting after API use has undefined results.
Consequently the already-running private xemu and native sessions must not be
used for a late-injection experiment. Use a new, explicitly hidden diagnostic
run when its owner is ready. Hiding the launcher alone does not guarantee that
the launched program will refrain from showing its own window.

For a target already launched with RenderDoc and with known target-control ident
and expected PID, these commands connect only to localhost and never force an
existing client off the connection:

```powershell
# Trigger one host Present-to-Present capture; timeout is 1..60000 milliseconds.
python tools/parity/run_renderdoc_helper.py capture IDENT EXPECTED_PID 30000
# Receive an available or upcoming explicit app-API capture, without triggering.
python tools/parity/run_renderdoc_helper.py listen IDENT EXPECTED_PID 30000
```

The helper verifies the target PID before requesting capture. Its JSONL includes
RenderDoc's **host** frame number and capture file path. Host frames are not
guest-loop numbers. `capture` drains an initial one-second inventory, then
requests one capture; `listen` can return an already available capture. Neither
command establishes a guest-frame association on its own. A timeout closes the
helper connection, not the target application, and does not cancel a capture
request that the target has already accepted. Do not trigger repeatedly on a
target that never presents.

## Native exact-frame integration

The current native hidden-window path deliberately skips
`IDXGISwapChain_Present` (`third_party/xboxrecomp/src/d3d/d3d8_device.c`,
`d3d8_PresentFrameWithInterval`). Therefore `TriggerCapture` cannot delimit a
hidden native run. Use the installed `renderdoc_app.h` API for an opt-in
diagnostic hook instead:

1. Load the installed DLL before `init_host_renderer` creates the D3D11 device.
   Call `RENDERDOC_GetAPI`, disable capture/focus hotkeys, and disable RenderDoc's
   overlay. Do not call `LaunchReplayUI`.
2. On the render thread, start capture at the chosen guest-loop/frame start.
   Record the exact loop/input/movie/selector state and use `SetCaptureTitle`
   with that guest-loop identity.
3. End capture after `pgraph_copy_presentable_to_swapchain` and the final game
   rendering pass, including the native CRT pass, on the matching frame. This
   works independently of DXGI Present. Keep the full frame bracket for draw
   and shader diagnosis. Existing in-process swapchain capture remains the
   simpler path when only final native pixels are required.
4. Obtain the file path with `GetCapture` or the console helper's `listen`, then
   inspect/export offline. The separate opt-in native hook now implements this
   workflow. Explicit app captures can report UINT32_MAX as RenderDoc's frame
   number, so retain the native hook's guest-loop/frame log as provenance.

For xemu, a future RenderDoc-launched private instance can keep its guest CPU
stopped at a known loop boundary while its host render thread presents. A
capture then records the host GPU texture and final gamma draw without savevm.
Check guest-loop/PC/CR3 before and after, and require GPU/FIFO and scanout state
to be stable. Capturing while the CPU is stopped alone does not prove that a
queued GPU frame has finished. Export the game framebuffer **after DAC gamma**
and before UI overlays, identifying the draw/event through shader and resource
evidence. Raw VRAM, the PVIDEO-composited display texture, and the final gamma
framebuffer remain distinct stages. See `EXACT_CAPTURE_LIMITS.md`.

## Sources and remaining verification

- [RenderDoc capture/injection limitations](https://github.com/baldurk/renderdoc/blob/286e07140d96bf3acda4059e085e8f5eb0e92608/docs/how/how_capture_frame.rst)
- [Pinned public replay API](https://github.com/baldurk/renderdoc/blob/286e07140d96bf3acda4059e085e8f5eb0e92608/renderdoc/api/replay/renderdoc_replay.h)
- [qrenderdoc startup order](https://github.com/baldurk/renderdoc/blob/286e07140d96bf3acda4059e085e8f5eb0e92608/qrenderdoc/Code/qrenderdoc.cpp)

Native run 016 completed that validation: its explicit app-API capture and
independent frame-7000 swapchain BMP match exactly in RGB (zero differing pixels).
Artifacts are `build-internal/parity-farm-hud-20260927-016_capture.rdc`,
`parity-farm-hud-20260927-016-final.png`, and
`dah_frame_9852_0000007000.bmp`. This verifies that native capture/export pair,
not xemu guest-frame association. Timing samples taken during GPU capture/readback
are diagnostic and must not be treated as normal runtime pacing measurements.
