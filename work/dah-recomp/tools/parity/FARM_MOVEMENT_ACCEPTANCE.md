# Farm movement acceptance after the heading fix

Use `farm_entry_four_direction_probe.txt` with fresh private profiles through
the existing normal Hangar Invade route. It skips the already-tested New Game
intro and preserves Farm's own titlecard and cinematic. Run both processes
hidden, with physical input disabled, and retain the same profile/settings and
input history. This probe uses no teleport, control-release override, RNG
write, or transform write.

| Pulse | First frame | Last held frame | Logical LX | Logical LY | Settle checkpoint |
| --- | ---: | ---: | ---: | ---: | ---: |
| Forward | 7200 | 7214 | 0 | 32767 | 7290 |
| Backward | 7320 | 7334 | 0 | -32768 | 7410 |
| Left | 7440 | 7454 | -32768 | 0 | 7530 |
| Right | 7560 | 7574 | 32767 | 0 | 7640 |

There are 105 neutral frames between pulses. Capture through at least 7640;
the last checkpoint includes 65 neutral frames. The script format is the same
as the established forward-only probe. Unspecified frames remain neutral.

## Preconditions and comparison order

1. Confirm Farm backend state 22, complete actor/camera observations, ended
   in-engine cinematic, `worldRealtime == 0`, and the retail main input section
   restored before 7200. An actor pointer or movement state 20 alone does not
   prove control ownership. Original `siteMovement.Update` asks
   `gui.input.GetAccess('Game')` and sends zero movement when access is absent.
2. Leave `DAH_PLAYER_MOVEMENT_COMPAT` unset for the release-candidate run. The
   old velocity/facing workaround is now disabled unless an internal run opts
   in explicitly; setting it to `0` remains equivalent but is less direct proof
   of the shipped default. Do not change it midway through a pulse.
   `DAH_MOVEMENT_PRECOMPAT_TRACE=1` with `DAH_INTERNAL_RUN=1` supplies bounded
   extra observations at 7198..7225 only. Later pulses use the regular observer.
3. Compare the actual controller result delivered to retail, including stick
   signs, magnitudes, durations, and neutral release. The same script text is
   insufficient evidence. The former unconditional native LX negation has been
   removed; verify the final delivered values to prove both lateral signs pass
   unchanged. Classify a mismatch as an input-delivery failure before judging
   left/right movement. Do not hide it by changing script signs or reference input.
4. Establish a consistent phase relationship between native `000DAD3C` rows
   and reference `XInputGetState` rows using the delivered-input event, movement
   state transition, first velocity change, and first position change. Record
   any constant phase offset; do not select a separate best shift for each
   metric. Preserve the original loop/phase tags. If one-frame ambiguity remains,
   report it rather than claiming exact timing.
5. For each pulse retain pre-input state, every transient frame, release, and
   the settle checkpoint. Compare raw actor position, object quaternion, scene
   node quaternion/basis, physics velocity, camera basis, and movement state.
   A differing transient trajectory is a failure even when the final distance
   is similar. Float-bit equality is the strongest result; report numerical
   differences without silently introducing a tolerance for acceptance.
6. Compare each later pulse only after its entire preceding trajectory passes.
   Initial posture matters: backward and sideways turns legitimately begin
   from the previous facing. This sequential test must match the reference's
   same history; it does not require forward/back displacement to cancel or
   every direction to travel the same distance. If the first mismatch occurs,
   use it as the next diagnostic boundary before interpreting later movement.

Debugger stops perturb measured-time cinematic pacing. Gameplay uses the
retail fixed step, but the input adapter's phase and sampling overhead must
still be recorded. This movement probe cannot establish loading/video timing
or pixel accuracy by itself.

## Current four-direction result

Reference 006 and native 021 contain every loop from 7198 through 7640 using
the same scripted input schedule. The native input log confirms the final
retail-facing values: forward `(0,32767)`, backward `(0,-32768)`, left
`(-32768,0)`, and right `(32767,0)`, followed by neutral at each release.
Actor and actor-object positions are bit-exact for all 443 rows. Movement state,
world fixed step, pause/realtime state, camera-update state, camera quaternion,
and both endpoint actor quaternions are exact.

Actor/object and scene quaternions differ in 12 intermediate rows beginning at
loop 7322 during the backward pulse, with maximum component error
`3.725290298461914e-7`; the scene basis maximum is `7.152557373046875e-7`.
Physics velocity is exact in 417/443 rows with maximum error
`3.5762786865234375e-6`. Camera local position is exact in 440/443 rows and
camera world matrix in 298/443 rows, both with maximum positional difference
`6.103515625e-5`. The repeat paired capture records movement +0x14, +0x18,
+0x2AC, and +0x2B0. All four are bit-identical at the first quaternion mismatch
on loop 7322; angular velocity and the heading fields first differ on loop
7323, after the rotation has already diverged. A third paired capture proves
the inner physics quaternion at `[[actor+0x110]+0x0C]+0x38` also first differs
on loop 7322 (`426/443` bit-exact rows, maximum component error
`3.5762786865234375e-7`). This places the cause in physics rotation
integration/normalization, before actor-object and scene propagation. Raw
comparisons: `build-parity-xemu/four-ref006-vs-native021.json`,
`build-parity-xemu/four-ref007-vs-native022.json`, and
`build-parity-xemu/four-ref008-vs-native023.json`.

Reference 012 and native 034 repeat the same complete route after restoring
the guest x87 control-word precision. Actor and actor-object position, actor
and scene quaternions, scene matrices, and inner physics quaternions now match
bit for bit in all 443 rows. The 14 focused movement-constructor angles and 14
physics-setter input/normalized pairs around loops 7316–7329 also match bit for
bit. Physics velocity is exact in 426/443 rows, camera local and world state in
440/443, movement heading in 443/443, and angular velocity in 442/443. Raw
comparisons: `build-parity-xemu/constructor-ref012-vs-native033.json`,
`build-parity-xemu/physics-ref012-vs-native033.json`, and
`build-parity-xemu/four-ref012-vs-native034.json`.

The reference traces record x87 control word `0x003F`, selecting PC=00
(24-bit significand). The old runtime retained host-double intermediates. The
runtime helper and lifter now round arithmetic and square-root results using
the guest PC/RC fields; the generated angle smoother and quaternion normalizer
use the same rule. This removes the former loop-7322 rotation divergence at its
source rather than rounding stored quaternions after the fact.

A second staged trace found the remaining velocity error after direction
calculation and during heading update. The vector was already different before
physics setter `0012BB30`; helper `00053FF0` still retained host-double x87
intermediates. With guest precision applied there, reference 012 versus native
040 is bit-exact in all 443 rows for physics velocity, angular velocity,
movement heading, player position, every actor/scene orientation and matrix,
and the inner physics quaternion. The staged movement-source and setter traces
are also exact in every compared event. Three steering rows inherited from
before loop 7198 and three camera-local/world rows remain. Raw reports:
`build-parity-xemu/velocity-stage-ref012-vs-native039.json`,
`build-parity-xemu/velocity-source-ref012-vs-native039.json`,
`build-parity-xemu/velocity-ref012-vs-native039.json`, and
`build-parity-xemu/four-ref012-vs-native040.json`.

## Source evidence for the recovered fault

In `src/recomp/gen/recomp_0009.c`, retail `000D4520` computes an acos
approximation. Original bytes at `000D4621` compare zero against the input at
`[esp+0x14]`; `000D463E` pops ESI; `000D463F` branches on the earlier flags.
SSE arithmetic and POP preserve those flags. The prior C translation deferred
the comparison until after POP, reading the caller's next stack word instead
of the original sign operand. The fix records COMISS flags at their original
position and tests saved CF/ZF, retaining unordered behavior.

Heading function `000D4680(x,y)` uses this acos result, so the defect reflects
negative X headings when the adjacent stack word is positive. The focused
actual-function regression compiles current generated `000D4170`, `000D4520`,
and `000D4680`, plus a shadow copy with the old branch for a negative control.
It passes 414 checks, reproduces 35 old stack-dependent failures, and measures
at most 0.002003708 radians of the existing retail approximation error.
For x=-0.94,y=-0.34, fixed heading is -2.79483485 versus old -0.346757799:
their cosines are -0.940479516 and +0.940479517 respectively.

Run `python tools/parity/test_guest_heading_math.py` from a Visual Studio
developer environment; `--cc` accepts an explicit compiler path. The test
extracts actual production functions and uses the real runtime header, loads
original XBE constants, and reconstructs only the startup lookup-table data
using retail `000D4390`'s formula. It runs no game or emulator process.

## Guest boundaries used to recover the mismatch

- Original `site_movement.lua` on-foot dispatch is
  `player.Move(ref, LX, 0, LY, jump, 0, 0)`, without a sign inversion or a
  one-third speed factor. The script is preserved in the reference RAM capture
  at physical offset `0x03A9D7CC` (Lua function line 48).
- `player.Move` CRC `0x3381FB36` dispatches through `00083A50:00083EC0` to
  `000818B0`, then `[actor+0x130]` vtable slot+0x50 (`00054680` for Crypto).
  `00054680` calls direction calculation `00054060`, heading/velocity update
  `00054200`, then `00054590`.
- `000D4680` entry arguments are x=`[esp+4]`, y=`[esp+8]`. Return `001118E7`
  belongs to camera-heading calculation; return `00054351` belongs to desired
  movement heading. Read at those boundaries before considering another fix.
- Movement +0x18 is normalized heading; +0x14 is angular velocity; +0x2AC and
  +0x2B0 are smoothed and target heading. `00054200:0005443C..00054477` and
  `000543B4` prove the stores.
- Actor object `[actor+0x28]` quaternion is +0x38..+0x44. Scene node
  `[actor+0x4A0]` quaternion is +0x40..+0x4C, with basis beginning +0x50.
  Physics body `[actor+0x110]` vtable slot+0x90 must be `0012BB30` before
  interpreting +0x84..+0x8C as linear velocity. Retail Crypto body vtable
  `0x2376E8` inherits that setter. Its rotation delegates through inner body
  +0x0C, vtable `0x237968`; `00129100` writes inner quaternion +0x38..+0x44.
