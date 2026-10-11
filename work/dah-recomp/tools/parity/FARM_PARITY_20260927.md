# Turnipseed Farm parity work — 2026-09-27

Menu fixes remain pinned in `MENU_WORK_PIN.md`. Current acceptance route is
normal New Game → Hangar → Invade Farm → full unskipped Farm arrival cinematic
→ player control. All live diagnostics use hidden, muted, isolated processes,
without desktop input. Reference controller injection changes only the logical
XInput result, not progression or simulation state.

## Confirmed fixes and evidence

- **Transient unlit vertices:** program kind 14 now reads the contiguous Xbox
  allocation used by the original dynamic vertex lock. Previously it read the
  low-memory alias, returning zero color/UV and collapsed vertices. Native run
  017 visibly restores the white shield ticks. The production PGRAPH regression
  covers seven draws / 500 vertices, with an old-code negative control and
  unrelated layout controls. This does not establish complete HUD parity.
- **Loading presentation:** the extra host-side Farm hold is disabled by
  default. Retail owns the saved backbuffer and title-card transition. The
  extra hold hid the title card and early cinematic. It is retained solely as
  an explicitly enabled internal diagnostic.
- **Heading calculation:** the lifted acos function deferred a COMISS condition
  until after POP ESI changed ESP. That read a neighboring stack value instead
  of the argument. The fix snapshots the original flags before the pop. The
  actual generated-function regression passes 414 checks and reproduces 35
  failures with the old branch. Native 018 versus xemu reference 004 then
  matches all 63 actor-position, object-position, actor-quaternion,
  scene-quaternion, and scene-matrix samples at loops 7198–7260 bit for bit.
  The old velocity/facing overrides are now internal opt-in diagnostics, and
  the unconditional input LX reflection is removed. The complete default
  four-direction route (443 consecutive loops, 7198–7640) now matches actor
  position and object position bit for bit at every loop. Movement state,
  fixed world step, pause/realtime state, camera update, and the final actor
  quaternion are also exact. The delivered logical stick values match the
  script for all four pulses. A 12-loop intermediate quaternion discrepancy
  begins during the backward turn at loop 7322; its largest component error is
  3.72529e-7 and it reconverges exactly. A second paired run reproduces the
  result exactly. Its new probes prove angular velocity, normalized heading,
  smoothed heading, and target heading are all bit-identical when the first
  quaternion mismatch appears at loop 7322. Those movement values begin to
  diverge only at 7323 as feedback from the rotation. A third paired capture
  reads the inner physics quaternion at `[[actor+0x110]+0x0C]+0x38` and finds
  its first mismatch on the same loop, 7322. The error is therefore already
  present inside physics rotation integration/normalization before the actor
  object and scene node copies are updated.
- **Guest x87 precision:** debugger traces at the movement quaternion boundary
  show xemu running with control word `0x003F`, whose PC field rounds every x87
  arithmetic result to a 24-bit significand. The recomp previously kept those
  intermediates as host doubles. The lifter/runtime now applies the guest PC
  and RC fields after x87 arithmetic and square root operations. Focused traces
  prove the movement constructor angle, setter input, and normalized result are
  bit-exact in all 14 compared loops around the old 7322 boundary. The complete
  repeated four-direction window is now bit-exact in all 443 rows for actor
  position, actor-object position and quaternion, scene quaternion and matrix,
  and the inner physics quaternion. The raw reports are
  `build-parity-xemu/constructor-ref012-vs-native033.json`,
  `build-parity-xemu/physics-ref012-vs-native033.json`, and
  `build-parity-xemu/four-ref012-vs-native034.json`.

## Movement baseline

All probes issue forward LY=32767 for loops 7200–7214, then release. Farm entry
is unskipped. Initial actor position is bit-identical:
`[974.2886962890625, 546.5062866210938, 9.982726097106934]`.

| Probe | Position at loop 7260 | Distance from start |
| --- | --- | --- |
| xemu reference 002 | `[971.4674072265625, 545.48291015625, 9.972424507141113]` | 3.001179349 |
| Native 016, old compatibility enabled | `[973.3285522460938, 546.1578979492188, 9.979220390319824]` | 1.021402732 |
| Native 017, compatibility disabled, before math fix | `[976.4429931640625, 545.359619140625, 9.990248680114746]` | 2.440470841 |
| Native 018, math fix and compatibility disabled | `[971.4674072265625, 545.48291015625, 9.972424507141113]` | 3.001179349 |

Native 017's first position update at loop 7202 matches xemu exactly. Subsequent
X motion reverses. The acos stack bug explains this reflection; repeatedly
overriding heading masks it but damages movement accumulation. Keep this
baseline when evaluating removal of the old compatibility code. The separate
left-stick X reflection also requires directional validation.

The fixed forward probe still has small discrepancies: velocity is bit-exact
in 61/63 samples (maximum absolute difference 4.76837e-7), camera local position
in 62/63 (6.10352e-5), and camera world matrix in 53/63. Raw report:
`build-parity-xemu/forward004-vs-native018.json`. Matching actor trajectories
does not establish complete floating-point, camera, frame, or timing parity.

The original four-direction report is
`build-parity-xemu/four-ref006-vs-native021.json`; the independently repeated
report with raw movement fields is
`build-parity-xemu/four-ref007-vs-native022.json`. Across all 443 rows,
physics velocity is bit-exact in 417 and camera local position in 440. Camera
quaternion is exact throughout. Camera world matrices retain small baseline
rounding differences and are bit-exact in 298 rows. The comparison uses the
same absolute scripted input loops, but the reference and native observers run
at different points in the retail loop; it therefore does not yet prove exact
phase or wall-clock timing.

After restoring guest x87 precision, reference 012 versus native 040 keeps all
443 actor and scene transforms bit-exact. A staged trace localized the former
velocity difference to interpolation helper `00053FF0`, after direction
calculation and during heading update. Applying the same guest precision rule
there makes physics velocity, angular velocity, and movement heading exact in
all 443 rows. Camera world matrices improve from 298/443 to 440/443; their
three remaining rows follow the same one-ULP camera-local position differences.
Three steering rows remain non-exact beginning at the first captured row and
are inherited from before the window. Raw reports are
`build-parity-xemu/velocity-stage-ref012-vs-native039.json` and
`build-parity-xemu/four-ref012-vs-native040.json`.

## Timing and capture limits

Original title-card Lua sets a three-second timer and pauses simulation. Both
observed runs had 88 paused loop observations after the Farm commit, then
unpaused on the 89th. Later runs vary (native 018 has 78 paused observations;
reference 004 has 89), confirming that the timer follows measured milliseconds
rather than a fixed loop count. Cinematic playback uses measured, capped delta time;
equal world ticks alone do not establish equal cinematic elapsed time.

RSP observation stops perturb wall-clock timing. Runtime random seed creation
also uses the current clock. Comparisons must record cinematic elapsed time,
input phase, RNG state, and capture association. No current result proves exact
wall-clock or pixel parity.

Native 016 RenderDoc's final exported RGB matches its independent frame-7000
BMP exactly. The equivalent exact guest-frame association for xemu remains
unverified. Reference host composition is captured offscreen; desktop pixels
are not used.

## Remaining discrepancies

- Extend the movement window earlier than 7198 to locate the three inherited
  steering rows, and trace the camera-local discrepancy beginning at loop 7217.
  Preserve exact guest arithmetic instead of accepting or rounding away either
  difference.
- The red secondary HUD bar is weapon-target dependent. Native 018 activates
  and renders its full geometry, then deactivates it; a newer xemu capture also
  lacks it. Retail Lua activates it only while the weapon-target health query
  returns a value. Compare target state before treating visibility as a defect.
- Align loading/title-card/cinematic captures by actual phase and movie elapsed
  time, then compare geometry, animation, color, and transition boundaries.
- Exact parity and physical-controller acceptance are not yet established.

Evidence lives under `build-internal/parity-farm-*20260927-*` and
`build-parity-xemu/renderdoc-runs/farm-renderdoc-20260927-*`.

## Cortex Scan completion handler

The live xemu cow scan in `build-parity-xemu/cortex-cow-live-002-state.jsonl`
transitions `20 -> 250 -> 251 -> 254`, repeats the scan states, and returns to
20. The equivalent native runs 006 and 007 reached `20 -> 250 -> 251` but
could not enter 254. The native ICALL trace at that boundary reported the
unresolved retail target `0x00055B50`, called from `0x00074ABA`.

The XBE state table at `0x00247820` identifies `0x00055B50` as the state-254
handler. Static function discovery had incorrectly extended `sub_000558C0`
to that address and omitted the following 410-byte routine. The routine was
recovered directly from `default.xbe`, added to the generated code and sorted
dispatch table, and added to `icall_seeds.json` so later regeneration retains
the boundary. The release map now contains `sub_00055B50`, and the release
candidate passes both CTest input targets.

Fresh-profile validation run 015 uses a gameplay-anchored route which crosses
the tutorial fence, reacquires the cow, and independently exercises the fixed
handler. Its observed state runs are `20 -> 250 -> 251 -> 254 -> 20`: state 250
for 21 loops, state 251 for 179 loops, and state 254 for 66 loops before the
normal return to state 20. No unresolved `0x00055B50` call occurs. Evidence is
`build-internal/cortex-cow-15-fixed-state.jsonl`,
`build-internal/cortex-cow-15-fixed.log`, and
`tools/parity/farm_cortex_cow_gameplay_probe.txt`.

The later full route exposed omitted retail callbacks after the state-254
handler began running. The recovered set is `0x000A1290`, `0x000A6700`,
`0x000A6730`, `0x000A68F0`, `0x000E97D0`, `0x000F5B00`, and `0x000F5E20`.
The already recovered `0x000F5B70` cleanup callback is now also in the sorted
dispatch table and seed list. These are direct translations of the verified
XBE instructions, including the original stack cleanup and indirect calls.

Fresh-profile validation run `current6` performs two cow Cortex Scans. Both
observed state runs are `20 -> 250 -> 251 -> 254`; the second returns to idle
state 20. `build-ninja/cortex-cow-current6.log` contains zero unresolved Xbox
targets and zero exceptions. The corresponding per-frame evidence is
`build-ninja/cortex-cow-current6-state.jsonl`.

The same candidate also passed the title composition regression. Consecutive
frames in `build-ninja/title-regression-final.log` use the stable five-pass
sequence (texture copy, two blur passes, present copy, present finalize) and
contain no inline screen-copy feedback pass.

The combined renderer and Cortex Scan correction was published as the single
root `DestroyAllHumans.exe` with SHA-256
`2AA97F5928FEF75400600E9B4FF2687EEE1D8F2337AF4B53A25C9EE9D9B95894`.
