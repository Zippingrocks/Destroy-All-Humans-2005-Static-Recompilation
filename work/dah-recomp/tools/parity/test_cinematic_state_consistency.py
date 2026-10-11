"""Cross-check actual C/Python/JS observers against isolated mapped RAM."""
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from cinematic_state import read_cinematic_state
from decode_xemu_ram import XboxRam


def run(native):
    root = Path(__file__).resolve().parent
    js = """import fs from 'node:fs';
import {readCinematicState} from %s;
const memory=fs.readFileSync(process.argv[1]);
const state=await readCinematicState(async(a,n)=>{const offset=a&0x7fffffff;
if(offset+n>memory.length)throw Error('Guest read failed');return memory.subarray(offset,offset+n);});
console.log(JSON.stringify(state));""" % json.dumps((root / 'xemu_cinematic_state.mjs').as_uri())
    flags = getattr(subprocess, 'CREATE_NO_WINDOW', 0)
    checked = 0
    with tempfile.TemporaryDirectory(prefix='dah-cinematic-observer-') as directory:
        for high in (False, True):
            for variant in ('one', 'base', 'derived_movie', 'empty', 'absent', 'wrong_manager', 'wrong_movie',
                            'bad_pointer', 'unmapped', 'null_link', 'cycle', 'previous',
                            'tail', 'count', 'duplicate', 'invalid_state', 'max', 'overflow'):
                data = bytearray(64 * 1024 * 1024)
                def word(a, v):
                    struct.pack_into('<I', data, a & 0x7fffffff, v)
                word(0x3000, 0x83)
                word(0x3000 + 512 * 4, 0x83)
                base = 0x80000000 if high else 0
                manager, sentinel = base + 0x300000, base + 0x300008
                count = {'empty': 0, 'duplicate': 2, 'max': 16, 'overflow': 17}.get(variant, 1)
                movies = [base + 0x310000 + i * 0x100 for i in range(count)]
                nodes = [a + 4 for a in movies]
                word(0x286784, manager)
                word(manager, 0x23611c if variant == 'base' else 0x22a6b8)
                word(sentinel, nodes[0] if nodes else sentinel)
                word(manager + 12, nodes[-1] if nodes else sentinel)
                word(manager + 0x18, count)
                for i, movie in enumerate(movies):
                    for off, val in ((0, 0x236100), (4, nodes[i + 1] if i + 1 < count else sentinel),
                                     (8, nodes[i - 1] if i else sentinel), (12, movie),
                                     (0x20, 0x98760000 + i), (0x68, 0x42c60000),
                                     (0x6c, 0x3f000001 + i), (0x70, 2), (0x74, 2)):
                        word(movie + off, val)
                edits = {'derived_movie': (base + 0x310000, 0x229fb4),
                         'absent': (0x286784, 0), 'wrong_manager': (manager, 0x123456),
                         'wrong_movie': (base + 0x310000, 0x123456),
                         'bad_pointer': (0x286784, 0xf0000000), 'unmapped': (0x286784, 0x500000),
                         'null_link': (base + 0x310004, 0), 'cycle': (base + 0x310004, base + 0x310004),
                         'previous': (base + 0x310008, 0), 'tail': (manager + 12, sentinel),
                         'count': (manager + 0x18, 2), 'duplicate': (base + 0x31010c, base + 0x310000),
                         'invalid_state': (base + 0x310074, 4)}
                if variant in edits:
                    word(*edits[variant])
                expected = read_cinematic_state(XboxRam(data, 0x3000))
                fixture = Path(directory) / 'memory.bin'
                fixture.write_bytes(data[:4 * 1024 * 1024])
                actual = json.loads(subprocess.check_output([str(native), str(fixture)], creationflags=flags))
                del actual['fixture']
                javascript = json.loads(subprocess.check_output(
                    ['node', '--input-type=module', '-e', js, str(fixture)], creationflags=flags))
                assert actual == expected, (variant, high, actual, expected)
                assert javascript == expected, (variant, high, javascript, expected)
                assert expected['cinematicComplete'] == (variant in ('one', 'base', 'derived_movie', 'empty', 'absent', 'max')), variant
                checked += 1
    print(f'{checked} C/Python/JS cinematic observer fixtures passed')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise SystemExit('Usage: test_cinematic_state_consistency.py NATIVE_FIXTURE.exe')
    run(Path(sys.argv[1]).resolve())
