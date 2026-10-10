"""Lift the retail Sonic Boom state callback missed by discovery.

The callback was observed unresolved during a long retail-path play session.
Its live table slot, exact boundary, and byte hash are checked against the
retail XBE. No external symbols or pre-release executable are used.
"""

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


START = 0x000A6AF0
END = 0x000A6B59
TABLE_SLOT = 0x00230124


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path)
    parser.add_argument("--evidence", type=Path)
    args = parser.parse_args()

    xbe_path = workspace / "default.xbe"
    configure_from_xbe(str(xbe_path))
    data = xbe_path.read_bytes()
    offset = va_to_file_offset(START)
    code_bytes = data[offset:offset + END - START]
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code_bytes, START))
    assert instructions
    assert instructions[-1].address + instructions[-1].size == END
    assert sum(ins.size for ins in instructions) == END - START
    assert instructions[-1].mnemonic == "ret"
    slot_offset = va_to_file_offset(TABLE_SLOT)
    assert int.from_bytes(data[slot_offset:slot_offset + 4], "little") == START
    for ins in instructions:
        if ins.mnemonic.startswith("j") and ins.mnemonic != "jmp":
            target = int(ins.op_str, 16)
            assert START <= target < END, hex(ins.address)

    functions = {START: {"name": f"sub_{START:08X}", "end": END}}
    code = FunctionTranslator(data, functions).translate_function(
        START, functions[START])
    assert code is not None
    evidence = {
        "schema": 1,
        "source": "retail-xbe-only",
        "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
        "callback": {
            "start": f"{START:08X}",
            "end": f"{END:08X}",
            "bytes": END - START,
            "instructions": len(instructions),
            "tableSlot": f"0x{TABLE_SLOT:08X}",
            "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
            "observation": (
                "retail vtable slot +0x5C; advances and resets the observed "
                "Sonic Boom weapon state sequence"
            ),
        },
    }
    if args.source:
        args.source.write_text(
            "#define RECOMP_GENERATED_CODE\n#include \"recomp_funcs.h\"\n\n" + code,
            encoding="utf-8")
    if args.evidence:
        args.evidence.parent.mkdir(parents=True, exist_ok=True)
        args.evidence.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    if not args.source and not args.evidence:
        print(json.dumps({**evidence, "code": code}))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
