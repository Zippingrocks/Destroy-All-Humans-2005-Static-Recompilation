# Impatient skip stress baseline (2026-10-03)

## Scope

`impatient_skip_stress_probe.txt` sends ordinary short Start and A presses,
with complete releases between them, across startup movies, the main shell,
Farm loading, the opening cinematic, and early gameplay. It does not write
menu, progression, cinematic, renderer, or save state. The xemu adapter writes
only the result buffer of the retail `XInputGetState` call.

Both tests ran invisibly. The recomp used its hidden internal runner and a new
save directory. The retail reference ran rendered on the private Windows
desktop `DAHParityDesktop`, from the pinned XBE and XISO, with `-snapshot` and
separate GDB/QMP ports. Only the isolated reference PID was stopped afterward.

## First paired result

| Milestone | Recomp loop | xemu loop |
| --- | ---: | ---: |
| startup backend | 16 | 20 |
| audio backend | 36 | 50 |
| intro backend | 51 | 70 |
| main shell | 546 | 545 |
| Farm backend | 1631 | 1530 |
| opening cinematic removed | 1706 | 1645 |

Neither process crashed, disconnected, or entered a fatal state. Both ended in
Farm, paused by a later Start press, with Crypto as the active focus and no
active cinematic or movie. Their final pointer-independent gameplay fields
agreed on movement state, heading, actor and camera orientation, fixed world
step, and player/actor relationship. Float-bit position differences were tiny
and expected because the fixed-loop inputs reached gameplay at different world
ticks after the unequal Farm load duration.

The Farm-entry delta is not currently evidence of a gameplay logic defect.
The two builds reached the main shell one loop apart. xemu completed the Farm
load earlier, so the same absolute-loop presses landed in different Farm
phases. In each build, the opening cinematic ended on the first A press that
arrived after the cinematic became active. Future gameplay comparisons should
anchor their second input phase to active, controllable Crypto rather than to
the process-wide loop. Absolute-loop input remains useful for deliberately
hostile startup and transition stress.

## Artifacts

- Native state: `build-ninja/impatient-skip-baseline-02-state.jsonl`
- Native log: `build-ninja/impatient-skip-baseline-02.log`
- xemu state: `build-parity-xemu/impatient-skip-xemu-02-state.jsonl`
- xemu input trace: `build-parity-xemu/impatient-skip-xemu-02-input.json`

Build output and traces remain local diagnostics and are not committed.

## Phase-aware follow-up

`impatient_skip_phase_stress_probe.txt` adds an `@gameplay` section with 25
rapid pause/resume, A/B, movement, camera, face-button, shoulder-button, and
trigger events. The xemu adapter anchors this section only after six
consecutive five-loop samples confirm Farm, an unpaused world, no cinematic,
and Crypto as player focus. The native harness keeps its existing stronger
anchor, which also proves player control by moving Crypto with a bounded
forward pulse.

The recomp and hidden xemu ran this route concurrently for 180 seconds. Both
executed every gameplay event without a crash or fatal log entry. Both ended
paused in Farm with Crypto focused, no cinematic or movie, and movement state
20. This result proves stability under the input storm; it is not an exact
gameplay-state comparison. xemu entered Farm early enough for the absolute A
presses to skip its cinematic, while the recomp entered after the final such
press and played the cinematic to completion before establishing its gameplay
anchor. A future transition gate should key the skip press to an observed
active Farm cinematic so both runs enter the gameplay phase from the same
cutscene outcome.

The bounded native runner may kill the process while the final JSONL record is
being written. In this run, 1,475 complete records parsed and the final partial
4,096-character line was ignored. This is a trace shutdown limitation, not a
game-state failure.

## Maximum-event cinematic barrage

`impatient_cinematic_barrage_probe.txt` fills the native harness's 128-event
capacity. It alternates short A, Start, and B presses from startup through the
shell, Farm loading, the opening cinematic, and later gameplay. A separate
phase-relative tail repeats pause/confirm and exercises movement, camera, and
both triggers after controllable Farm gameplay is established.

The recomp and hidden xemu ran the barrage concurrently for 240 seconds. Both
skipped the Farm opening cinematic successfully:

| Milestone | Recomp loop | xemu loop |
| --- | ---: | ---: |
| Farm backend/cinematic observed | 1831 | 1695 |
| cinematic removed | 1926 | 1805 |
| observed cinematic window | 95 loops | 110 loops |

Neither engine crashed, lost its trace connection, retained a movie/cinematic,
or lost Crypto as player focus. Their final paused state differed because the
absolute barrage continued after gameplay and therefore reached different
buttons at each run's different loop throughput. That difference is expected
for this hostile stability route; phase-relative routes remain the correct
tool for comparing equivalent gameplay outcomes.
