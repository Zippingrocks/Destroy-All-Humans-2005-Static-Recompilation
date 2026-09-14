"""Print byte-checked retail DSOUND callbacks for apply_patch (no writes)."""
import json
from pathlib import Path
import re
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / 'Repos' / 'xboxrecomp-main'))
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator

ranges = {0x001ECE7E: 0x001ECEC8, 0x001F50FF: 0x001F514E,
          0x001EC7B9: 0x001EC7CA, 0x001F49F9: 0x001F4A40,
          0x001EE1DE: 0x001EE1F9, 0x001EF685: 0x001EF6A0,
          0x001F514E: 0x001F5169, 0x001F225D: 0x001F234C,
          0x001F1C82: 0x001F1CB1, 0x001F24F3: 0x001F250E,
          0x001F24A8: 0x001F24F3, 0x001ED372: 0x001ED3BD,
          0x001ED270: 0x001ED2BE, 0x001ED3BD: 0x001ED40E}
original = {}
for line in (workspace / 'work/disasm-seeded/asm/DSOUND.asm').read_text().splitlines():
    match = re.match(r'\s*0x([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+', line)
    if match:
        original[int(match[1], 16)] = bytes.fromhex(match[2])

xbe_path = workspace / 'work/default.xbe'
configure_from_xbe(str(xbe_path))
data = xbe_path.read_bytes()
# Connected close-time object types, not a speculative neighborhood scan:
# 1EF07B creates descriptor vt2394D8 -> wrapper+1C and hardware vt239594
# (constructor1F4B24) -> wrapper+20. 1ECE04 releases these two members.
for slot, target in ((0x23949C, 0x1EE1DE), (0x2394D8, 0x1EF685),
                     (0x239594, 0x1F514E), (0x2394E0, 0x1EC7CA),
                     (0x23959C, 0x1EC7CA), (0x2394E4, 0x1EC7B9),
                     (0x2395A0, 0x1EC7B9), (0x239544, 0x1F225D),
                     (0x23954C, 0x1F1C82), (0x239530, 0x1F24F3),
                     (0x239554, 0x1F24A8)):
    p = va_to_file_offset(slot)
    assert int.from_bytes(data[p:p + 4], 'little') == target, hex(slot)
for address, encoding in {
    0x1EF0BF: 'c700d8942300', 0x1EF0E7: '894f1c',
    0x1EF115: 'e80a5a0000', 0x1EF128: '894720',
    0x1F4B38: 'c70694952300', 0x1ECE07: '8b4620',
    0x1ECE17: 'ff5108', 0x1ECE1E: '8b461c', 0x1ECE28: 'ff5108',
    # Stream constructor installs vt239530; initialization calls slot+14.
    0x1F1CDF: 'c70630952300', 0x1F2CF7: '8b01', 0x1F2CF9: 'ff5014',
    # Its active-stream cleanup calls slot+1C with four packet arguments.
    0x1F204D: '8b06', 0x1F2054: 'ff501c', 0x1F206F: 'ff501c',
    0x1F0FFC: 'ff5024',
}.items():
    expected = bytes.fromhex(encoding)
    p = va_to_file_offset(address)
    assert data[p:p + len(expected)] == expected == original[address], hex(address)
dis = Cs(CS_ARCH_X86, CS_MODE_32)
functions = {start: {'name': f'sub_{start:08X}', 'end': end}
             for start, end in ranges.items()}
translator = FunctionTranslator(data, functions)
code = ('/* Retail DSOUND release/action callbacks observed after logo playback.\n'
        ' * Byte-checked lifts; see tools/lift_audio_cleanup.py. */\n'
        '#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n\n')
details = []
for start, end in ranges.items():
    offset = va_to_file_offset(start)
    instructions = list(dis.disasm(data[offset:offset + end - start], start))
    assert instructions[-1].address + instructions[-1].size == end
    assert instructions[-1].mnemonic == 'ret'
    for ins in instructions:
        assert bytes(ins.bytes) == original[ins.address], hex(ins.address)
        if ins.mnemonic.startswith('j'):
            target = int(ins.op_str, 16)
            assert (start <= target < end or
                    (ins.address == 0x1F2344 and ins.mnemonic == 'jmp'
                     and target == 0x1F3BB4))
    lifted = translator.translate_function(start, functions[start])
    assert lifted is not None
    code += lifted + '\n\n'
    details.append({'start': f'{start:08X}', 'end': f'{end:08X}',
                    'bytes': end - start, 'instructions': len(instructions)})
print(json.dumps({'details': details, 'code': code}))
