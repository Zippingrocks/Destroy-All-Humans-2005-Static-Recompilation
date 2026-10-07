# Non-intrusive xemu parity lab

This directory compares the native recomp against a separate reference xemu
without taking desktop focus or consuming physical keyboard/controller input.
It never attaches automation to the user's foreground xemu process.

## Safety boundaries

- `run_isolated_xemu.ps1` defaults to a dry run. `-Start` is required.
- The reference XBE must match the pinned retail SHA-256 before launch.
- xemu runs from a private portable executable/config directory, receives a
  different HDD image, and uses `-snapshot`, so neither the foreground xemu
  settings/cache nor either HDD are persisted.
- The default uses `-display none`. `-Rendered` instead gives xemu a real GPU
  window on a separate Windows desktop object named `DAHParityDesktop`; that
  desktop is never switched into view, so the reference can execute the real
  movie/render path without touching the user's desktop or focus.
- `xemu_rsp_probe.mjs` has no guest-memory write command. A snapshot only halts,
  reads, and resumes the isolated guest.
- This xemu build omits QMP/HMP `screendump`; reference visuals therefore need
  GPU-surface memory capture/decoding rather than a visible-window hotkey.

## First connection check

```powershell
.\tools\parity\run_isolated_xemu.ps1 -Start
node .\tools\parity\xemu_rsp_probe.mjs probe --port 1235
```

Capture a narrowly scoped state region:

```powershell
node .\tools\parity\xemu_rsp_probe.mjs snapshot `
  --port 1235 --range 0x00225000:0x2000 `
  --out .\build-parity-xemu\frontend-state.json
```

## Background controller and frame captures

Keep reference input automatic binding disabled and background input capture
disabled in `xemu-isolated.toml`. `xemu_input_replay.mjs` uses the original
XInputGetState/XInputSetState boundary to supply logical pad results. It retains
retail enumeration, open/close, and device handles. It never writes progression,
menu, animation, or renderer state. Debugger stops perturb wall-clock timing;
this is a game-logic test, not physical-controller certification.

Rows before `@frame` use controller-poll time. Rows after it use the retail
loop counter at `0x25B1DC`; frame durations are loops rather than input polls.
Both engines accept the same row format. A controller-backed xemu replay requires
`run_isolated_xemu.ps1 -Rendered`: that window lives on the private
`DAHParityDesktop`, so it supplies xemu's neutral keyboard device and real GPU
path without appearing on or taking focus from the user's desktop. The
`-display none` mode remains useful for read-only probes, but does not create
the keyboard device needed by `xemu_input_replay.mjs`.
`@gameplay` starts a phase-relative schedule. The native harness retains its
control-proven gameplay anchor. The xemu adapter waits for six consecutive
five-loop observations in Farm with an unpaused world, no cinematic, and
Crypto owning player focus. This removes asset-load duration from gameplay
input comparisons without writing or forcing guest state.
For a state-gated reference step, `--relative` anchors its rows to the current
loop. Replay emits the observed press and release loop numbers:

```powershell
node .\tools\parity\xemu_input_replay.mjs --port 1235 `
  --script .\build-parity-xemu\route-step.txt --relative --seconds 5 `
  --out .\build-parity-xemu\route-step-input.json
```

`capture_xemu_checkpoint.ps1` verifies the private executable and QMP port's
owning PID, flushes GPU surfaces with a running `savevm`, pauses, reads physical
RAM, and resumes in `finally`. It then walks the captured x86 page tables and
decodes the native 640x480 BGRX scanout. Supply an installed Python with Pillow:

```powershell
.\tools\parity\capture_xemu_checkpoint.ps1 -XemuPid <private-reference-pid> `
  -Stem .\build-parity-xemu\unique-checkpoint -Python <python.exe>
```

Do not call `savevm` on an already paused reference: this xemu build skips a GPU
locking callback in that state and can deadlock. The helper requires a running
reference. The flush and subsequent pause are **not an exact frame boundary**.
Output metadata records this limitation. Raw dumps contain game RAM only; they
are local diagnostics and should not be committed or distributed.
The scanout is also before xemu's PVIDEO/display composition and DAC gamma.
It is useful renderer evidence, not a capture of xemu's final displayed output.
See `EXACT_CAPTURE_LIMITS.md` for the required frame capture hook and current
toolchain constraints.

For the native game, `run_internal.ps1 -UseRetailFps -UseMovieDefault` keeps the
retail pacing/movie paths, hides the window, supplies neutral input outside the
script, and mutes audio. Use a unique absolute `DAH_SAVE_DIR` to avoid profile
differences, `DAH_LOG_PATH` for a new log, and `DAH_PARITY_STATE_TRACE` for a new
JSONL trace. `DAH_PARITY_STATE_INTERVAL` selects the logging interval (default1).
`DAH_FRAME_CAPTURE_TRIGGER` names a file whose timestamp can be updated to
request two consecutive swapchain captures. The trigger works only with
`DAH_INTERNAL_RUN=1`, is polled every15 presentation calls, and takes no focus.

State traces record backend/UI activation, movie header, refresh/divisor,
world-step bits, and pointer-independent menu selector paths. An incomplete
selector traversal is reported explicitly. See `MENU_ROUTE.md` for the
state-gated route through Controls, Audio, Display, Pox, upgrades, and Hangar.

`compare_native_frames.py` compares original RGB pixels with no resizing,
alignment, or tolerance. Any pixel difference fails. Identical pixels alone
cannot pass timing/state parity; its output always keeps `timingVerified:false`.
Use capture-free runs separately for pacing measurements.

For a rendering defect, `DAH_PB_CAPTURE_START` delays the existing bounded raw
ring capture count until a selected submission (default1). This avoids filling
the capture budget during startup. `DAH_PASS_PIXEL_SUBMISSION` reads three
pixels at20,20 /50,50 /100,100 before and after every draw path in one selected
ring, capped at512 draws. Each record includes target, surface format, color
mask, blend state, texture, and before/after RGBA values. These synchronous GPU
readbacks invalidate that frame's pacing measurement. Small targets that do
not contain all three points report a failed read instead of invented pixels.

## First proven result (2026-09-25)

The rendered hidden-desktop reference and a hidden recomp run produced the same
nine-event startup lifecycle, including exact `logo_thq.bik` and `logo_pan.bik`
paths and ordering. After aligning at the THQ open, all six remaining events
were within **31.904 ms**, less than one 30 FPS frame. See
`movie_parity_baseline.json` and regenerate the full comparison with
`compare_movie_traces.mjs`.

This is a partial instrumented milestone result, not proof of exact boot,
frame-sequence, animation, or pixel parity. It aligns at THQ open and excludes
earlier boot time. A later traced run had a251.827ms maximum discrepancy, so the
initial number must not be used as a general timing guarantee. The retail
blocking Bink wait path is the normal player default;
`DAH_MOVIE_NONBLOCK=1` remains an explicit diagnostic experiment.

## Fixes validated by the lab (2026-09-26)

- The native millisecond clock now follows the retail `RDTSC*3/2200000`
  calculation instead of the host's coarse `GetTickCount64`. A 3013-case test
  includes overflow semantics and rejects the old implementation.
- The menu greyscale pass now supports NV2A stage1 `DPNDNT_AR`, sampling the
  original 1x256 `SZ_A8B8G8R8` table using T0 alpha/red. The table's lock path
  explicitly writes its contiguous alias; the uploader now reads that backing
  and converts RGBA bytes to the host BGRA format. This restores the missing
  dim menu backdrop. `test_dependent.mjs` checks real production upload/draw
  code, conflicting memory windows including valid zeros, and 4096 offscreen
  WARP channel values. Four old/wrong-behaviour controls fail as expected.
- `NV097_SET_BLEND_EQUATION` now reaches the host blend state. Captured retail
  scanline draws use reverse subtraction (`0x800B`); previously they used ADD
  and brightened the scene. `test_blend_equation.mjs` checks 112 offscreen WARP
  channel values through production command handling, draw submission and
  blend state. The old ADD behaviour fails its negative control.
- X8 render-target texture views now sample alpha as one, matching xemu's
  format tables. The Pox threshold pass previously discarded pixels using the
  RT's stored alpha, preserving red pixels that the glow pass added to the
  scene. Same-submission pixel traces confirm the corrected threshold replaces
  those pixels and removes the added red. `test_x8_alpha.mjs` checks 112 WARP
  channel values, A8 preservation, cache switching and dependent sampling;
  its old-behaviour control reproduces the stale red. See
  [X8_ALPHA_FIX_20260926.md](X8_ALPHA_FIX_20260926.md) for capture paths and limits.

Remaining work includes exact frame-boundary reference capture, equal initial
save/RNG/animation state, complete transition sequences, and the full menu/game
route. Current screenshots establish concrete rendering defects and fixes;
they do not establish pixel-perfect or complete timing parity.

# Investigation and debug restoration

- `RECOMP_INVESTIGATION_WORKFLOW.md` defines the evidence-preserving workflow
  for crashes, missing systems and parity defects.
- `DEBUG_RESTORATION_PLAN.md` defines how alpha PDB names and surviving retail
  debug facilities may be restored without contaminating normal parity runs.
- `ALPHA_RETAIL_DEBUG_EVIDENCE.md` pins the actual alpha PDB/XBE artifacts,
  separates original evidence from host-authored alpha-recomp experiments, and
  points to the machine-readable accepted-name ledger.
- `ALPHA_RETAIL_CRASH_AUDIT_20261007.md` inventories preserved and historical
  crashes, proves the restored callback coverage, and records which
  ActorSamSite structures survived or changed between alpha and retail.
- `WHOLE_ALPHA_RETAIL_COMPARISON_20261007.md` expands that work to every
  discovered function in every executable section, all strings and named class
  IDs, both complete block trees, and all data-section callback/vtable targets.
  Its row-level databases live under
  `tools/analysis/results/whole-alpha-retail/`.
- Incident files such as `SANTA_EMP_INCIDENT_20261006.md` apply the workflow to
  one reproducible defect and carry its acceptance matrix.
