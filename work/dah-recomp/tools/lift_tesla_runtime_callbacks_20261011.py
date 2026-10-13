"""Lift retail callbacks exposed by the recurring Tesla runtime crash."""
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

xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()
entries = (
    (0x00079450, 0x000795FE, "per-frame object state callback"),
    (0x000797E0, 0x000797E8, "contained-object forwarding thunk"),
)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path)
    parser.add_argument("--evidence", type=Path)
    args = parser.parse_args()
    output = [
        "/* Generated only from the retail XBE for recurring crash CE45648D31F5AFCD. */",
        '#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n',
    ]
    records = []
    functions = {
        start: {"name": f"sub_{start:08X}", "end": end}
        for start, end, _ in entries
    }
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    for start, end, purpose in entries:
        offset = va_to_file_offset(start)
        code_bytes = data[offset:offset + end - start]
        instructions = list(disassembler.disasm(code_bytes, start))
        assert instructions[-1].address + instructions[-1].size == end
        assert sum(ins.size for ins in instructions) == end - start
        # 0x79450 directly follows sub_00079320; the thunk has INT3 padding.
        assert start == 0x00079450 or data[va_to_file_offset(start - 1)] == 0xCC
        assert data[va_to_file_offset(end)] == 0xCC
        code = FunctionTranslator(data, functions).translate_function(start, functions[start])
        assert code is not None
        output.append(code)
        records.append({
            "start": f"0x{start:08X}",
            "end": f"0x{end:08X}",
            "bytes": end - start,
            "instructions": len(instructions),
            "purpose": purpose,
            "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
        })
    evidence = {
        "schema": 1,
        "source": "retail-xbe-only",
        "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
        "crashSignature": "DAH-CE45648D31F5AFCD",
        "callbacks": records,
    }
    if args.source:
        args.source.write_text("\n".join(output), encoding="utf-8")
    if args.evidence:
        args.evidence.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    if not args.source and not args.evidence:
        print("\n".join(output))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
