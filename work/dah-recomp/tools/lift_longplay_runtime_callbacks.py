"""Print byte-checked lifts for callbacks discovered during long playtests.

Each entry is an indirect retail target captured by the current-run ICALL
logger.  Fixed boundaries and code hashes keep the evidence tied to the
verified retail XBE instead of relying on automatic function discovery.
"""
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
    (
        0x000A21A0,
        0x000A21B2,
        "UFO::WeaponDestructoRay::Reset override observed during the "
        "Santa/Rockwell long play",
    ),
)

xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()
decoder = Cs(CS_ARCH_X86, CS_MODE_32)
result = []

for start, end, observation in FUNCTIONS:
    offset = va_to_file_offset(start)
    code_bytes = data[offset:offset + end - start]
    instructions = list(decoder.disasm(code_bytes, start))
    assert instructions[-1].address + instructions[-1].size == end
    assert sum(ins.size for ins in instructions) == end - start
    assert instructions[-1].mnemonic == "jmp"
    assert int(instructions[-1].op_str, 16) == 0x00097C00
    functions = {start: {"name": f"sub_{start:08X}", "end": end}}
    code = FunctionTranslator(data, functions).translate_function(
        start, functions[start])
    assert code is not None
    result.append({
        "start": f"{start:08X}",
        "end": f"{end:08X}",
        "bytes": end - start,
        "instructions": len(instructions),
        "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
        "observation": observation,
        "code": code,
    })

print(json.dumps(result))
