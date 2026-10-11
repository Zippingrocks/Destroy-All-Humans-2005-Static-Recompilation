# Turnipseed Farm reference checkpoints

This is a source-derived capture plan. No new xemu process operation, controller
input, or Farm capture was performed while preparing it. Establish the actual
reference loop numbers before claiming exact loading or gameplay timing.

## Route and anchor

From the settled mothership, return from Pox with state-gated B pulses, select
hub slot2 Hangar, and enter with A. The verified reference Hangar 024 displays
Turnipseed Farm / Destination Earth! and Invade! A. Capture this settled state,
then send one short A pulse and neutralize it. Observe the resulting state;
if a mission-selection page appears, capture it and accept Destination Earth!
as a separate event. Do not hold A through loading or the arrival sequence.

The source's retail mission-load recipe identifies site `farm`, mission `t1`,
backend path `blocks\sites\farm`, and warmed group `t1_entry_xbox`
(`src/dah_console_level.h`). It publishes `mission.forcelaunch` before unlock
keys, then requests the backend and warms the group. Use actual menu input for
the parity run; the console/autoload path is useful source evidence but does not
establish identical menu transitions or loading timing.

Define relative frame zero as the retail loop that accepts the launch input.
Also retain input delivery/poll loop and the last complete Hangar frame so an
input-boundary off-by-one cannot masquerade as a rendering delay.

## Capture phases

| Phase | State evidence | Pixel/timing evidence |
| --- | --- | --- |
| Selected destination | Settled `navicom`, Farm / Destination Earth! shown | Last complete Hangar frame |
| Launch accepted | First resulting UI/progress/backend change after the A pulse | First fade, black frame, or transition draw; preserve every frame in this short interval |
| Farm queued | Pending backend path becomes `blocks\sites\farm` | Last outgoing frame and first loading image |
| Backend loading | Pending backend state changes; current/pending identities and paths retained | Loading animation, text, fades, and their frame durations |
| Backend committed | Current path is Farm, pending is zero, current backend state is 22 | Does reference still show loading, black, arrival movie, or rendered world? Record rather than assume |
| World/player ready | Valid world, player/actor and renderer pointers | First complete Farm world frame, camera and Crypto visibility |
| Arrival sequence | Movie and UI state, camera/actor transform progression | First and last arrival/cutscene frames; do not skip the reference pass |
| First controllable frame | Tutorial/control state plus accepted small movement/camera input after arrival | First response frame, initial player position, camera, HUD, objective/Pox prompt |
| Settled gameplay | Same mission and tutorial state, neutral input | Several consecutive frames and then a short identical movement/camera pulse |

Backend state 22 is used by existing native code as ready/committed. It is not
proof that the original game's first controllable or presented frame has arrived.
Do not merge the commit, movie completion, first world draw, and control release
milestones into one checkpoint.

## Read-only fields already verified locally

- Retail loop: `0x25B1DC`.
- Driver: `0x25B1D0`; current backend at +0x4A28, pending at +0x4A2C.
- Each valid backend: state +0x10, path +0x50C (bounded string).
- Renderer: `[0x250E60]`; refresh flag +0x238, divisor +0x27C, interval +0x2C8.
- World: `[0x286768]`, expected vtable `0x235780`; simulation count +0x08,
  elapsed seconds bits +0x0C, step bits +0x10, paused/realtime bytes
  +0x303C/+0x303D. Update/getter evidence: `00105280`, `00115388`, `00115208`.
- RNG DWORD `0x278A58`, consumed by `000D4270/000D4290/000D42C0`; camera-update
  byte `0x258B48`, exposed by `00084B01`.
- Control system `[0x25FCEC]`, player at system+0x38, actor at player+0x38.
  Existing native Farm readiness validates actor vtable `0x22C9F8`; position
  +0x14C is documented by the existing actor-position diagnostics.
- Player focus/ship/Crypto pointers are +0x30/+0x34/+0x38; Crypto position is
  +0x14C/+0x150/+0x154. Character movement state is `[[actor+0x130]+0x48]`
  (`000817C0`). The same movement object exposes angular velocity +0x14,
  normalized heading +0x18, smoothed heading +0x2AC, and target heading +0x2B0;
  stores are proved by `00054200`. Presence alone does not establish that input
  is accepted.
- Camera node `[renderer+0xEC]`: parent +0x08, local position +0x20..+0x28,
  quaternion +0x40..+0x4C, world matrix +0x50..+0x8C. Renderer view position
  +0x80..+0x88 and forward vector +0x70..+0x78 match existing pose diagnostics.
- Existing parity logger/decoder provides movie state and active UI names.
  The optional input-adapter state observer now also provides pending-backend
  name/state; heap addresses themselves are not parity keys.

Only dereference validated pointers. Record camera orientation/position only
through verified fields, not guesses from nearby floats. Retain all dimensions,
format, gamma-stage, and frame association metadata with each image.

Native `dah_parity_state.h` and the paused-RAM decoder now emit these bounded
Farm fields with per-object `Complete` flags. Unavailable fields are JSON null;
float arrays preserve original bits. Addresses are evidence, not cross-engine
identities. Native `observer.presentationHeld` is explicitly a host observation,
not an original-game field. Native traces sample at `000DAD3C` after the retail
loop; the live xemu observer samples at `XInputGetState` before returning input.
These phases must be reconciled before comparing ticks or RNG state as if they
were the same instant. Never write an RNG seed or transform to make rows match.

## Native presentation hold needs separate accounting

As of 2026-09-27, `src/dah_frame.c:dah_farm_presentation_hold` is disabled by
default. The original title card and saved-backbuffer path own presentation.
The old hold can be reproduced only with both `DAH_INTERNAL_RUN=1` and
`DAH_FARM_PRESENTATION_HOLD=1`. In that diagnostic mode it holds the last loading
image whenever Farm is current or pending. After backend state 22, a valid
actor, camera/world, and a real draw, it waits for at least 12 warm frames,
checks visual content every third warm frame, requires four blank samples
before accepting a later nonblank frame, and has a 360-warm-frame fallback.
Simulation continues while this native-only gate holds presentation.

Log hold entry/release and its reason alongside the original backend/movie/UI
milestones. This heuristic can delay or conceal original frame transitions;
it must be measured against xemu before being treated as accurate. Avoid tuning
its counts against a single screenshot. The exact native RenderDoc hook and
swapchain BMP readback can reveal both underlying rendered output and the held
presented image at the same loop.

For xemu, current savevm-then-stop images still lack an exact render-frame latch.
Use those as state/visual context while retaining the limitation. A stable,
stopped guest plus a properly initialized future RenderDoc reference run is a
possible final-display path, but guest/GPU completion alignment must still be
verified. Loading-time wall-clock comparisons must exclude debugger pauses and
capture/readback overhead.

## Optional state sampling on the existing input adapter

```powershell
node tools/parity/xemu_input_replay.mjs --port PORT --script ROUTE.txt --out NEW-input.json --relative --seconds 180 --state-out NEW-state.jsonl --state-interval 5
```

The optional JSONL is opened exclusively before connecting; existing files and
the same path as `--out` are rejected. The adapter uses its existing RSP
connection and XInputGetState breakpoint, before writing the synthetic pad
result. There is no second debugger client, new breakpoint, or state write.
One row is emitted per observed retail loop divisible by the interval, with
30,000 rows maximum. Each Farm-state row is limited to 29 memory reads and 2,048 bytes
(the actual settled Hangar024 sample used 11 reads/370 bytes).

Rows include the phase/address, loop, relative frame, backend and pending
backend names/states, world elapsed/step bit patterns and tick, paused/realtime
bytes, renderer cadence fields, RNG state, and optional movie header. Missing
objects have zero pointers, null dependent values, and entries in `absent`.
Unreadable/invalid values stay null with explicit reasons in `unknown`, and
`complete` is false. Transport timeout/disconnection aborts rather than treating
a stale debugger reply as a successful memory read.

Every row declares `timingPerturbed: true`. This sampling phase is
`XInputGetState` at 0x2216B5, before controller-result delivery; the native parity
trace currently labels the later 0xDAD3C frame boundary. Retain those phase tags
and establish the appropriate before/after relationship instead of comparing
all fields at equal loop numbers indiscriminately. RNG and animation/time
fields can legitimately advance between those two boundaries.

Validation: syntax check, four fixture tests for high-address reads, explicit
absence, pointer/class rejection, missing memory, and fatal transport errors;
plus decoding the real saved Hangar024 RAM through its page tables. No live
xemu connection was used during these checks.

## Optional in-engine cinematic timeline

Add `--cinematic-state` to an input replay that already supplies `--state-out`.
This reads the retail in-engine cinematic manager after the Farm observer on
the same stopped RSP connection, before returning controller input. It adds no
breakpoints and never changes the cinematic clock. Native parity JSONL and the
paused-RAM decoder include the same fields automatically. These timelines are
distinct from the existing Bink movie header.

The manager is `[0x286784]`. Constructor `00112D80` establishes vtable
`0x23611C`; gameplay construction at `0005CD65` installs derived vtable
`0x22A6B8` with the same list layout. Both are validated. The sentinel is
manager+8, declared count manager+0x18, node-next +0, previous +4, movie +8;
update `00112BE0` confirms this traversal. Movie constructor `00112280` sets
vtable `0x236100`; derived construction at `0005910E` installs `0x229FB4`
after calling that base constructor, retaining the same timeline prefix.
Resource identity hash +0x20 and duration bits +0x68 are
loaded at `00112678`; elapsed bits +0x6C, flags +0x70 and lifecycle +0x74 are
proved by `00111CE0`, `00111EE0`, and `00111F90`. Lifecycle values are 0 loading,
1 ready, 2 playing, 3 finished. Start zeros elapsed; update adds its supplied
delta and clamps to duration; the manager removes finished movies on update.

Rows add `cinematicManager`, `cinematicManagerVtable`,
`cinematicDeclaredCount`, and `cinematics`, an ordered array of objects with
`node`, `object`, `vtable`, `nameHash`, `durationBits`, `elapsedBits`, `flags`,
`state`, and `complete`. `cinematicComplete` and `cinematicReason` distinguish
a verified empty list from unavailable, truncated or malformed data. Pointer
values are evidence only; pair sequences using the resource hash, lifecycle
and exact elapsed bits. Do not interpret pre-ready raw elapsed storage as an
active clock, or assume equal world ticks imply equal cinematic elapsed time.

Each optional cinematic sample has its own hard limit of 16 list entries,
34 reads and 2,144 bytes; a single valid movie costs 4 reads and 164 bytes, an
empty valid manager 2 reads and 32 bytes. The Farm sampler retains its original
29-read/2,048-byte budget, so the combined maximum is 63 reads/4,192 bytes.
`cinematicMemoryReads`/`cinematicMemoryBytes` report the added work; the input
trace records the opt-in flag and additional budget. All rows remain timing
perturbed: the extra stops/read time cannot establish original wall-clock
loading or cinematic pacing, especially when the engine uses measured delta.

Validation: `node --test tools/parity/test_xemu_cinematic_state.mjs` checks
exact bit preservation, both manager classes, malformed lists and classes,
the hard bounds, lifecycle values, transport failures and CLI validation.
`tools/parity/test_cinematic_state_consistency.ps1` compiles the actual C
observer and compares C/Python/JS output across 36 fixtures in low and high
guest-address windows. Offline Farm028 RAM has derived manager `0x22A6B8`,
count zero and a complete empty list. No game process is launched or accessed
by these tests.
