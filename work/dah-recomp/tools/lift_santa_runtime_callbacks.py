"""Print byte-checked lifts for callbacks observed during the Santa EMP run.

These indirect-only entries were recorded by the current-run ICALL logger.
The fixed start/end boundaries below are checked against the retail XBE before
translation so a later executable cannot silently reuse the evidence.
"""
import json
import hashlib
from pathlib import Path
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator


FUNCTIONS = (
    (0x0003CD20, 0x0003CDF6, "state callback that creates the retail fire actor"),
    (0x0003E2E0, 0x0003E301, "target-handle setter callback"),
    (0x0004ACC0, 0x0004ADB7, "runtime body/shape initialization callback"),
)

xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()
decoder = Cs(CS_ARCH_X86, CS_MODE_32)
result = []

for start, end, observation in FUNCTIONS:
    offset = va_to_file_offset(start)
    instructions = list(decoder.disasm(data[offset:offset + end - start], start))
    assert instructions[-1].address + instructions[-1].size == end
    assert instructions[-1].mnemonic == "ret"
    assert sum(ins.size for ins in instructions) == end - start
    for ins in instructions:
        if ins.mnemonic.startswith("j") and ins.mnemonic != "jmp":
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
        "codeBytesSha256": hashlib.sha256(
            data[offset:offset + end - start]).hexdigest().upper(),
        "observation": observation,
        "code": code,
    })

print(json.dumps(result))
