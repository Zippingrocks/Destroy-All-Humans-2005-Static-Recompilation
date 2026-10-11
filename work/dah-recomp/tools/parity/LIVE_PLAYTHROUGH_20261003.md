# Fresh interactive playthrough notes — 2026-10-03

Observed passively from PID 9044. The game was never controlled, paused, or
restarted by the observer. After the intro remained black for several minutes,
the player explicitly authorized terminating the stuck process and PID 9044
was ended.

## Stable behavior

- Fresh launch reset `furonlog.log` and `xbox_kernel.log`.
- Shell rendering held 60 Hz with zero failed presents, zero occluded presents,
  and zero invalid simulation steps.
- Initial movie playback held its native 25 Hz cadence and returned cleanly to
  the 60 Hz shell. Movie close cleared the full-screen transition without a
  retained movie frame.
- The first two observed `trailer2.bik` launches opened, decoded, played, and
  returned to the shell successfully.
- The shell recovered immediately and remained stable after every failed movie
  launch was exited.

## Reproducible movie failure

Later repeated launches of `d:\movies\trailer2.bik` opened a nonzero Bink
handle but never emitted `first decoded frame ready`. During each failure:

- the host continued presenting at approximately 25 Hz;
- `draw-frame-fps` fell to zero and the cumulative draw count stopped;
- the movie transition remained on its guarded black frame;
- the process remained responsive and reported no failed presents;
- exiting the movie restored normal 60 Hz shell drawing immediately.

This repeated on three consecutive launches. Detailed frame counters then
showed that Bink decoding continued normally throughout each black screen;
decoded and current-frame indices advanced together while the render callback
submitted no movie quad. The failure is therefore render-turn starvation,
not movie worker or decoder startup.

The same failure then occurred on `d:\movies\intro.bik` immediately after the
save-selection flow (`ecx=00F7F8A0`). The file returned a valid Bink handle and
decoded more than 1,400 frames while no movie quad was submitted. This proves
the defect is not specific to `trailer2.bik` or the Archives UI.

Each affected launch coincided with a burst of
`NtReleaseMutant: ReleaseMutex failed (error 6)` messages. The same mutex
errors also appeared during successful movie playback. They remain a separate
kernel follow-up and are not evidence for this render failure.

## Archives scheduling scope correction

Observed Archives launches do not use one fixed path-buffer address.
`trailer2.bik` launched with `ecx=00F7F914`, while earlier verified Archives
entries used `ecx=00F7F9E4`. The address-only Archives classification therefore
did not cover every Archives movie and could never cover the new-game intro.
The correction keys cooperative yielding to the proven regular movie-update
return address instead, so all movies return to the host render pump when
their next Bink frame is pending while open/preload remains blocking.

## Baseline kernel follow-ups

- Kernel ordinal 256 (`PsQueryStatistics`) was resolved on 2026-10-03. The
  bridge validates the retail 12-byte structure and reports active guest
  threads plus live guest handle tokens, removing the startup unresolved-export
  diagnostic without replacing it with a success-only stub.

## Known-bug sweep after the worker fix

The hidden `knownbugs-20261003b` phase-aware skip route completed through the
front end and into `blocks\\sites\\farm`. Its final state retained Crypto, the
weapon manager, HUD and world, with zero unresolved calls, fatal/exception
markers, failed presents or invalid simulation steps. The core input tests pass
2/2 and the movie scheduler passes 138 scenarios / 3811 assertions in every
environment variant.

The older cow-scan route's fixed front-end frames could remain in the shell
after movie cadence changed. It now includes the same input-poll-time startup
taps as the successful phase-aware route before switching to frame-bound menu
inputs; gameplay scan inputs remain anchored to active Crypto.

Validation `knownbugs-20261003d` reached Farm, activated Crypto, and delivered
both gameplay-anchored scan holds. Its movement replay stopped at
`(943.500, 524.394, 9.971)` without acquiring the cow, so it did not exercise
the scan callbacks and is not counted as a new cortex pass. The last completed
functional proof remains `cortex-cow-current6`, which exercised the full
`20 -> 250 -> 251 -> 254 -> 20` chain twice with no unresolved targets. This is
tracked as route targeting drift rather than a claimed gameplay regression.
- `ExQueryNonVolatileSetting` index `0x104` is now handled as
  `XC_FACTORY_GAME_REGION` and returns the North America retail region used by
  this title. This removes the unknown-setting result from save-slot polling.
- The worker-handle initialization fix removed the invalid mutant-release bursts
  from fresh movie runs.
- Save selection continues to poll metadata for all three slots while idle.
  Fresh runs show no error or failed mutation, so this remains observed retail
  behavior rather than a confirmed defect.

## Repeated-playback worker startup race

A later live run reproduced a distinct failure on the third consecutive
`trailer2.bik` launch. The open returned handle `02A457C0`, but no first frame
became ready and the host presented zero-draw black frames at 60 Hz for more
than one minute. PID 53196 was terminated only after that condition remained
unchanged across twelve five-second samples.

Bounded kernel instrumentation identified the invalid mutant arguments before
handle translation: Bink worker threads passed `00000000`, `00000003`, and
`0006000D`, while every successfully created bridge handle began with `48`.
`sub_0020E580` creates the worker and only then publishes its mutant and event
at worker-object offsets `+0x14` and `+8`. A native Windows thread can run
immediately and read those fields before the creating guest thread finishes
that compact initialization sequence. Reused worker memory explains why later
launches read nonzero stale values instead of the initial zeroes.

`sub_0020E510` now gates only the Bink worker entry until both sync fields hold
complete bridge-handle tokens. This restores the missing startup ordering
without changing decode cadence after initialization. A short hidden route and
a 170-second route both produced zero invalid releases; all three movie opens
reached `first decoded frame ready`, with no failed presents or invalid
simulation steps. The regular movie scheduling harness also passed all 3,811
assertions.

A longer route that allowed `trailer2.bik` to end naturally exposed a separate
teardown race. Each natural close produced a tight invalid-release burst (50 on
the first close and 64 on the second). The immediate reopen after the first
close decoded successfully, but the third open stalled before its first frame.
The startup gate is therefore retained as a verified fix for the initial
unpublished-handle race, while natural-close teardown remains under
investigation and is not counted as clean yet.

Failure-only tracing later caught the natural-close/reopen defect without
materially perturbing scheduling. Immediately after call 4 reused the prior
movie allocation, workers attempted to release stale tokens `48000009` and
`4800000D`; both table entries had already been closed and resolved to null.
The entry gate had accepted them because recycled worker memory still carried
valid-looking `0x48` tags. `sub_0020E580` now clears its event (`+8`) and mutant
(`+0x14`) slots before creating the native worker. The gate can therefore pass
only after the creator publishes the replacement handles. On the identical
route, call 3 then closed naturally and call 4 reopened the same movie address,
reached its first decoded frame, and recorded zero invalid releases.
