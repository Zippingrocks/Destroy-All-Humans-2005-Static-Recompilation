# Live Farm effect and scenery findings — 2026-10-04

The visible player run, PID 65412, remained under user control. The process was
not focused, moved, restarted, or closed by the debugging work.

## Observed defects and evidence

- The abducto-beam ground symbol was absent during the saucer cinematic.
- The user observed rapid disappearance of trees, buildings, and terrain.
- Orthopox and Holopox effect layers remained incomplete.
- After an A skip at input poll 10968, movie close released the transition
  latch with no movie frame pending. The immediately following draws rejected
  ordinary transition texture `03456800` on both backbuffers. A second skip
  sequence rejected `0346F800` and `0345E800`. This explains gameplay HUD
  becoming visible before its intended fade/transition layer.
- A rock beside the cow-pasture water visibly loaded, disappeared briefly,
  then returned while the player approached it. This remains a visible
  verification target for the static scenery retention change.
- The runtime reached unresolved indirect Lua callback `001932F0` from
  `00192850`, return address `0019288D`, five times in the captured run.
- Effect-heavy transitions requested ordinary texture offsets through the
  render-target-only composite path. Missing examples included `01711700`,
  `01B51C00`, and `016ED700`; those draws were discarded when no live render
  target existed at the requested offset.

## Candidate corrections

`001932F0..0019332C` is now an exact 60-byte, 20-instruction lift from the
pinned retail XBE. It is registered in the sorted dispatch table and retained
in `icall_seeds.json`. The reproducible boundary and translation helper is
`tools/lift_live_script_callback.py`.

Screen-space composite and inline MOV draws now try live render-target feedback
first, then decode and bind the requested offset as an ordinary Xbox texture.
This preserves real scene-feedback passes while allowing projected markers,
hologram layers, transition fades, and other effect quads to render instead of
being discarded. Retail HUD and cinematic script timing is left unchanged.

Static world clusters now tolerate two consecutive edge rejections during a
continuous camera move. The wider hold applies only to stationary static
clusters. Dynamic meshes retain the prior one-frame, movement-limited rule so
gravity/PK transitions can still hide actor limbs and attachments immediately.
Camera discontinuities continue to cancel all retention.

The release build also had three controller diagnostics enabled during normal
play: host XInput packets, final logical-pad changes, and conditioned stick
values. Continuous movement caused synchronous stderr writes and flushes on
the game thread. All three detailed traces now require `DAH_INPUT_TRACE=1` or
`DAH_STICK_CONDITION_TRACE=1`; controller input and the sparse existing health
markers are unchanged.

## Build status

The release candidate built successfully at
`build-ninja/dah_recomp_working.exe`; SHA-256:
`E81F9837AAE397817D27C233D03B64C6D15C0AF2712E45176AAB25303E852DA5`.
Both configured tests pass. Promotion and visible verification wait for the
current user-controlled process to exit normally.

## Follow-up Farm run, PID 78816

The read-only UI/cinematic observer caught the full end of the unskipped Farm
arrival. The cinematic list cleared and the gameplay HUD activated together at
retail loop 8444, world tick 2529. The established native baseline releases at
approximately tick 2527, so this run does not reproduce an early-HUD release.
The normal objective presentation began at tick 2592 and closed at tick 2778.

During the saucer beam shot, the renderer accepted Farm deform program kind 22
at submission 12293 and repeatedly submitted the saucer screen-effect texture
`0249F800` to the alternating scene targets. No distinct yellow world-space
projection/decal appeared in the bounded trace. This narrows the defect to the
projected-card/inline path rather than failure to start the overall beam shot.
The currently running player executable predates the opt-in full inline packet
trace; retain the next packet-complete run before changing vertex layout or
inventing replacement geometry.

The same uninterrupted run exercised the cow Cortex Scan/tutorial path. The
observer recorded the ability selector, Cortex target, thought bubble,
notification and brain-stem UI as separate game-tick transitions. Six cow
actors subsequently entered `animal_dead` together and streamed out before a
cinematic/loading/tutorial handoff. This proves the interaction is no longer
stuck at the UI prompt, but the simultaneous death transition still needs an
equivalent xemu trace before it can be accepted as retail behavior.

Player movement also exposed whole scenery-sector activation waves. At world
tick 16676, the actor list admitted fir and birch trees, river rocks, forest
clumps, hay bales, fence pieces and the rainwater tank on the same tick. This
is a stronger candidate boundary for the reported scenery pop than the
per-object frustum hold: the actors were absent from the world list before the
wave, so a cull-only correction cannot make them render earlier.

At ticks 17134 through 17177, the UI entered fade/loading and then restored the
gameplay HUD while a police car, two police officers and the farmer's wife were
created for the next encounter. The frame monitor recorded one 282.310 ms
interval in that handoff (`late=1`) with zero failed presents and zero invalid
simulation steps. Adjacent five-second windows returned to exact 30 Hz. Treat
this as a synchronous transition hitch until a matched xemu run establishes
the retail budget and event order.
