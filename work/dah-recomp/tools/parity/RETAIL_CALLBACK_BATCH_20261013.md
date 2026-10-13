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

## Recovery boundary completed

The final five genuine generated recovery entries are restored from retail:
the nonlocal x87 tail at `0x13FBDC` and the coherent descriptor-allocation CFG
entered at `0x142434`, `0x142450`, `0x14245C`, and `0x1424B3`. The latter keeps
its backward edges inside one continuation instead of recursively repeating the
parent's SEH prolog and lock acquisition. The isolated harness covers 13 cases
and 116 assertions, with four negative controls.

There are now **zero genuine no-op recovery stubs**. Six generated labels remain
inert because retail bytes prove they are false code edges inside XGRPH/BINK
data. They are excluded from dispatch and receive no callback-restoration credit.

This batch passed the isolated retail-byte harnesses, dispatch and callback
audits, the normal build and CTest suite, the internal build, and a bounded
300-frame internal boot with no unresolved callback, assertion, or crash marker.
Scenario-specific gameplay parity still requires matched retail/recomp runs.
