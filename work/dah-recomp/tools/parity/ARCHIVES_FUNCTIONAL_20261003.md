# Archives video and bonus-extras functional checkpoint — 2026-10-03

The hidden controller route enters the mothership Archives from the default
Hangar selection, opens the Archives browser, and exercises its content panels
without taking desktop focus. The browser exposes five panels in this save:
`museummovie`, `museumfuronigami`, `museumpropoganda`, `tutorialguide`, and
`stats`.

## Verified paths

- Videos: `archives_video_playback_probe.txt` opens the initial unlocked
  `THQ Logo` entry. `archives-video-playback-010.log` records
  `d:\movies\logo_thq.bik`, a nonzero Bink handle, decode/render activity,
  normal close, and a clean return through `museummovie` to `museum`.
- Furonigami bonus: `archives_bonus_galleries_probe.txt` opens
  `d:\movies\introani.bik`, decodes it, accepts B, and restores
  `museumfuronigami`.
- Propaganda bonus: the same probe opens `d:\movies\makingof.bik`, decodes it,
  accepts B, and restores `museumpropoganda`.
- Browser navigation and exit were also exercised for Tutorial Guide and Stats.

No crash, fatal path, or unresolved callback appeared during these runs. The
movie files are present in the packaged `movies` directory. Hidden/occluded
runs prove menu state, file selection, decoding, playback lifecycle, and return
behavior; final pixel comparison still requires a non-occluded capture.

## Captured transition checks

Pre-Present captures of the Videos path show three intentional black preroll
frames (`1320` through `1322`), followed immediately by decoded THQ-logo image
data at frame `1323`. Natural completion fades the final THQ frame to black at
`1488`, restores the Archives theater at `1489`, restores the list at `1490`,
and completes the room fade without a white or retained-movie frame.

`analyze_movie_transition.py` turns these frame sequences into a JSON record,
rejects all-white frames, and can enforce the expected preroll length. This
keeps the former white-screen/image-burn failure covered without changing game
timing or movie content.

## Diagnostics

`DAH_MUSEUM_TRACE=1` emits bounded, read-only snapshots when an Archives panel
becomes active. It exposes menu/slot names, active highlights, and UTF-16 label
storage without mutating save data or UI state. The trace is disabled by
default.
