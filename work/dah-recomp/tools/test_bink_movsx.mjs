/* In a Visual Studio x64 developer prompt:
 * node work/dah-recomp/tools/test_bink_movsx.mjs
 * Compiles exact patched production statements and runtime conversion macros.
 * This does not launch the game or create a window.
 */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, '../../..');
const gen = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_0021.c'), 'utf8');
const types = fs.readFileSync(path.join(root, 'Repos/xboxrecomp-main/templates/runtime/recomp_types.h'), 'utf8');
const asm = fs.readFileSync(path.join(root, 'work/disasm-seeded/asm/BINK.asm'), 'utf8');
const xbe = fs.readFileSync(path.join(root, 'work/default.xbe'));
const base = xbe.readUInt32LE(0x104), table = xbe.readUInt32LE(0x120) - base;
const sections = Array.from({ length: xbe.readUInt32LE(0x11c) }, (_, i) => {
  const p = table + i * 56;
  return { va: xbe.readUInt32LE(p + 4), raw: xbe.readUInt32LE(p + 12), size: xbe.readUInt32LE(p + 16) };
});
const targets = [0x215af8, 0x215e38, 0x216239, 0x216752, 0x216806, 0x2168ba, 0x21696f, 0x2169f1];
const expected = [...asm.matchAll(/^\s*0x([0-9A-F]+)\s+([0-9a-f]+)[ \t]+movsx[ \t]+(ebx|ebp), bp[ \t]*\r?$/gm)];
assert.deepEqual(expected.map(m => parseInt(m[1], 16)), targets);
const statements = expected.map(m => {
  const va = parseInt(m[1], 16), section = sections.find(s => va >= s.va && va + 3 <= s.va + s.size);
  assert(section);
  assert.equal(xbe.subarray(section.raw + va - section.va, section.raw + va - section.va + 3).toString('hex'), m[2]);
  const lines = [...gen.matchAll(new RegExp(`^[ \\t]*(.*?) /\\* MOVSX 0x${m[1]}: movsx ${m[3]}, bp \\*/\\r?$`, 'gm'))];
  assert.equal(lines.length, 1, `Missing exact restoration ${m[1]}`);
  assert.equal(lines[0][1], `${m[3]} = SX16(LO16(ebp));`);
  return { address: m[1], destination: m[3], statement: lines[0][1] };
});
const macros = ['SX16', 'LO16'].map(name => {
  const line = types.match(new RegExp(`^#define ${name}\\([^\\n]+`, 'm'));
  assert(line);
  return line[0];
}).join('\n');
const functions = statements.map((s, i) => `static uint32_t operation_${i}(uint32_t ebp) {
  ${s.destination === 'ebx' ? 'uint32_t ebx;' : ''}
  ${s.statement}
  return ${s.destination};
}`);
const fixture = `#include <stdint.h>
#include <stdio.h>
${macros}
${functions.join('\n')}
int main(void) {
  uint32_t (*operations[])(uint32_t) = { ${statements.map((_, i) => `operation_${i}`).join(', ')} };
  const uint32_t upper[] = {0, 0x12340000u, 0x80000000u, 0xffff0000u};
  unsigned comparisons = 0;
  for (unsigned n = 0; n < 8; ++n) {
    for (unsigned u = 0; u < 4; ++u) {
      for (uint32_t low = 0; low < 65536; ++low) {
        const uint32_t input = upper[u] | low;
        const uint32_t wanted = low < 32768 ? low : low - 65536u;
        const uint32_t actual = operations[n](input);
        if (actual != wanted) {
          fprintf(stderr, "MOVSX[%u] input=%08X got=%08X expected=%08X\\n", n, input, actual, wanted);
          return 1;
        }
        ++comparisons;
      }
    }
  }
  printf("PASS: %u signed coefficient vectors (all16-bit values, four unrelated upper halves, eight actual statements)\\n", comparisons);
  return 0;
}
`;
const temp = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-bink-movsx-'));
function run(label, source, wanted) {
  const c = path.join(temp, `${label}.c`), exe = path.join(temp, `${label}.exe`);
  fs.writeFileSync(c, source);
  const compile = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11',
    `/Fe:${exe}`, `/Fo:${path.join(temp, `${label}.obj`)}`, c], { cwd: temp, encoding: 'utf8', timeout: 30000 });
  assert.equal(compile.status, 0, `Compile failed: ${compile.error || compile.stdout || compile.stderr}`);
  const result = spawnSync(exe, [], { cwd: temp, encoding: 'utf8', timeout: 10000 });
  assert.equal(result.status, wanted, `Unexpected result: ${label}: ${result.error || result.stderr}`);
  console.log(wanted ? `PASS: rejected ${label}: ${result.stderr.trim()}` : result.stdout.trim());
}
console.log('PASS: all eight original MOVSX instructions byte-validated against XBE and generated statements');
run('current', fixture, 0);
for (let n = 0; n < functions.length; n++) {
  const old = functions[n].replace('SX16(LO16(ebp))', 'LO16(ebp)');
  run(`zero-extension-${statements[n].address}`, fixture.replace(functions[n], old), 1);
}
console.log(`TEST_OUTPUT ${temp}`);
