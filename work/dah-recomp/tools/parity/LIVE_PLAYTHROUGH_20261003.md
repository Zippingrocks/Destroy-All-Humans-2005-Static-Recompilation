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

- Kernel ordinal 256 remains unresolved at startup.
- `ExQueryNonVolatileSetting` index `0x104` is unhandled.
- Invalid mutant releases occur in bursts during movie lifecycle boundaries.
- The save-selection screen repeatedly reopens metadata and payload files for
  all three slots while idle, accompanied by a high-frequency stream of
  unhandled `0x104` nonvolatile-setting queries. Determine whether retail polls
  this state continuously or whether a missing result prevents the menu from
  settling.

These did not crash or stall the shell during this observation period.

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
complete bridge-handle tokens. This restores the ordering supplied by the Xbox
scheduler without changing decode cadence after startup. The identical hidden
route changed from 39–52 invalid `NtReleaseMutant` calls per launch sequence to
zero. A 170-second isolated route then opened all three expected movies; every
open reached `first decoded frame ready`, with zero release errors, failed
presents, or invalid simulation steps. The regular movie scheduling harness
also passed all 3,811 assertions.
