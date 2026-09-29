# Controller and keyboard acceptance gate (mandatory)

Status: **FAILED — physical play confirmed the current controls are unacceptable**

Historical candidate SHA-256 (evidence below predates the 2026-09-27 fixes):
`B580678163451F84C3E5FCF2B808BB1021F336CC181D545B688F389F28FC4DAE`

Automated evidence on that exact executable:

- Eight cardinal/diagonal route: `build-internal/eight-direction-optimized-hash.log`.
  All eight displacement vectors are distinct; facing/travel dot products are
  `0.9911` through `1.0000`.
- Retail Camera Pitch Normal and four-way camera:
  `build-internal/camera-normal-optimized-hash.log`. Settings word bit 0 is
  clear; pitch reaches both signs and returns to neutral; both yaw directions
  are delivered.
- Retail Camera Pitch Inverted:
  `build-internal/camera-inverted-optimized-hash.log`. The retail menu changes
  settings word bit 0 to one; identical pitch input reverses sign, reaches both
  sides, and returns to neutral.
- Real-time endurance: `build-internal/forward-two-minute-no-profile-realtime.log`.
  120 movement samples from poll 2580 through 6150; minimum inter-sample
  displacement `0.799992`; zero stationary samples. Across 24 five-second
  pacing windows: `29.982` minimum, `30.000` average, `30.024` maximum, with
  zero late frames, invalid simulation steps, failed presents, or occlusion.

This evidence satisfies the internal scripted portion only. Requirements 6
and 7 require visible physical-device evidence on this exact hash.

- Physical controller: `build-internal/physical-controller-visible.log`.
  Windows XInput port 0 was connected. The visible, unscripted player build
  captured START/D-pad/A and every left-stick quadrant: F=216, B=20, L=22,
  R=35, FL=76, FR=139, BL=14, BR=24 thresholded host packets. Thirty-eight
  world-motion samples were captured, along with right-stick Up=3, Down=2,
  Left=40, Right=70 cardinal samples and reversible pitch output. Requirement
  7 is satisfied on the current hash.
- Physical keyboard: `build-internal/physical-keyboard-visible-final.log`.
  The visible, unscripted player build captured W, A, S, D and all four
  diagonals at the intended cardinal/radial magnitudes. World-motion samples
  cover every resulting logical-stick quadrant and show Crypto changing both
  travel direction and facing with the input. Gameplay pacing after entry was
  normally `29.966` through `30.015` FPS with zero failed presents or invalid
  simulation steps. The run did not contain I/J/K/L camera input or a
  continuous camera exercise, so the current physical-keyboard evidence does
  not close the camera portion of requirement 7.

## 2026-09-27 Farm reference comparison

The user directed continued background xemu comparison through normal Farm
entry. This work does not pass the physical-device gate. A proven lifted-acos
bug read a stack operand after POP changed ESP, reflecting movement heading.
After restoring the original COMISS flags, a shared 15-frame forward pulse
matches xemu's actor position and quaternion bit for bit across all 63 sampled
loops. Tiny velocity/camera differences remain. The former facing/velocity
overrides are now internal opt-in negative controls, and the host LX mirror is
removed; four-direction validation is in progress. See
`parity/FARM_PARITY_20260927.md` for evidence and limitations.

The historical assessment below remains relevant to physical acceptance,
but its workaround description is superseded by that source-level correction.

Physical play overrides the telemetry-only conclusions above. At the time of
that historical candidate, direction signs and diagonals were confirmed but
walking speed, acceleration, and camera positioning/feel were not. The
two-minute W route is no longer required at the user's direction. The old
direction/facing corrections described by that run have since become internal
opt-in diagnostics after the 2026-09-27 source-level heading fix. Retail now
owns normal movement, and the direct camera-matrix override remains disabled
by default.
No control behavior may be described as fixed until physical play confirms
the movement and camera match the original game.

This gate is deliberately stricter than "the character moved." Gameplay,
camera, collision, animation, mission, and render debugging can all produce
false conclusions when controller signs or transforms are wrong. No build is
eligible for gameplay bug-fixing until every requirement below passes in the
same executable.

## Required evidence

Input-source rule: WASD is digital and must request a full-radius Xbox left
stick immediately (cardinals `32767`, diagonals radialized to the same maximum
magnitude). A physical controller must remain genuinely analog: the host
bridge preserves its raw magnitude and the retail game alone applies the
original Xbox deadzone, acceleration, response, and smoothing behavior.
Neither source may inherit the other source's policy.

1. Neutral pad: sixty real-time seconds with no character displacement and no
   camera drift beyond measurement noise.
2. Cardinal movement: Forward moves Crypto physically forward; Backward moves
   physically backward; Left and Right preserve their original-game sides.
3. Diagonal movement: Forward-left, Forward-right, Backward-left, and
   Backward-right each occupy the correct world-space quadrant. No pair may be
   swapped and no diagonal may collapse to one axis.
4. Camera: Up, Down, Left, and Right all move, use the original Xbox game's
   signs, return through neutral, and remain reversible after repeated input.
   Repeat pitch in both retail `Camera Pitch: Normal` and `Inverted` modes;
   the same physical stick input must produce opposite, reversible motion.
5. Facing versus travel: Crypto's facing, locomotion animation, and physical
   displacement agree for every cardinal and diagonal direction.
6. Physical controller: repeat cardinal movement and four-way camera motion on
   an Xbox or Xbox 360-compatible controller in the visible player build. The
   scripted internal pad is necessary evidence but cannot replace this check.
7. Physical keyboard: repeat all four cardinal directions and all four
   diagonals with W/A/S/D in the visible player build.  WASD must affect only
   the logical left stick (never the Xbox D-pad), must preserve the same
   facing/animation/travel agreement as the controller, and must request full
   radial magnitude immediately without input loss.

## Pass policy

- All seven requirements must pass on one identified executable hash.
- Turbo may accelerate directional/state coverage, but final
  physical-controller and physical-keyboard checks must run at real-time 30 FPS.
- Capture the log paths, executable SHA-256, and visible confirmation in this
  file before changing Status to **PASS**.
- Any later input-bridge, timing, camera, animation, or save-setting change
  invalidates the pass and returns Status to **BLOCKED**.
- Never use "fixed," "resolved," or "game accurate" for controller behavior
  while this file says BLOCKED.

## Current automated routes

- `farm_eight_direction_acceptance.txt`
- `farm_camera_up_then_down_probe.txt`
- `farm_camera_four_way_acceptance.txt`
- `farm_camera_inverted_acceptance.txt`
- `farm_camera_normal_acceptance_from_inverted.txt`
- `farm_two_minute_forward_acceptance.txt`

These routes are test inputs, not a self-certifying result. Their logs and
captures must be evaluated against every requirement above.
