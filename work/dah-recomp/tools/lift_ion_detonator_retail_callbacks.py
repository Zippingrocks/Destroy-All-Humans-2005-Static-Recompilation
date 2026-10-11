"""Lift the retail callbacks observed immediately before the Ion Detonator crash.

The normal function discovery missed these four entry points even though the
retail XBE stores them in a live function-pointer table.  Fixed boundaries,
table-slot assertions, and hashes keep the generated source tied to retail.
No symbol file or pre-release executable participates in this lift.
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


FUNCTIONS = (
    (0x00075660, 0x00075681, 0x0022C1FC,
     "retail table slot +0x50; copies three object-state words"),
    (0x00075780, 0x000757A1, 0x0022C1AC,
     "retail primary table slot +0x00; returns the live payload view"),
    (0x00075800, 0x00075815, 0x0022C218,
     "retail table slot +0x6C; returns the active or embedded payload"),
    (0x00075A10, 0x00075C52, 0x0022C1E8,
     "retail table slot +0x3C; advances object state and presentation"),
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
    result = []

    for start, end, table_slot, observation in FUNCTIONS:
        offset = va_to_file_offset(start)
        code_bytes = data[offset:offset + end - start]
        instructions = list(decoder.disasm(code_bytes, start))
        assert instructions
        assert instructions[-1].address + instructions[-1].size == end
        assert sum(ins.size for ins in instructions) == end - start
        assert instructions[-1].mnemonic == "ret"
        slot_offset = va_to_file_offset(table_slot)
        assert int.from_bytes(data[slot_offset:slot_offset + 4], "little") == start
        for ins in instructions:
            if ins.mnemonic.startswith("j") and ins.mnemonic != "jmp":
                target = int(ins.op_str, 16)
                assert start <= target < end, hex(ins.address)

        functions = {start: {"name": f"sub_{start:08X}", "end": end}}
        code = FunctionTranslator(data, functions).translate_function(
            start, functions[start])
        assert code is not None
        result.append({
            "start": f"{start:08X}",
            "end": f"{end:08X}",
            "bytes": end - start,
            "instructions": len(instructions),
            "tableSlot": f"0x{table_slot:08X}",
            "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
            "observation": observation,
            "code": code,
        })

    if args.source:
        source = "#define RECOMP_GENERATED_CODE\n#include \"recomp_funcs.h\"\n\n"
        source += "\n".join(item["code"] for item in result)
        args.source.write_text(source, encoding="utf-8")
    if args.evidence:
        evidence = [{key: value for key, value in item.items() if key != "code"}
                    for item in result]
        args.evidence.parent.mkdir(parents=True, exist_ok=True)
        args.evidence.write_text(json.dumps({
            "schema": 1,
            "source": "retail-xbe-only",
            "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
            "callbacks": evidence,
        }, indent=2) + "\n", encoding="utf-8")
    if not args.source and not args.evidence:
        print(json.dumps(result))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
