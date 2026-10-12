"""Print the byte-checked retail indirect callback at 0x0002C6E0.

The entry is referenced by vtable 0x002281D8 slot +0x18 and is observed from
a common per-frame object update caller at 0x0001E9E6.  The retail image has
an INT3 boundary immediately before the entry and another immediately after
its final ``ret 4``, giving this indirect-only function an exact boundary.
"""
import json
from pathlib import Path
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator

start = 0x0002C6E0
end = 0x0002C851
xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()

offset = va_to_file_offset(start)
instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(
    data[offset:offset + end - start], start))
assert instructions[-1].address + instructions[-1].size == end
assert instructions[-1].mnemonic == "ret"
assert instructions[-1].op_str == "4"
assert sum(ins.size for ins in instructions) == end - start
assert data[va_to_file_offset(start - 1)] == 0xCC
assert data[va_to_file_offset(end)] == 0xCC

for ins in instructions:
    if ins.mnemonic.startswith("j") and ins.op_str.startswith("0x"):
        target = int(ins.op_str, 16)
        assert start <= target < end, hex(ins.address)

functions = {start: {"name": f"sub_{start:08X}", "end": end}}
code = FunctionTranslator(data, functions).translate_function(start, functions[start])
assert code is not None
print(json.dumps({
    "start": f"{start:08X}",
    "end": f"{end:08X}",
    "bytes": end - start,
    "instructions": len(instructions),
    "code": code,
}))

