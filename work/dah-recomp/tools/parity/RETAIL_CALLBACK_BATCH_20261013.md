# Retail callback restoration batch — 2026-10-13

This batch restores only behavior supported by the retail `default.xbe` and
records the evidence needed to regenerate and test it. It does not use alpha
behavior or guessed semantic names.

## Restored retail code

- 12 table-referenced callbacks recovered from retail code and registration
  slots: ten constant type identifiers, one membership query, and one tail
  thunk. See `retail_type_callbacks_20261013.json`.
- 7 Microsoft CRT control-flow tails recovered byte-for-byte from retail code.
  See `../analysis/retail_crt_tails_20261013.json`.
- 3 late retail tails recovered from executable code: one CRT error tail and
  two XMV helper tails. See `retail_late_tails_20261013.json`.

The source lifters regenerate the three corresponding
`src/recomp/gen/recomp_retail_*_20261013.c` files. The `.mjs` harnesses compare
the emitted x86 bytes with retail and exercise the recovered behavior, including
negative controls that deliberately reject altered implementations.

## Dispatch correction

`recomp_dispatch.c` contained more entries than its hard-coded table size. The
last 58 existing entries could not be reached through either the binary-search
dispatcher or flat callback table. The size is now derived from the array, and
`test_dispatch_table.py` checks ordering, uniqueness, range coverage, and both
lookup models for all 10,851 entries.

## Remaining boundary

Five genuine generated recovery stubs remain at retail addresses `0x13FBDC`,
`0x142434`, `0x142450`, `0x14245C`, and `0x1424B3`. Six additional generated
labels are proven false code edges inside retail XGRPH/BINK data and receive no
callback-restoration credit. No cumulative indirect-call seed currently points
to any recovery stub.

This batch passed the isolated retail-byte harnesses, dispatch and callback
audits, the normal build and CTest suite, the internal build, and a bounded
300-frame internal boot with no unresolved callback, assertion, or crash marker.
Scenario-specific gameplay parity still requires matched retail/recomp runs.
