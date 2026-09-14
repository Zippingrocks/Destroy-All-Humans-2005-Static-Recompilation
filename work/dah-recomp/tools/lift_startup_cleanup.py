"""Print reviewed retail startup cleanup callbacks for apply_patch.

These entries were reached by PID 10676/42376 but missing from dispatch.
Explicit end bounds exclude padding; every decoded instruction is compared
to the existing original-byte disassembly before lifting. No file writes.
"""
import json
from pathlib import Path
import re
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / 'Repos' / 'xboxrecomp-main'))
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator

ranges = {
    0x00063510: (0x00063549, 'text'),
    0x00068B50: (0x00068B6E, 'text'),
    0x000F7180: (0x000F71C3, 'text'),
    0x0013C5A6: (0x0013C5F1, 'text'),
    0x00188750: (0x00188778, 'text'),
    0x001F4ADB: (0x001F4B0A, 'DSOUND'),
    0x0020B060: (0x0020B079, 'BINK'),
    0x0020E010: (0x0020E08D, 'BINK'),
}
original = {}
for section in set(section for end, section in ranges.values()):
    for line in (workspace / 'work' / 'disasm-seeded' / 'asm' / (section + '.asm')).read_text().splitlines():
        match = re.match(r'\s*0x([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+', line)
        if match:
            original[int(match[1], 16)] = bytes.fromhex(match[2])

xbe_path = workspace / 'work' / 'default.xbe'
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()
dis = Cs(CS_ARCH_X86, CS_MODE_32)
functions = {start: {'name': f'sub_{start:08X}', 'end': end}
             for start, (end, _) in ranges.items()}
translator = FunctionTranslator(data, functions)
details = []
code = ('/* Retail startup cleanup callbacks reached after the logo movies.\n'
        ' * Byte-checked lifts; see tools/lift_startup_cleanup.py. */\n'
        '#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n\n')
for start, (end, _) in ranges.items():
    offset = va_to_file_offset(start)
    instructions = list(dis.disasm(data[offset:offset + end - start], start))
    assert instructions[-1].address + instructions[-1].size == end
    assert instructions[-1].mnemonic == 'ret'
    for ins in instructions:
        assert bytes(ins.bytes) == original[ins.address], hex(ins.address)
        if ins.mnemonic.startswith('j'):
            assert start <= int(ins.op_str, 16) < end
    lifted = translator.translate_function(start, functions[start])
    assert lifted is not None
    code += lifted + '\n\n'
    details.append({'start': f'{start:08X}', 'end': f'{end:08X}',
                    'bytes': end - start, 'instructions': len(instructions)})
print(json.dumps({'details': details, 'code': code}))
