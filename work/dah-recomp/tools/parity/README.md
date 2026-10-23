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
`@relative-frame` uses the same counter but anchors row zero when each adapter
loads the route, which is appropriate only after state/presentation alignment.
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

## Attach to an already-running visible pair

`attach_live_dual_parity.ps1` is the non-relaunch path for a player-controlled
comparison. It hash-checks the pinned xemu build, requires the sole root
`DestroyAllHumans.exe`, establishes equal 640x480 client areas without focusing
either window, and starts the bounded state and visual watchers. It never starts,
closes, pauses, focuses, or restarts either game:

```powershell
.\tools\parity\attach_live_dual_parity.ps1 -Start
```

The state watcher reads both address spaces without writing them. It rejects
torn reads, compares backend/movie/player state and pointer-independent active
menu selectors, requires equal movie frames within the one-frame uncertainty of
sequential sampling, and records five seconds before and after a new divergence.
Stable loop offsets prove equal cadence but do not prove equal animation phase.
`live_dual_phase_watch.py` independently timestamps retail-loop edges in both
processes at 500 Hz. Its rolling report records measured cadence, matching-edge
phase median and p95/max deviation, skipped-edge observations, and read errors.
It establishes a phase baseline only from a stable equal-cadence edge window
while the state watcher reports matching semantics. A movie, transition, or
state divergence closes that epoch and preserves the failure; after both games
return to the same state, a new baseline permits continued testing without
erasing the earlier incident.
This remains capture-free: screenshots and GPU readbacks cannot perturb its
wall-clock timing evidence. The launcher writes `dual-phase.jsonl` and the
summary treats sustained cadence or phase-jitter disagreement as a timing
failure. Sampling bounds an individual edge timestamp to approximately one
sample interval; it does not claim a shared hardware presentation latch.
For a parity-launched recomp, `DAH_PARITY_PHASE_CONTROL=1` exposes a 16-byte
named host control block. `align_live_native_phase.py` can request one bounded
shift of the recomp's next frame deadline after fresh state and phase evidence
exists. This changes neither guest memory nor the fixed timestep. The shift is
setup activity: restart or rebaseline the phase probe and require a complete
rolling window before accepting captures. It does not align independently
started world clocks, RNG, menu transitions, or animation state.
The visual gate additionally requires the movie frame, or the live world tick
when no movie owns presentation, to match within one sequential-sample frame.
Its atomic current-status file expires after 250ms; the visual watcher cannot
label a screenshot aligned from an old state observation. Visual captures use
equal-size client pixels without resampling and retain only bounded, deduplicated
incidents. `frame_pair_metrics.py` reports brightness/saturation bias separately
from normalized structure and edge correlation, so shifted animation content is
not misclassified as a pure brightness defect.
State or phase divergence also saves one representative frame pair and
difference image keyed by the failure fields. Animated pixels within the same
failure do not create a new capture on every frame.
The semantic identity includes every active top-level retail UI root, the
verified menu selectors, RNG state, and the world animation clock within one
sequential-read tick. A title screen and the New Game/Load Game screen, or two
visually similar shell frames with shifted Earth animation, therefore cannot be
accepted merely because they share the same shell backend.

Generate a conservative machine-readable verdict at any point, including while
the games remain open:

```powershell
python .\tools\parity\summarize_live_dual_watch.py `
  "$env:TEMP\DAH1-live-parity\watches\SESSION_ID"
```

For the current gate alone, `live_parity_readiness.py SESSION` reports the
fresh state/phase blockers and the three verified binary hashes. It exits zero
only while the pair is eligible for pixel comparison and shared replay.

The summary only passes timing after a stable baseline, at least three aligned
heartbeats, no recorded divergence, and no material reference/native rate delta.
Visual parity passes only when state-aligned captured pixels are exact. A pass is
limited to the observed route. Live shared-controller testing remains useful for
discovery, but its two independent polls are not frame-scheduled proof; replaying
the same `@frame` route through both logical-pad adapters is the acceptance path.
New builds include the retail loop number on every changed `FURON-INPUT` row.
`input_trace_to_route.py INPUT.log ROUTE.txt` converts those final delivered pad
states into one normalized `@relative-frame` route. Both adapters anchor that
route at their current retail loop, after a watcher has proved matching state.
This turns a player-discovered sequence
into a repeatable test while excluding focus events and raw host-device details
from the artifact.

For a coordinated replay, set `DAH_INPUT_BARRIER` on the native process and
pass the same new path as `--barrier` to `xemu_input_replay.mjs`. Both adapters
remain neutral and leave their relative-frame anchor unset while that path is
absent. `release_dual_input_barrier.py` creates it atomically only after the
live state watcher has published three fresh, consecutive observations with
matching semantics and presentation phase:

```powershell
python .\tools\parity\release_dual_input_barrier.py `
  --state-status "$env:TEMP\DAH1-live-parity\watches\SESSION\current-alignment.json" `
  --phase-status "$env:TEMP\DAH1-live-parity\watches\SESSION\current-phase.json" `
  --barrier "$env:TEMP\DAH1-live-parity\routes\RUN.release"
```

The resulting barrier file records the accepted loop/world offsets. A timeout
does not inject input; failure to align remains a test failure rather than being
hidden by a late route start. The xemu adapter still uses debugger stops, so
this mode proves deterministic game-state response to the same logical input
route. Capture-free live watching remains the wall-clock cadence test.

When two looping Bink presentations are the same movie but out of phase,
`movie_frame_checkpoint_watch.py` can isolate renderer/color fidelity from the
timing failure. It chooses a bounded set of frame IDs, captures each process
independently, and accepts a screenshot only when the movie frame is unchanged
around both `PrintWindow` and a read-only snapshot of the two decoded Bink
surfaces. It compares only equal header/frame IDs and
retains at most one reference/native/difference triplet per checkpoint. The
surface reader treats `D3DResource::Data` as the NV2A physical aperture offset
used by both backends rather than translating it through xemu's CPU page table.
movie header is not an asset-path identity, so this evidence supplements rather
than replaces a route that proves the same movie-open event.

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

## Live shared-controller comparison

`run_live_dual_parity.ps1` is the visible exploratory counterpart to the
deterministic harness. It launches a snapshot-isolated retail xemu and the sole
root `DestroyAllHumans.exe`, binds xemu port 1 to the physical controller from
the user's normal xemu config, and enables xemu background input capture. The
launcher starts the recomp with `DAH_PARITY_BACKGROUND_INPUT=1`, an opt-in test
mode that keeps physical XInput active while the other window has focus. Normal
player launches retain focus muting. If a recomp was already running, the
launcher reports that it cannot verify this mode and the recomp must be
restarted through the launcher before shared-controller results are accepted.

The launcher verifies and copies the pinned, known-good xemu 0.8.136 executable
into `%TEMP%\DAH1-live-parity` before every launch, with update checks disabled
in that isolated config. The short disposable path avoids QEMU path parsing
problems and keeps generated runtime files out of the repository. It contains no third-party
Direct3D proxy DLLs, so graphics wrappers beside the user's normal xemu cannot
intercept an updater restart or the comparison process. Readiness is tied to
the process that owns the isolated GDB port, which also handles a legitimate
xemu self-restart without confusing it for a crash.
The isolated reference also skips the Xbox boot animation so repeated comparison
runs reach the game as quickly as the retail executable permits.
Both clients are restored and laid out at an exact 640x480 client size without
activation. The visual watcher refuses to resize pixels; unequal client sizes
are recorded as a setup incident. Pass `-SkipWindowLayout` only when testing
the dimension-mismatch detector itself.

The launcher defaults to a dry run:

```powershell
.\tools\parity\run_live_dual_parity.ps1
.\tools\parity\run_live_dual_parity.ps1 -Start
```

`-Start` also starts the state, phase, and visual watchers after both 640x480
clients are ready. Pass `-SkipWatchers` only when a separate diagnostic owns
those process-memory reads.

This mode is useful for discovering visual, animation, control, AI, and mission
divergences. It is not exact timing evidence because the two processes sample
the physical controller independently; a button edge can land on adjacent
frames. Reproduce each discovered issue with the same scripted pad rows in both
engines before accepting a timing or state parity result. Pixel comparison also
requires equivalent capture stages and aligned frame identities as described in
`EXACT_CAPTURE_LIMITS.md`.

To attach the non-invasive live synchronization and visual watchers to a pair
that was started separately:

```powershell
.\tools\parity\start_live_dual_watch.ps1 `
  -XemuPid <reference-pid> -NativePid <recomp-pid>
```

The state watcher reads both processes without pausing either engine. Every
sample is bracketed by the retail loop counter and torn reads are rejected. It
requires stable loop and world-tick offsets while backend, movie, pause,
renderer, camera and player modes match. Failure to establish that baseline is
itself recorded as a synchronization incident, with each engine's measured
update rate. This is strong live drift evidence, but the two host reads are not
a shared presentation latch.

The visual watcher captures both client areas without focusing them and never
resizes either image. It reports exact changed-pixel count, RGB error and bias,
luminance, saturation, black/white fractions, edge energy and mismatch bounds.
Dimension mismatch and blank-frame mismatch are setup/visual incidents. Other
pixel mismatches become acceptance failures only while the state watcher says
the engines have a stable aligned state. Evidence lives under
`%TEMP%\DAH1-live-parity\watches`, is capped at eight deduplicated incidents by
default, and is never written into the repository.

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
