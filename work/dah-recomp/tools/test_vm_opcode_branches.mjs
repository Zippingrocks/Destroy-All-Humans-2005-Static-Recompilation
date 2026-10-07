/* Run in a Visual Studio developer prompt. Extracts unchanged production
 * handlers and compiles only the isolated harness; no game or input starts. */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const here = path.dirname(fileURLToPath(import.meta.url));
const workspace = path.resolve(here, '../../..');
const production = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_seeded.c'), 'utf8');
const manual = fs.readFileSync(path.join(here, '../src/recomp_manual.c'), 'utf8');
const generatedDispatch = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_dispatch.c'), 'utf8');
const assembly = fs.readFileSync(path.join(workspace, 'work/disasm-seeded/asm/text.asm'), 'utf8');
const xbe = fs.readFileSync(path.join(workspace, 'work/default.xbe'));
const imageBase = xbe.readUInt32LE(0x104), sectionCount = xbe.readUInt32LE(0x11C);
const sectionTable = xbe.readUInt32LE(0x120) - imageBase;
const sections = Array.from({ length: sectionCount }, (_, i) => {
  const p = sectionTable + i * 56;
  return { va: xbe.readUInt32LE(p + 4), offset: xbe.readUInt32LE(p + 12), bytes: xbe.readUInt32LE(p + 16) };
});
function original(va, size) {
  const section = sections.find(s => va >= s.va && va + size <= s.va + s.bytes);
  assert(section, `Original bytes unavailable at ${va.toString(16)}`);
  return xbe.subarray(section.offset + va - section.va, section.offset + va - section.va + size);
}
const targets = ['00196E6A', '00196E78', '00196E8A', '00196EA4', '00196F35', '00196F85', '00196FD1',
  '00196A66', '00196B05', '00196BB7', '00196C61', '00196B5A'];
const bodies = targets.map(address => {
  const match = production.match(new RegExp(`^void sub_${address}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`, 'm'));
  assert(match, `Missing production handler ${address}`); return match[0];
});
const instructions = [...assembly.matchAll(/^\s*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]+(.*?)\r?$/gm)]
  .map(m => ({ va: parseInt(m[1], 16), bytes: Buffer.from(m[2], 'hex'), mnemonic: m[3], operands: m[4] }));
let verifiedInstructions = 0, verifiedBytes = 0;
for (const [start, end] of [[0x196E6A, 0x197006], [0x196A66, 0x196AB8],
                          [0x196B05, 0x196C0C], [0x196C61, 0x196CB6]]) {
  let expectedAddress = start;
  for (const instruction of instructions.filter(i => i.va >= start && i.va < end)) {
    assert.equal(instruction.va, expectedAddress, 'Original instruction coverage gap');
    assert.deepEqual(original(instruction.va, instruction.bytes.length), instruction.bytes);
    expectedAddress += instruction.bytes.length; ++verifiedInstructions; verifiedBytes += instruction.bytes.length;
  }
  assert.equal(expectedAddress, end);
}
assert.equal(original(0x225C20, 4).readUInt32LE(), 0, 'Original numeric comparison constant must be +0');
const table = original(0x197090, 49 * 4);
for (let opcode = 0; opcode < 49; ++opcode) {
  const va = table.readUInt32LE(opcode * 4), hex = va.toString(16).padStart(8, '0').toUpperCase();
  const name = `sub_${hex}`;
  const manualMapped = new RegExp(`if\\s*\\(xbox_va\\s*==\\s*0x${hex}u?\\)\\s*return\\s+${name}\\s*;`, 'i').test(manual);
  const manualSwitchMapped = new RegExp(`case\\s+0x${hex}u?\\s*:\\s*return\\s+${name}\\s*;`, 'i').test(manual);
  const generatedMapped = new RegExp(`\\{\\s*0x${hex}u?,\\s*\\(recomp_func_t\\)${name}\\s*\\}`, 'i').test(generatedDispatch);
  assert(manualMapped || manualSwitchMapped || generatedMapped, `Unmapped original opcode ${opcode.toString(16)} -> ${hex}`);
  assert(new RegExp(`^void ${name}\\(void\\)\\r?\\n\\{`, 'm').test(production), `No actual seeded handler body for ${hex}`);
}
console.log(`PASS: all 49 original-XBE table entries resolve to real production bodies; ${verifiedInstructions} tested-handler instructions match ${verifiedBytes} original bytes`);
const fixture = bodies.join('\n\n') + '\n';
console.log(`PRODUCTION_SOURCE_SHA256 ${crypto.createHash('sha256').update(fixture).digest('hex')}`);
const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-vm-opcode-test-'));
function compileRun(label, text, mustPass) {
  const folder = path.join(temporary, label); fs.mkdirSync(folder);
  fs.writeFileSync(path.join(folder, 'vm_opcode_fixture.inc'), text);
  const exe = path.join(folder, 'test.exe');
  const build = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11', `/I${folder}`,
    `/Fe:${exe}`, `/Fo:${path.join(folder, 'test.obj')}`, path.join(here, 'test_vm_opcode_branches.c')],
    { cwd: folder, encoding: 'utf8', timeout: 30000 });
  if (build.error || build.status !== 0) throw Error(`${label}: compilation failed ${build.error || ''}\n${build.stdout}\n${build.stderr}`);
  const run = spawnSync(exe, [], { cwd: folder, encoding: 'utf8', timeout: 30000 });
  if (run.error) throw run.error;
  assert.equal(run.status, mustPass ? 0 : 1, `${label}: ${run.stdout}\n${run.stderr}`);
  console.log(mustPass ? run.stdout.trim() : `PASS negative control ${label}: ${run.stderr.trim()}`);
}
compileRun('production', fixture, true);
compileRun('inverted-preserve-condition', fixture.replace('if (MEM32(frame - 8u) != 1u)', 'if (MEM32(frame - 8u) == 1u)'), false);
compileRun('omitted-numeric-increment', fixture.replace('xmm0.f[0] += MEMF(frame - 0x14u);', '/* negative control: increment omitted */'), false);
compileRun('wrong-iterator-copy', fixture.replace('MEM32(ebx + 4u) = edx;', 'MEM32(ebx + 8u) = edx;'), false);
compileRun('wrong-aggregate-chunk-stride', fixture.replace('(ebx >> 15) * 0x3Eu', '(ebx >> 15) * 0x3Fu'), false);
console.log(`TEST_OUTPUT ${temporary}`);
