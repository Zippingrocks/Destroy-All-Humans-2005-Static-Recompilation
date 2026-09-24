/* Run from a Visual Studio x64 developer prompt. Only standalone test programs
 * are compiled/executed; the game, desktop, and project build are untouched. */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, '../../..');
const runtime = path.join(root, 'Repos/xboxrecomp-main/templates/runtime');
const types = fs.readFileSync(path.join(runtime, 'recomp_types.h'), 'utf8');
const asm = fs.readFileSync(path.join(root, 'work/disasm-seeded/asm/text.asm'), 'utf8');
const xbe = fs.readFileSync(path.join(root, 'work/default.xbe'));
const base = xbe.readUInt32LE(0x104), table = xbe.readUInt32LE(0x120) - base;
const sections = Array.from({ length: xbe.readUInt32LE(0x11c) }, (_, i) => {
  const p = table + i * 56;
  return { va: xbe.readUInt32LE(p + 4), raw: xbe.readUInt32LE(p + 12), size: xbe.readUInt32LE(p + 16) };
});
const instructions = [...asm.matchAll(/^\s*0x([0-9A-F]+)\s+([0-9a-f]+)[ \t]+(\S+)[ \t]*([^\r\n]*)/gm)]
  .map(m => ({ va: parseInt(m[1], 16), bytes: m[2], op: m[3], args: m[4].trim() }));
const targets = [[0x12BA40, '0f2e05247d2200']];
const generated = new Map(['0013'].map(n => [n,
  fs.readFileSync(path.join(here, `../src/recomp/gen/recomp_${n}.c`), 'utf8')]));
let bytesValidated = 0;
function validateBytes(insn) {
  const s = sections.find(s => insn.va >= s.va && insn.va + insn.bytes.length / 2 <= s.va + s.size);
  assert(s);
  assert.equal(xbe.subarray(s.raw + insn.va - s.va,
    s.raw + insn.va - s.va + insn.bytes.length / 2).toString('hex'), insn.bytes);
  bytesValidated += insn.bytes.length / 2;
}
function scalarOperand(operand) {
  if (/^xmm[0-7]$/.test(operand)) return `${operand}.f[0]`;
  assert.match(operand, /^dword ptr \[.+\]$/);
  const address = operand.slice(11, -1).replace(/0x[0-9a-f]+/g,
    n => `0x${parseInt(n, 16).toString(16).toUpperCase()}`);
  return `MEMF(${address})`;
}
const sites = targets.map(([va, bytes]) => {
  const marker = va.toString(16).toUpperCase().padStart(8, '0');
  const originalIndex = instructions.findIndex(insn => insn.va === va);
  assert(originalIndex > 0);
  const compare = instructions[originalIndex - 1], lahf = instructions[originalIndex];
  const test = instructions[originalIndex + 1];
  assert.equal(compare.op, 'ucomiss'); assert.equal(compare.bytes, bytes);
  assert.equal(lahf.op, 'lahf'); assert.equal(lahf.bytes, '9f');
  assert.equal(test.op, 'test'); assert.equal(test.args, 'ah, 0x44');
  assert.equal(test.bytes, 'f6c444');
  const between = instructions.slice(originalIndex + 2, originalIndex + 4);
  const jumpIndex = between.findIndex(insn => insn.op === 'jp' || insn.op === 'jnp');
  assert(jumpIndex >= 0);
  for (const insn of between.slice(0, jumpIndex)) assert.equal(insn.op, 'fstp');
  const jump = between[jumpIndex];
  for (const insn of [compare, lahf, test, ...between.slice(0, jumpIndex + 1)]) validateBytes(insn);
  const operands = compare.args.split(', ').map(scalarOperand);
  const statement = `SET_HI8(eax, RECOMP_COMISS_LAHF(${operands.join(', ')})); /* UCOMISS/LAHF 0x${marker} */`;
  const source = generated.get('0013');
  assert.equal(source.split(statement).length, 2, `Exact single production restoration ${marker}`);
  const tail = source.slice(source.indexOf(statement)).split(/\r?\n/);
  const branchIndex = tail.findIndex(line => line.trim().startsWith('if ('));
  assert(branchIndex === 3 || branchIndex === 4);
  const branch = tail[branchIndex].trim();
  const target = parseInt(jump.args, 16).toString(16).toUpperCase().padStart(8, '0');
  assert.equal(branch,
    `if (${jump.op === 'jnp' ? '(!RECOMP_PARITY8((_fa) & (_fb)))' : 'RECOMP_PARITY8((_fa) & (_fb))'}) goto loc_${target}; /* ${jump.op}: ${jump.op === 'jnp' ? 'not parity' : 'parity'} */`);
  const memory = operands[1].startsWith('MEMF(');
  const address = memory ? operands[1].slice(5, -1) : '0';
  const setup = `${operands[0]} = lhs;\n    ${memory ? 'memory_value' : operands[1]} = rhs;`;
  const functionCode = `static Result site_${marker}(float lhs, float rhs, uint32_t initial_eax) {
    uint32_t eax = initial_eax, _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    uint32_t edx = 0x1000u, esp = 0x2000u;
    TestXmm xmm0 = {{0}}, xmm1 = {{0}};
    (void)edx; (void)esp; (void)xmm0; (void)xmm1;
    expected_memory_address = ${address}; memory_reads = 0;
    ${setup}
    ${statement}
${tail.slice(1, 3).join('\n')}
    (void)_fas; (void)_fbs;
    ${branch.replace(`loc_${target}`, 'taken')}
    return (Result){eax, 0};
taken:
    return (Result){eax, 1};
}`;
  return { marker, functionCode, statement, isJnp: jump.op === 'jnp', memory };
});
const macros = ['HI8', 'SET_HI8', 'RECOMP_PARITY8'].map(name => {
  const match = types.match(new RegExp(`^#define ${name}\\([^\\n]+`, 'm'));
  assert(match); return match[0];
}).join('\n');
const parity = types.match(/static inline int recomp_parity8\(uint32_t x\) \{[\s\S]*?\n\}/);
assert(parity);
const tableCode = `static const struct {
    uint32_t address; Result (*run)(float, float, uint32_t); int is_jnp; unsigned memory_operands;
} sites[] = {\n${sites.map(s => `    {0x${s.marker}u, site_${s.marker}, ${s.isJnp ? 1 : 0}, ${s.memory ? 1 : 0}},`).join('\n')}\n};`;
const fixture = fs.readFileSync(path.join(here, 'test_sse_lahf.c'), 'utf8')
  .replace('/* PRODUCTION_MACROS */', `${parity[0]}\n${macros}`)
  .replace('/* PRODUCTION_FIXTURES */', `${sites.map(s => s.functionCode).join('\n')}\n${tableCode}`);
const temp = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-sse-lahf-'));
const oracleObject = path.join(temp, 'oracle.obj');
const assembled = spawnSync('ml64.exe', ['/nologo', '/c', `/Fo${oracleObject}`,
  path.join(here, 'test_sse_lahf_oracle.asm')], { cwd: temp, encoding: 'utf8', timeout: 30000 });
assert.equal(assembled.status, 0, assembled.error || assembled.stdout || assembled.stderr);
function run(label, source, wanted) {
  const c = path.join(temp, `${label}.c`), exe = path.join(temp, `${label}.exe`);
  fs.writeFileSync(c, source);
  const compiled = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11',
    '/fp:precise', `/I${runtime}`, `/Fe:${exe}`, `/Fo:${path.join(temp, `${label}.obj`)}`,
    c, oracleObject], { cwd: temp, encoding: 'utf8', timeout: 30000 });
  assert.equal(compiled.status, 0, compiled.error || compiled.stdout || compiled.stderr);
  const result = spawnSync(exe, [], { cwd: temp, encoding: 'utf8', timeout: 30000 });
  assert.equal(result.status, wanted, `${label}: ${result.error || result.stdout || result.stderr}`);
  console.log(wanted ? `PASS: rejected ${label}: ${result.stderr.trim()}` : result.stdout.trim());
}
console.log(`PASS: ${targets.length} exact LAHF sites and original compare/test/branch operands; ${bytesValidated} retail XBE bytes validated`);
run('current', fixture, 0);
for (const s of sites) run(`missing-lahf-${s.marker}`, fixture.replace(s.statement, '/* original missing LAHF */'), 1);
console.log(`TEST_OUTPUT ${temp}`);
