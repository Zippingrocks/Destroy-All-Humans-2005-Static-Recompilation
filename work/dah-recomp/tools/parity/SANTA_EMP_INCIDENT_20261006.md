# Santa Modesta EMP incident — 2026-10-06

## Observed

During *Aliens Stole My Brain Stem*, Crypto became invisible and the native
recomp later crashed. The encountered EMP device appeared inert: no useful
collision/contact, pickup interaction, or observed jetpack-disable behavior.
These remain separate observations until a shared state transition is traced.

The current retail string table contains `GetJetPackEnable`,
`SetJetPackEnable`, and `SetJetPack`. This proves a retail ability-control API
survives in the shipped executable. It does not yet prove which mission object
or script invokes it.

The alpha PDB names alpha `0x0002A540` as
`UFO::PlayerObject::ProcessScript`. Its script-registration table contains the
same `SetJetPackEnable` hash (`0x47A92D5E`), the same command-table order, and
the same generic-handler structure as retail `0x00083A50`. The command branch
also matches semantically: it reads a Boolean argument, stores its inverse as
the player's internal disable byte (alpha `+0x3D8`, retail `+0x360`), and
returns. This is level B structural evidence for the retail function name and
level A evidence for the command hash and Boolean inversion.

The event trace now records every retail `SetJetPackEnable` write as an
`ability-flag` event with world tick, player address, old/new stored disable
byte, derived old/new enabled state and caller. This tells the next matched
Santa run whether the mission actually dispatched the command and whether the
player state changed, without adding or forcing gameplay behavior.

The retail Santa asset scripts now narrow the mission side further. The b3
ignition script starts both `b3_base` and `b3_emp`, then starts objective
`b3_empVo`. That objective is a `TagDistance` test between tag `b3_emp` and
`player_alien`, configured as distance `< 21`; completing it queues the EMP
tutorial notification and voice line. None of the mission-specific b3 scripts
contains `SetJetPackEnable`. The command instead survives in the shared
`site_movement.lua`, where `ability.jetpack` controls the normal jump path.
This means the tutorial proximity test is not the EMP pulse implementation.
The pulse, temporary weapon/jetpack lockout, destruction and effects must be
traced through the `ActorSamSite` gameplay path and the player ability state.
The b3 script's `ability.land` key is the separate saucer-landing ability and
must not be used as a shortcut for EMP behavior. The compact resource hashes
and prototype evidence are recorded in
`tools/analysis/results/santa-b3-script-evidence.json`.

The retail Santa directory adds two content anchors. Resource 4854 is the
1,548-byte `m_emp_mine` actor archetype and contains class string
`ActorTypeMineStatic`; adjacent resource 4855 is the 344-byte
`weapon_emp_detonate` actor archetype with class string `WeaponTypeDetonate`.
Their exact hashes, SHA-256 values, aligned resource-hash edges and explicit
limits are recorded in `tools/analysis/results/santa-emp-asset-evidence.json`.
No direct aligned edge from the mine root blob to the detonation-weapon name
hash was found, so runtime invocation remains open. The March 2004 Santa name,
string, builder and linker reports contain none of those four retail names.
That absence limits the alpha to shared-engine symbol evidence for this issue;
it cannot supply the final EMP content implementation by name.

## Crash evidence

- Crash text: `crashlog/crash-20261007T061712.003Z-p16976-t51848-DAH-1AF563F1251E7840.txt`
- Dump: matching `.dmp`
- Unique signature: `DAH-1AF563F1251E7840`
- Exception: access violation in the host translation of retail
  `sub_001066F0`, reading `0xEBFEE0A7`
- Immediately preceding unresolved vtable target: retail `0x00015FC0`, called
  from retail `0x00105BD0`
- Earlier unresolved lifecycle target: retail `0x00016CA0`

At `0x00105BD0`, the retail caller saves `edi` before its indirect call. The
unresolved-call fallback restores the older guest ESP. Caller cleanup then pops
the wrong words; later register values include retail code addresses and the
virtual-call chain reaches zero. This is a causal stack-corruption chain, not a
guess based only on the final fault.

Retail `0x00015FC0` is a four-instruction vtable thunk. It reads the owner at
`this+0x1C`, tests byte `owner+0x189`, tail-jumps to the already translated
`0x00105DA0` when the byte equals one, and otherwise returns. Retail
`0x00016CA0` is a scalar deleting destructor that calls `0x00016C20` and the
retail delete routine according to its flag. Both real entry points were absent
from generated function discovery and are now registered as byte-audited manual
callbacks.

The class identity around `0x00016CA0` is now structurally proven. Retail
constructor `0x00016B50` installs primary vtable `0x00226A80`, secondary vtable
`0x00226A20`, and constructs a `0x35C`-byte object. Alpha vtable `0x001EE848`
has the same shape, and its matching slot names alpha `0x0004A0B0` as
`Traffic::ActorSamSite::scalar deleting destructor`. Neighboring alpha symbols
include `Traffic::ActorSamSite::SetCollideFlag`, `SetCollideMask`, `EnableBody`,
`Update`, and `ApplyDamage`. This is level B evidence that the retail class is
`Traffic::ActorSamSite` and its missing destructor is retail `0x00016CA0`.

The runtime join is now proven as well. Read-only capture
`blanket-runs/santa-emp-live-p48988-20261007T065543Z.jsonl`, from recomp run
`20261007T064831185Z-p48988-9470C2DDEE4F43E3`, observed four objects with
primary vtable `0x00226A80` and exact resource name `m_emp_mine`. Their serials
were 1232, 1048, 1224 and 1065. All four exposed non-null body pointers whose
vtable was `0x00235CA8`. This establishes that the encountered EMP mines use
`Traffic::ActorSamSite`, and rules out missing object or body construction at
that captured checkpoint. It does not yet establish correct collision masks,
contact dispatch, trigger response or mission behavior.
The durable, compact record is
`tools/analysis/results/santa-emp-runtime-evidence.json`; the full JSONL remains
a local run artifact and is deliberately excluded from source control.

A read-only follow-up decoded the exact retail collision-object path. The
forceable interface forwards `SetCollideFlag`, `SetCollideMask`, and
`EnableBody` through the body at actor `+0x110`; that body owns its primary
collision object at `+0x18`. Retail methods `0x0012AA40`, `0x0012AA70`,
`0x0012AAA0`, and `0x0012AA90` prove how its packed filter word is read and
split. All four mines held `0x009D6009`: category 9, six-bit system group 0,
collide mask 5036. Retail `Physics::CollisionFilter::isCollisionEnabled` at
`0x00135F00`, with packed helper `0x00135EA0`, accepts a pair if either collide
mask contains the other category and then rejects equal nonzero system groups.
The mine value is therefore not a zero or disabled collide mask.

A later sample from the same process found Crypto at the source-proven player
path with packed filter `0x168E8802`: category 2, system group 0, collide mask
184785, and stored jetpack-disable byte 0. The retail predicate accepts this
Crypto/mine pair because the mine mask includes category 2. The samples were
not taken at the same tick, so a new aligned encounter must confirm the live
pair and proceed through shape, broadphase, contact callback and script
response. The next matched xemu checkpoint and `physics-body-command` trace
must also establish the intended transition and tick.

The read-only blanket observer now uses the proven class name, records its
physics-body state at discovery, records body-pointer changes as well as
vtable changes, and reports a `coverage-gap` if an observed ActorSamSite never
exposes a physics body. Run-end coverage says independently whether a SAM-site
class and one of its bodies were observed. These events distinguish a missing
entity/body from a missing contact or script response without changing game
state.

The neighboring retail actor functions also validate the alpha comparison
method: retail `0x00105FB0` matches alpha `Traffic::Actor::SetOnFire`, while the
following layout strongly maps the range to the alpha Traffic actor methods.
The generic similarity tool produced weaker unrelated candidates, so those
candidates were rejected. This is the intended A/B/C/D evidence discipline.

The retail script surface adds a direct causal bridge. The exact
`SetPhysicsEnableBody` string at `0x0022C024` is registered at retail
`0x00073A5C` with handler `0x000717D0`. That handler resolves tagged actors and
their forceable interface; its unfiltered enable branch calls `0x00105BD0`.
That is the same caller that reached missing vtable thunk `0x00015FC0` in the
crash. The callback restoration therefore repairs a proven body-enable path,
although the next instrumented run still has to show whether the EMP mission
dispatches it and with which tag and enable value.

The new event trace records that boundary as `physics-body-command`, including
world tick, tag hash, optional filter hash, actor, forceable interface,
requested state and caller. It also records `SetTagAlienAbilityEnable` writes
as `tag-alien-ability`, including the ability hash and old/new stored-disable
byte. A generated conditional-branch defect in retail handler `0x00072D40` was
corrected at the two affected comparisons: previously an unknown ability hash
could fall through and change the brain-ability byte because the generated
fallback flags variable was never updated. The correction reproduces the
retail `jne` decisions; it does not add a new ability.

The same current-run log exposed three additional indirect-only retail
callbacks: `0x0003CD20`, `0x0003E2E0`, and `0x0004ACC0`. They were reached from
retail vtables `0x00228C48`, `0x00228D68`, and `0x002297C0`; one recorded
`0x0003CD20` call occurred in a chain whose actor argument was the live
`m_emp_mine` at `0x02E66090`. Exact XBE disassembly shows that `0x0003CD20`
advances an actor state and creates the retail `fire` actor when its timers
expire, `0x0003E2E0` stores a target handle returned through a virtual method,
and `0x0004ACC0` creates and configures a runtime body or shape. All three are
now byte-boundary-checked by `tools/lift_santa_runtime_callbacks.py`, compiled
in `recomp_santa_callbacks.c`, and registered for indirect dispatch. They
restore original retail code paths; their presence is not yet proof that the
EMP pulse or Crypto visibility matches xemu.

The exact-range alpha comparison then separated those observations. Retail
`0x0004ACC0` belongs to `UFO::BuildingFixture`: its containing vtable has the
same `0x6FC7A9F5` class ID and matching prefix as alpha BuildingFixture, while
neighboring retail `0x0004AB10` occupies and behaves like the alpha
`ApplyDamage` method. The added retail virtual at `0x0004ACC0` still has no
proven method name. It is a legitimate missing callback found during the Santa
run, but it is not a direct EMP-device callback. Retail `0x0003E2E0` is a
strong semantic `SetTarget` candidate, but its class ID `0x4A0548A5` is absent
from the alpha, so that name remains an alias. The weak ActorSamSite candidate
for `0x0003CD20` was rejected because its class ID and control flow do not
match. These accepted, provisional and rejected results are preserved in the
symbol ledger rather than compiled into invented names.

## What the callback fix establishes

The fix removes two proven unresolved entry points and the identified guest
stack corruption route. It does not, by itself, establish that EMP collision,
pickup, mission scripting, visual effects, or jetpack disabling are complete.
Those require the matched runtime validation below.

## EMP validation matrix

| Layer | Required native evidence | Required xemu comparison | Status |
|---|---|---|---|
| Resource | exact resource/type/hash and successful construction | same object identity at checkpoint | recomp proven: four `m_emp_mine` / `ActorSamSite`; xemu open |
| World | stable transform, streaming and visibility | same spawn/despawn timing | recomp checkpoint captured; matched timing open |
| Physics | shape, body, filter and broadphase registration | same blocking/contact behavior | four bodies proven; filter is category 9/group 0/mask 5036; cross-tick retail pair test accepts Crypto; aligned pair, shape, broadphase and contact open |
| Interaction | contact/pickup eligibility and dispatched callback | same allowed/denied interaction | open |
| Mission | script event and mission-state transition | same event tick/order | open |
| Ability | old/new jetpack-enabled state and caller | same disable/restore timing | open |
| Presentation | animation, effect, audio and HUD response | aligned frame/audio sequence | open |
| Recovery | checkpoint reload, leave/return, destruction/reset | same final state | open |
| Stability | no `0x15FC0`/`0x16CA0`/`0x3CD20`/`0x3E2E0`/`0x4ACC0` unresolved calls or crash signature | sustained matched run | five callbacks restored; runtime open |
| Crypto render | actor remains present and correctly visible | matched visibility state | open |

Do not mark the EMP fixed until every applicable row has evidence. If the prop
is intentionally not pickable in xemu, record that as the reference behavior
rather than adding pickup behavior.

## Reusable tells learned from this incident

- A visible feature failure and a crash in the same scene may still be separate
  defects; trace before joining them.
- A tiny vtable thunk omitted by discovery can disable a large gameplay chain.
- Code addresses appearing in object registers point toward guest stack
  imbalance after an unresolved callback.
- A retail gameplay string proves a surviving API/name, while the alpha PDB can
  supply a candidate class or function identity. Neither alone proves the
  retail call mapping.
- The earliest unresolved call in the causal window is a stronger repair point
  than the final null vtable call.
- Preserve every current-run unresolved target with its caller, vtable, object,
  world state and executable identity. A repeated target can reveal a missing
  subsystem even when it is not the sole cause of the visible symptom.
- Treat callbacks seen in one long process as a candidate set, not a causal
  group. The BuildingFixture result demonstrates why class identity must be
  recovered before assigning a scene-wide failure to every unresolved target.
- A vtable-slot match becomes substantially stronger when constructor size,
  secondary vtables, destructor shape, and neighboring class methods also
  agree. Keep runtime resource identity separate until it is observed.
- A non-null body proves construction, not collision. When an actor can be
  walked through, continue through shape, filter, broadphase, contact and
  script response instead of rebuilding a body that already exists.
- Decode packed fields from the actual retail predicate, not from a plausible
  bit split. Here bits 5..10 are a system group and bits 11+ are the collide
  mask; labeling them backwards would have produced the wrong repair.
- Script strings and their registration xrefs can connect a visible gameplay
  defect to a precise translated handler. Follow that handler through its
  callers before deciding whether a missing callback is related.
- Generated flag fallbacks are a review signal. Confirm every affected retail
  branch from the original instruction before replacing it with an explicit
  comparison; never apply a global search-and-replace.
