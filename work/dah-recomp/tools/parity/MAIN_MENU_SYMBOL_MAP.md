# Main Menu Semantic Map

This is the canonical reverse-engineering map for the **main menu and mothership frontend only**. It gives stable semantic names to retail addresses without rewriting generated `sub_XXXXXXXX` identifiers, so regeneration cannot erase the work and uncertain names cannot silently become fact.

The machine-readable registry is [`main_menu_symbols.json`](main_menu_symbols.json). Run `python tools/parity/validate_main_menu_symbols.py` from `work/dah-recomp` to verify that every mapped address still has a function body, that names and addresses are unique, and that every entry carries evidence and a confidence level. Run `python tools/parity/build_main_menu_call_frontier.py` to regenerate [`main_menu_call_frontier.json`](main_menu_call_frontier.json), the review queue of direct native callees that still need classification.

Menu behavior is tracked separately in [`main_menu_coverage.json`](main_menu_coverage.json). Its 25 bounded routes keep static understanding, recomp runtime coverage, and xemu parity as separate facts. Run `python tools/parity/validate_main_menu_coverage.py` to validate and summarize that ledger.

## Boundary

Included:

- startup logos and the handoff to the title screen;
- title input, profile selection, new/save/load confirmation, and exit confirmation;
- the mothership hub (`tthubMain`, `tthubUFO`, and `controllerlegend`);
- Options, Controls, Audio, and Display;
- Archives, all museum panels, and Bink playback invoked from Archives;
- Pox's Lab screens and upgrade presentation that do not require acquiring mission progress;
- Hangar/navicom presentation and selection up to the site-launch boundary;
- frontend camera animation, UI animation, input, audio, timers, save interactions, idle behavior, rendering, and transition sequencing.

Excluded:

- mission and site gameplay;
- in-level AI, weapons, vehicles, physics, and mission scripts;
- earning progress or unlocks through gameplay;
- the destination-side loading and cutscene logic after a navicom site launch commits.

A shared engine function may appear as a direct frontend dependency. That does not pull the rest of its engine subsystem into this map.

## Naming rules

`confirmed` means a retail registration string or script-visible name identifies the function. `high` means instruction behavior and call relationships establish its role but the original C++ identifier is unavailable. `medium` means the broad role is clear while an event, property, or helper remains unnamed. `low` is reserved for tentative entries and is not yet used.

Semantic names describe observed behavior. They are not claimed to be Pandemic's original C++ identifiers. Exact original identifiers require a matching PDB, MAP file, or debug executable; none is present with the retail image. Retail Lua names and debug source paths are exact where preserved in data.

## Current tranche

The initial registry contains 34 functions across five areas:

| Area | Functions mapped | Remaining uncertainty |
|---|---:|---|
| Frontend loop and transition | 2 | Expand direct callgraph and identify the completion object's concrete class |
| Timers | 1 | Recover the human-readable update-event name |
| Display options and Lua strings | 4 | Identify the registration name for the renderer wrapper |
| Frontend widgets | 6 | Resolve eight property hashes, event type 9, and two helper actions |
| Movie playback | 21 | Map the remaining in-engine movie path and low-level Bink helpers |

The strongest result in this tranche is the fullscreen movie lifecycle. It now has stable names for open, first-frame decode, update, render, stop, close, surface release, and readiness gates. That gives Archives movie bugs a finite path to inspect rather than a loose collection of anonymous callbacks.

## Known frontend script surface

Retail debug strings preserve these exact Lua source paths:

- `input\blocks\shell\main\gui\input\gui_input_tthub.lua`
- `input\blocks\shell\main\gui\input\gui_input_transition.lua`
- `input\blocks\shell\main\gui\input\gui_input_lab.lua`
- `input\blocks\shell\main\gui\input\gui_input_lab_upgrade.lua`
- `input\blocks\shell\main\gui\input\gui_input_lab_poxspeak.lua`
- `input\blocks\shell\main\gui\input\gui_input_navicom.lua`
- `input\shared\gui\site\input\gui_site_input_options*.lua`
- `input\shared\gui\site\input\gui_site_input_selectprofile.lua`

These names define the script side of the boundary. The native side is expanded by following direct calls, vtables, Lua registration tables, hashed properties, and runtime traces from these states.

## Completion ledger

The menu map reaches a defensible end point when all of these are true:

1. **Static closure:** every native function directly reachable from the included frontend roots is classified as mapped, shared dependency, or deliberately excluded. Every indirect vtable and registered Lua callback used by those paths has a target or a documented unresolved slot.
2. **State closure:** every screen and transition in [`MENU_ROUTE.md`](MENU_ROUTE.md) has a named state, entry/exit condition, input route, render route, and save/unlock dependency.
3. **Runtime closure:** a clean profile and an existing profile exercise every reachable menu choice, back path, confirmation, idle path, movie, and allowed first-visit variant without an unknown callback appearing in the trace.
4. **Parity closure:** matched xemu and recomp captures agree on ordering, frame timing, selected state, text/visibility, camera, audio cue, movie behavior, and transition frames within documented tolerances.
5. **Regression closure:** deterministic route replays and still-frame checks pass, the registry validator passes, and no known menu issue remains open.

This makes completion knowable. We may later discover a rare retail branch, but it will enter the ledger as new evidence rather than keeping the definition of “done” vague.

## Next evidence targets

- hash candidate widget property strings against the unresolved values in `0x00101220`, `0x001022D0`, and `0x00104480`;
- identify the concrete UI classes whose vtables contain `0x001023E0` and `0x00103F20`;
- generate the direct-call frontier from `FrontendFrameDispatcher` and classify each callee without recursively absorbing gameplay systems;
- add route coverage records for title, profile, hub, options, archives, lab, and navicom.
