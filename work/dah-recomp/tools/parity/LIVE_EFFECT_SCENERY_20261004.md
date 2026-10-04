# Live Farm effect and scenery findings — 2026-10-04

The visible player run, PID 65412, remained under user control. The process was
not focused, moved, restarted, or closed by the debugging work.

## Observed defects and evidence

- The abducto-beam ground symbol was absent during the saucer cinematic.
- The user observed rapid disappearance of trees, buildings, and terrain.
- Orthopox and Holopox effect layers remained incomplete.
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
hologram layers, and other effect quads to render instead of being discarded.

Static world clusters now tolerate two consecutive edge rejections during a
continuous camera move. The wider hold applies only to stationary static
clusters. Dynamic meshes retain the prior one-frame, movement-limited rule so
gravity/PK transitions can still hide actor limbs and attachments immediately.
Camera discontinuities continue to cancel all retention.

## Build status

The release candidate built successfully at
`build-ninja/dah_recomp_working.exe`; SHA-256:
`D816063CE4F59816F55EA9D874C71CDDEE646F504F9F42C42C81E437B90B6B2F`.
Both configured tests pass. Promotion and visible verification wait for the
current user-controlled process to exit normally.
