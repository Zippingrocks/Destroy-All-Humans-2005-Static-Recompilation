/* Developer-prompt regression: only compiles/runs an extracted source fixture.
 * Does not build/launch the game, simulate presentation, or access desktop UI. */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here = path.dirname(fileURLToPath(import.meta.url));
const workspace = path.resolve(here, '../../..');
const production = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_0013.c'), 'utf8');
const fixture = production.match(/^void sub_00122D70\(void\)\r?\n\{[\s\S]*?^\}/m)?.[0];
assert(fixture, 'Missing actual movie update production function');
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
  assert(section); return xbe.subarray(section.offset + va - section.va, section.offset + va - section.va + size);
}
const instructions = [...assembly.matchAll(/^\s*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]+(.*?)\r?$/gm)]
  .map(m => ({ va: parseInt(m[1], 16), bytes: Buffer.from(m[2], 'hex'), mnemonic: m[3], operands: m[4] }));
let instructionCount = 0, byteCount = 0;
for (const [start, end] of [[0x122D70, 0x122E50], [0x5A468, 0x5A478], [0x1228F9, 0x1228FE]]) {
  let cursor = start;
  for (const instruction of instructions.filter(i => i.va >= start && i.va < end)) {
    assert.equal(instruction.va, cursor);
    assert.deepEqual(original(instruction.va, instruction.bytes.length), instruction.bytes);
    cursor += instruction.bytes.length; ++instructionCount; byteCount += instruction.bytes.length;
  }
  assert.equal(cursor, end);
}
assert.equal(original(0x5A468, 5).toString('hex'), 'e823840c00'); // CALL update, return5A46D.
assert.equal(original(0x5A46F, 5).toString('hex'), 'b801000000'); // Caller discards movie AL.
assert.equal(original(0x1228F9, 5).toString('hex'), 'e972040000'); // Tail-call preserves PC.
assert.equal(original(0x123294, 5).toString('hex'), 'e8d7faffff'); // Distinct initial preload.
console.log(`PASS: ${instructionCount} original instructions / ${byteCount} bytes, including return-gate and preload-caller proof`);
console.log(`PRODUCTION_SOURCE_SHA256 ${crypto.createHash('sha256').update(fixture).digest('hex')}`);
const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-movie-nonblock-test-'));
function compile(label, source) {
  const folder = path.join(temporary, label); fs.mkdirSync(folder);
  fs.writeFileSync(path.join(folder, 'movie_nonblock_fixture.inc'), source);
  const exe = path.join(folder, 'test.exe');
  const build = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11', `/I${folder}`,
    `/Fe:${exe}`, `/Fo:${path.join(folder, 'test.obj')}`, path.join(here, 'test_movie_nonblock.c')],
    { cwd: folder, encoding: 'utf8', timeout: 30000 });
  assert.equal(build.status, 0, `${label}: ${build.error || ''}\n${build.stdout}\n${build.stderr}`);
  return exe;
}
function run(exe, envValue, enabled, mustPass, archives = false) {
  const env = { ...process.env };
  delete env.DAH_MOVIE_NONBLOCK;
  if (envValue !== undefined) env.DAH_MOVIE_NONBLOCK = envValue;
  const args = [enabled ? '1' : '0'];
  if (archives) args.push('1');
  const result = spawnSync(exe, args, { env, encoding: 'utf8', timeout: 30000 });
  assert.equal(result.status, mustPass ? 0 : 1, `${result.error || ''}\n${result.stdout}\n${result.stderr}`);
  console.log(mustPass ? `env=${JSON.stringify(envValue)} ${result.stdout.trim()}` : `PASS negative control: ${result.stderr.trim()}`);
}
const productionExe = compile('production', fixture);
run(productionExe, undefined, false, true); // Normal launches preserve retail blocking semantics.
for (const value of ['', '0', 'true', '01', '10', '1 ']) run(productionExe, value, false, true);
run(productionExe, '1', true, true);
assert(production.includes('dah_archives_movie_active = ecx == 0x00F7F9E4u;'));
run(productionExe, undefined, true, true, true); // Archives yields without the diagnostic env switch.
for (const [label, oldText, replacement] of [
  ['missing-pending-defer', '(dah_movie_nonblock || dah_archives_movie_active) &&\n            dah_movie_update_call', '(dah_movie_nonblock > 1 || dah_archives_movie_active) &&\n            dah_movie_update_call'],
  ['unsafe-preload-defer', '(dah_movie_nonblock || dah_archives_movie_active) &&\n            dah_movie_update_call', 'dah_movie_nonblock || dah_archives_movie_active'],
  ['omitted-nextframe-call', 'sub_0020D460();', 'if (dah_movie_nonblock != 1) sub_0020D460(); else esp += 8;'],
]) {
  assert(fixture.includes(oldText));
  let changed = fixture.replace(oldText, replacement);
  if (label === 'unsafe-preload-defer') changed = changed.replace('dah_movie_trace("DECODE", &calls);', '(void)dah_movie_update_call; dah_movie_trace("DECODE", &calls);');
  run(compile(label, changed), '1', true, false);
}
console.log(`TEST_OUTPUT ${temporary}`);
