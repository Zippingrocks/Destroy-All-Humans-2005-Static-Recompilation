"""Print the byte-checked retail Rockwell event callback at 0x000A3720.

The callback is an indirect-only vtable entry observed from the Rockwell event
paths at 0x000A3A44, 0x000A3D18, and 0x000A4BD8. Its final instruction is the
retail tail call to the already-recompiled sub_00099A10.
"""
import json
from pathlib import Path
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator

start = 0x000A3720
end = 0x000A3750
tail_target = 0x00099A10
xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()

offset = va_to_file_offset(start)
instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(
    data[offset:offset + end - start], start))
assert instructions[-1].address + instructions[-1].size == end
assert instructions[-1].mnemonic == "jmp"
assert int(instructions[-1].op_str, 16) == tail_target
assert sum(ins.size for ins in instructions) == end - start

for ins in instructions[:-1]:
    if ins.mnemonic.startswith("j"):
        target = int(ins.op_str, 16)
        assert start <= target < end, hex(ins.address)

functions = {
    start: {"name": f"sub_{start:08X}", "end": end},
    tail_target: {"name": f"sub_{tail_target:08X}", "end": 0x00099B49},
}
code = FunctionTranslator(data, functions).translate_function(start, functions[start])
assert code is not None
print(json.dumps({
    "start": f"{start:08X}",
    "end": f"{end:08X}",
    "bytes": end - start,
    "instructions": len(instructions),
    "code": code,
}))
