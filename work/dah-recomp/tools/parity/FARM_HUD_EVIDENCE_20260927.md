# Farm HUD evidence — 2026-09-27

This records the HUD investigation alongside the normal Farm entry route.
It does not establish complete HUD, gameplay, or pixel parity. Menu work
remains pinned. All observations used hidden game processes or saved artifacts.

## Confirmed shield renderer correction

The retail shield is `main/alien/healthandconcentration/change/bar`, vtable
`0022A8D8`. Its render path is `0005FF00` → `0005FBD0` → `000E9250`.
`000E9250` packs 24-byte XYZ3/UV2/BGRA8 vertices. `000E8FF0` locks the dynamic
buffer through `001DD6C0`, obtaining `Data | 80000000`. The native memory layout
has separate low and contiguous allocations; these bytes are not low-RAM aliases.

The exact unlit shader (`[0027DB48]`, program `00250CB4`) and declaration select
PGRAPH program kind 14. `nv2a_pgraph_d3d11.c` now fetches this verified kind from
the contiguous graphics window, as kinds 17/18 already did. Other kinds and
sampling behavior are unchanged.

Evidence:

- Native 016 game state already matched reference shield state: active and
  visible, fill `419FFFFE/41A00000`, 40 positive segments. Its matching shield
  draw had 240 indices and clip words `023E002B/00190024`; all fetched vertices
  collapsed to `(330.5,49)` with zero UV and color. Index count alone does not
  identify this draw: other materials also issue 240 indices.
- Native 017 frame 6500 restored the visible white shield ticks. Native 018
  frame 6200 retained them. These are live visual confirmations of this fix,
  not claims that every HUD pixel matches.
- `tools/test_unlit_backing.mjs` exercises the actual production
  `submit_indexed_3d` path and vertex fetch with distinct low/high RAM contents,
  including first index 599, repeated indices, zero-valued correct buffers,
  shader/declaration guards, and other program kinds. Seven draws and 500
  vertices pass. Its old-line negative control fails at actual `(330.5,49)`
  versus expected `(72.5,45)`.

## Red enemy bar: visibility is driven by target state

The separate red bar is `main/enemyhealth/bar`, vtable `0023511C`. This is not
an unconditional persistent strip. Native 018 records:

| Loop / world tick | Own active | Ancestors active | Rectangle / fill |
| --- | --- | --- | --- |
| 5621 / 2102 | true | true | initial zero-width / zero |
| 5622 / 2103 | false | true | initial zero-width / zero |
| 5623 / 2104 | true | true | `(431,64,100,6)` / `(1,1)` |
| 5793 / 2274 onward through 8212 / 4693 | false | true | same full rectangle / `(1,1)` |

Thus the later missing draw is explained by the widget's own inactive state;
the recorded geometry is correct. This alone does not prove a parity bug.
Native 016's offline capture likewise had no submitted rectangle at
`(431,64)..(531,70)`, but that run did not record this widget's activation.

The original Lua 4 chunk is intact in saved reference RAM at physical
`03A03D40..03A047C0`, source
`input/shared/gui/site/display/gui_site_display_main_enemyhealth.lua`.
Its line-18 Handler sets a 0.033-second timer on activation. Each timer event:

1. Calls `player.GetWeaponTargetActorHealthFrac()`.
2. If the result is non-nil, activates `bar` and `mesh` and sets the bar value.
3. Otherwise, deactivates both objects.
4. Rearms the same timer.

The 53-instruction handler's nil branch is instruction 18, jumping to 36;
instructions 36–45 deactivate bar and mesh. This handler contains no tutorial
elapsed-time condition. The containing chunk parses 2686 bytes plus two padding
bytes using the official [Lua 4 binary loader](https://www.lua.org/source/4.0/lundump.c.html)
and [instruction definitions](https://www.lua.org/source/4.0/lopcodes.h.html).

## Source-proven query chain for a future observer

The registration at `0022DB64` associates hash `9DAA743F`, name at `0022D8D0`,
and dispatcher `00083A50`. Its case `0008478E` reads:

```text
control = [0025FCEC]
player  = [control + 38]
focus   = [player + 30]
weapon  = [focus + 138]
target  = [weapon + 1BC]
```

`001390D0` pushes numeric 1.0 when the target pointer is nonzero, otherwise nil.
That is the observed retail implementation despite the function's fraction name.
The saved retail machine bytes at `0008478E` agree with the generated source.
For the observed Crypto class, player/focus/weapon vtables are respectively
`0022D658`, `0022C9F8`, and `0022F7D8`. A future observer must validate each
pointer and class and report absent/unmapped data explicitly. No observer field
or gameplay behavior was added for this chain in run 018.

## Comparison limits

Both older reference RAM snapshots, neutral 028 at world tick 3283 and paused
RenderDoc 001 at tick 7438, contain an active/full red bar. However, both have
`[weapon+1BC] == 0` at the captured instant. The reason for this stale or otherwise
unmatched widget state is not established. They cannot alone justify forcing
the native bar active.

Reference 002's gameplay PNG has shield ticks and the green bar, with no red
secondary bar. Its capture was triggered after loop 6689 / world tick 2761,
one loop after `worldRealtime` changed from 1 to 0. Host capture 158032 arrived
about 1.19 seconds later, and metadata explicitly says exact guest-frame
association is false. Native 018 frame 6200 also lacks the red bar, but is later
relative to its own gameplay handoff. Target state and actual guest capture
phase must be aligned before treating their visibility as equivalent.

The diagnostic `hudEnemyBarColorBits` contains the requested four raw words
`D0..DC`; these are **not RGBA**. The first RGB endpoint is `D0/D4/D8`, the
second is `DC/E0/E4`, and alpha is `E8`. Saved reference endpoint red is
`3F48C8CA` (approximately 0.784314), alpha is 1.0. The native header comment
calling `D0..DC` RGBA needs a comment-only correction after the live run.

Observer validation completed before 018: 16 native/Python consistency tests
and 10 RSP observer tests passed. The RSP observer budget is explicitly 28
reads / 2048 bytes; the populated orientation path uses at most 27 reads /
1831 bytes. The linked enemy-widget diagnostics are native/offline only,
because adding that traversal would exceed the remaining RSP read budget.
