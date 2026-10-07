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
| Physics | shape, body, filter and broadphase registration | same blocking/contact behavior | four bodies proven; shape/filter/contact open |
| Interaction | contact/pickup eligibility and dispatched callback | same allowed/denied interaction | open |
| Mission | script event and mission-state transition | same event tick/order | open |
| Ability | old/new jetpack-enabled state and caller | same disable/restore timing | open |
| Presentation | animation, effect, audio and HUD response | aligned frame/audio sequence | open |
| Recovery | checkpoint reload, leave/return, destruction/reset | same final state | open |
| Stability | no `0x15FC0`/`0x16CA0` unresolved calls or crash signature | sustained matched run | code restored; runtime open |
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
- A vtable-slot match becomes substantially stronger when constructor size,
  secondary vtables, destructor shape, and neighboring class methods also
  agree. Keep runtime resource identity separate until it is observed.
- A non-null body proves construction, not collision. When an actor can be
  walked through, continue through shape, filter, broadphase, contact and
  script response instead of rebuilding a body that already exists.
- Script strings and their registration xrefs can connect a visible gameplay
  defect to a precise translated handler. Follow that handler through its
  callers before deciding whether a missing callback is related.
- Generated flag fallbacks are a review signal. Confirm every affected retail
  branch from the original instruction before replacing it with an explicit
  comparison; never apply a global search-and-replace.
