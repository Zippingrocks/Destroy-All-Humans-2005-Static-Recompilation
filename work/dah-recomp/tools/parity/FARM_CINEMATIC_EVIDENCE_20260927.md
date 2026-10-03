# Farm cinematic evidence, 2026-09-27

The Farm cinematic now has a validated read-only clock on both engines. These
runs do **not** establish exact loading, timing, or pixel parity. Native017 was
built before the derived cinematic-class validation fix, so it cannot supply
movie elapsed values. Native018 supplies those values, but its sampled elapsed
sequence differs from both reference sequences. Old reference host screenshots
also contain scaling introduced by our launcher, not by the original game.

All work behind this report used saved logs, source and offline RenderDoc
replay. It did not control a game, send input, change clocks or touch a running
process. Paths below are relative to `work/dah-recomp` unless stated otherwise.

## Saved inputs and observer limits

| Run | State file | Valid rows used | Limitation |
| --- | --- | ---: | --- |
| Reference002 | `build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-002/state-farm-route.jsonl` | 10,402, loops 49..10450 | No cinematic observer |
| Reference003 | `build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-003/state-farm-route.jsonl` | 10,263, loops 699..10961 | Valid movie observer; instrumented timing |
| Native015 | `build-internal/parity-farm-state-20260926-015.jsonl` | 6,661 | No cinematic observer; presentation hold active |
| Native017 | `build-internal/parity-farm-fixed-20260927-017.jsonl` | 10,219 | Final partial JSON line excluded; derived movie class rejected |
| Native018, follow-up read | `build-internal/parity-farm-fixed-20260927-018.jsonl` | 8,212 complete rows at read | Partial trailing line excluded; complete cinematic interval available |
| Reference004, follow-up read | `build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-004/state-farm-route.jsonl` | 10,234, loops 294..10527 | Valid movie observer; instrumented timing |

Reference samples stop at `XInputGetState` before the controller result; native
samples are at retail phase `000DAD3C`. A matching loop number therefore is not
a matched sample phase. Reference state sampling explicitly reports
`timingPerturbed=true`; GPU capture/readback also changes host pacing.

Both reference 002/003 input scripts use six-frame pulses at loops 1200 START,
1400 A, 1700 A, 2100 A, 2300 START, 2700 A and 3000 A. The START at 2300 skips
the earlier New Game intro; the Farm cinematic is unskipped. Reference003's
15-frame forward pulse begins at 7200, after cinematic completion. No clock,
RNG, actor transform or cinematic elapsed value was written by these observers.

## Loading and release milestones

Numbers are absolute retail loop observations, not wall-clock durations.

| Milestone | Ref002 | Ref003 | Native015 | Native017 |
| --- | ---: | ---: | ---: | ---: |
| Farm pending after launch input at 3000 | 3001 | 3001 | 3001 | 3001 |
| Farm committed, backend state 22 | 3827 | 3850 | 3704 | 3701 |
| First world tick 1 | 3828 | 3851 | 3705 | 3702 |
| Cinematic realtime begins | 3937 | 3962 | 3799 | 3798 |
| World tick at cinematic start | 9 | 9 | 7 | 8 |
| First native cinematic UI active | not observed | not observed | 3793 | 3791 |
| Cinematic ends / realtime released | 6688 | 6742 | 6319 | 6315 |
| World tick at release | 2760 | 2789 | 2527 | 2525 |
| Start-to-release loop delta | 2751 | 2780 | 2520 | 2517 |

At cinematic start, world elapsed seconds are respectively 0.3000000119,
0.3000000119, 0.2333333343 and 0.2666666806. At release they are 84.2923965454,
84.2692031860, 84.2326049805 and 84.2649536133. Even the two reference runs
differ by 23 loops at commit, 25 at cinematic start and 54 at release. A fixed
native delay derived from those offsets would encode instrumentation/load
variance rather than demonstrate the original transition condition.

Native015 held presentation throughout loops 3001..4063 (1,063 samples); release
at 4064 occurred at world tick 272 / elapsed 9.0673322678s. Native017 has no held
samples. This makes the newly visible early frames useful diagnostics, but the
removed hold must not be replaced by another guessed duration.

## Clock identity and current alignment

The Farm object has manager vtable `0x22A6B8`, movie vtable `0x229FB4`, name hash
`0xDA349F1D`, duration bits 1118301936 and duration 83.9666748046875 seconds. These
derived classes are constructed through the source-audited base constructors
`00112D80` and `00112280`. The bounded observers retain raw field bits and mark
unsupported classes or incomplete traversal explicitly.

In reference 003, the object is loading at 3850..3851, ready at 3852..3961 and
playing at 3962..6741. Its playing elapsed starts at 0 and reaches 83.9392166138s
on the last sampled playing row. The list is empty at 6742. Elapsed storage
before state 2 is not an initialized clock and must not be interpreted as time.
Native017 rejected all 2,614 movie-present rows with
`unexpected-cinematic-movie-vtable`; its null fields cannot be recovered from
the saved JSON. Native015 has no such field at all.

Native018 validates the same movie. It commits Farm at 3441, first plays at 3526,
last plays at 5620 (elapsed 83.9415817261s), and releases at 5621. Reference004
commits at 3841, first plays at 3939, last plays at 6727 (83.9566268921s), and
releases at 6728. These counts are diagnostic measurements, not ordinary pacing.

Across the complete playing samples, native 018 has exactly one elapsedBits
match with reference 003 and exactly one with reference 004: elapsed 0. At that
point, camera view position and forward vectors match bit-for-bit; actor
position does not. Movie flags match after the proven low-bit mask below.

Reference003's pre-capture observation at loop 4004 has elapsed bits 1067567807,
or 1.2639998198s. The nearest native 018 observation is loop 3560, bits 1067685250,
or 1.2780001163s: **+14.0002966ms**. Their camera forward bits match; camera view
position Y differs by 1 ULP and actor position Z by 1 ULP. This is close phase
evidence, not an exact time match or a valid claim that their pixels must match.

Without a native 017 movie clock, using world elapsed minus start gives only a
rough pairing: native 017 loop 3836 is 1.26699993s after its start against the
reference's 1.26399982s. Their camera view Y differs by 1 ULP and actor position
bits match. That approximation must not replace direct movie elapsed now that
native 018 has valid fields.

## Meaningful movie flags

The retail constructor `src/recomp/gen/recomp_0012.c`, label `001122D9`, reads
the existing `movie+0x70` word and ANDs it with `0xFFFFFFFC`. It initializes only
bits 0 and 1; higher bits survive from prior storage. Start routine `00111EE0`
sets bit 1 and enables world realtime. The event handler `00112050` sets/clears
bit 0 around its associated manager calls, and finish routine `00111F90` tests
the same two bits for cleanup. The established semantic mask is **0x3**.

| Observation | Raw flags | `flags & 3` |
| --- | --- | ---: |
| Native018 first playing | `0x3A0CBC02` | 2 |
| Reference003/004 first playing | `0x0023407E` | 2 |
| Native018 subsequent playing | `0x3A0CBC03` (973913091) | 3 |
| Reference003/004 subsequent playing | `0x0023407F` (2310271) | 3 |

Keep the raw words for diagnosis. Compare established bits for semantic parity;
do not write or clear the heap word just to make its unrelated high bits equal.

## Captured image provenance and host aspect correction

All following files live under their reference run directory. Offline exports
were made with the existing no-window console replay helper.

| Run/capture | Game display export | Host display export |
| --- | --- | --- |
| 002 / `capture_frame97185.rdc` | event 21459, `texture:0`, `cinematic-game-output.png` | event 21742, `texture:64`, `cinematic-host-output.png` |
| 003 / `capture_frame94914.rdc` | event 21363, `texture:0`, `cinematic-game-output.png` | event 21646, `texture:64`, `cinematic-host-output.png` |

In these captures, texture 0 is 640x480 `R8G8B8A8_UNORM`; texture 64 is 640x480
`R8G8B8A8_SRGB`. The earlier game texture and the host DAC/gamma display pass
are distinct stages. Resource tokens are local to each capture. Source
`Repos/xemu/ui/xui/gl-helpers.cc` (relative to workspace root) loads the DAC
palette for its display shader, so color/intensity equality needs an explicit
stage correspondence as well as matching dimensions.

The retained 002/003/004 configs force `display.ui.aspect_ratio='16x9'` while
their host window is 640x480. The local xemu config specification explicitly
allows `4x3` and defines fit default `scale`. `GetDisplayAspectRatio` and
`RenderFramebuffer` compute scaleY = (4/3)/(16/9)=0.75, clear black, then use
`gl_Position=in_Position*in_ScaleOffset.xy+in_ScaleOffset.zw`. This proves why
the host image has 640x360 content and 60-pixel bars above/below. Those bars are
not evidence of a missing native cinematic effect. The game display texture
retains 640x480 geometry.

The private launcher now explicitly writes `4x3`, fit `scale`, window 640x480,
and records these in its plan for future runs. Its generated TOML was parsed
and checked without launching anything. Existing run configs were preserved.
This changes host presentation only; it does not change the copied Xbox
EEPROM or establish that guest video-mode state is equal. Retain mode and
640x480 framebuffer provenance when comparing both engines.

Reference003 `phase-captures.jsonl` records loop 4004 / movie 1.2639998198s
**before** calling the capture helper. The helper then drains its target
inventory for one second before requesting capture while the guest continues.
The capture's host frame 94914 is therefore not an exact image of loop 4004.
The annotation correctly says `exactGuestFrameAssociation=false`.
Reference002 likewise records loading before loop 3001 (capture 85639),
cinematic before 3939 (capture 97185), and gameplay before 6689 (capture 158032).
None has a proven exact guest-frame association.

## Visual issue to resolve next

Native017 saved frame 3800 (`build-internal/dah_frame_17568_0000003800.bmp`)
is uniformly gray-blue. Frame 3900 shows the moon/cloud opening with a washed
light-gray/blue appearance. Frame 4000 shows the drive-in billboard scene.
Reference003's game export shows the dark moon/cloud opening. This prioritizes
the opening scene's fade/postprocess and color pipeline for a properly aligned
comparison. These images have different movie times and possibly different
gamma stages, so they do not yet isolate a rendering defect. Reference002's
single loading image is black, but one image does not establish every loading
transition or justify concealing all early native frames.

1. Use valid state 2, movie hash, duration and direct elapsedBits to select the
   opening scene in native 018 and a future reference. Keep raw flags, compare
   mask 3, and record actual elapsed deltas; never overwrite clocks to align.
2. If no exact elapsed sample exists, retain surrounding samples and report
   the time bracket. A nearest sample is not an exact animation-frame match.
3. Capture a proven guest/GPU boundary and retain before/after state. CPU-stop
   alone does not prove NV2A FIFO/scanout completion. Current 003 annotations
   cannot be retroactively promoted to exact capture identity.
4. Compare the same 640x480 game-output stage for geometry first. Establish
   equivalent DAC/gamma treatment before using a pixel-difference metric to
   diagnose the opening brightness. Do not add the old host bars to native.
5. Trace fade/postprocess draw state only after scene time and output stages
   are matched. Keep loading commit and cinematic release conditions separate
   from measured host throughput; do not add a fixed loop offset.

Menus remain deferred. These observations guide Farm work and explicitly leave
exact timing, transition coverage and pixel parity unverified.

## Projector, bloom and morph-skin correction

Later GPU captures isolated three independent faults in the Pox Farm shot.
Native capture `build-internal/cinematic-hologram-rdoc-053_capture.rdc` and
xemu capture `build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-012/capture_frame5823447.rdc`
are the retained replay inputs.

- An inline 28-dword fullscreen draw was incorrectly decoded as five generic
  vertices. Its declaration is four vertices of float4 position, float2 UV
  and packed colour. The dedicated MOV path now preserves that layout.
- The 142-vertex projector pass decoded `IMAGE_RECT=0x028001E0` as 480x640.
  NV2A stores width in the high half and height in the low half; using 640x480
  removes the gray/striped projector block. Native texture 2 is visually
  unchanged across events 8515 and 8601 apart from the intended refraction.
- Programmable screen passes write fog distance through `oFog`. The native
  combiner previously substituted fog-colour alpha zero, making the 320x240
  blur target a solid rectangle and spreading it into a pale full-frame wash.
  The translator now tracks `SET_FOG_MODE` and `SET_FOG_PARAMS`, applies the
  NV2A fog equation, and supplies the transformed constant to postprocess
  combiners. Capture 053 events 8636, 8674, 8712 and 8753 contain the scene,
  its blur, and localized bloom rather than constant gray.

The same retail-paced sweep found a deterministic morph-skin rejection at
vertex 146 of an 873-index draw. Morph stream 1 contains Xbox quiet-NaN
sentinels while `c85.y` is exactly zero. NV2A's multiply returns zero when one
operand is zero, but the host validator rejected the NaN before multiplication
and discarded the entire strip. Zero-weight morph streams are now skipped in
both 62-instruction morph paths. `build-internal/farm-skin-fixed-058.log`
reports zero `DAH-FARM-VERTEX-FAIL` or `DAH-CRYPTO-VERTEX-FAIL` entries across
the formerly failing interval; frames 3800 through 4550 retain complete Crypto
and Pox silhouettes.

The verified internal executable was published as the single root
`DestroyAllHumans.exe` with SHA-256
`144CC5692A98466F6ABCDBA021977FD97FED94647B6B69C471830F275D4C9777`.

## Paddock mesh-stability sweep

`tools/parity/farm_entry_cow_mesh_probe.txt` replays the established
fresh-profile Farm route, then holds the left stick forward for loops 7200
through 7499. The same schedule was delivered through the recomp and xemu
logical-pad adapters; xemu remained in its existing hidden process and was
reset through QMP rather than relaunched.

Native run 061 captured every fifth presented frame from 7150 through 7745.
`build-internal/cow-dense-contact-061.png` is a 24-sample stationary crop of
the paddock from frames 7625 through 7740. The independently animated cattle
retain their heads, torsos and legs in every sample; Crypto also remains
complete through the approach. Neither `cow-mesh-probe-061.log` nor its
archived runtime log contains a Farm/Crypto vertex rejection, NaN failure,
rejected state, fatal error or exception. This validates the zero-weight and
zero-morph handling over the reported gameplay view, including the character
and cattle mix.

The paired state traces are:

- `build-parity-xemu/cow-mesh-probe-061-state.jsonl`
- `build-internal/cow-mesh-probe-061.jsonl`

Their observers remain one boundary apart (`XInputGetState` before result
delivery versus native `000DAD3C`). At the route's stationary start and
settled end, actor-position float bit patterns are identical. During the
300-frame forward pulse, the nearest sampled rows differ by one delivered
movement step, as expected from those phase labels; the settled frame 7600
position is bit identical again at
`[951.0103149414062, 526.1287841796875, 9.967509269714355]`.

A bounded diagnostic also watched the D3D8 gamma-ramp entry point for the
whole route. Retail made no gamma-ramp call. The diagnostic was then removed.
The remaining xemu/native brightness difference therefore belongs to render
and postprocess state, not a discarded retail gamma transition.

## Exact 59.001-second stencil/postprocess correction

The retained exact-time pair is xemu
`build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-012/capture_frame5836419.rdc`
and native run 071
`build-internal/cinematic-stencil-071-rdoc_capture.rdc`. Native entered the
capture at cinematic seconds `59.001007`, state hash `DA349F1D`; xemu's
corresponding display export is `xemu-cinematic-59000-game.png`.

Action-stream alignment isolated the brightness discontinuity to a four-vertex
fullscreen draw. In xemu, the draw uses stencil `NotEqual`, reference `0x80`,
compare/write masks `0xFF`, after a stencil clear to `0x80`. It therefore
changes no pixels. Native had two independent omissions: NV097 stencil methods
were not translated, and `NV097_CLEAR_SURFACE` hard-coded the host stencil
clear value to zero. Translating the stencil state alone reproduced the exact
draw state but still allowed the draw because the buffer contained zero.

Run 071 retains `NV097_SET_ZSTENCIL_CLEAR_VALUE` and decodes the Z24S8 register
as xemu does: stencil in the low byte, 24-bit depth above it. RenderDoc event
9274 now reports stencil enabled, function `NotEqual`, reference 128 and masks
255. The game-output images immediately before and after that draw have mean
`53.3652484809028` and byte-for-byte RGB MAE `0`. The late frame no longer has
the erroneous dark overlay:

| Measurement at 59.001 seconds | Native 068 | Native 071 | xemu |
| --- | ---: | ---: | ---: |
| Mean RGB level | 57.2812 | 77.5379 | 77.5813 |
| RGB MAE versus xemu | 23.2034 | 10.8649 | 0 |

This is a measured reduction, not a claim of pixel identity. Remaining local
differences include the saucer light/bloom and rasterized edges. Run 071 has no
Farm/Crypto vertex failure, fatal, exception or assertion marker; Crypto and
Pox remain complete in the captured frame. The D3D11 depth/stencil cache key
now also includes all stencil operations and the write mask so later stencil
state changes cannot reuse a stale object.

The verified build was published as the single root `DestroyAllHumans.exe`
with SHA-256
`8C3985153ED86D61779BC9E897DDD101A3BE72EB75E8150CD1F7A5BED5DEB70E`.

Two capture-free follow-up runs then sampled the promoted renderer every 20
host frames without changing guest time. Run 072 retains frames 5200 through
6020; run 073 retains frames 6000 through 7900. The large mean-luminance
changes in the cinematic segment correspond to visible camera cuts. Frame
6320 is the actual black handoff and frame 6340 reveals Farm gameplay. During
the stationary gameplay window 6400 through 7180, the largest sampled
20-frame mean-luminance change is 0.41. During the settled post-movement window
7600 through 7900, all 16 samples lie between mean levels 63.151 and 63.462.
Neither run reports a Farm/Crypto vertex failure, fatal, exception or assertion
marker. Visual inspection across the dense sequence retains complete Crypto,
Pox and cow silhouettes through the cutscene, handoff, idle, forward movement
and settled paddock view.

## Exact late-Pox timestamp bracket

The retained xemu late-cinematic reference is
`build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-012/capture_frame5857879.rdc`.
Its guest movie clock sample is `83.5838318` seconds and its duration is
`83.9666748` seconds. Native run 079 requested that same decimal through the
read-only cinematic-clock RenderDoc trigger. The first native render sample at
or beyond it is host frame 6309 at `83.599327` seconds; run 080 retains frame
6308 immediately before that boundary. Thus the xemu sample is bracketed by
adjacent native frames rather than assigned a guessed host-frame offset.

The clock trigger previously stored the requested decimal as a double while
the guest clock is a float. At the last movie sample, promotion could leave the
request a few billionths above the exact guest value and miss the capture. The
internal trigger now stores and compares the request as a float. This changes
diagnostic capture selection only; it does not write guest memory or alter game
timing.

Against `xemu-cinematic-83500-game.png`, native frame 6308 measures full-frame
RGB MAE `11.47` and frame 6309 measures `11.81`. Both frames retain the complete
Pox projection, saucer, projector arms and surrounding scene. The late scene's
native-minus-xemu signed channel bias before bloom is small: `+1.47` red,
`+0.55` green and `-0.20` blue. A global brightness or saturation correction
would therefore hide local differences while damaging already-matched pixels.

Run 079 also retains equivalent pre/postprocess exports from the exact capture.
The native/xemu RGB MAE at each game-output stage is:

| Stage | RGB MAE | Native mean | xemu mean |
| --- | ---: | ---: | ---: |
| Scene before bloom | 8.71 | 74.61 | 74.00 |
| 640x480 to 320x240 downsample target | 4.25 | 56.20 | 56.03 |
| First four-tap blur | 6.97 | 38.28 | 37.70 |
| Second four-tap blur | 3.90 | 56.30 | 56.13 |
| Final additive game target | 11.47 | 93.43 | 92.59 |

The four native postprocess draws match xemu's pass structure. Their vertex
intensities are also identical: 38 for downsample, 128 for both blur passes and
63 for the final additive pass. Clamp/linear sampling and normalized final-pass
coordinates match as well. The remaining late-frame error begins in the scene
render and is amplified by the correct bloom composite; it is not evidence for
changing the bloom constants or applying a global colour correction. These
measurements remain a two-frame time bracket, not a claim of pixel identity.

## Farm sky texture-coordinate correction

The first meaningful native/xemu divergence was already present after the
first 213-index sky draw. Xemu vertex debugging at event 106 shows its float2
texture input padded as `(-0, 0.096613, 0, 1)` and UV transform constant
`c78 = (4, 4.37113883e-8, 0, -2.12912846)`. Native event 39 instead emitted U
near zero because the static/menu adapter left the absent texture W component
at zero and therefore discarded `c78.w`. This shifted the animated cloud layer
horizontally while the world camera and later geometry remained aligned.

The static/menu path now completes the missing texture W component with one
before evaluating its retail DP4 transform. The correction is intentionally
scoped away from packed skin, morph and bone streams. Exact-time run 084 fired
at the same first native sample beyond the xemu clock, `83.599327` seconds with
cinematic hash `DA349F1D`. Its measured RGB errors are:

| Checkpoint | Before | After |
| --- | ---: | ---: |
| First sky draw | 15.13 | 0.11 |
| Scene before bloom | 8.71 | 2.76 |
| Final late-Pox frame | 11.47 | 3.27 |

The final native/xemu mean levels are 92.87 and 92.60. Run 084 retains complete
Pox and saucer geometry and reports no Farm/Crypto vertex failure, fatal,
exception or assertion marker. This is a large measured improvement, but the
remaining 3.27 MAE still includes local raster, glow and adjacent-frame phase
differences and is not pixel identity.

The verified build was published as the single root `DestroyAllHumans.exe`
with SHA-256
`BC8F01DDB1CAF5F007BC46E25C02D951A1BCA013B2BB9388C96C961BED261378`.

## Static scenery cull stability

Hidden Farm runs 115, 116 and 118 added an opt-in scene-cull transition trace
and isolated the reported brief tree-line disappearance to the title's static
world-cluster class: object flag `0x2000`, model type 7 and static model marker
`0x88`. Dynamic cows, the saucer and other actors have different object/model
flags and are excluded from the correction.

The host now retains a previously visible static cluster for one frame when a
single frustum test rejects it. The raw rejection is still recorded, so a
cluster that remains outside the view is removed on the next frame. Camera
translation discontinuities larger than 25 world units clear the retention on
that frame, preventing scenery from leaking across cinematic cuts. This does
not expand model bounds or disable normal scene culling.

Validation run 119 covered 755 consecutive Farm cinematic samples. It applied
45 one-frame holds to static world clusters, including the repeatedly observed
cluster at `(912, 412, 27)`. The effective visibility trace no longer reports
that cluster's one-frame disappearance. The run reports no fatal, exception,
unresolved indirect-call, rejected-state, Farm vertex or Crypto vertex marker.
Coarse retained frames 7710, 7740 and 7770 keep the tree line and foreground
scenery coherent through the affected pan. These results establish the native
stability correction; they do not by themselves prove full-frame pixel
identity with xemu.
