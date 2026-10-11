"""Lift high-confidence retail vtable entries omitted by function discovery.

Input comes from audit_static_vtable_gaps.py.  Every emitted function must be
an instruction-aligned retail body, start immediately after INT3 padding, end
at the next padding boundary, and be referenced by the recorded retail vtable
slot.  This keeps the generated code tied to the retail XBE rather than names
or behavior inferred from another build.
"""

import argparse
import hashlib
import json
from pathlib import Path
import sys


workspace = Path(__file__).resolve().parents[3]
repo = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--audit",
        type=Path,
        default=repo / "tools/analysis/results/static-vtable-gap-audit.json",
    )
    parser.add_argument("--source", type=Path)
    parser.add_argument("--evidence", type=Path)
    args = parser.parse_args()

    audit = json.loads(args.audit.read_text(encoding="utf-8"))
    rows = [row for row in audit["candidates"] if row["safeLiftCandidate"]]
    xbe_path = workspace / "default.xbe"
    configure_from_xbe(str(xbe_path))
    data = xbe_path.read_bytes()
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    functions = {
        int(row["address"], 16): {
            "name": f"sub_{int(row['address'], 16):08X}",
            "end": int(row["inferredEnd"], 16),
        }
        for row in rows
    }
    translator = FunctionTranslator(data, functions)
    output = ['#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n']
    records = []

    for row in rows:
        start = int(row["address"], 16)
        end = int(row["inferredEnd"], 16)
        offset = va_to_file_offset(start)
        code_bytes = data[offset : offset + end - start]
        instructions = list(decoder.disasm(code_bytes, start))
        assert instructions, row["address"]
        assert sum(ins.size for ins in instructions) == end - start, row["address"]
        assert instructions[-1].address + instructions[-1].size == end, row["address"]
        assert instructions[-1].mnemonic in {"ret", "jmp"}, row["address"]

        for slot_text in row["vtableLocations"]:
            slot = int(slot_text, 16)
            slot_offset = va_to_file_offset(slot)
            assert int.from_bytes(data[slot_offset : slot_offset + 4], "little") == start

        code = translator.translate_function(start, functions[start])
        assert code is not None, row["address"]
        output.append(code)
        records.append(
            {
                "start": row["address"],
                "end": row["inferredEnd"],
                "bytes": end - start,
                "instructions": len(instructions),
                "terminalMnemonic": instructions[-1].mnemonic,
                "vtableLocations": row["vtableLocations"],
                "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
            }
        )

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
    print(f"lifted {len(records)} retail vtable callbacks")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
