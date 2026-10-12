# DAH1 PC port completion standard

This project measures completion by proven retail behavior. A change does not
receive completion credit merely because it removes a crash, makes an object
visible, or permits a mission to continue.

## Change classes

Every native function and generated-code hook must be recorded in
`port_integrity_manifest.json` as exactly one of:

- **retail-restoration** — code and calling convention recovered from a
  verified retail XBE boundary;
- **parity-implementation** — behavior recreated from repeatable retail
  evidence where direct translation is not yet available;
- **compatibility-layer** — the PC host bridge for input, timing, filesystem,
  audio, windowing, graphics API, or exception semantics;
- **diagnostic-instrumentation** — observational capture or tracing that does
  not change retail game state;
- **development-tooling** — explicitly invoked commands and controlled test
  setup excluded from ordinary play;
- **temporary-mitigation** — a provisional gameplay-affecting workaround.

Only a verified `retail-restoration` receives function-restoration completion
credit. The other classes remain visible and are evaluated by their own
acceptance criteria. A temporary mitigation never counts as completed work.

## Required evidence for a gameplay fix

1. Record the run identity, executable hash, level, checkpoint and input
   sequence.
2. Identify the earliest proven divergence rather than the last visible
   symptom.
3. Preserve the retail function bytes, exclusive boundary, callers, callees,
   calling convention, vtable slot or event identity.
4. Restore the smallest proven boundary without inventing game state.
5. Compare the same checkpoint and input sequence in native and retail xemu.
6. Test the original trigger, checkpoint reload, area reload and an unrelated
   negative-control scene.
7. Record remaining uncertainty. An untested expectation is not a pass.

## Automated gates

`tools/audit_port_integrity.py` fails when it finds:

- a native `dah_*` function absent from the manifest;
- a stale classification that no longer exists in source;
- a generated-code native hook absent from the manifest;
- an unclassified manual dispatch override;
- an indirect-call seed that still reaches a no-op recovery stub;
- a checked-in ledger that does not match the source tree.

`tools/audit_crash_callbacks.py` independently verifies accumulated callback
implementations, dispatch, retained crash observations and known retail table
sets. Both checks are required because callback completeness does not prove
mission, animation, timing, rendering or pixel parity.

## Scenario closure

A scenario can be marked complete only when its input, game state, actor
lifecycle, mission events, animation, effects, render sequence, audio/HUD
timing and final frames match the retail reference within documented limits.
It must also survive death/restart, checkpoint reload, area reload and a long
session without introducing unresolved calls, observer anomalies or a new
crash signature.

A level is complete only after every mission, side activity, cinematic,
weapon, vehicle, ability, death/restart path and return-to-mothership path has
closed scenarios. The PC port is complete only when all levels and frontend
flows are closed, recovery no-op stubs reachable by retail behavior are gone,
temporary mitigations are zero, and broad exploratory runs produce no
unexplained divergence.

## Current truth

`PORT_INTEGRITY_LEDGER.md` is generated from source and the classification
manifest. It is an accounting of known native intervention and debt, not a
percentage claim. Percentages may be published only for a denominator that is
explicitly enumerated, such as verified callbacks in a named vtable or passed
scenarios in a versioned scenario suite.
