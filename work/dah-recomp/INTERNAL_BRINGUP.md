# Internal verification notes — 2026-09-12

Target: a real, interactive main menu at measured 30 FPS. Not yet achieved.
The user's visible build is not the test target. Build and run only
`build-internal`; it has independent data, saves, and logs. The bounded runner
does not show/focus a window, poll physical input, or output audible sound.

## Verified repairs

- The retail timer event path now permits its script callbacks, opening
  `movies/logo_thq.bik` instead of stopping before the movie.
- Xbox MMX capability detection no longer leaves converter callbacks null.
- Restored 969 MMX instructions in the existing/new Bink conversion routines,
  checked against original disassembly. Packed integer helpers passed
  4,476,487 comparisons against SSE2 hardware results.
- Kernel ordinal 235 consumes six guest arguments, not five. Its missing
  WaitMode argument caused incorrect parameter mapping and stack cleanup.
- Kernel dispatch selection is thread-local. A shared selector allowed Bink
  workers to invoke another thread's bridge/stack cleanup.
- 36 CMP-to-SBB carry dependencies in the Bink bundle-width setup restored.
  For a 640-wide frame, the affected length fields are ten bits, not eleven.
  The underlying lifter also preserves CMP/TEST carry for future generation;
  50 recomp unit tests and the six existing carry self-checks passed.
- Exact-source kernel bridge tests passed 12 cases. Four negative controls
  reject the previous argument map, cleanup size, missing count bound, and
  shared dispatch selector.
- The Bink wait clock now receives the original 733333333 Hz RDTSC timebase
  from QPC. Frames advance at each movie's native 25 FPS without speeding up
  the media to meet a presentation counter.
- Indexed movie geometry and pixels resolve through the actual contiguous
  GPU-memory window (0x80000000 + offset), not unrelated low guest RAM.
  The narrow renderer accepts the observed retail shader/layout/combiner,
  uploads native movie pixels, and rejects unknown configurations.
- Restored 46 omitted D3D MMX transfers; 8,192 complete-function regression
  cases passed. Restored eight MOVSX BP operations in Bink; 2,097,152 exact
  signed-vector tests passed. The three inverse-transform repairs removed
  the scattered block artifacts in subsequent actual captures.
- All 49 original VM opcode-table entries now have implementations and
  dispatch; exact-handler regression passed 5,765 cases / 3,182,203 assertions.
- Startup cleanup and number-formatting callbacks pass 49 exact-wrapper
  cases (409 original XBE bytes); the first four audio cleanup callbacks
  pass 143 cases (241 original bytes). Tests include deliberately broken
  stack/argument controls. These are scoped original-code restorations.
- The audio-close chain now contains seven byte-checked callbacks and passes
  167 cases. The six connected frontend callbacks pass 1,126 cases; a separate
  512-case test checks the two-vector argument layout of 0x104480.
- Restored 16 UCOMISS-to-LAHF flag transfers in frontend/VM code. Exact-site
  checks cover 203 original bytes; 305,408 cases match a native SSE flag oracle.
- Fixed CRT classifier 0x13F383: correct EBP, live FXAM classification/sign,
  byte-sized shifts/rotates, and both XLAT lookups. Tests cover 100,000 native
  FXAM comparisons and 7,744 actual-source dispatch cases. Without XLAT, the
  routine indexed between pointers and jumped to 0xF4C20013.

## Runtime evidence, not success claims

- PID 10116: first actual movie indexed draw reaches the pushbuffer at
  submission 204. Four indices refer to a float4/float2/ARGB vertex layout;
  texture 0 is the native 640×448 linear X8R8G8B8 movie buffer.
- PID 41512: after the kernel repairs, a Bink entropy decoder overran guest
  memory. Traces and original-code comparison identified the carry defect.
- PID 44460: after carry repair, first-frame bundle traces show ten-bit
  lengths and valid counts of 520. The bounded 60-second run did not crash,
  but stalls waiting before the next movie frame. No menu or 30 FPS native
  rendering has been verified. Its first submitted vertex was all zero and
  was correctly rejected by the narrow movie renderer.
- PID 10676: first actual nonblank movie captures; THQ and Pandemic movies
  both complete. Images still contained block artifacts. Subsequent menu
  script execution hit missing opcode 0x196A66 and crashed.
- PID 19464: clean THQ animation confirmed from actual framebuffer capture
  280 after the MOVSX repair. Startup then stalled in native audio-stop
  polling; missing audio dispatch callbacks were restored afterward.
- PID 42376: both movies complete again, now with correct audio event
  dispatch. Main-menu setup progresses through restored VM aggregate code;
  missing RegisterKeyTable and formatting callbacks were the next blockers.
- PID 23988: RegisterKeyTable now executes; menu object setup and mission
  dispatch progress further. Missing 0x1023E0 / 0x103F20 / 0x1022D0 callbacks
  are the next proven blockers. No main-menu image or stable 30 FPS menu
  has been verified. This is still incomplete.
- PID 4856: previous three missing frontend callbacks no longer occur;
  another connected property callback (0x104480) is restored next.
- PID 2020: audio-close and known frontend callbacks resolve, advancing
  further through menu setup. The next errors are CRT classification's
  invalid target above and missing name-lookup unwind 0x191FAA. The latter
  is now restored and tested over 512 saved-register/return combinations.
  The CRT's six real remainder-table targets are being restored separately.
- PID 46916: both clean intro movies play and complete. Two steady five-second
  intervals measured 30.000/30.005 loop and drawn-frame FPS, with p99 intervals
  of 33.333/33.336 ms. Native audio shutdown still caused a roughly 516 ms
  transition hitch. After movie completion the last captured framebuffer was
  black; menu startup reached missing script, timer, audio and render-format
  callbacks. This is NOT a successful main-menu boot.
- Restored the observed 0x8BA90 / 0xE3BE0 script natives and 0x11C180 timer
  callback: 40,120 actual-body cases, 381 original bytes and five negative
  controls. Added stream-format 0x1F225D and its narrowly connected callbacks;
  the audio suite now covers 26,125 cases and eight negative controls.
- Closed both original jump tables in the render-target format encoder at
  0x1E0420. Ten missing arms retain the original common tails and `ret 8` ABI.
  Complete encoder tests cover 127,472 combinations of format, dimensions and
  depth format against the actual XBE tables; three negative controls fail.

An opt-in `DAH_MOVIE_NONBLOCK=1` scheduling adapter is available via
`tools/run_internal.ps1 -NonblockingMovie`. Only the proven regular update
caller may return while BinkWait is pending; preload stays synchronous and
no decode, texture, timestamp, or frame advance is forged. Exact-function
tests verify 150 updates / 125 decode-and-advance events in five simulated
seconds. PID 46916 verifies clean movie continuity with measured 30 FPS host
updates during steady playback, while preserving the movie's native decode rate.
The original blocking behavior remains the default. Frame summaries now
include p95/p99 intervals to expose stutter rather than only average FPS.

September 13 checkpoint (incomplete visual target):

- Native atlas rendering now displays Press Start; the restored original
  0x63510 event callback advances to real New Game / Load Game text.
  Evidence: `build-internal/dah_frame_26348_0000001180.bmp`.
- The text-only menu baseline PID40384 completed a 360-second bounded run,
  including over five minutes after Start. This does NOT validate a complete
  3D menu or the newer renderer. Background scene assets were still missing.
- Startup no longer calls AllocConsole: stdout/stderr already go to recomp.log.
  Only build-internal was rebuilt; the user's other executable is untouched.
- Newer in-workspace 3D code was preserved and corrected for BC1: BASE_SIZE
  fields encode texel dimensions, blocks are row-major, and captured static
  textures use low RAM. Removed the incorrect Morton-tile decoder and stale
  UI IMAGE_RECT sizing. BC1 is decoded to BGRA for tiny 1/2-texel host textures.
  Content is refreshed even when an asset reuses the same address.
  `tools/test_bc1.c`: 260 shape/size cases plus block order, interpolation,
  transparency, pitch and short-input checks. Captured UI transport still passes.
- Added a 17-slot program start bound and whole-strip rejection for invalid
  transformed vertices, rather than creating artificial offscreen triangles.
- PID1756: 65-second hidden run survives and has steady 30 FPS intervals after
  startup hitches. BC1 trace correctly reads 2x2 / 8 bytes at 0x028FDF00.
  Frame1240 still does NOT match the reference: only text/dark malformed geometry.
- Remaining blocker: menu MVP c36..39 collapses scene vertices near the screen
  center, with clip W around 1e8. Trace the original CPU matrix inputs/producers;
  do not replace them with guessed camera values. DAH_MATRIX_TRACE enables a
  bounded read-only source trace in 0xD64A0 for the active camera matrix.
  PID19084 narrows it further: caller0xE7246 passes view data at0x00F7D470
  copied by0xD6100 from active camera+0x50. Its basis contains3203280,
  9200206,-12335760,15388787 before multiplication. Projection at0x27D630
  has ordinary values(-2.41421342,3.21895123,1.00003994,-0.0100003993).
  Trace the producer of the camera view matrix; do not blame the GPU upload
  or substitute a guessed matrix. PID19084 survives its50-second bound.
  Lighting validity, other shader/combiner programs, render targets and proper
  depth/culling also still need validation before claiming the full 3D scene.

The target remains the user's complete space/Earth/mothership/saucer reference,
rendered from native assets at stable 30 FPS. Text or a ticking loop is not enough.

`recomp-internal-<PID>.log`, optional `recomp-crash-<PID>.log`, actual framebuffer
BMPs, and indexed pushbuffer dumps live beside the internal executable.
Capture readback is synchronous and must be disabled for a final pacing soak.
The static `DAH_HOST_FRAME` probe is disabled throughout these tests and is
never menu evidence. Hidden-window occlusion and a ticking loop alone are not
proof that the game is rendering correctly.
