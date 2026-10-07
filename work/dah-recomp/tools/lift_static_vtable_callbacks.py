"""Print byte-checked lifts for retail vtable entries missed by discovery.

These entries are direct members of retail function-pointer tables and begin
after a return or CC padding.  Fixed boundaries and byte hashes keep the lift
tied to the verified retail XBE; class names remain unassigned until retail
and alpha layout evidence agrees.
"""
import hashlib
import json
import argparse
from pathlib import Path
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator


FUNCTIONS = (
    (0x00016A90, 0x00016B47, 0x00226800,
     "traffic actor vtable slot +0x50; event/effect callback"),
    (0x0009A210, 0x0009A22E, 0x0022F3DC,
     "class 0x2786C33B vtable slot +0x24; scalar deleting destructor"),
)

xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()
decoder = Cs(CS_ARCH_X86, CS_MODE_32)
result = []

for start, end, table_slot, observation in FUNCTIONS:
    offset = va_to_file_offset(start)
    code_bytes = data[offset:offset + end - start]
    instructions = list(decoder.disasm(code_bytes, start))
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

parser = argparse.ArgumentParser()
parser.add_argument("--source", type=Path)
parser.add_argument("--evidence", type=Path)
args = parser.parse_args()
if args.source:
    source = "#define RECOMP_GENERATED_CODE\n#include \"recomp_funcs.h\"\n\n"
    source += "\n".join(item["code"] for item in result)
    args.source.write_text(source, encoding="utf-8")
if args.evidence:
    evidence = [{key: value for key, value in item.items() if key != "code"}
                for item in result]
    args.evidence.write_text(json.dumps({
        "schema": 1,
        "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
        "callbacks": evidence,
    }, indent=2) + "\n", encoding="utf-8")
if not args.source and not args.evidence:
    print(json.dumps(result))
