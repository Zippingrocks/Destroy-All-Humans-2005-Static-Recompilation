# Whole alpha/retail comparison — 2026-10-07

## Scope

This pass compares the complete March 12, 2004 prototype corpus available in
the workspace with the complete retail Xbox corpus used by the recomp. It is
not limited to the Santa Modesta crash path. The generated database covers:

- every discovered function range in every disassembled executable section;
- every executable alpha symbol that begins at a discovered function;
- normalized instruction shape, class-ID return functions and embedded ASCII
  strings;
- every file in both available block/archive trees, with byte counts and
  SHA-256 hashes;
- every contiguous function-pointer-like run in retail `.rdata` and `.data`,
  checked against the native recomp dispatcher.

The exact input hashes and all row-level results are in
`tools/analysis/results/whole-alpha-retail/whole-comparison-summary.json` and
the CSV files beside it. Regenerate them with
`tools/analysis/compare_whole_alpha_retail.py`.

## Executable coverage

The retail inventory contains 10,828 discovered function ranges. Instructions
were parsed for 10,801; 27 ranges are retained as explicit exceptions rather
than silently dropped. The heuristic alpha inventory contains 8,943 ranges.
The original PDB supplies 9,652 code-symbol addresses, including 917 real
entry boundaries that the heuristic inventory merged into adjacent functions
or omitted. Adding those authoritative boundaries produces 9,860 alpha ranges,
9,801 with parsed instructions.

| Executable section | Retail discovered / parsed | Alpha discovered / parsed |
|---|---:|---:|
| `.text` | 9,677 / 9,669 | 8,249 / 8,249 |
| `D3D` | 269 / 268 | 328 / 291 |
| `DSOUND` | 417 / 417 | 502 / 484 |
| `XGRPH` | 25 / 25 | 24 / 24 |
| `XMV` | 64 / 64 | 225 / 223 |
| `XPP` | 161 / 161 | 227 / 225 |
| `XNET` | absent | 305 / 305 |
| retail Bink sections | 215 / 197 | absent |

The 18 unparsed retail `BINKYUY2` ranges account for most retail exceptions.
The separate Bink, D3D, DirectSound, XMV, graphics and XPP sections are part of
the totals; this is not a `.text`-only survey. Alpha's XNET code is recorded as
prototype infrastructure and is not misclassified as missing retail gameplay.

## Function relationship map

Every retail function has one row in `whole-function-map.csv`:

| Candidate state | Retail functions |
|---|---:|
| exact normalized structural candidate | 2,364 |
| additional high-confidence candidate | 650 |
| medium candidate | 2,200 |
| weak or ambiguous candidate | 4,828 |
| no named alpha candidate | 786 |

This supplies 3,014 strong structural candidates and another 2,200 useful
leads. A candidate is not automatically accepted as a retail function name.
Constants, addresses and branch destinations are normalized for comparison,
so generic accessors and tiny thunks can resemble unrelated functions. Names
are promoted only after class layout, callers, vtable slot and runtime behavior
agree.

The strong candidate set reaches every major engine area. Keyword groups below
overlap because one symbol may belong to several systems:

| Named system evidence | Strong candidates |
|---|---:|
| rendering and graphics | 409 |
| physics and Havok | 305 |
| audio and movies | 425 |
| UI, HUD and menus | 128 |
| missions and scripting | 215 |
| AI and traffic | 63 |
| weapons and ordnance | 185 |
| player, character and ship | 77 |

These rows give future defects a searchable starting point. A missing weapon
effect, pedestrian recovery routine, menu transition or saucer callback can be
joined to an alpha name candidate, then confirmed against retail code and xemu.

## Classes and object identity

The alpha symbols expose 64 named `VirtualClassId` functions. Fifty-eight of
their 32-bit IDs occur unchanged at a vtable-referenced retail
`mov eax, immediate; ret` entry. The earlier count was 51 because function
discovery had merged several six-byte methods into neighboring ranges.
`PlayerCharacter`, `PlayerShip`, `ActorCar`, `ActorPedestrian`,
`WeaponCortex`, `WeaponDeathRay`, and `WeaponHypnoRay` are now proven shared.

Six alpha IDs still do not occur unchanged: `ActorSamSite`, `ParticleEffect`,
`CameraObject`, `AnimObject`, `WeaponBrainRay`, and `WeaponCloak`. This does
not mean those classes were removed. It proves only that these six alpha IDs
cannot yet be copied into retail unchanged. Retail has 218 vtable-referenced
return-immediate entries; 58 are shared identities and the remainder stay
unnamed until class layout, callers and behavior agree.

## Strings and debug evidence

The scan found 4,042 unique alpha strings and 2,245 unique retail strings:

| String relationship | Count |
|---|---:|
| shared exactly | 1,085 |
| alpha-only | 2,957 |
| retail-only | 1,160 |

Alpha-only material includes original debug-display, console, heap, visual
debugger and XNet diagnostics. Retail-only material includes final command and
gameplay terms such as `CanFireWeapon`, `DetachWeapon`, `SetWeaponEventFunc`
and `UnregisterMission`. A string is evidence that a term or code path existed;
it does not by itself prove that the containing feature is reachable.

## Complete block/archive comparison

Every available file was hashed. The alpha tree has 109 files totaling
317,306,406 bytes; 60 are retained builder/linker reports and 49 are game
payloads. Retail has 46 game payloads totaling 768,532,836 bytes.

Across game payload paths, 25 occur in both versions and every one changed.
Twenty-four are alpha-only and 21 are retail-only. The shared Area 42,
Rockwell, Santa Modesta and Union Town directory/resident/discard/stream
payloads all changed. Retail adds complete Farm, Capitol and Capitol boss site
sets, a main-shell stream, transition stream and centralized English audio,
including the 503,336,968-byte sound stream. Alpha instead has per-site sound
streams, two explicit intro segments, a launch set and build reports that are
valuable for reconstructing asset names and relationships.

This establishes that the prototype is a structural guide, not a drop-in asset
or behavior source. Retail content, retail XBE execution and xemu remain the
authority for final missions and presentation.

## Recomp callback coverage

The data-section scan found 567 pointer-like tables containing 3,575 unique
retail code targets. Of those, 2,895 are discovered function starts and every
one is reachable through the native dispatcher. There are zero known missing
discovered function starts in these tables.

The remaining 680 targets begin at valid retail instructions inside a range
that heuristic discovery treated as one function. Three hundred twelve are
already explicitly dispatchable. This pass recovered two byte-verified vtable
entries: traffic callback `0x00016A90` and the deleting destructor at
`0x0009A210` for retail class ID `0x2786C33B`. Both now have generated bodies
and manual dispatch entries. The other 368 remain candidates because many are
intentional loop/switch entries or shared trap targets such as unaligned
`0x00139ADB`; they must be accepted from boundary, table and runtime evidence,
not implemented wholesale.

## How this drives completion

For a new defect, use the retail address or runtime event to select the relevant
rows, inspect its alpha candidate and neighboring named functions, confirm the
retail class/vtable/caller relationship, and then test the exact behavior
against xemu. Accepted names belong in the existing evidence ledger; weak names
remain candidates. Content defects use `whole-content-map.csv` to establish
whether the prototype has a corresponding site or resource before any alpha
assumption is made.

This is complete static coverage of the available executables and block trees.
It is not proof that every mission branch, animation, particle, AI state or
frame transition has executed. Dynamic completion still requires deterministic
routes through every retail mission, weapon, vehicle, ability, death/restart
path and cutscene, with state traces and matched xemu captures. The database
makes those runs cumulative and traceable: new failures can be placed in the
whole-program map instead of being rediscovered as isolated mysteries.
