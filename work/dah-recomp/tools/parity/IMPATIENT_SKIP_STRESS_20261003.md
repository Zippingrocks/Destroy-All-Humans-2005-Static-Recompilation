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
