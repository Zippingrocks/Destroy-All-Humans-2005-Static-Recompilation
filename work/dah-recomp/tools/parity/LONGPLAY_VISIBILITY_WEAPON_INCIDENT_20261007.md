# Long-play visibility, cutscene, text, and DestructoRay incident

## Run identity

- Run: `20261007T064831185Z-p48988-9470C2DDEE4F43E3`
- Native process: `48988`
- Executable SHA-256: `901E64782833D3C4A7DE2D1F4EA2CA24332074562B69E35EA60163614E800AAD`
- Retail XBE SHA-256: `B9491B30EAEE82AF6C805D9B0036EC1119059B0660A0923803EBDB6219FA02EB`

The player reported these observations during the same long run. They remain
separate defects until a shared state transition or call boundary joins them:

- G-man hats detached or failed to remain attached, especially in cutscenes;
- characters vanished and Crypto sometimes spawned partially invisible;
- Crypto remained invisible throughout the G-man interrogation cutscene;
- the interrogation cutscene lacked effects, exposed broken models for one or
  two seconds, and paused before continuing;
- a Rockwell tank vanished;
- menu, objective, or other text became incorrect;
- the Disintegrator may have fired too quickly after mission completion.

## Retrospective evidence

The persistent event trace contains 125,950 complete frame records. Its median
and p95 interval are both 33,333 microseconds and p99 is 33,341 microseconds.
The largest interval is 173,766 microseconds. A cluster at world tick 21,335
contains 68,697 and 78,098 microsecond intervals. Those records prove isolated
hitches, but the run lacked a cutscene-shot marker, so they cannot yet be
assigned to the reported interrogation freeze.

The run logged a new unresolved indirect target at `0x000A21A0`, reached from
return address `0x0009E5BB` while a parent object reset three child objects
through vtable slot `0x40`. Retail vtable `0x0022FB38` has class ID
`0xB0011E79`. The alpha PDB and executable identify the same class ID as
`UFO::WeaponDestructoRay`; its corresponding alpha vtable slot is the shared
`UFO::Weapon::Reset` entry. Neighboring DerivedFrom, VirtualClassId, and
ProcessEvent slots also align. This is evidence level B for the retail name
`UFO::WeaponDestructoRay::Reset`.

The 18 original retail bytes call the object's state virtual with false and
tail-call base reset `0x00097C00`, which clears state bytes `+0x34` and `+0x37`.
Skipping the callback therefore skipped real weapon shutdown/reset work. The
callback is now byte-checked by `tools/lift_longplay_runtime_callbacks.py`,
compiled in `recomp_longplay_callbacks.c`, and registered for indirect
dispatch. This is the smallest proven repair relevant to the possible
post-mission Disintegrator state. A matched native/xemu firing interval is still
required before declaring cadence parity.

## Watcher correction

The actor observer was not running through the reported segment, and the UI
observer had to be launched separately. That prevented retrospective proof of
the first bad render pointer, attachment state, or one-frame text transition.
`watch_blanket_runs.py` now starts both hidden, read-only observers for every
matching user-launched process. `live_blanket_observer.py` also records Crypto's
render pointer and state byte. The current process was left untouched and both
new observers were attached after this incident; they can capture subsequent
changes but cannot reconstruct the earlier cutscene.

## Open boundaries

The next aligned interrogation run must record the first render/visibility
transition for Crypto and the G-men, UI/cinematic transitions, and the exact
frame hitch. Hat attachment and skeletal-part visibility still need a proven
retail object path before the observer can name those fields. Vehicle/tank
streaming and render decisions require the same treatment. These open layers
must not be marked fixed from the DestructoRay callback.
