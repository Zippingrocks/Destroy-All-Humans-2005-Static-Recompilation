"""Compile actual lifted acos/heading functions and a pre-fix negative control.

Run from a Visual Studio developer shell (or pass --cc for another C compiler).
Only generated test files and binaries are written, in a temporary directory.
"""
import argparse
from pathlib import Path
import re
import struct
import subprocess
import tempfile


def extract(source, address):
    match = re.search(r'void sub_' + address + r'\(void\)\n\{.*?\n\}', source, re.S)
    if not match:
        raise ValueError(f'Missing lifted function {address}')
    return match.group()


def run(compiler):
    root = Path(__file__).resolve().parents[4]
    game = root / 'work/dah-recomp'
    runtime = root / 'third_party/xboxrecomp/templates/runtime'
    source = (game / 'src/recomp/gen/recomp_0009.c').read_text()
    inverse = extract(source, '000D4170')
    acos = extract(source, '000D4520')
    heading = extract(source, '000D4680')
    fixed_branch = 'if (_flags & 0x41) goto loc_000D4652;'
    if acos.count(fixed_branch) != 1:
        raise ValueError('Expected the COMISS flag snapshot fix exactly once')
    old_acos = acos.replace('sub_000D4520', 'old_acos').replace(
        fixed_branch, 'if ((xmm2.f[0] <= MEMF(esp + 0x14))) goto loc_000D4652;')
    old_heading = heading.replace('sub_000D4680', 'old_heading').replace(
        'sub_000D4520', 'old_acos')
    functions = '\n\n'.join((inverse, acos, heading, old_acos, old_heading))

    # Load original constant bytes. The runtime-created acos lookup table is
    # initialized by the C harness using the formula from retail D4390.
    xbe = (root / 'work/default.xbe').read_bytes()
    word = lambda offset: struct.unpack_from('<I', xbe, offset)[0]
    base, count, sections = word(0x104), word(0x11C), word(0x120)
    memory = bytearray(0x300000)
    for index in range(count):
        section = sections - base + index * 56
        address, raw, length = word(section + 4), word(section + 12), word(section + 16)
        copied = max(0, min(length, len(memory) - address))
        if copied:
            memory[address:address + copied] = xbe[raw:raw + copied]
    flags = getattr(subprocess, 'CREATE_NO_WINDOW', 0)
    with tempfile.TemporaryDirectory(prefix='dah-heading-math-') as directory:
        temporary = Path(directory)
        (temporary / 'guest_heading_functions.inc').write_text(functions)
        fixture = temporary / 'guest-memory.bin'
        fixture.write_bytes(memory)
        executable = temporary / 'heading-test.exe'
        test = Path(__file__).with_suffix('.c')
        if Path(compiler).stem.lower() in ('cl', 'clang-cl'):
            command = [compiler, '/nologo', '/std:c11', '/O2', '/fp:strict', '/W3',
                       '/wd4102', '/D_CRT_SECURE_NO_WARNINGS',
                       f'/I{runtime}', f'/I{temporary}', str(test),
                       f'/Fe{executable}', f'/Fo{temporary / "heading-test.obj"}']
        else:
            command = [compiler, '-std=c11', '-O2', '-fno-fast-math',
                       f'-I{runtime}', f'-I{temporary}', str(test), '-lm', '-o', str(executable)]
        for invocation in (command, [str(executable), str(fixture)]):
            result = subprocess.run(invocation, creationflags=flags, text=True,
                                    stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            print(result.stdout, end='')
            result.check_returncode()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', default='cl')
    run(parser.parse_args().cc)
