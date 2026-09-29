# Menu graphics checkpoint, paused for Farm parity

Menu bug investigation was explicitly paused in favor of exact loading into
Turnipseed Farm and its first gameplay frames. No red-border fix was attempted.

The first explicit native RenderDoc capture was replayed and exported entirely
through the console helper, without UI or game-process control:

- Capture: `build-internal/parity-x8-fixed-20260926-013_capture.rdc`, 7,782,254 bytes.
- Source process 53636; hook host frame 6001, retail loop 6000 -> 6001.
- 76 actions and 49 textures. RenderDoc's own frame number is UINT32_MAX for
  this manual capture; retain the hook log as the authoritative loop tag.
- Final swapchain copy is event 2311 to `texture:0`, 640x480 R8G8B8A8_UNORM.
- Last rendered presentable is event 2307, `texture:2`.
- Those two exports are byte-identical in RGBA. RGB SHA-256 is
  `f2214cd37c35df6921a25f931ff36e3d109cd8b069f59cd877f9fa876f010199`;
  native capture's BGR-order FNV-1a convention gives `2E442309`.
- Exported alpha spans 191..255. Pixel comparisons should explicitly use RGB;
  an image viewer compositing alpha is not the opaque swapchain's presentation.

Artifacts are under `build-parity-xemu/` with prefix
`renderdoc-x8-guest6001-20260926-001-`: `inspect.jsonl`, `final.png`,
`presentable.png`, `scene.png`, `composite.png`, `half.png`, and `report.json`.
Intermediate labels describe their role approximately; event/resource IDs are
the precise provenance. The final image shows Pox's Lab.

No independent BMP exists for this exact source frame: process 53636 captured
5970 and 6030. Native BMP numbering starts at zero, while the hook uses a
one-based frame serial; the matching next validation pair is BMP counter 6000
with `DAH_RENDERDOC_FRAME=6001`, provided startup/present-call behavior is the
same. The root owner should schedule both in one fresh run.

Remaining menu issue: red strips are visible at the native image's right and
bottom boundaries, reported absent from the xemu Pox reference. Their originating
draw has not been identified. The capture retains all draws needed for later
pixel-history/intermediate investigation; no cause or correction is established.
Final-vs-presentable equality shows the final CopyResource preserves these
pixels, but does not identify which earlier pass produced them.

The helper's compile/probe, offline inspection, event selection, and PNG export
are now exercised. Live target-control capture/listen remain untested; explicit
native app capture works through the owner's separate opt-in game hook.
