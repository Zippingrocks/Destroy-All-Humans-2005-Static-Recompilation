# Alpha/retail crash audit — 2026-10-07

## Preserved crash inventory

The current crash database contains one unique native exception:
`DAH-1AF563F1251E7840`, an access violation in the host translation of retail
`0x001066F0`. The report and dump are preserved under the workspace
`crashlog/` directory. The bad read is the final fault, not the first bad
operation.

The causal chain begins at unresolved retail vtable target `0x00015FC0`, called
from `0x00105BD0`, after an earlier unresolved scalar deleting destructor at
`0x00016CA0`. The unresolved fallback restored the pre-call guest stack.
Because the caller had saved a register immediately before dispatch, its later
cleanup popped retail code addresses as object state. The corrupted state then
survived until `0x001066F0` dereferenced it.

Both omitted entry points now have instruction-equivalent implementations and
manual dispatch entries. `0x00015FC0` preserves its conditional tail jump and
normal return; `0x00016CA0` preserves destructor order, conditional delete and
`ret 4` cleanup. The four other callbacks exposed by the same long run
(`0x0003CD20`, `0x0003E2E0`, `0x0004ACC0`, and `0x000A21A0`) also have exact
retail lifts and dispatch entries.

`tools/audit_crash_callbacks.py` checks the crash database, all twelve current
and historical callback bodies, every dispatch entry, the original retail
bytes of the two causal callbacks, and their retail vtable slots. Its compact
output is committed at
`tools/analysis/results/crash-callback-audit.json`.

## Historical failure audit

The Bink guest-memory overrun from PID 41512 was an early bring-up failure.
The original-code comparison found a carry defect; the repaired decoder later
completed both startup movies. PID 10676 subsequently reached a missing VM
opcode at `0x00196A66`. All 49 original opcode-table entries now have bodies
and dispatch, and the exact-handler regression covers that entry. These events
predate the current crash recorder and do not have independent modern crash
signatures.

Six older gameplay callback reports are also closed in current source:

| Address | Original observation | Current state |
|---|---|---|
| `0x00085FE0` | Rockwell alternate embedded-object thunk | exact eight-byte thunk restored and generated dispatch present |
| `0x00041540` | Rockwell/Holobob state forwarding | exact 37-byte routine restored and generated dispatch present |
| `0x00054B20` | Santa gameplay callback | complete `0x13E`-byte lift and generated dispatch present |
| `0x0004F9E0` | Santa gameplay callback | complete `0x164`-byte lift and generated dispatch present |
| `0x0011FA30` | alleged Farm per-actor callback | already implemented; report came from a stale log copied as fresh evidence |
| `0x00143689` | alleged Farm jump-table arm | already implemented; same stale-log incident |

The last two are methodology failures rather than game crashes. They remain in
the audit so stale logs cannot make them look unresolved again.

## What survived from alpha

The original March 2004 PDB and XBE preserve useful engine structure:

- Alpha and retail share the `Traffic::ActorSamSite` class family, a `0x35C`
  object size, corresponding primary/secondary interfaces, and the deleting
  destructor at primary-vtable slot `+0x24`.
- Alpha `Traffic::ActorSamSite::scalar deleting destructor` at `0x0004A0B0`
  structurally identifies retail `0x00016CA0`. A retail runtime capture then
  independently joined this class to four `m_emp_mine` resources.
- `SetJetPackEnable` retains command hash `0x47A92D5E`, command-table order and
  Boolean invert/store behavior between alpha and retail, despite the player
  field moving from alpha `+0x3D8` to retail `+0x360`.
- The collision filter keeps the reciprocal category/mask decision. Retail
  extends the packed filter with a six-bit system group and rejects equal
  nonzero groups.
- `UFO::BuildingFixture` retains class ID `0x6FC7A9F5` and an identifiable
  `ApplyDamage` neighborhood.

## What clearly changed

- The alpha ActorSamSite primary vtable stops being function pointers before
  offset `+0x98`; retail continues through at least `+0xE4`. Missing callback
  `0x00015FC0` is at retail slot `+0xE4`, so it is a retail-added virtual with
  no alpha name or implementation to borrow.
- The same nominal slot is not always the same method after interface changes.
  Retail `0x00109870` at slot `+0x84` does not behave like alpha
  `Traffic::ActorSamSite::Update`, and that tempting name is rejected.
- Final EMP resources and types (`m_emp_mine`, `weapon_emp_detonate`,
  `ActorTypeMineStatic`, and `WeaponTypeDetonate`) are absent from the alpha
  artifact searches. Their retail behavior must come from retail bytes and
  matched xemu observation.
- Historical callback similarity searches produce weak or generic candidates
  for most tiny thunks. They are restored by their exact retail instructions
  and remain unnamed unless class, caller, vtable and runtime evidence agree.

The alpha therefore exposes real family names and earlier engine semantics,
but retail remains authoritative for addresses, expanded interfaces, final
content and precise behavior.

## Validation

- Release build: succeeded with the Visual Studio C++ and Windows SDK
  environment loaded by `tools/build_release.ps1`.
- Project CTest: 2/2 passed.
- VM opcode regression: all 49 original entries resolve; 240 instructions /
  842 XBE bytes checked; 5,765 cases and 3,182,203 assertions passed, including
  four negative controls.
- Startup cleanup regression: eight production wrappers / 466 XBE bytes;
  949 cases passed, including wrong-stack-cleanup and signed-clock negative
  controls.
- Crash callback audit: one preserved signature, twelve implemented and
  dispatchable callbacks, both causal callbacks byte-identical to the retail
  XBE ranges, and the alpha/retail vtable boundary verified.
- Published `DestroyAllHumans.exe` SHA-256:
  `088E4763280473175D547CF053AC5B099C5B4348B0E48D06C9AB0C0042BBD533`.
