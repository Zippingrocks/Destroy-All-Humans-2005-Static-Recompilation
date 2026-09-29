# Frame-rate accuracy audit

## Current conclusion

- **The player default follows the retail-selected divisor.** A blanket host
  override is not a valid release policy.
- **60 Hz is source- and frontend-runtime-supported.** The retail
  renderer setter has explicit divisor-1 and divisor-2 branches, and the retail
  world update derives its fixed step from that divisor. An isolated untouched
  xemu run selected divisor 1/interval 1 through the post-logo frontend on
  2026-09-25. This proves a retail 60 Hz frontend path, not 60 Hz gameplay.
- **Rates above 60 Hz are not exposed by the retail timing policy.** They must
  not be implemented by increasing the simulation tick. The accurate route is
  to keep a proven simulation rate and add host-side presentation/interpolation.

## Retail evidence

`src/recomp/gen/recomp_frontend_callbacks.c`, `sub_000E0510`, preserves the
retail renderer-rate setter. A divisor of 2 selects interval 2; a divisor of 1
selects interval 1. Other values follow the retail fallback branch rather than
establishing a higher supported rate.

`src/recomp/gen/recomp_0011.c`, `sub_001049F0`, preserves the retail world-step
calculation. In fixed-step mode it selects the 50/60 Hz base, divides one by
that base, and multiplies by the renderer divisor when the divisor is greater
than one. Therefore NTSC divisor 2 produces 1/30 second and divisor 1 produces
1/60 second.

`src/dah_frame.c`, `sample_policy`, follows the guest's divisor when `DAH_FPS`
is unset. `DAH_FPS=30` and `DAH_FPS=60` are explicit diagnostic overrides;
other values do not override retail. The host pacing period tracks the active
retail divisor and refresh policy.

Movies use a separate Xbox-TSC/QPC-derived clock. Changing the gameplay loop
must not be used to speed up, slow down, or otherwise retime Bink playback.

## Enhancement classes

### Safe to develop now

These are host presentation changes and must not write guest timing or gameplay
state:

- stable frame pacing and lower presentation latency;
- higher output resolution and window/fullscreen scaling;
- optional post-process sharpening;
- host-side texture filtering improvements;
- diagnostic capture and performance telemetry.

They still require image comparison because they can alter appearance, but they
cannot be called gameplay-accuracy regressions unless they feed back into guest
state.

### Source-supported, validation required

- the retail 60 Hz divisor-1 path;
- input sampling at the resulting update rate;
- camera, animation, particles, UI animation, physics, AI, mission scripts,
  audio synchronization, loading transitions, and save/load behavior at 60 Hz.

The compatibility camera path still contains an explicit 30 Hz integration
constant in `src/recomp_manual.c`. It is disabled by default, but it is direct
evidence that compatibility/diagnostic code also needs an FPS-coupling audit.

### Experimental only

- 90/120/144 Hz simulation;
- uncapped simulation;
- frame-generation or interpolation presented as retail output;
- changing movie clocks to follow the gameplay rate.

Above 60 presentation should use a proven 30 or 60 Hz simulation plus host-side
interpolation. It must remain opt-in until interpolation is visually verified
and confirmed not to mutate guest state.

## State-specific acceptance gates

Each frontend/gameplay state must run at the rate selected by untouched retail.
A diagnostic override is never promotion evidence. A state passes only with:

1. equal event order and mission/script outcomes at equal simulated times;
2. equal movement speed, acceleration, turn rate, camera rate, and input
   thresholds within measured tolerances;
3. no collision, physics, AI, animation, particle, or audio timing divergence;
4. xemu-matched boot, movie, frontend, loading, and cutscene transitions;
5. stable two-minute gameplay and save/load replay without crash or stall;
6. frame telemetry showing one second of simulation per second of wall time,
   excluding measured loading stalls.

The maximum accurate FPS is the highest rate retail selects for that state and
the recomp passes at that rate. A booting rate, a high average FPS, or a visually
smooth menu is not sufficient evidence.

## 2026-09-25 internal smoke baseline

Two forced-rate hidden runs confirmed that both policies are reachable. They
crossed the blocking startup movies, so their low later windows measured native
movie cadence rather than a frontend performance ceiling:

- 30 Hz (`build-internal/recomp-internal-64972.log`): first two five-second
  windows measured 29.686 and 26.645 loop FPS.
- 60 Hz (`build-internal/recomp-internal-65964.log`): first two five-second
  windows measured 58.680 and 31.720 loop FPS. The second window accumulated
  100 late frames and advanced only 2.650 simulated seconds in 5.013 wall
  seconds.

An untouched isolated xemu runtime snapshot later established the relevant
frontend policy directly: renderer `0x0027D620` held refresh flag 2, divisor 1,
and interval 1 after the startup movie sequence. This is the retail 60 Hz
frontend baseline.

After changing the recomp default to follow retail, internal run
`build-internal/recomp-internal-28792.log` held 59.981-60.159 FPS for eight
consecutive five-second frontend windows with no late frames after transition.

The longer `build-internal/recomp-internal-67864.log` run covered 295.558 stable
frontend seconds after transition. Across 59 five-second windows it averaged
59.915 FPS; p95 interval averaged 16.667 ms. Two isolated occluded-Present host
stalls (147.571 and 225.312 ms) caused five late frames and a worst window of
56.966 FPS. This is not a perfect five-minute pass. The surrounding guest work
remained about 2.0-2.4 ms per frame, and all following windows immediately
returned to 60 FPS, so the next investigation is hidden/occluded DXGI present
behavior rather than guest simulation or menu rendering.

The host now skips only the final DXGI Present call when Windows confirms the
private internal-test HWND is invisible. Guest rendering, render-queue work,
the presentable-surface copy, and optional capture remain active; visible player
windows retain the original Present path. Follow-up run
`build-internal/recomp-internal-69988.log` covered 305 stable frontend seconds.
It averaged 59.932 FPS with p95 16.667 ms and had one 237.667 ms render-queue
stall (two late frames); the remaining 304 seconds immediately returned to 60.
A 155-second fine-profile follow-up (`recomp-internal-3352.log`) did not
reproduce a post-transition hitch. Sustained guest/menu work remained roughly
3-4 ms per frame versus the 16.667 ms budget, so no persistent menu performance
bottleneck is present. Literal zero-hitch promotion still requires a clean
visible-window run because an isolated Windows scheduling pause cannot be
eliminated by changing retail game timing.
