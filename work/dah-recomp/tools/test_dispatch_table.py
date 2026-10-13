#!/usr/bin/env python3
"""Guard generated indirect dispatch coverage against a stale size constant."""
import re
from pathlib import Path

project = Path(__file__).resolve().parents[1]
source = (project / "src/recomp/gen/recomp_dispatch.c").read_text(encoding="utf-8")
entries = [
    int(value, 16) for value in re.findall(
        r"^\s*\{\s*0x([0-9A-Fa-f]{8})u,\s*\(recomp_func_t\)", source, re.MULTILINE
    )
]
assert len(entries) > 10000
assert entries == sorted(entries), "dispatch table must remain sorted for binary search"
assert len(entries) == len(set(entries)), "duplicate dispatch address"
assert re.search(
    r"g_recomp_table_size\s*=\s*sizeof\(g_recomp_table\)\s*/\s*sizeof\(g_recomp_table\[0\]\)",
    source,
), "dispatch size must derive from the actual table"
base = int(re.search(r"g_flat_base\s*=\s*0x([0-9A-Fa-f]+)u", source).group(1), 16)
span = int(re.search(r"g_flat_span\s*=\s*0x([0-9A-Fa-f]+)u", source).group(1), 16)
assert all(base <= address < base + span for address in entries)

def binary_lookup(target):
    low, high = 0, len(entries)
    while low < high:
        middle = low + (high - low) // 2
        if entries[middle] < target: low = middle + 1
        elif entries[middle] > target: high = middle
        else: return entries[middle]
    return None

flat = {address - base: address for address in entries}
for address in entries:
    assert binary_lookup(address) == address
    assert flat.get(address - base) == address
for address in (base - 1, base + span, 0, 0xFFFFFFFF):
    assert binary_lookup(address) is None
    assert flat.get((address - base) & 0xFFFFFFFF) is None
print(f"PASS: all {len(entries)} generated dispatch entries reachable in binary and flat lookup models")
