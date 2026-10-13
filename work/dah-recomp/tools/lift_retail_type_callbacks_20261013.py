"""Recover twelve small, byte-checked retail function-table callbacks.

No alpha symbols or guessed class names are used. The ten constants are
identified only as retail type IDs because the neighboring table entries
compare the same values. Live reachability is not claimed by this static audit.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PROJECT = ROOT / "work/dah-recomp"
SOURCE = PROJECT / "src/recomp/gen/recomp_retail_type_callbacks_20261013.c"
EVIDENCE = PROJECT / "tools/parity/retail_type_callbacks_20261013.json"
# entry, constant, original .rdata pointer slot
GETTERS = (
    (0x00012700, 0x68F1100B, 0x00225EA8),
    (0x00012A40, 0x1975BCED, 0x00226060),
    (0x00015AE0, 0x177F1145, 0x00226510),
    (0x000161C0, 0xF90E4ACE, 0x00226738),
    (0x0005FA20, 0xF2D43FBF, 0x0022A8DC),
    (0x0009A260, 0x71C8DF8F, 0x0022F498),
    (0x0009C2D0, 0x8BFCF9A0, 0x0022F620),
    (0x000A1270, 0x6460CAB8, 0x0022FA00),
    (0x000A1DB0, 0x68195EBC, 0x0022FAC0),
    (0x000A4980, 0x9BCE23F0, 0x0022FE20),
)
QUERY = 0x00012A10
QUERY_SLOT = 0x0022605C
QUERY_BYTES = bytes.fromhex(
    "8b4424043dedbc75197505b001c204003db6c705b474f4"
    "3dfc40328874ed3d3929083874e63debfa5fa70f94c0c20400"
)
THUNK = 0x000127D0
THUNK_TARGET = 0x000117D0
THUNK_SLOT = 0x00225F20


def retail_image():
    data = (ROOT / "work/default.xbe").read_bytes()
    u32 = lambda o: struct.unpack_from("<I", data, o)[0]
    table = u32(0x120) - u32(0x104)
    sections = []
    for i in range(u32(0x11C)):
        p = table + i * 56
        sections.append((u32(p + 4), u32(p + 12), u32(p + 16)))

    def read(va, size):
        for start, offset, length in sections:
            if start <= va and va + size <= start + length:
                return data[offset + va - start:offset + va - start + size]
        raise ValueError(f"Retail range is not file-backed: {va:08X}+{size}")
    return data, read


def generate():
    data, read = retail_image()
    records = []

    def verify(start, expected, slot, kind):
        assert read(start, len(expected)) == expected, f"Retail bytes changed at {start:08X}"
        assert struct.unpack("<I", read(slot, 4))[0] == start, f"Table slot changed at {slot:08X}"
        # A return immediately before the next entry or INT3 padding after it
        # proves the selected range ends at an instruction boundary.
        assert read(start + len(expected), 1) == b"\xcc" or start == QUERY
        records.append({
            "start": f"0x{start:08X}", "end": f"0x{start + len(expected):08X}",
            "bytes": len(expected), "tableSlot": f"0x{slot:08X}",
            "purpose": kind, "codeBytesSha256": hashlib.sha256(expected).hexdigest().upper(),
        })

    out = [
        "/* Retail-only callback restoration; regenerate with tools/lift_retail_type_callbacks_20261013.py. */",
        '#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n',
    ]
    for start, value, slot in GETTERS:
        expected = b"\xb8" + struct.pack("<I", value) + b"\xc3"
        verify(start, expected, slot, "type ID return")
        out.append(f"""/* 0x{start:08X}: mov eax, 0x{value:08X}; ret. Retail table 0x{slot:08X}. */
void sub_{start:08X}(void)
{{
    g_eax = 0x{value:08X}u;
    g_esp += 4u;
}}
""")
    verify(QUERY, QUERY_BYTES, QUERY_SLOT, "type membership query with ret 4")
    out.append("""/* Retail 0x00012A10..0x00012A40. MOV AL/SETE AL preserve the upper EAX bytes. */
void sub_00012A10(void)
{
    g_eax = MEM32(g_esp + 4u);
    if (g_eax == 0x1975BCEDu) goto accepted;
    if (g_eax == 0xB405C7B6u) goto accepted;
    if (g_eax == 0x883240FCu) goto accepted;
    if (g_eax == 0x38082939u) goto accepted;
    SET_LO8(g_eax, g_eax == 0xA75FFAEBu);
    g_esp += 8u; /* ret 4 */
    return;
accepted:
    SET_LO8(g_eax, 1u);
    g_esp += 8u; /* ret 4 */
}
""")
    expected = b"\xe9" + struct.pack("<i", THUNK_TARGET - THUNK - 5)
    verify(THUNK, expected, THUNK_SLOT, "direct tail forwarding thunk")
    out.append("""/* 0x000127D0: jmp 0x000117D0. Preserve the caller's return address. */
void sub_000127D0(void)
{
    sub_000117D0();
}
""")
    evidence = {
        "schema": 1, "source": "retail-xbe-only",
        "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
        "discovery": "Missing dispatch entries referenced by adjacent retail .rdata function pointers",
        "validationScope": "Exact bytes, table slots, production-body register/stack tests; matched gameplay pending",
        "callbacks": sorted(records, key=lambda r: r["start"]),
    }
    return "\n".join(out), json.dumps(evidence, indent=2) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    source, evidence = generate()
    if args.check:
        assert SOURCE.read_text(encoding="utf-8") == source, "Production source differs from verified lift"
        assert EVIDENCE.read_text(encoding="utf-8") == evidence, "Evidence differs from verified retail bytes"
    else:
        SOURCE.write_text(source, encoding="utf-8")
        EVIDENCE.write_text(evidence, encoding="utf-8")
    print("PASS: 12 retail table slots and 113 instruction bytes verified")


if __name__ == "__main__":
    main()
