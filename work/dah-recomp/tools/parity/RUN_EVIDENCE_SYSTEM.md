# Run evidence system

Every normal recomp launch owns one immutable directory under
`debug-runs/<UTC>-p<PID>-<executable-hash>/`. This prevents evidence from a
previous playthrough from being mistaken for evidence from the current one.
`dah_current_run.json` remains a small pointer to the latest directory for
automation.

Each directory contains:

- `manifest.json`: run identity, executable hash, paths, and exit state.
- `runtime.log`: the existing text diagnostics and callback evidence.
- `events.jsonl`: ordered structured events with a shared sequence and world
  tick. The game thread only appends fixed-size records to a bounded ring; a
  below-normal-priority writer performs file I/O.
- `anomalies.jsonl`: stable fingerprints derived from the event stream. The
  first version detects every missed 30 Hz frame budget, short scene
  visibility flashes, loss of Crypto's render object, HUD/cinematic overlap,
  and trace overflow.
- `summary.json`: per-run counts, the worst measured frame, and dropped-event
  status. A missing summary means the process did not reach orderly shutdown,
  which is useful crash or forced-exit evidence rather than a clean pass.

Run `python work/dah-recomp/tools/parity/summarize_debug_runs.py` after one or
more playthroughs. It writes `debug-runs/index.json` and `ISSUE_INDEX.md`,
groups matching fingerprints across builds, retains representative details,
and records which issues recur. A partial final JSONL record is ignored so a
crash cannot invalidate earlier evidence.

During a live playthrough, open the developer console and enter
`mark <short note>` at the moment something looks wrong. The note is written
to both structured streams with the same sequence and world tick as automatic
events, providing a reliable anchor for the frames immediately around an
observed bug.

The fingerprints are triage signals, not proof of an emulation error. A frame
budget miss may be caused by host scheduling, and a visibility transition may
be intentional. Promotion to a parity bug still requires a matched retail
xemu checkpoint or direct retail code/data evidence. This distinction keeps
the watcher useful without turning heuristics into gameplay patches.

Environment overrides remain supported. `DAH_LOG_PATH` and `DAH_EVENT_TRACE`
can redirect the two primary streams for controlled automation, while the run
manifest, anomaly stream, and summary stay grouped by session. Setting
`DAH_EVENT_TRACE=0` disables structured tracing for a performance control run.
