# Retail and alpha debug restoration plan

The alpha PDB makes debug restoration realistic, but it should be restored as
an evidence tool in stages. Debug code must stay optional and must never alter a
normal parity run.

## What survives

The alpha symbols name substantial facilities including
`Driver::Debug::Console`, script registration and handlers,
`Core::DebugSymbol`, Havok visual debugger/display code, body/contact/constraint
viewers, cameras, renderer inspection and collision views.

Retail still contains names including `SetActorDebug`,
`SetActorDebugDistance`, `SetActorDebugFlags`, `SetRoadDebug`,
`SetRoadDebugFlags`, `SetDebugFadeDeadObjects`, `GetDebugPhysicsFlag`,
`DebugPhysics`, `debugsymbol`, `driver::debug`, and `schemeCommands`. This is
strong evidence that parts of the same naming conventions and registration
surface reached retail. It is not evidence that every alpha command retained
the same address, layout or semantics.

There is already one exact validation of this method. Alpha
`UFO::PlayerObject::ProcessScript` at `0x0002A540` and retail `0x00083A50`
share the same script-command hashes and table order around
`SetJetPackEnable`, including hash `0x47A92D5E`. Both command branches parse a
Boolean and store its inverse in the player object, with the expected retail
layout shift. This proves that some command names, hashes and dispatch
semantics survived; it does not grant a blanket mapping to unrelated symbols.

## Phases

1. **Inventory only.** Cross-index alpha PDB symbols, retail strings, retail
   xrefs, vtables and function candidates. Record hashes and evidence level.
2. **Read-only host adapter.** Expose current object/state/call information
   already available to the recomp through bounded logs and the existing local
   console. Do not open retail TCP listeners or depend on Xbox devkit services.
3. **Draw-only overlays.** Restore proven retail actor, road, collision,
   physics, camera and streaming visualizers behind explicit `DAH_DEBUG_*`
   gates. Verify that enabling an overlay does not change simulation results.
4. **Interactive commands.** Restore mutating commands only when their retail
   registration and implementation are mapped. Keep them in internal builds;
   label any run that uses them as diagnostic rather than parity evidence.

## Symbol validation

For each proposed retail name, store retail address/range, alpha address/name,
retail and alpha hashes, caller/callee comparison, constants, field offsets,
vtable slot, strings/xrefs, evidence level and reviewer notes. Accept exact or
structurally proven mappings. Keep uncertain names as aliases in the evidence
database rather than compiling them into source comments as facts.

## Safety and accuracy rules

- Normal builds and runs remain unaffected unless a debug gate is enabled.
- Debug rendering may read simulation state but cannot write it.
- Do not reuse alpha addresses directly in retail code.
- Do not restore networking or remote-control surfaces until a local,
  read-only workflow is complete and there is a specific need.
- Do not use debug commands to bypass the behavior being tested.
- Every overlay or command logs its own activation in the run identity.

The first useful targets are collision/body visualization, actor resource and
class labels, streaming/render eligibility, mission event/state display, and
ability flags such as jetpack enable. Together these expose the whole EMP chain
without guessing gameplay behavior.
