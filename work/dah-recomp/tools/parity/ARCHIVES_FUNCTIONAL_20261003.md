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

## Complete packaged-movie audit

`audit_archives_bink.py` walks every packaged `.bik` and validates its Bink
signature, declared file size, dimensions, frame rate, audio-track table,
frame-index bounds and ordering, largest-frame bound, and final payload
boundary. `archives_movie_asset_audit_20261003.json` records a clean result for
all 23 movies (23 passed, 0 failed). This includes the long bonus movies and
`plan9.bik`, whose valid zero padding between its frame table and first frame is
preserved.

The available save exposes only some entries, so three representative entries
were exercised in-engine without progressing gameplay: THQ Logo from Videos,
Furonigami from its bonus gallery, and Making Of from Propaganda. They all use
the same Archives launcher and native Bink decode/render/close path. Locked
entries have complete container and frame-table coverage but have not been
claimed as visually watched end-to-end.

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

## Furonigami black-screen correction

The normal PC player could remain on the movie-transition black clear after
opening `introani.bik`. The decoder and full-screen draw were healthy in the
cooperative diagnostic run; the failure was the production update spinning in
`BinkWait` on the game thread instead of returning to the host frame pump.

Every movie now yields only when a regular update finds its next frame not
ready. Live repeated playback proved that Archives movies can use several path
buffers, and the same starvation later affected the new-game intro, so the
former address-specific exception was incomplete. Initial preload remains
blocking, decoded frames still flip and call `BinkNextFrame` through the retail
path, and close lifecycle is unchanged. Startup logos retain their native
movie clock and frame order; the host may present a duplicate movie frame
while Bink reports that its next frame is pending.
`test_movie_nonblock.mjs` completes 3,811 assertions for the cooperative path,
including pending-frame preservation, native-rate decode/advance cadence,
texture selection, preload, and final-frame close.
