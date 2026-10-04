# Farm weapon matrix — 2026-10-04

An internal-only sequence runner accepts a comma-separated weapon list and
uses the original progression store and weapon manager to equip each entry.
`giveallweapons` is the displayed console spelling; the older underscored
spelling remains accepted for compatibility. The firing probes use the retail
left-trigger weapon binding rather than the right-trigger ability binding.

The full Farm sweep granted all 15 progression keys and exercised every
on-foot weapon available in that level. Switching Holobob and Ion Detonator
exposed three omitted retail callbacks at `0x000A56A0`, `0x000A21C0`, and
`0x000A5000`. Their exact retail bodies are now restored and retained as
indirect-call seeds.

The focused post-fix run `recomp-internal-37640.log` equipped Ion Detonator,
fired it, switched to Quantum Deconstructor, completed the sequence, and
recorded no unresolved indirect call or fatal marker. Quantum, Brain Ray, and
the three saucer weapons remain unavailable to the on-foot Farm manager
because that map does not load their original assets; that result is not an
equip regression.

Holobob retains the previously measured xemu parity: state 2 to state 3 takes
62 frames in both xemu and the native recomp. The full native lifecycle also
reaches depletion, undisguise, concentration restoration, cortex scan, and a
second disguise. The restored `0x000A56A0` callback covers the teardown path
exposed while switching away from Holobob during this matrix.
