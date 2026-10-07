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
than silently dropped. The alpha inventory contains 8,943 ranges, 8,925 with
parsed instructions, and 8,735 starts carrying original symbol names.

| Executable section | Retail discovered / parsed | Alpha discovered / parsed |
|---|---:|---:|
| `.text` | 9,677 / 9,669 | 7,772 / 7,755 |
| `D3D` | 269 / 268 | 257 / 257 |
| `DSOUND` | 417 / 417 | 382 / 382 |
| `XGRPH` | 25 / 25 | 23 / 23 |
| `XMV` | 64 / 64 | 65 / 65 |
| `XPP` | 161 / 161 | 161 / 161 |
| `XNET` | absent | 283 / 282 |
| retail Bink sections | 215 / 197 | absent |

The 18 unparsed retail `BINKYUY2` ranges account for most retail exceptions.
The separate Bink, D3D, DirectSound, XMV, graphics and XPP sections are part of
the totals; this is not a `.text`-only survey. Alpha's XNET code is recorded as
prototype infrastructure and is not misclassified as missing retail gameplay.

## Function relationship map

Every retail function has one row in `whole-function-map.csv`:

| Candidate state | Retail functions |
|---|---:|
| exact normalized structural candidate | 2,367 |
| additional high-confidence candidate | 652 |
| medium candidate | 2,193 |
| weak or ambiguous candidate | 4,840 |
| no named alpha candidate | 776 |

This supplies 3,019 strong structural candidates and another 2,193 useful
leads. A candidate is not automatically accepted as a retail function name.
Constants, addresses and branch destinations are normalized for comparison,
so generic accessors and tiny thunks can resemble unrelated functions. Names
are promoted only after class layout, callers, vtable slot and runtime behavior
agree.

The strong candidate set reaches every major engine area. Keyword groups below
overlap because one symbol may belong to several systems:

| Named system evidence | Strong candidates |
|---|---:|
| rendering and graphics | 407 |
| physics and Havok | 308 |
| audio and movies | 427 |
| UI, HUD and menus | 127 |
| missions and scripting | 212 |
| AI and traffic | 63 |
| weapons and ordnance | 184 |
| player, character and ship | 77 |

These rows give future defects a searchable starting point. A missing weapon
effect, pedestrian recovery routine, menu transition or saucer callback can be
joined to an alpha name candidate, then confirmed against retail code and xemu.

## Classes and object identity

The alpha symbols expose 63 named `VirtualClassId` functions. Fifty of their
32-bit IDs occur unchanged in a retail return-immediate function. Thirteen
alpha IDs do not occur unchanged:

- `PlayerCharacter`, `PlayerShip`, `ActorCar`, `ActorPedestrian`,
  `ActorSamSite`, `ParticleEffect`, `CameraObject` and `AnimObject`;
- `WeaponCortex`, `WeaponDeathRay`, `WeaponHypnoRay`, `WeaponBrainRay` and
  `WeaponCloak`.

This does not mean those classes were removed. It proves their alpha IDs cannot
be copied into retail unchanged. For example, `ActorSamSite` survives with the
same broad class family and object size, but the alpha ID `0x8BF075A5` becomes
retail `0xF64BBE96` and its retail vtable grows. This is exactly the kind of
version drift that made the restored EMP callbacks require retail bytes rather
than an alpha implementation.

Retail contains 207 two-instruction `mov eax, immediate; ret` functions. The
50 shared values are strong identity evidence. The other immediate values are
kept as candidates because that machine-code shape alone does not prove a
class ID.

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

The data-section scan found 863 pointer-like tables containing 2,857 unique
retail code targets. Of those, 2,735 are discovered function starts and every
one is reachable through the native dispatcher. There are zero known missing
discovered function starts in these tables.

The remaining 122 targets enter inside a discovered function. Five are already
handled explicitly. The other 117 are retained as `internal-target-candidate`
rows for caller and runtime review. They are commonly switch arms or loop
entries and must not be reported or implemented wholesale as missing
callbacks. The earlier apparent total of 982 gaps came from scanning executable
sections and mixing jump tables with callbacks; the corrected database removes
that false signal.

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
