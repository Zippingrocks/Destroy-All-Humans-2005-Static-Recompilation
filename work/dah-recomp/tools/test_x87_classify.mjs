/* Only builds/runs the isolated source fixture and native hardware oracle. */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, '../../..');
const production = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_0014.c'), 'utf8');
const binary = production.match(/^void sub_0013F383\(void\)\r?\n\{[\s\S]*?^\}/m)?.[0];
const unary = production.match(/^void sub_0013F31C\(void\)\r?\n\{[\s\S]*?^\}/m)?.[0];
assert(binary && unary);
const fixture = binary + '\n\n' + unary;
const xbe = fs.readFileSync(path.join(root, 'work/default.xbe'));
const base = xbe.readUInt32LE(0x104), count = xbe.readUInt32LE(0x11C), table = xbe.readUInt32LE(0x120) - base;
function original(va, bytes) {
  for (let i = 0; i < count; ++i) {
    const s = table + i * 56, start = xbe.readUInt32LE(s + 4), length = xbe.readUInt32LE(s + 16);
    if (va >= start && va + bytes <= start + length) {
      const p = xbe.readUInt32LE(s + 12) + va - start; return xbe.subarray(p, p + bytes);
    }
  }
  throw Error(`Missing original range ${va.toString(16)}`);
}
const asm = fs.readFileSync(path.join(root, 'work/disasm-seeded/asm/text.asm'), 'utf8');
let cursor = 0x13F31C, instructions = 0;
for (const m of asm.matchAll(/^\s*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]+(.*?)\r?$/gm)) {
  const va = parseInt(m[1], 16), bytes = Buffer.from(m[2], 'hex');
  if (va < 0x13F31C || va >= 0x13F40F) continue;
  assert.equal(va, cursor); assert.deepEqual(original(va, bytes.length), bytes);
  cursor += bytes.length; ++instructions;
}
assert.equal(cursor, 0x13F40F);
assert.equal(original(0x259A6C, 16).toString('hex'), '080408080804080800040c0800040c08');
const data = `static const uint8_t original_xlat[] = {${[...original(0x259A6C, 16)]}};\n` +
  `static const uint8_t original_fmod[] = {${[...original(0x2597D0, 80)]}};\n` +
  `static const uint8_t original_unary[] = {${[...original(0x25AA9A, 96)]}};\n`;
console.log(`PASS: ${instructions} classifier instructions match243 original bytes; using original fmod/sinh/cosh/tanh dispatch and XLAT tables`);
console.log(`PRODUCTION_SOURCE_SHA256 ${crypto.createHash('sha256').update(fixture).digest('hex')}`);
const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-x87-classify-test-'));
const oracle = path.join(temporary, 'oracle.obj');
const assemble = spawnSync('ml64.exe', ['/nologo', '/c', `/Fo${oracle}`, path.join(here, 'test_x87_classify_oracle.asm')],
  { encoding: 'utf8', cwd: temporary, timeout: 30000 });
assert.equal(assemble.status, 0, `${assemble.error || ''}\n${assemble.stdout}\n${assemble.stderr}`);
function compileRun(label, source, pass) {
  const dir = path.join(temporary, label); fs.mkdirSync(dir);
  fs.writeFileSync(path.join(dir, 'x87_classify_fixture.inc'), source);
  fs.writeFileSync(path.join(dir, 'x87_original_tables.inc'), data);
  const exe = path.join(dir, 'test.exe');
  const build = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11', ...(!pass ? ['/wd4702'] : []), `/I${dir}`, `/I${path.join(here, '../src')}`,
    `/Fe:${exe}`, `/Fo:${path.join(dir, 'test.obj')}`, path.join(here, 'test_x87_classify.c'), oracle],
    { encoding: 'utf8', cwd: dir, timeout: 30000 });
  assert.equal(build.status, 0, `${label}: ${build.error || ''}\n${build.stdout}\n${build.stderr}`);
  const run = spawnSync(exe, [], { encoding: 'utf8', cwd: dir, timeout: 30000 });
  assert.equal(run.status, pass ? 0 : 1, `${label}: ${run.error || ''}\n${run.stdout}\n${run.stderr}`);
  console.log(pass ? run.stdout.trim() : `PASS negative control ${label}: ${run.stderr.trim()}`);
}
compileRun('production', fixture, true);
compileRun('wrong-seh-frame', fixture.replace('ebp = g_ebp;', 'ebp = g_seh_ebp;'), false);
compileRun('missing-xlat', fixture.replaceAll('SET_LO8(eax, MEM8(ebx + LO8(eax)));', '/* omitted XLAT */'), false);
compileRun('wrong-byte-sign', fixture.replaceAll(' | (HI8(ecx) & 0x80u)', '').replaceAll(' | (LO8(ecx) & 0x80u)', ''), false);
compileRun('stale-fp-comparison', fixture.replaceAll('dah_x87_fxam_live_status(fp_top(), g_fp_top)', '(uint16_t)((g_fp_top << 11) | (g_fp_cmp == 0 ? 0x4000u : 0x0100u))'), false);
compileRun('unary-only-missing-xlat', binary + '\n\n' + unary.replace('SET_LO8(eax, MEM8(ebx + LO8(eax)));', '/* missing unary XLAT */'), false);
compileRun('unary-only-wrong-frame', binary + '\n\n' + unary.replace('ebp = g_ebp;', 'ebp = g_seh_ebp;'), false);
console.log(`TEST_OUTPUT ${temporary}`);
