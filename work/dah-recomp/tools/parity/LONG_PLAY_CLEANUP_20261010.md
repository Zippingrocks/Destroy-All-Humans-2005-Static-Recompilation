# Long-play cleanup callback — retail repair

The October 10 follow-up run observed four unresolved indirect calls to retail
address `0x0002A1A0`. Every call came from `0x0001EC2A`, which iterates a
container and invokes vtable slot `+0x0C` with the deleting flag set. The
objects carried retail vtable `0x002280A0`; its slot at `0x002280AC` stores
`0x0002A1A0`.

Retail instructions show the scalar deleting cleanup entry. It restores the
class and secondary-base vtables, destroys the members at offsets `+0x13C`
and `+0xB0`, runs the base cleanup, and frees the object when requested.
Ordinary discovery merged this entry into the adjustor-thunk function that
starts at `0x0002A190`, so calls to the internal entry had no dispatch target.
Skipping it retained four complete objects and their member state through a
long death/reload session.

The callback is separately lifted from retail bytes
`0x0002A1A0..0x0002A1E9`. Its exact table slot, boundary, and hash are recorded
in `tools/analysis/results/longplay-cleanup-callback-evidence.json`. The repair
uses only the verified retail XBE.

The same run contained seven world-clock resets. Crypto's render word reached
the expected death value `FFFF0001`, the player object was removed during the
level teardown, and a fresh Crypto object returned with `FFFF0100` before
becoming active at `FFFF0101`. No depth allocation failed, and the depth
surface was correctly rebound when its retail format changed. This narrows
the remaining long-session risk to skipped retail lifecycle callbacks such as
this destructor rather than a failed Crypto respawn or depth-cache exhaustion
in this run.
