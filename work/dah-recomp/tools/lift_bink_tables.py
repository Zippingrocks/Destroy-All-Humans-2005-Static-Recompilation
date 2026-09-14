"""Print isolated C lifts for verified retail BINK32 callback entries.

The first RET bounds each callback; internal branches are verified not to
escape that range. Output is JSON for review/apply_patch, not a file write.
"""
import json
import pathlib
import sys

workspace = pathlib.Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator

xbe_path = workspace / "work" / "default.xbe"
configure_from_xbe(str(xbe_path))
xbe_data = xbe_path.read_bytes()
dis = Cs(CS_ARCH_X86, CS_MODE_32)
starts = [0x217680, 0x217B70, 0x218530, 0x21F040,
          0x21F200, 0x21F480, 0x21F7A0]
functions = {}
details = []
assembly = []
for start in starts:
    offset = va_to_file_offset(start)
    instructions = []
    for ins in dis.disasm(xbe_data[offset:offset + 0x1000], start):
        instructions.append(ins)
        if ins.mnemonic == "ret":
            break
    assert instructions[-1].mnemonic == "ret", hex(start)
    end = instructions[-1].address + instructions[-1].size
    for ins in instructions:
        if ins.mnemonic.startswith("j") or ins.mnemonic.startswith("loop"):
            assert start <= int(ins.op_str, 16) < end, (hex(start), ins.op_str)
    functions[start] = {"name": f"sub_{start:08X}", "end": end}
    details.append({"start": f"{start:08X}", "end": f"{end:08X}",
                    "instructions": len(instructions),
                    "return": instructions[-1].op_str})
    assembly.append(f"; Function: sub_{start:08X}")
    for ins in instructions:
        assembly.append(f"  0x{ins.address:08X}  {ins.bytes.hex():24}"
                        f"{ins.mnemonic:9} {ins.op_str}")
    assembly.append("")

start, end = 0x21E4B0, 0x21E58C
offset = va_to_file_offset(start)
assembly.append(f"; Function: sub_{start:08X}")
for ins in dis.disasm(xbe_data[offset:offset + end - start], start):
    assembly.append(f"  0x{ins.address:08X}  {ins.bytes.hex():24}"
                    f"{ins.mnemonic:9} {ins.op_str}")
assembly.append("")

translator = FunctionTranslator(xbe_data, functions)
code = ("/* Retail BINK32 callbacks from the static table at 0x0029BFA0.\n"
        " * Isolated lifts preserve entry boundaries and return ABI. */\n"
        "#define RECOMP_GENERATED_CODE\n"
        '#include "recomp_funcs.h"\n\n')
for start, info in functions.items():
    lifted = translator.translate_function(start, info)
    assert lifted is not None
    code += lifted + "\n\n"
print(json.dumps({"details": details, "code": code,
                  "asm": "\n".join(assembly)}))
