# Controller acceptance gate (mandatory)

Status: **BLOCKED until rerun on the current executable**

This gate is deliberately stricter than "the character moved." Gameplay,
camera, collision, animation, mission, and render debugging can all produce
false conclusions when controller signs or transforms are wrong. No build is
eligible for gameplay bug-fixing until every requirement below passes in the
same executable.

## Required evidence

1. Neutral pad: sixty real-time seconds with no character displacement and no
   camera drift beyond measurement noise.
2. Cardinal movement: Forward moves Crypto physically forward; Backward moves
   physically backward; Left and Right preserve their original-game sides.
3. Diagonal movement: Forward-left, Forward-right, Backward-left, and
   Backward-right each occupy the correct world-space quadrant. No pair may be
   swapped and no diagonal may collapse to one axis.
4. Camera: Up, Down, Left, and Right all move, use the original Xbox game's
   signs, return through neutral, and remain reversible after repeated input.
5. Facing versus travel: Crypto's facing, locomotion animation, and physical
   displacement agree for every cardinal and diagonal direction.
6. Endurance: after the intro fully finishes, hold Forward for two continuous
   minutes at the real-time 30 FPS target. Require movement samples throughout,
   no stuck detector, no crash, no invalid simulation steps, and no input loss.
7. Physical controller: repeat cardinal movement and four-way camera motion on
   an Xbox or Xbox 360-compatible controller in the visible player build. The
   scripted internal pad is necessary evidence but cannot replace this check.

## Pass policy

- All seven requirements must pass on one identified executable hash.
- Turbo may accelerate directional/state coverage, but the endurance and final
  physical-controller checks must run at real-time 30 FPS.
- Capture the log paths, executable SHA-256, and visible confirmation in this
  file before changing Status to **PASS**.
- Any later input-bridge, timing, camera, animation, or save-setting change
  invalidates the pass and returns Status to **BLOCKED**.
- Never use "fixed," "resolved," or "game accurate" for controller behavior
  while this file says BLOCKED.

## Current automated routes

- `farm_eight_direction_acceptance.txt`
- `farm_camera_up_then_down_probe.txt`
- `farm_two_minute_forward_acceptance.txt`

These routes are test inputs, not a self-certifying result. Their logs and
captures must be evaluated against every requirement above.
