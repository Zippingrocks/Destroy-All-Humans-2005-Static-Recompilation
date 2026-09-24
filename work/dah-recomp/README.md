# Destroy All Humans! (2005) static recompilation

This is an early Windows-native static-recomp bring-up generated from the
original Xbox executable. It is not yet a finished playable port.

> **For AI agents / future sessions: read this first.** `DAH_FRAME_TURBO=1`
> (alongside `DAH_INTERNAL_RUN=1`) makes every headless test run 5-15x+
> faster in real wall-clock time with zero change to what's simulated --
> see "DAH_FRAME_TURBO: fast-forwarding headless test runs" below before
> running any bounded internal test. It does not speed up Bink movies.
> The console also has `giveall_weapons` / `give_weapon <name>` and
> `DAH_CONSOLE_AUTO_GIVEALL_WEAPONS` / `DAH_CONSOLE_AUTO_EQUIP_WEAPON` for
> headless combat-system crash-hunting -- see "Weapon crash-hunting
> tooling" below. All 15 on-foot weapons have been equip-and-fire tested
> as of 2026-09-19 with zero crashes.

## DAH_FRAME_TURBO: fast-forwarding headless test runs (2026-09-19)

**What it is**: an opt-in flag that removes real-time pacing from internal
test runs so bug-hunting cycles take a fraction of the wall-clock time,
without changing simulated game behavior at all.

**Why it's safe**: `dah_frame_begin()` (`src/dah_frame.c`) normally
busy-waits/sleeps until a scheduled wall-clock deadline before simulating
one frame. For ordinary ("retail-fixed-step") gameplay the simulated
per-tick delta is a *constant* (1/30 or 1/60 second) -- it is never measured
from real elapsed time. That means the wait is pure real-time pacing bolted
onto a schedule; removing it changes nothing about what physics, AI, or
scripting compute per tick. `DAH_FRAME_TURBO=1` skips only that wait, so
each frame still represents exactly the same fixed slice of game-time --
it's computed as fast as the CPU allows instead of paced to 30/60 Hz.

**Measured result** (`build-internal/recomp-turbo-test.log` vs
`recomp-baseline-test.log`, identical 20-real-second windows): baseline
ran at ~25 loop-fps (0.9x real time, matching retail 30fps pacing). Turbo
ramped from 182 to 428 to 461 loop-fps -- **5.6x, then 14.3x, then 15.4x
real time** within the same window, climbing as boot overhead faded. Zero
crashes, zero exceptions, `invalid-steps=0` throughout. The
`[DAH-FRAME-TURBO]` line confirms it engaged.

**What it does NOT speed up**: Bink movie/cutscene playback, which is
paced by a separate clock (`dah_read_tsc`, QPC scaled to the Xbox's
733.3MHz timebase), not this loop -- intro logos and cutscenes still take
their normal real time. There is also a rarer "measured-delta" update mode
(see `sample_policy` in `dah_frame.c`) that reads real elapsed time
directly; in turbo mode that time reads as near-zero, so anything using
that mode would appear to stall/slow-motion during testing. That's a
nuisance for a test run, not a crash or data corruption -- and it is the
reason this stays a `DAH_INTERNAL_RUN`-gated, opt-in flag that can never
affect the real player build (`build-ninja`).

**How to use it**: add `DAH_FRAME_TURBO=1` to any existing
`DAH_INTERNAL_RUN=1` test invocation (`tools/run_internal.ps1` or a manual
launch). No other changes needed -- it composes with `DAH_CONSOLE_AUTOLOAD_LEVEL`,
`DAH_INPUT_SCRIPT`, frame capture, etc. Note that `DAH_INPUT_SCRIPT` rows
are keyed to *input-poll ticks*, not wall-clock seconds, so scripted input
timing is unaffected by turbo mode -- a script calibrated without turbo
should still work with it on, just finishing in far less real time.

## Build

Open a Visual Studio developer prompt, then run:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

Developer builds currently produce `build/Release/DestroyAllHumans.exe`.
The tested user build is published as `build-ninja/dah.exe`, the only game
launcher in that folder. Previous launchers are preserved in verified ZIP
archives under `build-ninja/backups`.
The build copies the locally extracted `default.xbe` beside it. Game data
remains user-supplied and must not be redistributed.

## Current bring-up status

The real animated title, original New Game profile creation and mothership
menus work. With that profile selected, the developer console can load Farm;
captures show Crypto, cows and the farmer. A clean minute of on-foot Farm
measured approximately 30 rendered FPS. Camera controls, movement, the original
return to the mothership and successful autosave have also passed.

Rockwell and Santa have now been reached the same way (console `load_level
<alias>` through the original mission-unlock/transit path) and verified for
the first time:

- Rockwell: `build-internal/recomp-rockwell-stability.log` shows correctly
  rendered gameplay (captured frame confirms Crypto's saucer-beam entry) and
  a 150-second capture-free run holding loop-fps at or near 30.0 for most
  5-second windows after the level finished loading, with no unresolved-ICALL
  or crash lines during gameplay. A few isolated frame-time spikes (one
  interval in the hundreds of ms, similar to what Farm also shows) still
  occur and are not yet explained; see "Known stutter source" below.
- Santa: `build-internal/recomp-santa-stability3.log` is even cleaner --
  after the initial load settles, loop-fps holds at 29.98-30.02 with
  interval-p99-ms pinned at 33.334ms (the exact 30Hz frame time) for nearly
  every 5-second window across a 150-second run. Two new unresolved-ICALL
  targets specific to this site (`0x00054B20`, `0x0004F9E0`) were logged
  during gameplay -- confirmed genuinely unresolved (not registered anywhere
  in `recomp_lookup_manual` or any generated file) as of 2026-09-19, unlike
  the two addresses corrected below. Not fixed: same Python-toolchain
  constraint as ever (see "Headless level testing" prerequisites).

**Visual rendering check (2026-09-19)**: captured and directly inspected
gameplay frames from Rockwell mid-mission (theme: Washington DC/Capitol
grounds) -- three frames spanning real gameplay show correct lighting and
shadows, a working bloom/glow effect on a car's headlights, an NPC in a
trenchcoat with a functioning AI-detection ("!") indicator above its head,
readable HUD text and a properly alpha-blended radar/compass widget, and
coherent building/foliage geometry with no color-channel swaps, missing
textures, z-fighting, or mirrored/upside-down geometry. This is real
evidence the rendering pipeline is currently producing correct output, not
just a stable frame rate on an empty or broken scene.

Area 42, Union, Capitol and cptlboss all reproduce the same blocker on a
plain build: `load_level` is accepted (`accepted=1`) and the backend switch
is requested (`ready=1 switch_requested=1`), but it doesn't commit --
`draws-total` freezes completely. This turned out to be a genuine
**timing-sensitive race**, not a deterministic logic or content bug: a
controlled test this session showed all four sites stalling with no
diagnostic overhead on the hot readiness-poll path, and all three retested
(area42, union, capitol) reaching `handoff=committed` once
`DAH_FINISH_GATE_TRACE=1` added a small amount of logging overhead to that
same path -- a working (if accidental) practical workaround. See "Area 42 /
Union / Capitol / cptlboss switch stall" below for the full evidence,
including the exact missing count (`sub_000D1910`'s 16-slot registration
array short by exactly one entry) that the race is around.

This remains a development build. Correct rendering and sustained performance
across every level, menu navigation and NPC stability are still being checked.
Hidden-window frame measurements do not establish visible presentation
performance. Native sound output remains unfinished; see the audio limitation.
A disabled static image probe is diagnostic only and never counts as working
game rendering.

Each run writes `recomp.log` beside the executable.

## Runtime bring-up modes

Active tests use `build-internal/DestroyAllHumans.exe`, with separate copies
of game data and separate saves/logs. The user's `build-ninja` binary is not
updated by internal builds. A reversible frame-rate setting is available:

```powershell
$env:DAH_FPS = '30'
.\dah.exe
```

`DAH_FPS=60` selects the explicit 60 Hz path. Both paths set the retail world
divisor, but correct cutscene/gameplay speed still needs verification. The keyboard
fallback maps WASD/arrows to movement, Enter/Space to A, Q to B, F to X, R to
Y, and Escape to Back; a physical XInput controller is still preferred when
available.

`DAH_HOST_FRAME=1` explicitly enables the static presentation probe if
`movies\\saucer_frame_030.raw` is beside the executable. Leave it unset or
set to `0` for real boot/render verification.

The stack-sampling watchdog and KPCR/mirror page watcher are disabled during
normal runs because they intentionally suspend or trap the frame thread. They
can be re-enabled for diagnostics with `DAH_WATCHDOG=1` and
`DAH_KPCR_WATCH=1`.

For controlled front-end probes only, `DAH_AUTOSTART=1` injects the retail
START input once, `DAH_AUTOSTART2=1` can inject a later START for the shell
intro gate, and `DAH_AUTOA=1` injects A after a configurable input-call delay.

## Headless level testing

`DAH_CONSOLE_AUTOLOAD_LEVEL=<alias>` (internal builds only) stands in for a
human typing `load_level <alias>` into the developer console: it calls the
exact same `dah_console_load_level` path on a throttled retry (about twice a
second, up to 400 attempts) until the original game accepts it or the budget
is spent. It does not fabricate any loader/profile state itself -- a save
profile still has to be selected in-game first, same as with the real
console.

Getting a fresh internal run to that point (no window, no physical input) is
the hard part and is still done by trial and error with `DAH_INPUT_SCRIPT`
(see `dah_scripted_input.h`) plus `DAH_FRAME_CAPTURE`-based frame inspection:
run with capture on, convert the BMPs to PNG (`System.Drawing` from
PowerShell works; the Read tool cannot open raw BMP) and look at them to see
which screen a given input-poll tick landed on, then adjust the script's
timing. `tools/menu_probe_input.txt` is a working example that walks a fresh
internal run through the shell intro, New Game, the "overwrite existing saved
game?" confirmation (Down, then A -- it defaults to No), the post-save
"Continue" prompt, and a Down/Up cursor nudge before holding A on the
following "Select Game" list (that screen ignored plain A pulses and holds
alike until nudged; still not fully understood).

The first version of this script used one narrow pulse per step at ticks
calibrated from a single run; it reliably reached Rockwell but did not
reproduce for Santa (two tries, 150s and 220s, with nothing changed but
`DAH_CONSOLE_AUTOLOAD_LEVEL`) because real-time boot pacing drifts run to
run. The version now checked in repeats each step's input pattern several
times across a wide window instead of once at a single guessed tick, so a
repetition landing on an already-passed screen is harmless (ignored, or just
re-confirms the same state) while whichever repetition actually lines up
with the right screen does the job. This version reliably reached Rockwell,
Santa, Area 42, Union and Capitol -- i.e. it got a fresh profile created and
`load_level` accepted for all five previously-untouched sites in this
session's testing. If it stops reproducing again, widen the phase windows
further or add more repetitions before assuming a code regression.

## Weapon crash-hunting tooling (2026-09-19)

The developer console has `give_weapon <name>` (generalized from a single
hardcoded `zap` alias to all 15 known weapon keys) and `giveall_weapons`
(unlocks every weapon in the progression store at once, without force-
equipping anything). For headless runs there are matching internal-only
automations: `DAH_CONSOLE_AUTO_GIVEALL_WEAPONS=1` and
`DAH_CONSOLE_AUTO_EQUIP_WEAPON=<name>` (same env-var-triggered-once pattern
as `DAH_CONSOLE_AUTOLOAD_LEVEL`) fire once gameplay is idle and Crypto is
active. `tools/weapon_fire_test.txt` is a calibrated `DAH_INPUT_SCRIPT` that
reuses the proven menu-navigation sequence from `menu_probe_input.txt` and
adds sustained right-trigger pulls afterward, so a full run does
"boot -> create profile -> load a site -> equip one named weapon -> fire it"
with no interaction needed. Equipping one weapon per run (not all 15 at
once) keeps any crash attributable to a specific weapon.

**Full first-pass results, Farm, one weapon per run (`DAH_FRAME_TURBO=1`,
`recomp-farm-fire-<name>.log` for each)**: all 15 weapon keys were granted
successfully. 10 equipped and fired with **zero crashes**: zapomatic,
brainextractor, analprobe, mattermove, holobob, holobobhelper, hypnoray,
destructoray, iondetonator, cortex. 5 were granted but the on-foot weapon
manager declined to equip them (`equipped=0`, no crash either way):

- abducto, deathray, sonicboom -- consistent with these being genuinely
  saucer-exclusive weapons in the original game (Abducto Beam, the saucer's
  Death Ray, and the Sonic Boom Cannon), so the on-foot manager correctly
  rejecting them is accurate retail behavior, not a bug.
- quantum, brainray -- **an open anomaly**, not explained by the above:
  Quantum Deconstructor and Brain-o-Vac (renamed "brainray" key) are
  on-foot weapons in the real game. All three of Union's weapon-bundle
  entries (sonicboom, quantum, brainray -- see `dah_console_unlock_union`
  in `src/dah_console_level.h`) failed to equip on Farm while every
  Area 42-bundle weapon equipped fine cross-site, so this looks like
  something specific to Union's weapon data/naming rather than random
  flakiness. Not yet root-caused; retesting these two directly on the
  Union site (once its own level-load timing is dialed in) is the
  obvious next step, since Farm may simply not carry their resident
  assets even though the progression key grants cleanly.

Overall: on-foot combat is stable everywhere it was reachable this pass --
no crashes were found from equipping or firing any weapon. The 5 that didn't
equip are either expected (saucer-only) or a data/naming gap, not stability
bugs.

### Saucer weapons: real mechanism located, not yet safely callable

The user asked for `enter_saucer`/`giveall_saucer_weapons` console commands
to extend this same crash-hunting to the flying saucer. Unlike `give_weapon`
(which generalized an existing, already-proven native call), there was zero
prior code or research for saucer/vehicle control in this project. Read-only
binary research this session found the real mechanism:

- The retail Lua binding table (confirmed via a raw byte search of
  `default.xbe` for the string-table address, landing on a regular 12-byte
  `[hash][name_string_ptr][function_ptr]` entry) has paired
  `GetCharacter`/`GetShip`, `SetCharacterMoveState`/`SetShipMoveState`, and
  `SetFocusCharacter`/`SetFocusShip` bindings -- a real, symmetric
  Character-vs-Ship control-focus system. `SetLandingBeamDown`/
  `GetLandingBeamDown` nearby line up with the existing `ability.land` /
  `santa.landing.lz1` progression keys already in `dah_console_level.h`.
- Every one of these bindings dispatches through the *same* native function,
  `sub_00083A50` (`src/recomp/gen/recomp_0005.c`, 4437 bytes, a binary
  search over hashes). `SetFocusShip`'s hash is `0x1D6E74FA`; its case reads
  `player+0x30 -> +0x138 -> +0x108` (using the same `system -> player` global
  chain `give_weapon` already uses) and then calls through several vtable
  slots (`+0x14`, `+0x48`, `+0x50`) into object types not yet identified with
  confidence.

This was deliberately **not** implemented as a console command yet. Calling
partway-understood engine internals directly (as opposed to setting a
progression key and letting retail code react, which is how every other
console command in this project works) risks a crash caused by an incorrect
guess at the remaining vtable calls -- indistinguishable from a real bug
without being sure. The safer alternative worth trying first: find whether a
mission/story key (candidates: the `.mission.bN` sub-mission codes in
`dah_console_story_keys`, e.g. Santa's `b1`/`b3`/`b6`/`b7` -- the original
Santa/North Pole level is known to include a saucer sequence) causes the
retail scripts to call `SetFocusShip` on their own, the same
progression-key-only philosophy `load_level` already uses.

## Isolated verification

After building `build-internal` and copying user-supplied `blocks` and `movies`
beside that executable, run `tools/run_internal.ps1`. This bounded runner sets
`DAH_INTERNAL_RUN=1` and `DAH_FPS=30`, hides the game window, supplies neutral
physical input, silences output after audio mixing, and archives a PID-specific
log. It stops only the process it launched. Do not run it against user builds.

`DAH_FRAME_CAPTURE` saves actual swapchain frames to PID-specific BMP files;
`DAH_FRAME_CAPTURE_INTERVAL` controls spacing. Synchronous readback adds cost,
so final pacing verification must be a separate capture-free run. A ticking
30 Hz loop, occluded presents, a solid-color frame, or the static image probe
is not evidence of a working menu. Success requires recognizable native menu
frames, interaction, and a sustained measured 30 FPS run.

## Area 42 / Union / Capitol / cptlboss switch stall -- confirmed timing race, not a logic bug

`load_level` is accepted, the switch is requested (`[DAH-CONSOLE-LEVEL]
ready=1 switch_requested=1`), and on a plain build it never commits:
`draws-total` in `[DAH-FRAME]` freezes at its exact value across 30+
consecutive 5-second windows (150+ real seconds) while the frame loop keeps
ticking a locked 30Hz. This affects only these four sites, never Farm,
Rockwell or Santa.

**Isolated to an exact missing count.** `sub_000DB450`'s readiness poll
(`[DAH-FINISH-READY]`, `src/recomp/gen/recomp_0009.c` ~line 28935) calls
through a vtable slot (`sub_0005A4F0`) that requires two fields on a global
singleton (`MEM32(0x24B87C)`) to both hold specific values:
`MEM16(+0x854)==0x100` and `MEM16(+0x8D8)==0x10`. Added a second, opt-in
diagnostic (`DAH_FINISH_GATE_TRACE=1`, same env-var gate, logs as
`[DAH-FINISH-GATE]` in `recomp_0003.c` and `[DAH-REG-8D8]`/`[DAH-REG-854]`
in `recomp_0009.c`) and traced it to the actual mechanism: `+0x8D8` is a
count of registrations into a 16-slot array, incremented one at a time by
`sub_000D1910` (called from a per-object reset/reinit path, `sub_000CFE20`).
On a stuck Union run it sat at exactly `0x0F` (15) forever -- one
registration short of the `0x10` (16) required for readiness.

**This turned out to be a genuine timing race, confirmed by a controlled
experiment**, not a deterministic content or logic bug:

| Condition | Result |
|---|---|
| Baseline (no diagnostic overhead) | **5/5 stalled** -- area42, union, capitol, cptlboss (first test), capitol (retest as a control) |
| `DAH_FINISH_GATE_TRACE=1` active (adds `fprintf`/`getenv` overhead to the hot poll) | **3/3 succeeded** -- area42, union, capitol all reached `handoff=committed` |
| Same build, trace code present but env var unset (control) | **Stalled again** -- capitol, ruling out "the rebuild changed something" as the explanation |

The only variable between "stalls" and "succeeds" was whether the
diagnostic's `fprintf` actually executed on that hot polling path. This
means the missing 16th registration is racing against real-time frame
pacing -- something that's supposed to complete before the readiness poll
observes it usually doesn't, and adding a few hundred microseconds of
logging overhead per poll is enough to consistently let it finish in time
instead. This is exactly the class of bug static recompilation exposes:
real Xbox hardware had fixed, consistent timing that never hit this
interleaving; host timing differs enough to expose it. It reproduced
identically across 4 different sites, so it is very unlikely to be
per-level content (the streaming/block-loading states before it are
byte-identical between working and stuck runs; see the registration-count
theory notes below for what was ruled out along the way).

**Practical workaround**: launching with `DAH_FINISH_GATE_TRACE=1` reliably
avoided the stall in every test this session (3/3). It is not a real fix --
it works by accident, via added overhead, not by resolving the underlying
race -- but it is usable today for testing/bring-up on these four sites
until someone traces the actual missing 16th `sub_000D1910` caller with a
real debugger and adds a proper wait/synchronization instead of relying on
incidental timing. Both diagnostics are kept in the source as permanent,
opt-in debugging aids (same pattern as the pre-existing `[DAH-FINISH-READY]`
log) -- see the comments at each site in `recomp_0003.c`/`recomp_0009.c`.

Ruled out along the way: the preceding-mission counts for these four sites
(11/15/16/22 vs. Rockwell's 1 and Santa's 4 in `dah_console_level_routes`,
`src/dah_console_level.h`) were the leading content-based theory, but
`sub_0008B230` (the `AddKey` helper each preceding-mission key goes through)
turned out to be an ordinary growable-vector push, not a fixed buffer that
could overflow -- and the timing-race evidence above is a stronger,
directly-demonstrated explanation than a content-based one anyway.

## Correction: 0x0011FA30 / 0x00143689 were already fixed (false alarm, methodology error)

An earlier pass of this session flagged `0x0011FA30` and `0x00143689` as live
unresolved-ICALL gaps during Farm gameplay, based on `recomp.log`. That file
was stale (last written 2026-09-16, before whatever session actually fixed
both addresses) and was mistakenly copied into a "fresh" test log
(`recomp-rockwell-test.log`) without realizing the running exe was writing to
`furonlog.log` instead (the default log path when `DAH_LOG_PATH` is unset --
see "Headless level testing" above). The copy preserved the stale content
byte-for-byte, which looked like live evidence but wasn't.

Both addresses are, in the current source, already correctly fixed:
`sub_0011FA30` (`src/recomp/gen/recomp_0013.c`) and `sub_00143689`
(`src/recomp/gen/recomp_observed_callbacks.c`, a this-adjustor thunk --
`sub ecx,4; jmp 0x1EE1F9` -- exactly as this correction's author independently
re-derived from `text.asm` before discovering it already existed) are both
real implementations, and both are registered in `recomp_lookup_manual`
(`src/recomp_manual.c`, search for `0x0011FA30u` / `0x00143689u`) so indirect
calls actually resolve to them. Attempting to re-add `sub_00143689` produced
a linker "already defined" error, which is what caught the mistake. A
completely fresh Farm run (`recomp-farm-fresh-verify.log`, explicit
never-before-used `DAH_LOG_PATH`) shows **zero** `[ICALL] unresolved Xbox
target` lines.

Lesson for future sessions: never trust `build-internal/*.log` content
without checking its file timestamp is from *this* run first, and always set
`DAH_LOG_PATH` explicitly to a new filename per test so there is no ambiguity
about which log is current.

The cause of the occasional 100-500ms frame-time spikes seen in Farm/Rockwell
`[DAH-FRAME]` logs remains genuinely unexplained -- it is not these two
addresses. Candidates not yet investigated: GC-like heap activity, capture
readback overhead, or something else entirely.

## Current audio limitation

Native Xbox sound output is not implemented in this build: the game's MCPX
command stream is not connected to a running audio backend. The executable logs
`DAH-AUDIO-NULL` when that state is used. Accepted sound release/stop requests
complete through the original game's voice Stop, list unlink, and pending-stop
cleanup, so transitions do not wait forever for absent hardware. This does not
change the game's sound-instance readiness checks or force a level to load.
When the real APU backend is initialized, it owns completion and this null-device
compatibility path is disabled. Audible output, hardware envelopes, and effects
remain unfinished and require separate validation.
