# Alpha and retail debug evidence inventory

This inventory separates original alpha artifacts from later host-side work.
That distinction matters: the alpha project contains useful experiments and
tests, but a helper written for its recomp is not proof that retail shipped the
same function.

## Pinned original artifacts

| Artifact | Size | SHA-256 | Use |
|---|---:|---|---|
| `ufo.pdb` | 21,082,112 | `AF4AF62CBE76FE1B7A5CBB6B9CDBB52F1CD5D79E085A9CB9657521D874B22321` | original alpha symbol/type/name evidence |
| March 12, 2004 `ufo-dev.xbe` | 2,256,896 | `CD1EBC185BB9AB9207971E6BD21FB434511DB29471080DCE85A08B21D514ACC8` | original alpha code, data, vtables and registrations |
| extracted `sf-symbols.json` | 2,404,999 | `2DDC12E60C78662F26E86925F5B63357EE67D964E2BB829A8CCDE50DE3F5C3E7` | machine-readable PDB symbol index |

The PDB is real and usable. It names thousands of alpha functions, classes,
vtables and debug facilities. It belongs to the alpha XBE, so none of its
addresses may be copied into retail. A name is transferred only after retail
code/data provides exact or structural evidence under
`RECOMP_INVESTIGATION_WORKFLOW.md`.

## Derived and host-authored material

| Material | What it can establish | What it cannot establish |
|---|---|---|
| `analysis/debug-symbols.json` | source-file attribution from alpha assert strings; currently 99/8,943 functions (1.11%) | an original function name or a retail address |
| alpha disassembly and `sf-symbols.json` | alpha instruction shape, names, class layout, vtable slots and registration hashes | unchanged retail semantics by itself |
| alpha recomp tests and investigation notes | prior hypotheses, known triggers, validation patterns and candidate boundaries | original behavior unless tied back to alpha bytes or xemu |
| `src/dev_console.c` and other host helpers | reusable UI/logging/test infrastructure | proof that the original alpha or retail game contained that host implementation |
| patch scripts such as `patch_debug_hud.py` | byte-checked alpha modifications and useful negative controls | authority to apply the same modification to retail |

This means the alpha recomp absolutely contains work worth mining. Its notes,
tests, recovered callbacks and debug experiments should be searched whenever a
retail system fails. Each useful result must be reattached to original alpha
bytes/PDB data and then independently matched to retail before it becomes a
retail implementation or name.

## Accepted retail mappings

The machine-readable ledger is
`tools/analysis/results/alpha-retail-symbol-evidence.csv`. It currently records:

- retail `0x00083A50` as alpha `UFO::PlayerObject::ProcessScript` with level B
  evidence, including the identical `SetJetPackEnable` command hash and branch
  semantics;
- retail `0x00016CA0` as
  `Traffic::ActorSamSite::scalar deleting destructor` with level B evidence
  across constructor size, vtables, slot and destructor shape; a live Santa
  Modesta capture independently joins this class to resource `m_emp_mine`;
- retail `0x00105FB0` as `Traffic::Actor::SetOnFire`, used as a structurally
  matched neighborhood anchor;
- retail `0x00015FC0` as an exact restored thunk whose name remains unknown.

An accepted mapping is a local fact with recorded scope. It does not validate
adjacent functions, every command in a dispatcher, or the identity of a
mission resource using the class.

`tools/analysis/find_xbe_string_xrefs.py` makes the retail registration search
repeatable. Given an XBE and exact strings, it records the input hash, every
NUL-terminated occurrence, each file-backed dword xref and nearby dwords. The
first committed result,
`tools/analysis/results/retail-ability-command-xrefs.json`, anchors
`SetJetPackEnable`, `GetJetPackEnable`, `SetTagAlienAbilityEnable`, and
`SetPhysicsEnableBody`. Xrefs remain clues until the referenced handler is
disassembled and its behavior is verified.

## Reproducible intake for a missing retail system

1. Search the alpha PDB index, alpha strings, vtables, registrations, notes and
   tests for candidate names and triggers.
2. Mark every candidate as original artifact, derived analysis, or host-authored
   experiment.
3. Find retail anchors: command hash, string xref, vtable slot, constants,
   constructor size, field offsets, callers and callees.
4. Add the candidate to the evidence CSV with its level and status. Unknown
   names retain their address.
5. Instrument the retail boundary without changing state, then reproduce the
   same checkpoint in native and xemu.
6. Promote the name or behavior only after level A/B evidence and matched
   runtime behavior agree.

For debug restoration, start with read-only state and draw-only overlays whose
retail registration survives. Mutating console commands remain internal until
their retail command entry and implementation are mapped. Alpha networking and
devkit console services are reference material, not the first restoration
target.
