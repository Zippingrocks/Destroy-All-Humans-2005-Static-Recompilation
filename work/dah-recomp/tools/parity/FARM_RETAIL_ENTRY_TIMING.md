# Retail Farm entry clocks and gates

This is source/trace evidence, not a claim that entry timing or pixels already
match. The baseline observations are native `parity-farm-state-20260926-015`
and reference `renderdoc-runs/farm-renderdoc-20260926-001/state-farm-route.jsonl`.
Original Lua chunks remain intact in that reference run's `farm-paused.ram.bin`.
Offsets below are physical file offsets in this particular RAM artifact.

## Titlecard and control ownership

The retail Lua 4 chunk at `0x03A611A8` identifies itself as
`input/shared/gui/site/input/gui_site_input_titlecard.lua`. Its Handler,
source line 7, performs these actions:

- Activation starts a 3-second timer, pauses simulation, sets
  `playerLocal.noHalting`, and adds the titlecard input section.
- Generic player-one button input shortens the timer to 0.01 seconds.
- Timer expiry deactivates the display titlecard, pops the input section,
  resumes simulation, stops the cinematic sound mix, and clears
  `playerLocal.titleCard`.

The separate display chunk at `0x03A2FF98`,
`gui_site_display_titlecard.lua` Handler line 19, polls the title material's
`IsLoaded` every 0.01 seconds. Once loaded, it activates the title image and
starts `fadeIn` for 0.5 seconds. A subsequent 0.5-second timer activates the
subtitle if the display-subtitles setting is enabled. Thus the display's
resource readiness and fade are separate from the input titlecard timer.

Both existing traces commit Farm at world tick zero, reach world tick one and
pause, then unpause after 88 paused-loop samples. Native commit/pause/unpause
loops are 3704/3705/3793; reference loops are 3838/3839/3927. The common pause
pattern supports the retail gate. It does not establish equal loading latency
or an exact displayed-frame match between their differing observation phases.

Later instrumented runs demonstrate that 88 is not an engine invariant.
Native 018 is paused at loops 3442..3519 (78 observations); reference 004 is
paused at 3842..3930 (89 observations). The source timer is three seconds of
the timer manager's measured millisecond delta, so loop counts vary with host
pacing and debugger overhead. Never tune a fixed loop count to these samples.

The chunk at `0x03A67630`, `common_cinematic.lua`, provides the release path.
`Stop`, source line 197, pops the cinematic input section, stops the engine
cinematic, starts its callback objective, activates the reticle, clears
cinematic immunity/noHalting/FreezeConcentration, unblocks stimuli, and sets
`cinematic.current` to an empty table. The regular ready callback starts the
engine cinematic and requests a 0.9-second fade in. Finishing may also request
a 0.9-second fade, subject to the original holdblank/nofadeout/type branches.

Movement state 20 and camera-update byte 1 remain present during the cinematic
and gameplay, so neither is a control-release predicate. The original
`siteMovement.Update` asks `gui.input.GetAccess('Game')` and supplies zero
movement when access is absent. Use ended cinematic state, restored input
section, and the original callback/control flow to identify the release.

The Lua chunk format/opcode definitions were checked against the official
[Lua 4 undumper](https://www.lua.org/source/4.0/lundump.c.html) and
[opcode definitions](https://www.lua.org/source/4.0/lopcodes.h.html).

## Three clocks must remain distinct

`sub_000DAC90` calls `000D8300`, which obtains current milliseconds from
`000D83E0`, writes the difference to timer manager+0x28, and stores the current
time at +0x24. `000D8330` reads that difference; the main loop converts it to
seconds with the original 0.001 float before update. Native `000D83E0` now
uses integer monotonic milliseconds through `dah_monotonic_milliseconds`.

World step selection is `001049F0`:

- If world+0x303D is set, use measured delta capped at 0.1 seconds.
- Otherwise use renderer divisor divided by its 60- or 50-Hz refresh setting.
- Store the result at world+0x10. World update `00105280` increments world tick
  +8 and elapsed time +0x0C only when world+0x303C is not paused.

Engine cinematic start `00111EE0` clears cinematic elapsed, changes lifecycle
to playing, and sets world+0x303D. Stop `00111F90` clears that flag. Update
`00111CE0` advances cinematic elapsed+0x6C by its supplied delta, clamps to
duration+0x68, evaluates animation/events, and finishes at the duration.
The cinematic manager is still updated in `0005C930` while world simulation
is paused. World tick, world elapsed, and movie elapsed are therefore distinct.

The in-engine movie list is `[0x286784]`, with sentinel manager+8; list-node+8
is the movie object. Original/derived movie classes preserve duration+0x68,
elapsed+0x6C, flags+0x70, and lifecycle+0x74. Existing Bink `movieHeader`
observations do not describe this Farm cinematic. The dedicated cinematic
observer documents and validates the actual list in `FARM_CAPTURE_PHASES.md`.

In baseline015, native gameplay resumes at world elapsed approximately
84.2326 seconds/tick2527. Reference001 resumes near 84.2873 seconds/tick2709.
The different tick counts cannot justify inserting 182 frames of delay:
the cinematic runs on measured deltas and debugger stops affect those deltas.

## Original backbuffer behavior and the extra host hold

Renderer `[0x250E60]` has a saved backbuffer texture at +0x484 and an enable
byte at +0x488. Its vtable slots +0x54/+0x58 invoke `000E0A20`/`000E0A30`,
which set/clear the byte. Script registration `000E44C0` names these
`EnableBackBuffer` and `DisableBackBuffer` through `000E4480`/`000E4490`.
`000E08E0` creates/copies the saved texture and writes a black outer border.

Original `000E0F50`, recovered in `recomp_seeded.c`, performs clear/state setup
and draws the saved fullscreen texture only when +0x488 is enabled and +0x484
is nonzero. Those guest-controlled conditions are the evidence for whether a
saved frame should be shown during loading.

The native host's `dah_farm_presentation_hold` added a separate gate while the
simulation continued. Baseline015's hold released at loop4064 only through
its 360-warm-frame fallback, after the entire native titlecard and the start
of the cinematic. It was not the titlecard timer or a retail backbuffer flag.
Removing that extra gate exposes original rendered frames; it does not by
itself prove the underlying loading image or fade matches reference pixels.
Capture renderer+0x488/+0x484 and GUI fade state when diagnosing an early black
reference image versus visible native loading artwork.

## Comparison protocol under debugger pauses

Record normal Hangar Invade, Farm backend commitment, titlecard activation,
title-material readiness, titlecard dismissal, cinematic playing/elapsed,
fade transitions, cinematic finish, and restored game input as separate
milestones. For each retain the retail loop, world tick, world elapsed/step,
paused/realtime flags, exact cinematic elapsed bits, active GUI sections,
renderer backbuffer state, input result, and image association.

Native `000DAD3C` observations occur after the retail loop; reference
`XInputGetState` observations occur before returning a controller result.
Establish their phase relationship before interpreting an equal loop number
as an equal instant. Compare cinematic images by the same resource, lifecycle,
and elapsed time, then compare individual event crossings and rendered frames.
Do not align the entire cinematic by world tick or independently shift every
frame to obtain a visually convenient match.

RSP-paused wall time is not original loading/cinematic time. Preserve stop/read
overhead and mark the run perturbed; use the game's actual clock fields for
phase diagnosis. True presentation pacing requires an uninterrupted reference
capture or another clock/capture method whose interruption effects are known.
Never change a guest timer, seed, transform, or movie position to manufacture
equality in an accuracy run.

Finally, original `site_startup.lua` PostStart line27 (chunk `0x03AA26F0`)
calls `random.SetSeed()` with no argument before player initialization.
Dispatcher `0011507E` uses the default clock-based seed path. Preserve and
record RNG provenance; equal input scripts alone do not guarantee identical
random state or every background actor's pose.
