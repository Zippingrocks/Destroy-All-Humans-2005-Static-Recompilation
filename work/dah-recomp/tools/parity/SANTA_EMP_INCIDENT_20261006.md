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
It does **not** yet prove that the encountered EMP device is an ActorSamSite;
the next capture must join the class to its runtime resource name.

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

## What the callback fix establishes

The fix removes two proven unresolved entry points and the identified guest
stack corruption route. It does not, by itself, establish that EMP collision,
pickup, mission scripting, visual effects, or jetpack disabling are complete.
Those require the matched runtime validation below.

## EMP validation matrix

| Layer | Required native evidence | Required xemu comparison | Status |
|---|---|---|---|
| Resource | exact resource/type/hash and successful construction | same object identity at checkpoint | open |
| World | stable transform, streaming and visibility | same spawn/despawn timing | open |
| Physics | shape, body, filter and broadphase registration | same blocking/contact behavior | open |
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
