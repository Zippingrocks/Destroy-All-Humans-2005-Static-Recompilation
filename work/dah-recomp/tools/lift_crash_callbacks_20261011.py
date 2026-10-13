"""Print byte-checked retail callbacks observed before the 2026-10-11 crash."""
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
entries = ((0x0001F500, 0x0001F657), (0x00075330, 0x00075338))
result = []

for start, end in entries:
    offset = va_to_file_offset(start)
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(
        data[offset:offset + end - start], start))
    assert instructions[-1].address + instructions[-1].size == end
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
    result.append({
        "start": f"{start:08X}",
        "end": f"{end:08X}",
        "bytes": end - start,
        "instructions": len(instructions),
        "code": code,
    })

print(json.dumps(result))
