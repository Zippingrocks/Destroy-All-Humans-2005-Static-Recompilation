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

Each phase has a concrete exit condition. Inventory ends when every proposed
name has an evidence-ledger row. The read-only adapter ends when it can identify
the actor/resource, mission objective, body/filter, last contact, ability flags
and relevant call boundaries in one timestamped run. Draw-only overlays end
when enabled and disabled runs produce identical simulation traces. A mutating
command is eligible only after its retail registration hash, argument parsing,
state writes, callers and reset behavior are byte- or structure-matched and a
normal build cannot invoke it accidentally.

## Symbol validation

For each proposed retail name, store retail address/range, alpha address/name,
retail and alpha hashes, caller/callee comparison, constants, field offsets,
vtable slot, strings/xrefs, evidence level and reviewer notes. Accept exact or
structurally proven mappings. Keep uncertain names as aliases in the evidence
database rather than compiling them into source comments as facts.

When retail function discovery omitted a callback, use the byte-audited start
and exclusive end with `match_alpha_retail_symbols.py --retail-address ...
--retail-end ...`. The tool hashes its inputs and compares that exact range.
This keeps missing discovery metadata from blocking symbol work while still
requiring manual vtable, class-ID, signature and behavior validation.

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

The first class-level proof is now recorded for retail primary vtable
`0x00226A80`: constructor layout and size, corresponding vtables, the
deleting-destructor slot, and neighboring methods identify alpha
`Traffic::ActorSamSite`. Retail expands the primary interface beyond the alpha
table; restored retail callback `0x00015FC0` is at added slot `+0xE4`. The blanket
observer uses that name and reports the runtime resource separately. A Santa
Modesta capture has now joined four instances to `m_emp_mine` and shown a
non-null body on each one. This is the model for restoring later debug labels:
prove the class, observe which asset or mission object uses it, then trace the
specific state transition that is wrong.

The first physics-level proof follows the same rule. Alpha
`Physics::CollisionFilter::isCollisionEnabled` maps structurally to retail
`0x00135F00`; retail helper `0x00135EA0` exposes the evolved packed layout and
the exact pair decision. This supports a read-only overlay showing object name,
category, system group, collide mask, pair acceptance, body state and last
contact. It does not support forcing contact or changing a mask. Shape,
broadphase and contact-callback instrumentation remain separate stages.

The first explicit rejection is equally useful. Alpha primary-vtable slot
`+0x84` names `Traffic::ActorSamSite::Update`, but retail slot `+0x84` points
to `0x00109870`, which takes two arguments and handles a collision/event
payload rather than rebuilding the alpha SAM-site transform. That candidate is
recorded as rejected in the ledger. It demonstrates why a shared class and
slot are evidence inputs rather than permission to copy an alpha name.
