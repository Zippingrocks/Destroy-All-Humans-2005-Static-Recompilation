## 2026-09-19 (evening) — Camera pitch "look up, can't look down" bug: UNSOLVED, session paused mid-investigation

**Symptom (user-confirmed, live, real controller, real build-ninja/dah.exe):**
once you push the camera stick up, pushing it back down does nothing --
camera stays pinned looking up. This is the #1 priority bug in the project
right now per the user. NOT YET FIXED. Read this whole section before
touching input/camera code again.

**Ruled out with high confidence (do not re-investigate these):**
1. Our host input translation layer
   (`Repos/xboxrecomp-main/src/input/xinput_device.c`,
   `stick_conditioner.c`) -- both the Windows/XInput backend and the SDL
   backend were code-reviewed and empirically tested. `stick_conditioner.c`'s
   `xbox_condition_stick()` is a pure, stateless, symmetric function --
   verified by hand and by live `[FURON-HOST-INPUT]`/`[FURON-INPUT]` log
   evidence (raw and conditioned values are correctly signed and symmetric
   in both directions). This layer is NOT the bug.
2. The game's own low-level analog-stick deadzone/response-curve routine,
   found at `sub_000FF520` in `src/recomp/gen/recomp_0011.c` (around line
   22014, the function that immediately follows the single call site of
   `sub_002216B5` / `dah_xinput_get_state_bridge`). Added an opt-in trace
   there (`DAH_STICK_CONDITION_TRACE=1`, prints `[DAH-STICK-CONDITION]`,
   see the block right after `loc_000FF899` around line 22464) and verified
   empirically with a scripted full-up/full-down sweep: raw=32767 ->
   smoothed=1, raw=-32768 -> smoothed=-1. Correctly symmetric. NOT the bug.
   (My first read of this function's asm-derived branches looked like an
   inverted clamp -- it is not; the shared floor/ceiling constants are one
   positive and one negative by design and the empirical trace proves it's
   fine. Don't waste time re-deriving this from the generated C by hand --
   trust the trace data instead.)

**What's still unknown / where the bug actually lives:**
Somewhere between "conditioned analog stick value" (proven correct) and
actual on-screen camera pitch, there is a genuine bug -- almost certainly a
recompilation-correctness issue in the camera integrate/clamp code, not our
compat layer. Two headless attempts to reproduce it failed for an
unexpected reason: the global camera object at fixed guest address
`0x00250E60` (heavily referenced across `recomp_0010.c`, confirmed a real,
persistent, valid pointer every run) simply **does not respond to scripted
stick input at all** in either of the headless setups tried so far
(`DAH_CONSOLE_AUTOLOAD_LEVEL=rockwell`, and organic Farm boot via
`tools/menu_probe_input.txt`-style navigation) -- a full byte-diff of a
0x200-byte window at that address across an entire up/down/up/down sweep
showed only one changing field (offset 0x0D4, monotonically increasing --
that's a frame/tick counter, not orientation; see
`DAH_CAMERA_MEMDIFF_TRACE=1`, prints `[DAH-CAMERA-MEMDIFF]`, added in
`dah_camera_memdiff_poll()` in `src/recomp_manual.c` just above
`dah_xinput_get_state_bridge`). Also tried the pre-existing
`dah_trace_rockwell_player_camera()`/`DAH_ROCKWELL_PLAYER_TRACE=1` trace
(camera fields at node+0x70/0x80 etc.) -- same result, static, unresponsive
to input; also `player`/`actor` pointers stayed NULL in both headless
setups the whole time (that trace's pointer chain was built for an NPC pose
investigation, not the player camera -- don't reuse it for this).

**Working hypothesis for why headless repro failed:** whatever object is
`0x00250E60` in these headless setups is probably not the same camera
instance/mode that's active during real interactive third-person play (e.g.
a default/establishing camera, or gameplay requires a state our
console-driven boot never reaches). Headless console-command-driven level
loads may fundamentally not reach "real controllable third-person camera"
state the same way organic menu-driven play does.

**Recommended next step (not yet done):** the memory-diff technique itself
worked correctly and is cheap/safe (`dah_camera_memdiff_poll()`, gated by
`DAH_CAMERA_MEMDIFF_TRACE=1`, requires `DAH_INTERNAL_RUN=1`, purely
read-only logging, does not touch guest state, safe to leave compiled into
both build-internal and build-ninja). The efficient next move is to run it
against **build-ninja with a real user controller** instead of scripted
headless input: launch `dah.exe` with `DAH_INTERNAL_RUN=1
DAH_CAMERA_MEMDIFF_TRACE=1` set (this does not change any player-visible
behavior, only adds stderr logging), have the user play normally and
specifically push the camera stick hard up for a few seconds then hard down
for a few seconds, then read `furonlog.log`, grep for
`[DAH-CAMERA-MEMDIFF]`, and diff snapshots across that window exactly like
this session's headless diff (see the PowerShell `Cmp` helper pattern used
tonight). Whichever byte offset changes with "up" and then fails to reverse
with "down" is the smoking gun -- at that point you have a concrete
address/offset to chase without needing a disassembler. This was queued up
and ready to run when the session was paused (build-ninja was freshly
rebuilt with this diagnostic and `dah.exe` was already repromoted) but the
live user test was never actually run -- **do this first** next session.

**Files touched this sub-investigation (all safe, additive, opt-in,
gated, already built into both build-internal and build-ninja):**
- `src/recomp/gen/recomp_0011.c` -- added `[DAH-STICK-CONDITION]` trace
  (`DAH_STICK_CONDITION_TRACE=1`) inside `sub_000FF520`.
- `src/recomp_manual.c` -- added `dah_camera_memdiff_poll()` +
  `[DAH-CAMERA-MEMDIFF]` trace (`DAH_CAMERA_MEMDIFF_TRACE=1`), called from
  both `dah_xinput_get_state_bridge()` exit paths.
- `tools/camera_pitch_probe_input.txt`,
  `tools/camera_pitch_probe_farm_input.txt` -- scripted RY sweep test
  inputs (proved the headless-repro dead end above; still useful scaffolding
  for the next attempt if a working headless repro path is ever found).

No fix has been applied for the actual pitch bug. Do not report this as
resolved. The earlier `xinput_device.c` "no inversion, native XInput
passthrough" change from earlier on 2026-09-19 is still believed correct
(see the code comments in that file) and is NOT the cause of this
remaining symptom -- it's a separate, deeper bug.

# Internal verification notes — 2026-09-12

Target: a real, interactive main menu at measured 30 FPS. Not yet achieved.
The user's visible build is not the test target. Build and run only
`build-internal`; it has independent data, saves, and logs. The bounded runner
does not show/focus a window, poll physical input, or output audible sound.

**Tooling note (2026-09-19), read before any bounded test run**:
`DAH_FRAME_TURBO=1` alongside `DAH_INTERNAL_RUN=1` removes real-time frame
pacing from internal runs -- measured 5.6x-15.4x real time with zero
crashes/exceptions/invalid-steps in a controlled A/B test
(`recomp-turbo-test.log` vs `recomp-baseline-test.log`). It changes nothing
about what's simulated (retail-fixed-step gameplay's per-tick delta is a
constant, not measured wall time); it only removes the wait. Does not speed
up Bink movie playback (separate clock). See README.md's "DAH_FRAME_TURBO"
section for the full explanation. Use it on every headless test from now on
unless specifically diagnosing frame-pacing itself.

**Tooling note (2026-09-19), weapon crash-hunting**: `give_weapon <name>`
now supports all 15 known weapon keys (was hardcoded to `zap` only) and a
new `giveall_weapons` command unlocks all of them in the progression store.
`DAH_CONSOLE_AUTO_GIVEALL_WEAPONS=1` / `DAH_CONSOLE_AUTO_EQUIP_WEAPON=<name>`
trigger these headlessly; `tools/weapon_fire_test.txt` is the calibrated
input script (menu nav + sustained RT pulls). Full first pass on Farm (one
weapon equipped and fired per run, `DAH_FRAME_TURBO=1`): 10/15 equipped and
fired with zero crashes (zapomatic, brainextractor, analprobe, mattermove,
holobob, holobobhelper, hypnoray, destructoray, iondetonator, cortex). 5/15
granted but not equipped, no crash: abducto/deathray/sonicboom (confirmed
genuinely saucer-exclusive in the real game -- correct behavior) and
quantum/brainray (open anomaly -- these ARE on-foot weapons in the real
game; all three Union-bundle weapons failed to equip on Farm while
Area 42's equipped fine cross-site, so this looks Union-specific, not
random). See README.md "Weapon crash-hunting tooling" for the full table
and the saucer-mechanism research findings (SetFocusShip/SetFocusCharacter
hash-dispatch table located via a raw XBE byte search, traced into
`sub_00083A50`, not yet safely completable -- deliberately not implemented
as a console command pending either further tracing or a safer
progression-key-based trigger).

## Verified repairs

- The retail timer event path now permits its script callbacks, opening
  `movies/logo_thq.bik` instead of stopping before the movie.
- Xbox MMX capability detection no longer leaves converter callbacks null.
- Restored 969 MMX instructions in the existing/new Bink conversion routines,
  checked against original disassembly. Packed integer helpers passed
  4,476,487 comparisons against SSE2 hardware results.
- Kernel ordinal 235 consumes six guest arguments, not five. Its missing
  WaitMode argument caused incorrect parameter mapping and stack cleanup.
- Kernel dispatch selection is thread-local. A shared selector allowed Bink
  workers to invoke another thread's bridge/stack cleanup.
- 36 CMP-to-SBB carry dependencies in the Bink bundle-width setup restored.
  For a 640-wide frame, the affected length fields are ten bits, not eleven.
  The underlying lifter also preserves CMP/TEST carry for future generation;
  50 recomp unit tests and the six existing carry self-checks passed.
- Exact-source kernel bridge tests passed 12 cases. Four negative controls
  reject the previous argument map, cleanup size, missing count bound, and
  shared dispatch selector.
- The Bink wait clock now receives the original 733333333 Hz RDTSC timebase
  from QPC. Frames advance at each movie's native 25 FPS without speeding up
  the media to meet a presentation counter.
- Indexed movie geometry and pixels resolve through the actual contiguous
  GPU-memory window (0x80000000 + offset), not unrelated low guest RAM.
  The narrow renderer accepts the observed retail shader/layout/combiner,
  uploads native movie pixels, and rejects unknown configurations.
- Restored 46 omitted D3D MMX transfers; 8,192 complete-function regression
  cases passed. Restored eight MOVSX BP operations in Bink; 2,097,152 exact
  signed-vector tests passed. The three inverse-transform repairs removed
  the scattered block artifacts in subsequent actual captures.
- All 49 original VM opcode-table entries now have implementations and
  dispatch; exact-handler regression passed 5,765 cases / 3,182,203 assertions.
- Startup cleanup and number-formatting callbacks pass 49 exact-wrapper
  cases (409 original XBE bytes); the first four audio cleanup callbacks
  pass 143 cases (241 original bytes). Tests include deliberately broken
  stack/argument controls. These are scoped original-code restorations.
- The audio-close chain now contains seven byte-checked callbacks and passes
  167 cases. The six connected frontend callbacks pass 1,126 cases; a separate
  512-case test checks the two-vector argument layout of 0x104480.
- Restored 16 UCOMISS-to-LAHF flag transfers in frontend/VM code. Exact-site
  checks cover 203 original bytes; 305,408 cases match a native SSE flag oracle.
- Fixed CRT classifier 0x13F383: correct EBP, live FXAM classification/sign,
  byte-sized shifts/rotates, and both XLAT lookups. Tests cover 100,000 native
  FXAM comparisons and 7,744 actual-source dispatch cases. Without XLAT, the
  routine indexed between pointers and jumped to 0xF4C20013.

## Runtime evidence, not success claims

- PID 10116: first actual movie indexed draw reaches the pushbuffer at
  submission 204. Four indices refer to a float4/float2/ARGB vertex layout;
  texture 0 is the native 640×448 linear X8R8G8B8 movie buffer.
- PID 41512: after the kernel repairs, a Bink entropy decoder overran guest
  memory. Traces and original-code comparison identified the carry defect.
- PID 44460: after carry repair, first-frame bundle traces show ten-bit
  lengths and valid counts of 520. The bounded 60-second run did not crash,
  but stalls waiting before the next movie frame. No menu or 30 FPS native
  rendering has been verified. Its first submitted vertex was all zero and
  was correctly rejected by the narrow movie renderer.
- PID 10676: first actual nonblank movie captures; THQ and Pandemic movies
  both complete. Images still contained block artifacts. Subsequent menu
  script execution hit missing opcode 0x196A66 and crashed.
- PID 19464: clean THQ animation confirmed from actual framebuffer capture
  280 after the MOVSX repair. Startup then stalled in native audio-stop
  polling; missing audio dispatch callbacks were restored afterward.
- PID 42376: both movies complete again, now with correct audio event
  dispatch. Main-menu setup progresses through restored VM aggregate code;
  missing RegisterKeyTable and formatting callbacks were the next blockers.
- PID 23988: RegisterKeyTable now executes; menu object setup and mission
  dispatch progress further. Missing 0x1023E0 / 0x103F20 / 0x1022D0 callbacks
  are the next proven blockers. No main-menu image or stable 30 FPS menu
  has been verified. This is still incomplete.
- PID 4856: previous three missing frontend callbacks no longer occur;
  another connected property callback (0x104480) is restored next.
- PID 2020: audio-close and known frontend callbacks resolve, advancing
  further through menu setup. The next errors are CRT classification's
  invalid target above and missing name-lookup unwind 0x191FAA. The latter
  is now restored and tested over 512 saved-register/return combinations.
  The CRT's six real remainder-table targets are being restored separately.
- PID 46916: both clean intro movies play and complete. Two steady five-second
  intervals measured 30.000/30.005 loop and drawn-frame FPS, with p99 intervals
  of 33.333/33.336 ms. Native audio shutdown still caused a roughly 516 ms
  transition hitch. After movie completion the last captured framebuffer was
  black; menu startup reached missing script, timer, audio and render-format
  callbacks. This is NOT a successful main-menu boot.
- Restored the observed 0x8BA90 / 0xE3BE0 script natives and 0x11C180 timer
  callback: 40,120 actual-body cases, 381 original bytes and five negative
  controls. Added stream-format 0x1F225D and its narrowly connected callbacks;
  the audio suite now covers 26,125 cases and eight negative controls.
- Closed both original jump tables in the render-target format encoder at
  0x1E0420. Ten missing arms retain the original common tails and `ret 8` ABI.
  Complete encoder tests cover 127,472 combinations of format, dimensions and
  depth format against the actual XBE tables; three negative controls fail.

An opt-in `DAH_MOVIE_NONBLOCK=1` scheduling adapter is available via
`tools/run_internal.ps1 -NonblockingMovie`. Only the proven regular update
caller may return while BinkWait is pending; preload stays synchronous and
no decode, texture, timestamp, or frame advance is forged. Exact-function
tests verify 150 updates / 125 decode-and-advance events in five simulated
seconds. PID 46916 verifies clean movie continuity with measured 30 FPS host
updates during steady playback, while preserving the movie's native decode rate.
The original blocking behavior remains the default. Frame summaries now
include p95/p99 intervals to expose stutter rather than only average FPS.

September 13 checkpoint (incomplete visual target):

- Native atlas rendering now displays Press Start; the restored original
  0x63510 event callback advances to real New Game / Load Game text.
  Evidence: `build-internal/dah_frame_26348_0000001180.bmp`.
- The text-only menu baseline PID40384 completed a 360-second bounded run,
  including over five minutes after Start. This does NOT validate a complete
  3D menu or the newer renderer. Background scene assets were still missing.
- Startup no longer calls AllocConsole: stdout/stderr already go to recomp.log.
  Only build-internal was rebuilt; the user's other executable is untouched.
- Newer in-workspace 3D code was preserved and corrected for BC1: BASE_SIZE
  fields encode texel dimensions, blocks are row-major, and captured static
  textures use low RAM. Removed the incorrect Morton-tile decoder and stale
  UI IMAGE_RECT sizing. BC1 is decoded to BGRA for tiny 1/2-texel host textures.
  Content is refreshed even when an asset reuses the same address.
  `tools/test_bc1.c`: 260 shape/size cases plus block order, interpolation,
  transparency, pitch and short-input checks. Captured UI transport still passes.
- Added a 17-slot program start bound and whole-strip rejection for invalid
  transformed vertices, rather than creating artificial offscreen triangles.
- PID1756: 65-second hidden run survives and has steady 30 FPS intervals after
  startup hitches. BC1 trace correctly reads 2x2 / 8 bytes at 0x028FDF00.
  Frame1240 still does NOT match the reference: only text/dark malformed geometry.
- Remaining blocker: menu MVP c36..39 collapses scene vertices near the screen
  center, with clip W around 1e8. Trace the original CPU matrix inputs/producers;
  do not replace them with guessed camera values. DAH_MATRIX_TRACE enables a
  bounded read-only source trace in 0xD64A0 for the active camera matrix.
  PID19084 narrows it further: caller0xE7246 passes view data at0x00F7D470
  copied by0xD6100 from active camera+0x50. Its basis contains3203280,
  9200206,-12335760,15388787 before multiplication. Projection at0x27D630
  has ordinary values(-2.41421342,3.21895123,1.00003994,-0.0100003993).
  Trace the producer of the camera view matrix; do not blame the GPU upload
  or substitute a guessed matrix. PID19084 survives its50-second bound.
  Lighting validity, other shader/combiner programs, render targets and proper
  depth/culling also still need validation before claiming the full 3D scene.

The target remains the user's complete space/Earth/mothership/saucer reference,
rendered from native assets at stable 30 FPS. Text or a ticking loop is not enough.

`recomp-internal-<PID>.log`, optional `recomp-crash-<PID>.log`, actual framebuffer
BMPs, and indexed pushbuffer dumps live beside the internal executable.
Capture readback is synchronous and must be disabled for a final pacing soak.
The static `DAH_HOST_FRAME` probe is disabled throughout these tests and is
never menu evidence. Hidden-window occlusion and a ticking loop alone are not
proof that the game is rendering correctly.

## September 19 checkpoint -- first non-Farm level reached

Target: reach and characterize the five sites never previously loaded
(rockwell, santa, area42, union, capitol). No source changes were needed for
Rockwell; the blocker was purely getting a fresh internal run to a state
where `load_level` is accepted, with no window and no physical input
available this session.

- Added `DAH_CONSOLE_AUTOLOAD_LEVEL` (`src/recomp_manual.c`,
  `dah_console_autoload_poll`): an internal-only, throttled retry of
  `dah_console_load_level` through the exact same code the human console
  command calls. It fabricates nothing; it is only an alternate input path
  for a command a person would otherwise type, the same category as the
  existing `DAH_AUTOSTART`/`DAH_AUTOSTART2`/`DAH_AUTOA` synthetic presses.
- PID 22896 / `recomp-menu-probe6.log`: `tools/menu_probe_input.txt` (a
  `DAH_INPUT_SCRIPT`, tuned against captured BMP frames converted to PNG)
  carried a fresh internal run through the shell intro, New Game, the
  "overwrite existing saved game?" confirm (defaults to No; needs Down then
  A), the post-save "Continue" prompt, and a Down/Up cursor nudge before an
  A hold on the following "Select Game" list -- that screen otherwise
  ignored both discrete A pulses and a long A hold with no visible reaction
  across six separate attempts. `[DAH-CONSOLE-LEVEL] alias=rockwell
  mission=m2 path=blocks\sites\rockwell prepared=1 accepted=1` followed by
  `handoff=committed`: Rockwell loaded through the original mission-unlock
  and site-transit path, same as Farm's.
- PID 10372 / `recomp-rockwell-stability.log`: a 150-second capture-free
  rerun of the identical script. Post-handoff `[DAH-FRAME]` windows hold
  loop-fps at 29.9-30.1 for most 5-second windows, with a few windows
  dropping into the low-to-high 20s and one late-window collapse to 21.9fps
  (likely the forced kill at the time bound, not gameplay). No
  `unresolved`/`ICALL-FAIL`/crash lines appear anywhere after the handoff.
  Earlier in the same class of run (`recomp-rockwell-test.log`, Farm) two
  unresolved indirect-call targets were found during live gameplay, not
  boot -- `0x0011FA30` (a real, 16-aligned, undetected function start called
  as a per-actor per-frame update hundreds of thousands of times) and
  `0x00143689` (a non-aligned jump-table arm inside `sub_0014358B`'s tail).
  Neither is fixed; see README's "Known stutter source" section for why
  (no Python on this machine to run the project's own recompiler, and
  hand-lifting without a unit test does not meet this project's bar).
- Reusing the identical single-pulse script for `santa` did not reproduce
  within two tries (150s, then 220s) -- `selected_slot` stayed unselected
  the entire time in both. The absolute tick numbers were calibrated to one
  specific run's real-time pacing and were not a fixed recipe.

Follow-up, same day: `tools/menu_probe_input.txt` was rewritten to repeat
each navigation step's input pattern across a wide window of ticks instead
of firing once at a single guessed tick (a repetition landing on an
already-passed screen is harmless). This version reliably created a fresh
profile and got `load_level` accepted for all five previously-untouched
sites in immediate succession:

- **Santa**: `recomp-santa-stability3.log`. `handoff=committed`. Post-load
  stability is the cleanest seen yet -- loop-fps 29.98-30.02 and
  interval-p99-ms pinned at 33.334 (exact 30Hz) for nearly every 5-second
  window across 150s. Two new unresolved-ICALL targets specific to this
  site appear during gameplay: `0x00054B20` (ret=`0x00074ABA`) and
  `0x0004F9E0` (ret=`0x00054A57`). Not fixed (see README's "Known stutter
  source").
- **Area 42**: `recomp-area42-stability.log`. `accepted=1`,
  `ready=1 switch_requested=1` -- then never commits. `draws-total` freezes
  at 67066 and stays frozen for 30+ consecutive 5-second `[DAH-FRAME]`
  windows (150+ real seconds) while loop-fps keeps ticking a locked 30.0 --
  the render loop is alive, nothing is being drawn. No crash, no
  ICALL-fail.
- **Union**: `recomp-union-stability.log`. Identical shape to Area 42:
  `accepted=1`, `switch_requested=1`, then frozen (`draws-total=66904`).
- **Capitol**: `recomp-capitol-stability.log`. Identical again:
  `accepted=1`, `switch_requested=1`, then frozen. The `[DAH-FINISH]` log
  lines (see below) for Union and Capitol are line-for-line identical in
  their field values through call=64, strongly suggesting one shared root
  cause across all three sites rather than three independent bugs.

Isolated the stuck point precisely by comparing `[DAH-FINISH-READY]`
(`src/recomp/gen/recomp_0009.c` line ~28935, inside `sub_000DB450`, reached
through an icall on `MEM32(edx+0x60)`) between a working and a stuck run:

- Rockwell (working, `recomp-rockwell-stability.log`): exactly 6 total
  calls, each returning a **different** result -- `00000001`, `0025CF01`,
  `0025DB01`, `0025E701`, `00274500`, `0025F301` -- then
  `handoff=committed` immediately after call 6.
- Area 42 / Union / Capitol (stuck): the poll reaches that same `00274500`
  and then returns it **unchanged** for dozens of calls in a row (the
  diagnostic itself throttles its own logging past 64, so the true count is
  higher, but draws-total staying frozen for another 150+ seconds confirms
  it never advances).

The `[DAH-BLOCK-CB]`/`[DAH-STREAM-CB]` package-loading callbacks immediately
before this (states 2, 3, 6, 7, 8, 15, 17, 11, 12, opening each site's
`resident.pkg`/`stream.pkg`/`discard.pkg`) run through in the *identical*
sequence for Rockwell and Area 42 -- ruling out the streaming pipeline
itself as the cause. Whatever `00274500` represents (likely a
resource/completion descriptor still mid-flight) simply never finishes
transitioning to the next state for these three sites specifically. Next
step for whoever continues this: trace the vtable call at
`MEM32(edx+0x60)` from `sub_000DB450` to find what it's actually polling
for, and check whether the shared trait among Area 42/Union/Capitol
(preceding_missions = 11/15/16 in `dah_console_level_routes`, vs. 1 and 4
for Rockwell/Santa -- see `src/dah_console_level.h`) is the real cause or a
coincidence.

Follow-up probe: `cptlboss` (preceding_missions=22, `recomp-cptlboss-stability.log`)
was also tested and shows the identical stall (`accepted=1`,
`switch_requested=1`, then the same `[DAH-FINISH-READY]` progression --
`00000001`, `0025CF01`, `0025DB01`, `00000000`, `0025E701`, then stuck
repeating `00274500`). Consistent with the preceding_missions theory but not
proof of it. Checked `sub_0008B230` (the `AddKey` helper each
preceding-mission key goes through, in `src/recomp/gen/recomp_0005.c`
line ~41705): it is an ordinary growable-vector push (compares a
size/capacity pair at `+0x3A50`/`+0x3A54` and calls a grow helper
`sub_0008B120` when full), not a fixed-size buffer that could silently
overflow. So a simple capacity-overflow theory is weakened; the actual
mechanism linking bulk key insertion (if that is even the real trigger) to
the stuck switch-readiness poll is still unknown. This needs either a real
debugger attached to the process, or the project's own Python
disassembler/recompiler (unavailable on this machine -- see README's
"Headless level testing" prerequisites) to trace forward from
`sub_000DB450`'s vtable call properly. Log-reading alone has reached
diminishing returns for this specific bug.

Same-day follow-up -- root cause found to be a genuine timing race, resolved
(as a practical workaround, not a real fix). Traced `sub_0005A4F0`'s two
numeric gates to their source: `MEM16(singleton+0x8D8)` is a count of
registrations into a 16-slot array (`+0x858`), incremented one at a time by
`sub_000D1910` (called from a per-object reset path, `sub_000CFE20`), and
readiness requires it to equal exactly `0x10` (16). Added a second opt-in
diagnostic under the same `DAH_FINISH_GATE_TRACE=1` gate: `[DAH-FINISH-GATE]`
in `recomp_0003.c` (logs the two gate values) and `[DAH-REG-8D8]`/
`[DAH-REG-854]` in `recomp_0009.c` (logs each registration call). A stuck
Union run (`recomp-union-gate-trace.log`) showed `field8D8=000F` (15) held
for 200+ consecutive polls -- one registration short of 16, forever.

Controlled experiment (all runs same build, only `DAH_FINISH_GATE_TRACE`
toggled):

| Run | Trace | Result |
|---|---|---|
| area42, union, capitol (first pass), cptlboss | off | stalled (4/4) |
| capitol (control re-run, same build as the trace runs below) | off | stalled |
| area42 (`recomp-area42-gate-trace.log`) | on | `handoff=committed` |
| union (`recomp-union-reg-trace.log`) -- `newcount=16` on the very first logged registration | on | `handoff=committed` |
| capitol (`recomp-capitol-traced.log`) | on | `handoff=committed` |

5 stalls with the diagnostic off, 3 successes with it on, one of those
3 immediately preceded by a same-build control stall with it off -- the only
variable was whether `fprintf`/`getenv` overhead executed on the hot
`sub_000DB450` polling path. That is conclusive for "this is a timing race,
not a deterministic bug": something that normally completes the 16th
`sub_000D1910` registration usually loses a race against the readiness poll
observing it, and a few hundred microseconds of added overhead per poll is
enough to let it win instead. Real Xbox hardware had fixed timing that never
exposed this interleaving; host recompilation timing does.

Practical workaround for now: launch with `DAH_FINISH_GATE_TRACE=1` to test
these four sites. Not a real fix -- the actual missing caller of
`sub_000D1910` (whatever normally supplies the 16th registration) still
needs to be found and given a proper wait/synchronization, which needs a
real debugger (or the project's Python tooling once available) to trace
forward from `sub_000CFE20`'s caller. Both diagnostics are left in place as
permanent opt-in aids for whoever picks this up.
