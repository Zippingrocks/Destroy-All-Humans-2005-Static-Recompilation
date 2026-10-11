# PDB boundary and retail vtable audit — 2026-10-07

## Finding

The March 2004 `ufo.pdb` is more than a naming reference. Its 9,652 code
symbol addresses are original compiler/linker entry boundaries. The heuristic
alpha disassembly contained only 8,735 of those addresses as function starts,
so it had merged or omitted 917 valid entries. The missing set includes methods
for Cortex Scan, Death Ray, Holobob, Hypno Ray, Zap-O-Matic, Crypto, the
saucer, pedestrians, vehicles, particles, camera and animation systems.

`tools/analysis/compare_whole_alpha_retail.py` now augments the alpha inventory
with every PDB code-symbol boundary before comparing function shape. It also
extracts retail class IDs directly from vtable-referenced instruction entries,
rather than requiring the retail disassembler to have guessed each six-byte
method boundary. This proves 58 of 64 named alpha class IDs survive unchanged
in retail. Only `ActorSamSite`, `ParticleEffect`, `CameraObject`, `AnimObject`,
`WeaponBrainRay`, and `WeaponCloak` remain unmatched by ID.

## Recovered retail callbacks

Scanning every retail instruction address exposed two aligned vtable entries
that were executable in the XBE but absent from the recomp dispatcher:

| Retail entry | Original range | Retail table evidence | Result |
|---|---|---|---|
| `0x00016A90` | `0x00016A90..0x00016B47` | traffic actor tables at `0x00226800`, `0x00226998`, and `0x00226B68` | 183-byte event/effect callback lifted and dispatched |
| `0x0009A210` | `0x0009A210..0x0009A22E` | class `0x2786C33B` table slot `0x0022F3DC` | 30-byte scalar deleting destructor lifted and dispatched |

`tools/lift_static_vtable_callbacks.py` verifies the retail XBE table slots,
instruction boundaries, branch targets and SHA-256 hashes before generating
`src/recomp/gen/recomp_static_vtable_callbacks.c`. The evidence record is
`tools/analysis/results/static-vtable-callback-evidence.json`.

The class at `0x0022F3B8` is deliberately left unnamed. Its retail ID does not
match alpha Death Ray, and the PDB comparison prevented the superficially
similar destructor slot from being mislabeled. A retail name will be accepted
only when constructor, class hierarchy, vtable layout and behavior converge.

## Remaining candidates

All 2,895 heuristic retail function starts referenced by pointer tables are
dispatchable. Another 312 internal/raw entries are explicitly dispatchable.
The database retains 368 unhandled internal-address candidates. These are not
368 confirmed missing functions: the set contains switch arms, loop entries
and shared trap/pure-virtual targets. Each future lift requires the same
boundary, table/caller and retail-byte evidence used above.
