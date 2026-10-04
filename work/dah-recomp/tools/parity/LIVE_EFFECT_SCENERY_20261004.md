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
