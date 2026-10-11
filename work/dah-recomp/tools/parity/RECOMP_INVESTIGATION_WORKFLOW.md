# Recomp investigation workflow

This is the required workflow for a missing, broken, inaccurate, or crashing
game system. It preserves the evidence that led to a fix and makes the same
method reusable on the next system.

## 1. Freeze the run

Record the UTC time, process ID, executable hash, level, mission, checkpoint,
input sequence, and whether the run was retail xemu or the native recomp. Keep
the crash dump, crash text, `furonlog.log`, event trace, observer output, and
screenshots together. Run `validate_current_run.py` before treating a live log
as evidence. Never merge observations from different runs without labeling
them.

## 2. Split observations from hypotheses

Write each visible symptom independently. For example, an invisible player, an
inert EMP prop, missing collision, and a process crash are four observations.
They become one defect only after a shared call, object, or state transition is
observed. This prevents a plausible story from replacing evidence.

## 3. Build the last-good-to-first-bad timeline

Correlate these layers in order:

1. input and mission/script event;
2. entity spawn, resource identity, transform, render and lifecycle state;
3. physics body, broadphase/contact, pickup/interaction and damage events;
4. gameplay state such as ability enable, energy and animation;
5. effects, audio, HUD and camera;
6. unresolved indirect calls and guest stack/register state;
7. exception address, access type and crash signature.

The earliest proven divergence is the repair boundary. A later null dereference
is evidence of damage, not automatically the cause.

## 4. Recover code identity

Disassemble the retail bytes around the boundary and enumerate callers,
callees, vtable slots, object-field offsets, constants, strings and neighboring
functions. Compare with the alpha PDB and alpha executable using the following
evidence levels:

- **A — exact:** identical bytes or control flow with verified address changes.
- **B — structural:** matching control flow, constants, call neighborhood,
  vtable position and object layout.
- **C — supported hypothesis:** matching string, RTTI, resource hash or nearby
  symbol, but incomplete code agreement.
- **D — clue only:** name proximity or a similarity score by itself.

Levels A and B may justify a retail function name or implementation. Levels C
and D guide instrumentation and searches; they do not justify code changes.
`tools/analysis/match_alpha_retail_symbols.py` generates candidates and hashes
all of its inputs, but its ranking is never an automatic rename.
Use `tools/analysis/find_xbe_pattern.py` when a distinctive alpha instruction
sequence survives with changed addresses or field offsets. Treat the hit as a
candidate until its function boundary, vtable/call slot and semantics are
checked.

If automatic retail function discovery omitted the target, pass its verified
exclusive boundary with `--retail-end`. This analyzes the exact raw instruction
range instead of silently treating it as part of the preceding function. The
Santa callback set is the reference case: the class-level BuildingFixture
match for `0x4ACC0` was accepted, the semantic SetTarget alias for `0x3E2E0`
was kept provisional, and the weak ActorSamSite name for `0x3CD20` was
rejected.

Treat retail asset scripts as first-party evidence too. Inventory the relevant
site block, unpack only the required resource type, record the resource hash,
size and SHA-256, and disassemble the bytecode without editing it. Separate a
mission trigger from the system it introduces: a `TagDistance` tutorial
objective can prove when a voice line starts while saying nothing about the
actor's pulse, collision, disable state or effects. Preserve a compact evidence
record in source control; do not commit extracted game assets or bytecode.

## 5. Restore the smallest proven boundary

Prefer exact missing callbacks, thunks, destructors, registration records, or
script bridges over downstream state patches. Preserve the retail calling
convention, return cleanup, tail calls, flags and object writes. Put manual
entries in `recomp_lookup_manual` when function discovery missed a real vtable
target. Do not invent gameplay state to make a symptom disappear.

When the current-run log reports an indirect target, preserve the target,
return address, vtable, `this`, nearby actor/resource identity, world tick and
executable identity before lifting it. Define and byte-check the exact function
boundary, generate the original instructions, register the address in indirect
dispatch, then require the same scenario to stop reporting that target. The
Santa EMP run's `0x3CD20`, `0x3E2E0`, and `0x4ACC0` callbacks are the reference
example in `tools/lift_santa_runtime_callbacks.py`.

An unresolved indirect call is especially urgent when its caller pushes a
saved register before dispatch. The current safe fallback restores the
pre-call guest ESP; continuing caller code can then pop the return address or
arguments into registers and poison later virtual calls. The tell is:

`unresolved target -> code addresses appear in object registers -> zero or
invalid vtable target -> access violation`.

## 6. Instrument the complete behavior chain

Instrumentation must answer which object acted, which object received it, the
old and new state, the retail call address, the world tick, and the mission
phase. Gate high-volume traces behind an environment variable and bound them.
Debug views are observational: they must not alter game state or be counted as
parity evidence.

Track pointer presence separately from the pointed object's vtable. A body can
be attached or removed while both samples decode to a null vtable, and watching
only vtable changes loses that lifecycle boundary. For a named class, record
the class proof and runtime resource identity separately; a correct vtable name
does not prove which mission prop instantiated it.

Treat a live object, a live body, a collision shape, a broadphase entry, a
matching filter pair, a contact callback, and a gameplay response as separate
checkpoints. Seeing one never implies the later checkpoints. This distinction
turned the Santa EMP problem from “missing physics” into the narrower open
question of filter/contact/script behavior after four mine bodies were observed.
Decode a packed field through its consumers before naming or changing it. The
Santa filter word initially looked like category/mask/user data; the retail
pair predicate proved category/system-group/collide-mask instead. That
correction changed the conclusion from “disabled filter” to “filter pair is
eligible; trace shape, broadphase and contact next.”

For an interactive world object, trace at least resource load, construction,
registration, collision shape/body, contact or pickup eligibility, script
event, ability/state mutation, animation, effect/audio/HUD response,
destruction or reset, streaming out, and checkpoint reload.

## 7. Compare the same checkpoint in xemu

Use the same save, checkpoint, camera, input edges and world tick window.
Compare state changes first and pixels second. Pixel differences cannot explain
whether a collision callback or mission event fired. Once state timing agrees,
compare frame sequence, effects, animation, audio/HUD timing and final image.

## 8. Validate and close

A fix needs a positive reproduction and negative controls. Re-run the original
trigger, reload the checkpoint, leave and return to the area, and test a level
without the feature. Require no new unresolved targets in the relevant window,
no recurrence of the crash signature, and no observer anomalies. Record the
exact evidence, code changed, tests, remaining unknowns and executable hash.

“No crash” is one acceptance item. A system is complete only when its full
behavior chain and matched xemu timing are accounted for.

## Incident packet template

Keep one small document per defect with these fields so the reasoning survives
after the run and can be repeated:

- observed symptoms, each stated independently;
- run identity and immutable hashes;
- last-good and first-bad event, with world ticks;
- retail boundary, callers, callees, original bytes and calling convention;
- alpha/PDB candidate with evidence level and rejected alternatives;
- runtime class-to-resource join and relevant object/body state;
- retail asset/script resource hashes, prototype paths and relevant calls;
- smallest code repair and observational probes added;
- native and xemu reproduction steps and checkpoint alignment;
- positive result, negative controls, remaining open layers and shipped hash.

The Santa EMP incident document is the first filled example. Future bug work
should copy its structure and add new evidence rather than overwrite earlier
observations.
