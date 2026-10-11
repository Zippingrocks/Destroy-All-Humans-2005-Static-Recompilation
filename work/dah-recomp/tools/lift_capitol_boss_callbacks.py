"""Lift the two retail Capitol boss vtable entries missed by discovery."""

import argparse
import hashlib
import json
from pathlib import Path
import sys


workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator


CALLBACKS = (
    (0x00034C70, 0x00034C8B, "Capitol boss type-query callback"),
    (0x00035000, 0x0003500E, "Capitol boss activation callback"),
)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path)
    parser.add_argument("--evidence", type=Path)
    args = parser.parse_args()

    xbe_path = workspace / "default.xbe"
    configure_from_xbe(str(xbe_path))
    data = xbe_path.read_bytes()
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    functions = {
        start: {"name": f"sub_{start:08X}", "end": end}
        for start, end, _ in CALLBACKS
    }
    output = ['#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n']
    records = []

    for start, end, purpose in CALLBACKS:
        offset = va_to_file_offset(start)
        code_bytes = data[offset:offset + end - start]
        instructions = list(decoder.disasm(code_bytes, start))
        assert instructions
        assert instructions[-1].address + instructions[-1].size == end
        assert sum(ins.size for ins in instructions) == end - start
        code = FunctionTranslator(data, functions).translate_function(
            start, functions[start]
        )
        assert code is not None
        output.append(code)
        records.append({
            "start": f"0x{start:08X}",
            "end": f"0x{end:08X}",
            "bytes": end - start,
            "instructions": len(instructions),
            "purpose": purpose,
            "vtable": "0x00228908",
            "vtableSlot": f"0x{start == 0x00035000 and 0x84 or 0x00:02X}",
            "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
        })

    evidence = {
        "schema": 1,
        "source": "retail-xbe-only",
        "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
        "callbacks": records,
    }
    if args.source:
        args.source.parent.mkdir(parents=True, exist_ok=True)
        args.source.write_text("\n".join(output), encoding="utf-8")
    if args.evidence:
        args.evidence.parent.mkdir(parents=True, exist_ok=True)
        args.evidence.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    if not args.source and not args.evidence:
        print("\n".join(output))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
