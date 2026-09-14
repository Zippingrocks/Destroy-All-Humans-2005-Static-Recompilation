/* Run in a Visual Studio x64 developer prompt:
 * node work/dah-recomp/tools/test_d3d_mmx_transfer.mjs
 * Validates all original instruction bytes, then compiles the actual two
 * generated function bodies. No game, window, input, or audio is started.
 */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const here = path.dirname(fileURLToPath(import.meta.url));
const workspace = path.resolve(here, '../../..');
const generated = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_0019.c'), 'utf8');
const assembly = fs.readFileSync(path.join(workspace, 'work/disasm-seeded/asm/D3D.asm'), 'utf8');
const xbe = fs.readFileSync(path.join(workspace, 'work/default.xbe'));
const imageBase = xbe.readUInt32LE(0x104);
const sectionCount = xbe.readUInt32LE(0x11c);
const sectionTable = xbe.readUInt32LE(0x120) - imageBase;
const sections = Array.from({ length: sectionCount }, (_, i) => {
  const p = sectionTable + i * 56;
  return { va: xbe.readUInt32LE(p + 4), size: xbe.readUInt32LE(p + 8),
    offset: xbe.readUInt32LE(p + 12), rawSize: xbe.readUInt32LE(p + 16) };
});
const instructions = [...assembly.matchAll(/^[ \t]*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]*(.*?)[ \t]*\r?$/gm)]
  .map(m => ({ va: parseInt(m[1], 16), bytes: m[2], opcode: m[3], operands: m[4].split(';')[0].trim() }));
const normalize = s => s.replace(/\s+/g, '').toLowerCase();
const targets = [{ name: 'sub_001DD740', start: 0x1dd740, end: 0x1dd7d0, mmxCount: 16 },
  { name: 'sub_001DD940', start: 0x1dd940, end: 0x1ddb97, mmxCount: 30 },
  { name: 'sub_001D9ED0', start: 0x1d9ed0, end: 0x1d9f72, mmxCount: 24 },
  { name: 'sub_001D9F80', start: 0x1d9f80, end: 0x1da050, mmxCount: 16 }];
let byteCount = 0;
let instructionCount = 0;
const bodies = targets.map(target => {
  const match = generated.match(new RegExp(`^void ${target.name}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`, 'm'));
  assert(match, `Missing function ${target.name}`);
  const body = match[0];
  const original = instructions.filter(i => i.va >= target.start && i.va < target.end);
  let expectedVA = target.start;
  for (const i of original) {
    const bytes = Buffer.from(i.bytes, 'hex');
    assert.equal(i.va, expectedVA, `Disassembly gap at ${expectedVA.toString(16)}`);
    const section = sections.find(s => i.va >= s.va && i.va + bytes.length <= s.va + s.rawSize);
    assert(section, `No XBE section at ${i.va.toString(16)}`);
    assert.deepEqual(xbe.subarray(section.offset + i.va - section.va,
      section.offset + i.va - section.va + bytes.length), bytes, `XBE byte mismatch at ${i.va.toString(16)}`);
    expectedVA += bytes.length;
    byteCount += bytes.length;
    instructionCount++;
  }
  assert.equal(expectedVA, target.end);
  const mmx = original.filter(i => /\bmm[0-7]\b/.test(i.operands));
  const restored = [...body.matchAll(/^\s*(.*?) \/\* MMX 0x([0-9A-F]+): (.*?) \*\/\r?$/gm)];
  assert.equal(mmx.length, target.mmxCount);
  assert.equal(restored.length, mmx.length);
  assert(!/\/\* (?:TODO|SSE): .*\bmm[0-7]\b/.test(body), `Remaining omission in ${target.name}`);
  for (let n = 0; n < mmx.length; n++) {
    const i = mmx[n], r = restored[n];
    assert.equal(parseInt(r[2], 16), i.va);
    assert.equal(normalize(r[3]), normalize(`${i.opcode} ${i.operands}`));
    const [dst, src] = i.operands.split(/,\s*/);
    let expected;
    if (i.opcode === 'movq' && /^mm[0-7]$/.test(dst)) {
      assert(/^mm[0-7]$/.test(dst));
      const address = src.match(/^qword ptr \[(.*)\]$/)?.[1];
      assert(address);
      expected = `${dst} = (uint64_t)MEM32((uint32_t)(${address})) | ((uint64_t)MEM32((uint32_t)(${address}) + 4u) << 32);`;
    } else {
      assert(['movntq','movq'].includes(i.opcode));
      assert(/^mm[0-7]$/.test(src));
      const address = dst.match(/^qword ptr \[(.*)\]$/)?.[1];
      assert(address);
      expected = `MEM32((uint32_t)(${address})) = (uint32_t)${src}; MEM32((uint32_t)(${address}) + 4u) = (uint32_t)(${src} >> 32);`;
    }
    assert.equal(normalize(r[1]), normalize(expected), `Restored semantics mismatch at ${i.va.toString(16)}`);
  }
  return body;
});
console.log(`PASS: ${instructionCount} original instructions/${byteCount} XBE bytes; all 86 MMX transfers match exact operands and addresses`);
const fixture = bodies.join('\n\n') + '\n';
console.log(`SOURCE_FIXTURE sha256=${crypto.createHash('sha256').update(fixture).digest('hex')}`);
const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-d3d-mmx-test-'));
function compileAndRun(label, source, mustPass) {
  const directory = path.join(tempDir, label);
  fs.mkdirSync(directory);
  fs.writeFileSync(path.join(directory, 'd3d_mmx_fixture.inc'), source);
  const executable = path.join(directory, 'test.exe');
  const compile = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11',
    `/I${directory}`, `/Fe:${executable}`, `/Fo:${path.join(directory, 'test.obj')}`,
    path.join(here, 'test_d3d_mmx_transfer.c')], { cwd: directory, encoding: 'utf8', timeout: 30000 });
  if (compile.error || compile.status !== 0) {
    process.stdout.write(compile.stdout || '');
    process.stderr.write(compile.stderr || '');
    throw new Error(`Compile failed: ${label}: ${compile.error || compile.status}`);
  }
  const run = spawnSync(executable, [], { cwd: directory, encoding: 'utf8', timeout: 30000 });
  if (run.error) throw run.error;
  if ((mustPass && run.status !== 0) || (!mustPass && run.status !== 1)) {
    process.stderr.write(run.stderr || '');
    throw new Error(`Unexpected test result ${label}: ${run.status}`);
  }
  console.log(mustPass ? run.stdout.trim() : `PASS: rejected ${label}: ${run.stderr.trim().split('\n').at(-1)}`);
}
compileAndRun('current', fixture, true);
for (let n = 0; n < bodies.length; n++) {
  const control = bodies.map((body, i) => i === n ? body.replace(/^.*\/\* MMX 0x.*$/gm,
    '    /* regression control: omitted original MMX transfer */') : body).join('\n\n');
  compileAndRun(`omitted-${targets[n].name}`, control, false);
}
console.log(`TEST_OUTPUT ${tempDir}`);
