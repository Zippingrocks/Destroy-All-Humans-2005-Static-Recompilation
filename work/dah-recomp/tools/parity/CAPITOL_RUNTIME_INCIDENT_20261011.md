# Capitol runtime incident — 2026-10-11

## Observations

The retained Capitol run reported three non-null indirect targets that were
missing from the recomp.  All addresses and boundaries below come from the
retail XBE.

| Target | Caller return | Retail evidence | Observed symptom |
|---|---:|---|---|
| `0x0002C6E0` | `0x0001E9E6` | vtable `0x002281D8`, slot `+0x18`; `0x171`-byte callback | Silhouette/pre-reveal actor state rendered incorrectly |
| `0x0001F500` | `0x000955A9` | vtable `0x00227404`, slot `+0x04`; `0x157`-byte event dispatcher | Sonic Boom and Quantum Deconstructor ammo pickups did not apply |
| `0x00075330` | `0x00074C6F` | vtable `0x0022C128`, slot `+0x04`; eight-byte forwarding thunk | callback skipped, followed immediately by a null indirect call and access violation |
| `0x0002BFB0` | `0x0001EC2D` | vtable `0x002281D8`, slot `+0x0C`; `0x32`-byte scalar deleting destructor | actor cleanup callback skipped earlier in the same run |
| `0x00074DD0` | `0x00093DCA` | vtable `0x0022C128`, slot `+0x0C`; `0x3A`-byte transform/state callback | tower state update skipped repeatedly |
| `0x00075410` | `0x00075571` | vtable `0x0022C128`, slot `+0x34`; `0x1E`-byte scalar deleting destructor | tower object/list state corrupted, followed by null calls and access violation |

The crash signature is `DAH-CE45648D31F5AFCD`.  Immediately before the
access violation, `0x00075330` was skipped.  Retail advances `this` by
`0x14` and tail-dispatches slot `+0x34` of the contained object.  The recomp
instead preserved the caller's stale return registers; the next call at
`0x000760DA` used a null target and faulted.  Restoring the thunk removes that
specific causal chain.  The run happened near a Tesla tower, but the evidence
does not establish a retail class name for the object, so the implementation
uses only its address-derived name.

A second encounter produced crash signature `DAH-5CE241E1BBDBD156` and
advanced farther into the same retail object lifecycle.  It called
`0x00074DD0` six times, then skipped `0x00075410` from the object release path
at `0x0007556E`.  The caller immediately consumed the object and list state
that the missing destructor should have updated; two null indirect calls and
the access violation followed.  Both callbacks are now lifted directly from
the retail bytes.  The earlier `0x0002BFB0` actor destructor seen in that run
is restored as well so the encounter cannot accumulate stale actor state.

`0x0001F500` compares four retail event hashes and routes each supported event
through an object-specific handler, falling back to the base dispatcher for
other events.  The missing call occurred at the interaction dispatch site and
is the strongest retained evidence for the failed saucer-ammo pickups.  The
restored callback is expected to repair that path, but pickup parity remains
open until a new run confirms that both ammo counters increase and the pickup
objects complete their retail lifecycle.

## Repair and validation

The three callbacks are byte-checked by
`tools/lift_callback_0002C6E0.py` and
`tools/lift_crash_callbacks_20261011.py` and
`tools/lift_tesla_tower_callbacks_20261011.py`.  Their addresses are retained in
`icall_seeds.json`, dispatched by `recomp_manual.c`, and included in the
cumulative crash-callback audit.

Validation performed after the repair:

- full native executable build;
- keyboard and stick-conditioner CTest suite;
- cumulative callback audit: 111 seeds dispatchable, no seeded no-op stubs;
- retained-log audit: all 12 non-null observed callback targets dispatchable.

## Required playtest

1. Replay the pre-reveal Silhouette scenes and compare her model, animation,
   and reveal transition with retail xemu.
2. Approach and collect Sonic Boom ammunition; confirm the pickup disappears
   at the retail moment and the ammunition counter changes once.
3. Repeat for Quantum Deconstructor ammunition.
4. Exercise the Tesla-tower encounter and confirm neither prior crash
   signature recurs, `0x00075330`, `0x00074DD0`, and `0x00075410` no longer
   appear as unresolved calls, and no following null call occurs.
