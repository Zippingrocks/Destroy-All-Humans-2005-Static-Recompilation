# Idle-scene frame pacing — 2026-10-04

The live release run reproduced visible periodic stutter in the front-end idle
scene and its attract movie. Presentation itself remained healthy: the runtime
reported no failed presents, invalid simulation steps, unresolved callbacks,
or fatal markers. Individual frame intervals nevertheless spiked from the
normal 16.67 ms cadence into the hundreds of milliseconds, with several
startup/idle windows reaching 0.5–2.7 seconds.

The release log identified an active diagnostic left over from controller
investigation. `DAH_CAMERA_MEMDIFF_TRACE` defaulted on during ordinary play and
dumped 512 camera bytes every 30 input polls. Each snapshot used 128 formatted
writes on the guest thread while the runtime log was deliberately unbuffered.
The lower-frequency Rockwell pose recorder also defaulted on. Both probes are
now opt-in and remain available by setting their environment variables to `1`.

Hidden validation run `recomp-internal-35896.log` recorded zero camera-memory
dumps, zero Rockwell pose dumps, and zero fault markers. After startup movie
work, its ordinary idle windows held approximately 60 Hz; p99 frame intervals
were normally about 16.7 ms and most five-second windows had maximum intervals
between 16.7 and 17.1 ms. The still-running pre-fix release provided an
additional control: once its old trace reached its built-in 30,000-poll limit,
the next three live windows held 60 Hz with maximum intervals of 16.668,
16.719, and 16.704 ms. This isolates the recurring idle stutter to synchronous
diagnostic I/O rather than game simulation or presentation failure.
