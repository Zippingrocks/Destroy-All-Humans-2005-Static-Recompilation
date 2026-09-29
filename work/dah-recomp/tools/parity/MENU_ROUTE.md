# Retail menu parity route

This is a state-gated route, not a list of absolute wall-clock delays. It was
derived from the retail Lua 4 bytecode/debug strings in the captured Xbox RAM,
the existing native input audits, and `afterintro-20260926-010.png`. The entire
route has not yet been replayed and verified on both engines.

## Starting point and input

The fresh New Game route is title Start -> New Game A -> empty profile A ->
save confirmation A -> intro -> mothership. Verify each visible state before
advancing. Existing profiles can add an overwrite dialog and must not be treated
as equivalent starting conditions.

For a menu-only run, the retail intro is legitimately skippable: while
`moviePlaying` is true, `gui_site_input_selectprofile.lua` accepts
`cfgInput.start` or `cfgInput.advance`. Its handler calls `movie.Stop`, stops
`CheckIntroMovie`, removes the `intromovie` active input section, stops subtitles,
and invokes `LoadFarm` (despite its name, this path returns to `ttHubUFO`). Send
one A or Start pulse only after confirming the intro has begun. This does not
validate the full intro or its timing.

Use `@frame` scripts and a single short logical pad pulse (for example 6 loops)
followed by neutral input. Observe the destination state before scheduling the
next pulse. The common digital bits are Up=1, Down=2, Left=4, Right=8, Start=10
(hex); A/B are separate analog fields. Existing older scripts counted controller
polls and repeated broad input windows; they are useful route evidence but are
not suitable for exact transition comparisons.

## Hub, Options, Pox, and Hangar

| Checkpoint | Input from preceding checkpoint | Expected observable state |
| --- | --- | --- |
| Hub | Intro finishes or receives one skip pulse | `tthubMain`, `tthubUFO`, and `controllerlegend` active; slot2 Hangar selected |
| Options | Down, neutral, A | `options` active after camera transition; Controls initially selected |
| Controls | A | `optionsController`; rows Camera Pitch, Camera Turn, Vibration |
| Control edits | Right then Left on each row, Down between rows | Each setting changes and restores; selected row advances once per Down |
| Options return | B | `options` active |
| Audio | Down, neutral, A | `optionsAudio`; Music, Effects, Dialogue, and Xbox Sound Mode rows |
| Audio edits | Left then Right on volume rows | Use decrement first at maximum volume so restoration is meaningful; retain originals for all checks |
| Display | B, Down, neutral, A | `optionsDisplay`; exact rows depend on platform/video mode |
| Subtitle edit | Right then Left on first row | Subtitle value changes and restores |
| Hub return | B, then B after Options is confirmed | Camera returns to hub; observe selected underline rather than assuming selection |
| Pox's Lab selection | Navigate hub to slot4, then A | `tthubLab`; camera transition and Orthopox animation |
| First lab tutorial | Wait for tutorial completion | First visit uses `shell.upgradetute`, `shell_lab_upgradetute`, and `PoxLipsynchAnimDone`; proceeds to `labAlien` |
| Later lab visit | A from settled `tthubLab` | Transition from `camera.lab` into `labAlien` |
| Saucer hologram | Right or Left from `labAlien` | `labUFO`; alien/UFO activation animations switch |
| Crypto hologram | Right or Left from `labUFO` | `labAlien` |
| Crypto upgrades | A from `labAlien` | `labUpgrade`, initial weapon `zapomatic`, mode `alien` |
| Upgrade navigation | Left/Right and Up/Down separately | Weapon/category and upgrade selection; capture text, price, DNA, highlight, mesh, and Pox |
| Hologram return | B from `labUpgrade` | Camera transition back to `labAlien` or `labUFO` according to mode |
| Lab landing | B from settled hologram menu | `tthubLab` |
| Hub return | B from settled `tthubLab` | Hub; may autosave if `saveDirty` |
| Hangar | Navigate to hub slot2, A | `navicom`; mother hologram fades out and navicom fades in |
| Destination selection | Right and Left, observing each change | `siteName`, `siteRing`, `siteActive`, mission label and unlock state change |
| Hub return | B from settled `navicom` | Camera `camera.navicom`, transition destination `tthubUFO` |

Fresh profiles do not unlock all destinations or upgrades. Compare the actual
fresh-profile restrictions, and retain a separate progressed-profile route for
all available places and purchase animations. A in `navicom` launches the
selected mission; A in `labUpgrade` attempts a purchase. Treat those as distinct
route branches with their own starting save state. Back on the hub itself opens
the Exit Game confirmation, so do not send blind repeated B pulses.

## Read-only state and timing observations

`decode_xemu_ram.py` already reads the retail loop at `0x25B1DC`, renderer at
`[0x250E60]`, backend at `[0x25B1D0+0x4A28]`, pending backend at
`[0x25B1D0+0x4A2C]`, and UI root at `[[0x258470]]`. UI containers form a linked
list with sentinel `object+0x44`, next at node+0, and child at node+8. Object name
is at +0x0C, active byte at +4, parent at +8, and flags at +0x5C. Resolve objects
by their full name paths because heap addresses differ between engines/runs.

Selection can be observed without changing Lua state:

- Hub: `tthubMain/slotN/underline` active byte. The actual initial RAM capture
  has only slot2's underline active, matching the Hangar screenshot.
- Options/Controls/Audio/Display: inspect each slot's `bkgnd` active state and
  text child state. Read all rows and preserve their order from their slot names.
- Lab upgrades: `labUpgrade/slots/slotN/selected` and the associated text/icon
  nodes, weapon title, price, and DNA label.
- Hangar: `navicom/siteName`, `siteRing`, `siteActive`, `newStoryMission`, and
  `sandboxMission` children.

The native `DAH_TTHUB_TRACE` and `DAH_HUB_RENDER_TRACE` diagnostics already log
the hub tree, flags, and raw fields at +0x68..+0x7C. Those raw geometry fields can
be compared by bits at equal relative frames without guessing their meanings.
The retail world step is the float at `[0x286768]+0x10`. Renderer refresh is
derived from +0x238; divisor is +0x27C and presentation interval is +0x2C8.

Camera transitions use Lua `transitionAnim`/`transitionName` and poll
`world.IsNodeAnimPlaying`; lab tutorial completion uses
`mesh.GetAnimProgress(poxMesh)` through `PoxLipsynchAnimDone`. The Pox
`CheckAnimStatus` task watches animation progress; it does not use sound-channel
playback status as the completion test. Subtitle duration is obtained separately
from `world.GetGlobalSoundDuration`/`sound.GetDuration`. If Pox stalls, inspect the
mesh animation clock before attributing it to silent audio.

The native retail timer callback `sub_0011C180` accepts update event `0x6BFC080F`.
Its timer object fields are state +0x10, callback index +0x14, accumulated float
+0x18, start float +0x1C, duration float +0x20, and repeat byte +0x24. When a timer
object is identified from its owner, log these fields to find a delayed callback
or float-threshold mismatch. Do not assume a global fixed timer address.

For each transition capture input accepted, first destination UI activation,
first destination present, and stable destination. Align at the accepted input
and compare frame 0,1,2,... through completion, including each animation clock.
Pause/debugger capture can validate state and pixels but perturbs wall time.
`savevm` flush followed by `stop` is not an exact presented-frame boundary; a
native pixel difference there is evidence of a difference, not proof that two
frames represent the same animation instant.

## Evidence sources

Retail RAM: `build-parity-xemu/ram-afterintro-20260926-010.bin` and
`ram-intro-20260926-008.bin`, with their checkpoint CR3 metadata. The RAM contains
Lua 4 binary chunks with source paths and debug strings, including:

- `input\\blocks\\shell\\main\\gui\\input\\gui_input_tthub.lua`
- `input\\blocks\\shell\\main\\gui\\input\\gui_input_transition.lua`
- `input\\blocks\\shell\\main\\gui\\input\\gui_input_lab.lua`
- `input\\blocks\\shell\\main\\gui\\input\\gui_input_lab_upgrade.lua`
- `input\\blocks\\shell\\main\\gui\\input\\gui_input_lab_poxspeak.lua`
- `input\\blocks\\shell\\main\\gui\\input\\gui_input_navicom.lua`
- `input\\shared\\gui\\site\\input\\gui_site_input_options*.lua`
- `input\\shared\\gui\\site\\input\\gui_site_input_selectprofile.lua`

The strings establish names and intended branches; executing each checkpoint
on both engines is still required to certify the route and its timing.
