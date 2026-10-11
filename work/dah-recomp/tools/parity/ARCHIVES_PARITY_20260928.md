# Archives parity checkpoint — 2026-09-28

## Exact reference pair

- Recomp: `build-ninja/live-recomp.png`
- xemu: `build-ninja/live-xemu.png`
- Alignment: recomp shifted +1 px on X after resizing to the 1280x720 xemu client.
- Stable-room baseline before the fix: 14.3838 RGB MAE. A fitted room transform was approximately `xemu = 1.003 * recomp - 14.4`, with 1.9 RGB MAE after the fit.
- Five consecutive paired captures showed 0 red eye pixels in the recomp and 49–51 left / 42–43 right in xemu, proving a persistent missing draw rather than animation noise.

## Missing reflective detail program

The missing draw used exact retail vertex-program fingerprint `05B0BBCF` (32 instructions / 128 words), with four active arrays and 57/75-index eye meshes. Its screen bounds matched both xemu eye clusters.

Implementation:

- `third_party/xboxrecomp/src/nv2a/dah_static_reflection_vertex.h`
- program kind 29 in `third_party/xboxrecomp/src/nv2a/nv2a_pgraph_d3d11.c`

The implementation preserves the retail position, diffuse lighting, additive vertex color, reflected cube coordinate, and both texture coordinates. It also validates the packed normal/UV/color declaration before accepting the draw.

## GPU writeback proof

An isolated exact Archives replay sampled triangle centroids before and after the kind-29 draws at submission 2346. The previously untouched background pixels changed to the expected reflective colors:

- left display eye: `000913FF -> 6F0B00FF`
- right display eye: `000913FF -> 6C0D13FF`
- adjacent reflection/detail pixels also changed to the expected blue, gold, and silver values.

Every draw returned `hr=00000000`. This confirms that the missing-eye fix reaches the active render target; it is not only a classifier or vertex-transform success.

## Postprocess classification

The retail MOV program is shared by fullscreen passes and ordinary indexed UI sprites. `submit_postprocess` now requires geometry covering at least 75% of the active surface before it mutates host postprocess state. This prevents 128x128 menu sprites from taking the render-target path first.

Hidden/minimized swapchain captures are not valid final-image references here: both the previous root executable and the fixed build produce the same white 3D area when every present reports occluded, while their non-occluded visible sessions render the room. Hidden runs remain valid for draw/state/pixel probes.

## Published build

The single root executable `DestroyAllHumans.exe` was updated after its prior visible process exited normally. SHA-256 at publication: `B25F44948756025096333D29D602A72DEADEE1150342BBEB293FB17006C9FDA7`.

The next visible comparison should recapture the same Archives item from this build and measure:

1. red-eye pixel counts,
2. room color bias after the corrected postprocess state,
3. remaining figure/smoke/edge differences after alignment.

## 2026-10-03 follow-up

A fresh pre-Present capture confirms that both display figures now retain their
red reflective eyes. Across settled frames `1097` through `1125`, comparison
against `live-xemu.png` is temporally stable: the room stays approximately
`+14.29` RGB levels brighter, while a fitted slope remains approximately `1.0`.
This points to the Archives grading/composite path rather than geometry or
animation drift.

The opt-in compositor trace identifies the active retail pass as a dependent-AR
lookup from scene target `03F11000` through table `0412E000`. Its state is
stable across alternating output surfaces: texture program `000001E1`,
combiner `00011101`, lookup filter `02023F01`, and final combiner
`0000000E,00001C80`. The table itself is a monotonic 256-entry color ramp.

There is no Archives-specific xemu GPU capture in the current evidence set.
Do not compensate with a global brightness offset: later Farm evidence already
matches closely and would regress. A runtime correction should wait for a
same-frame xemu capture of this lookup pass so its dependent coordinates,
sampler behavior, and final composite can be compared directly.
