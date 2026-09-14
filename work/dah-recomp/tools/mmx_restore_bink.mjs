#!/usr/bin/env node
/**
 * Restore omitted MMX in the existing Bink translation without regenerating
 * unrelated code or discarding manual fixes. Each emitted instruction is
 * checked against the corresponding retail disassembly instruction.
 *
 * node work/dah-recomp/tools/mmx_restore_bink.mjs --write
 * node work/dah-recomp/tools/mmx_restore_bink.mjs --check
 * With neither flag, report the proposed mechanical changes without writing.
 */
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import assert from 'node:assert/strict';

const toolDir = path.dirname(fileURLToPath(import.meta.url));
const projectDir = path.resolve(toolDir, '..');
const workspace = path.resolve(projectDir, '..', '..');
const asmDir = path.join(workspace, 'work', 'disasm-seeded', 'asm');
const genDir = path.join(projectDir, 'src', 'recomp', 'gen');
const args = new Set(process.argv.slice(2));
for (const arg of args) {
  assert(['--write', '--check'].includes(arg), `Unknown argument ${arg}`);
}
assert(!(args.has('--write') && args.has('--check')), 'Choose --write or --check');

const helpers = new Set([
  'pxor', 'por', 'punpcklbw', 'punpckhbw', 'punpcklwd', 'punpckhwd',
  'punpckldq', 'punpckhdq', 'psubusw', 'psllw', 'pslld', 'psllq', 'psrlw',
  'psrlq', 'pmulhw', 'pmullw', 'paddw', 'paddsw',
]);
const register = /^mm[0-7]$/;
const normalize = text => text.toLowerCase().replace(/\s+/g, '').trim();
const hex = value => value.toString(16).toUpperCase().padStart(8, '0');

const asm = new Map();
const asmFiles = fs.readdirSync(asmDir).filter(name => /^BINK.*\.asm$/i.test(name))
  .sort().map(name => path.join(asmDir, name));
// These callback ranges were absent from the initial section disassembly.
// lift_bink_tables.py emits this supplement from the actual retail XBE bytes.
asmFiles.push(path.join(toolDir, 'bink_table_original.asm'));
for (const asmFile of asmFiles) {
  const name = path.basename(asmFile);
  const text = fs.readFileSync(asmFile, 'utf8');
  for (const line of text.split(/\r?\n/)) {
    const match = line.match(/^\s*0x([0-9A-Fa-f]+)\s+([0-9a-fA-F]+)\s+(\w+)\s*(.*)$/);
    if (!match) continue;
    const [, address, bytes, mnemonic, operands] = match;
    const value = Number.parseInt(address, 16);
    const instruction = { address: value, bytes, mnemonic, operands: operands.trim(), source: name };
    if (asm.has(value)) {
      assert.equal(normalize(asm.get(value).mnemonic + asm.get(value).operands),
                   normalize(mnemonic + operands), `Conflicting disassembly at ${address}`);
    } else {
      asm.set(value, instruction);
    }
  }
}

function memory(operand) {
  const match = operand.match(/^(dword|qword) ptr \[([^\]]+)\]$/);
  assert(match, `Unsupported MMX memory operand: ${operand}`);
  const [, width, address] = match;
  // Guest arithmetic wraps at32 bits, including the second half of qword.
  assert(/^(?:0x[0-9a-f]+|[0-9]+|eax|ebx|ecx|edx|esi|edi|ebp|esp|\s|[+*\-])+$/i.test(address),
         `Unexpected memory expression: ${address}`);
  return { width, address: `(uint32_t)(${address})` };
}

function value64(operand) {
  if (register.test(operand)) return operand;
  if (/^(?:0x[0-9a-f]+|[0-9]+)$/.test(operand)) return operand + 'u';
  const { width, address } = memory(operand);
  if (width === 'dword') return `(uint64_t)MEM32(${address})`;
  return `((uint64_t)MEM32(${address}) | ((uint64_t)MEM32(${address} + 4u) << 32))`;
}

function emitMmx(instruction) {
  const { address, mnemonic, operands } = instruction;
  const [destination, source, extra] = operands.split(/,\s*/);
  assert(!extra && source, `Unexpected operand count at ${hex(address)}`);
  let statement;
  if (mnemonic === 'movq') {
    if (register.test(destination)) {
      statement = `${destination} = ${value64(source)};`;
    } else {
      const target = memory(destination);
      assert.equal(target.width, 'qword', 'MOVQ store must be64 bits');
      assert(register.test(source), 'MOVQ store source must be MMX');
      statement = `MEM32(${target.address}) = (uint32_t)${source}; ` +
                  `MEM32(${target.address} + 4u) = (uint32_t)(${source} >> 32);`;
    }
  } else if (mnemonic === 'movd') {
    assert(register.test(destination), `Unexpected MOVD destination ${destination}`);
    let value;
    if (/^(eax|ebx|ecx|edx|esi|edi|ebp|esp)$/.test(source)) value = source;
    else {
      const target = memory(source);
      assert.equal(target.width, 'dword', 'MOVD load must be32 bits');
      value = `MEM32(${target.address})`;
    }
    statement = `${destination} = (uint64_t)(uint32_t)(${value});`;
  } else {
    assert(helpers.has(mnemonic), `Unsupported MMX operation ${mnemonic}`);
    assert(register.test(destination), `Unexpected destination at ${hex(address)}`);
    statement = `${destination} = MMX_${mnemonic.toUpperCase()}(${destination}, ${value64(source)});`;
  }
  return `${statement} /* MMX 0x${hex(address)}: ${mnemonic} ${operands} */`;
}

const planned = [];
for (const filename of ['recomp_0020.c', 'recomp_0021.c', 'recomp_bink_tables.c']) {
  const filenameFull = path.join(genDir, filename);
  const before = fs.readFileSync(filenameFull, 'utf8');
  const newline = before.includes('\r\n') ? '\r\n' : '\n';
  let mmxChanged = 0;
  let mmxVerified = 0;
  let rdtscChanged = 0;
  const functionReports = [];
  let after = before.replace(
    /\/\*\*\r?\n \* (sub_[0-9A-F]+)\r?\n \* Original: 0x([0-9A-F]+) - 0x([0-9A-F]+)[\s\S]*?^\}/gm,
    (functionText, functionName, startHex, endHex) => {
      const start = Number.parseInt(startHex, 16);
      const end = Number.parseInt(endHex, 16);
      const original = [...asm.values()]
        .filter(instruction => instruction.address >= start && instruction.address < end &&
                               /\bmm[0-7]\b/.test(instruction.operands))
        .sort((a, b) => a.address - b.address);
      if (!original.length) return functionText;
      let position = 0;
      const result = functionText.split(/\r?\n/).map(line => {
        if (!/\bmm[0-7]\b/.test(line) || /^\s*uint64_t mm/.test(line)) return line;
        const instruction = original[position++];
        assert(instruction, `More MMX statements than retail instructions in ${functionName}`);
        const emitted = emitMmx(instruction);
        const indent = line.match(/^\s*/)[0];
        if (line.includes('/* MMX 0x')) {
          assert.equal(line.trim(), emitted, `Edited restored instruction in ${functionName}`);
        } else if (/\/\* movd \*\//.test(line)) {
          assert.equal(instruction.mnemonic, 'movd', `MOVD sequence mismatch in ${functionName}`);
          const [destination, source] = instruction.operands.split(/,\s*/);
          const value = source.includes('ptr') ? `MEM32(${memory(source).address.replace(/^\(uint32_t\)\((.*)\)$/, '$1')})` : source;
          assert.equal(normalize(line.replace(/\/\*.*\*\//, '')),
                       normalize(`${destination} = ${value};`), `Existing MOVD mismatch at ${hex(instruction.address)}`);
          mmxChanged++;
        } else {
          const placeholder = line.match(/^\s*\/\* (?:(?:TODO|SSE): )?(.*?) (?:\(MMX\/SIMD integer\) )?\*\/\s*$/);
          assert(placeholder, `Unrecognized MMX line in ${functionName}: ${line}`);
          assert.equal(normalize(placeholder[1]), normalize(`${instruction.mnemonic} ${instruction.operands}`),
                       `MMX sequence mismatch at ${hex(instruction.address)}`);
          mmxChanged++;
        }
        mmxVerified++;
        return indent + emitted;
      }).join(newline);
      assert.equal(position, original.length, `Missing generated MMX instructions in ${functionName}`);
      functionReports.push({ function: functionName, instructions: position });
      return result;
    });
  const leftover = after.match(/^\s*\/\* (?:TODO: |SSE: )?.*\bmm[0-7]\b.*\*\/\s*$/m);
  assert(!leftover,
         `Unrestored MMX placeholder in ${filename}: ${leftover?.[0].trim()}; functions=${JSON.stringify(functionReports)}`);
  after = after.replace(/\/\* TODO: rdtsc  \*\//g, () => {
    rdtscChanged++;
    return '{ uint64_t _tsc = dah_read_tsc(); eax = (uint32_t)_tsc; edx = (uint32_t)(_tsc >> 32); } /* rdtsc */';
  });
  function addInclude(header) {
    if (!after.includes(`#include "${header}"`)) {
      assert(after.includes('#include "recomp_funcs.h"'), `${filename} lacks include anchor`);
      after = after.replace('#include "recomp_funcs.h"', `#include "recomp_funcs.h"${newline}#include "${header}"`);
    }
  }
  if (mmxVerified) addInclude('recomp_mmx.h');
  addInclude('dah_timing.h');
  planned.push({ filenameFull, before, after });
  console.log(JSON.stringify({ filename, mmxChanged, mmxVerified, rdtscChanged, functions: functionReports }));
}

// Validate every target before writing any file. Re-running --write is idempotent.
if (args.has('--check')) {
  assert(planned.every(item => item.before === item.after), 'Restoration pending; run with --write');
} else if (args.has('--write')) {
  for (const { filenameFull, before, after } of planned) {
    if (before !== after) fs.writeFileSync(filenameFull, after);
  }
}
