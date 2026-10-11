# Exact xemu capture: current limits and proposed hook

Inspected locally on 2026-09-26. This note describes source findings and a
proposed diagnostic implementation. The hook has not been implemented or run.
No xemu process was controlled during this investigation.

## What the current checkpoint proves

The current capture requests `savevm` while the reference is running, then
requests `stop`, reads CR3 and PCRTC_START, and copies Xbox physical RAM from the
host process. The save operation downloads dirty GPU surfaces into guest RAM.
However, `savevm` resumes the guest before the following `stop` arrives. The game
can advance between those operations. The copied CPU state and the last surface
download are therefore not guaranteed to describe the same guest frame.

These checkpoints are useful for menu state, asset/layout inspection, and
finding visible differences. They do not establish exact transition timing,
frame identity, or final displayed pixel equality. Debugger stops, snapshot
serialization, trace output, and readbacks also perturb wall-clock timing.

For an exact comparison, record the accepted input frame, state at a chosen
retail loop/presentation boundary, completed GPU frame identity, and the pixels
belonging to that frame. Compare capture-free timing separately.

## Why saving an already paused guest is unsafe here

The local source shows a mismatched lock lifecycle:

1. `hw/xbox/nv2a/nv2a.c:391`, `nv2a_vm_state_change`, handles
   `RUN_STATE_SAVE_VM` by locking/draining the FIFO, halting FIFO submission,
   requesting a GPU download, waiting for completion, and reacquiring the FIFO
   and PGRAPH locks for snapshot serialization.
2. `hw/xbox/nv2a/nv2a.c:421`, `nv2a_post_save`, unconditionally unlocks the FIFO
   and PGRAPH locks.
3. `system/cpus.c:294`, `do_vm_stop`, emits the VM state notification only if
   the previous state is live. An already paused/debug-stopped guest does not
   take the save-state notification path, so the required acquisition can be
   skipped while the post-save unlock still runs.

Changing the command spelling does not avoid this path:

- HMP `savevm`: `migration/migration-hmp-cmds.c:480` calls `save_snapshot`.
- QMP `snapshot-save`: `migration/savevm.c:3577`,
  `snapshot_save_job_bh`, calls the same `save_snapshot`.
- xemu's snapshot wrapper: `ui/xemu-snapshots.c:250`,
  `xemu_snapshots_save`, also calls `save_snapshot`.
- `migration/savevm.c:3261` calls `vm_stop(RUN_STATE_SAVE_VM)` during that save.

No alternate `x-snapshot` debugger capture command was found in this source.
Do not use paused `savevm` as a proposed frame-boundary capture workaround.

## Why ordinary memory reads and screendump are insufficient

`system/physmem.c:4174`, `cpu_memory_rw_debug`, translates addresses and calls
`address_space_rw`. This debugger path does not invoke xemu's TCG memory-access
callback that downloads cached GPU surfaces on a guest CPU read.

The actual OpenGL surface callback is
`hw/xbox/nv2a/pgraph/gl/surface.c:424`, `surface_access_callback`. It marks
overlapping dirty surfaces for download, wakes PFIFO, and waits for completion.
Reading physical RAM through HMP, GDB, or ReadProcessMemory is not equivalent to
the guest executing that callback. A complete RAM copy may contain stale pixels.

The available reference build omits QMP/HMP `screendump`. Its source declaration
is gated by `CONFIG_PIXMAN` in `qapi/ui.json:198` and `hmp-commands.hx:255`.
Enabling it alone would not guarantee a GPU-accurate result: the implementation
in `ui/ui-qmp-cmds.c:331` reads the console's CPU `DisplaySurface`, whereas the
usual xemu renderer explicitly bypasses the VGA surface to obtain a cached GPU
texture (`ui/xemu.c:815`).

## Raw VRAM versus the final displayed image

These are distinct comparison stages and must be named in capture metadata:

| Stage | Content and processing | Relevant source |
| --- | --- | --- |
| Raw GPU surface downloaded into VRAM | Guest-format pixels, pitch, swizzle/layout, and native-resolution downscaling when surface scale is greater than one | `hw/xbox/nv2a/pgraph/gl/surface.c:682`, `surface_download_to_buffer`; `:765`, `surface_download` |
| xemu display texture | Scanout selection/line-offset handling and PVIDEO overlay composition | `hw/xbox/nv2a/pgraph/gl/display.c:165`, `render_display_pvideo_overlay`; `:279`, `render_display`; `:375`, `pgraph_gl_sync` |
| Final game image in xemu UI | DAC gamma, aspect-ratio policy, scaling, and screen-off behavior applied to that display texture | `ui/xui/gl-helpers.cc:237`, gamma shader; `:459`, framebuffer shader setup; `:887` and `:943`, `RenderFramebuffer` |
| xemu screenshot PNG | Offscreen rendering through the UI framebuffer shader, with aspect-ratio adjustment and optional size limit | `ui/xui/gl-helpers.cc:978`, `RenderFramebufferToPng` |

A BGRX decode of PCRTC_START RAM is **pre-display raw scanout**, not xemu's final
displayed RGB image. It can omit PVIDEO, DAC gamma, scanout line selection, and
UI scaling. A comparison must use equivalent stages in the native build and
xemu. Do not attribute every raw-pixel difference to a game renderer bug without
checking the capture stage, format, dimensions, pitch, and frame identity.

For raw-surface work, use surface scale 1 and record the actual layout rather
than assuming every buffer is linear 640x480 BGRX. For final displayed pixels,
capture xemu's composed display texture and deliberately match the gamma stage;
avoid accidental window-size interpolation or aspect-ratio resampling.

## Proposed diagnostic hook

Add a narrowly scoped HMP command, callable through the existing QMP
`human-monitor-command`. Require that the guest CPU is already stopped at the
chosen breakpoint. The command must leave the CPU stopped and must not alter
guest menu, input, progression, or animation state.

Implementation points:

- HMP registration and prototype: `hmp-commands.hx` and
  `include/monitor/hmp.h`, with an xemu-specific guard.
- HMP handler: `monitor/hmp-cmds.c`, forwarding to the NV2A helper and returning
  an explicit success/error result plus metadata.
- GPU helper: `hw/xbox/nv2a/nv2a.c`, where the private
  `nv2a_lock_fifo`/`nv2a_unlock_fifo` helpers are available; public declaration in
  `hw/xbox/nv2a/nv2a.h` if required.

Proposed sequence, following the existing renderer synchronization pattern:

1. Validate stopped guest state, renderer availability, output destination, and
   requested capture bounds. Allocate an owned output buffer before taking
   GPU locks. Refuse to overwrite an existing evidence file.
2. `nv2a_lock_fifo(d)` drains to a FIFO idle/stall point and takes the required
   FIFO/PGRAPH locks. Preserve the previous `pfifo.halt` value.
3. Set `pfifo.halt=true`, invoke `pgraph_pre_savevm_trigger(d)`, then
   `nv2a_unlock_fifo(d)` to release locks and kick the worker.
4. Release BQL while waiting for `pgraph_pre_savevm_wait(d)`, then reacquire BQL.
   The PFIFO worker processes pending renderer downloads even while FIFO
   submission is halted (`hw/xbox/nv2a/pfifo.c:452`, especially `:464-467`).
5. Reacquire FIFO/PGRAPH locks; copy the selected surface or complete VRAM and
   its metadata into owned host memory. Record the scanout and completed-frame
   information at this point.
6. Restore the previous halt value and release locks on every completion/error
   path. Write the owned buffer after releasing GPU locks. Keep the guest CPU
   stopped throughout.

OpenGL download trigger/wait functions are in
`hw/xbox/nv2a/pgraph/gl/renderer.c:151` and `:160`. Vulkan implements the same
renderer operations in `hw/xbox/nv2a/pgraph/vk/renderer.c:150`. Use the renderer
interface rather than performing OpenGL calls on the monitor thread. Review
timeout/cancellation behavior carefully; an error path must not release locks
it does not own or leave FIFO halted unexpectedly.

Record at least: guest loop/input anchor, guest PC, CR3, PCRTC_START, active
surface address/format/width/height/pitch/swizzle, surface scale, FIFO DMA GET/PUT,
flip read/write/modulo state, and `pgraph.frame_time`.
`hw/xbox/nv2a/pgraph/pgraph.c:882`, `NV097 FLIP_INCREMENT_WRITE`, increments that
GPU frame counter; `:901`, `FLIP_STALL`, provides another useful presentation
boundary. A CPU end-of-loop breakpoint does not by itself prove that PCRTC
already displays that loop's rendered image. Validate the association explicitly.

This first hook provides coherent stopped-guest raw pixels and state. Final
display capture would be a second stage: queue readback on the renderer thread
after `pgraph_gl_sync`/the Vulkan equivalent, retaining PVIDEO composition and
applying the chosen DAC gamma stage. `nv2a_get_framebuffer_surface` returns a GPU
texture handle; it is not a ready CPU pixel buffer and must be released with
`nv2a_release_framebuffer_surface` when that API is used.

## Current local build constraints

The existing source checkout has no xemu `build`/`dist` directory, configured
`build.ninja`, `config-host`, or compilation database. The parity xemu is a
prebuilt 22,258,780-byte executable with no adjacent PDB or build libraries.

During this inspection, GCC/G++, make, Meson, pkg-config, Docker, and Clang were
not found on PATH. Standard C:/D: MSYS64/MinGW64 directories and Program Files
LLVM/Docker directories were absent. The available MSVC/Ninja game toolchain is
not a configured xemu toolchain. WSL inventory returned
`Wsl/EnumerateDistros/Service/E_ACCESSDENIED`, so no usable Linux build
environment was established.

The local Windows CI definition (`.github/workflows/build-windows.yml`) uses a
Linux MXE static cross-toolchain container, whose dependencies are described in
`ubuntu-win64-cross/gcc.Dockerfile`. `build.sh:235` also supports native
MSYS/MinGW builds. Either path requires substantially more setup than compiling
one helper with the game's existing MSVC environment.

No toolchain installation or xemu rebuild is planned as part of this checkpoint
pass. Continue exact state/selector comparisons at explicit breakpoints, retain
current visual captures as unaligned evidence, and implement/test the dedicated
capture hook when a working xemu build environment is available.
