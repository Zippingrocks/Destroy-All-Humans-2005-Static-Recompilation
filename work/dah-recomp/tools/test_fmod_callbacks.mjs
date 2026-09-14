import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const source=fs.readFileSync(path.join(here,'../src/recomp/gen/recomp_fmod_callbacks.c'),'utf8').replace(/^#include "recomp_funcs.h"\r?\n/m,'');
const manual=fs.readFileSync(path.join(here,'../src/recomp_manual.c'),'utf8');
const xbe=fs.readFileSync(path.join(here,'../../default.xbe'));
const sections=xbe.readUInt32LE(0x11C), table=xbe.readUInt32LE(0x120)-xbe.readUInt32LE(0x104);
function original(va,size){for(let i=0;i<sections;++i){const p=table+i*56,start=xbe.readUInt32LE(p+4),n=xbe.readUInt32LE(p+16);if(va>=start&&va+size<=start+n){const offset=xbe.readUInt32LE(p+12)+va-start;return xbe.subarray(offset,offset+size);}}throw Error('Original bytes unavailable');}
const expected=[0x13B5A0,0x13F4C2,0x13F45B,0x13F4C2,0x13F420,0x13F4C2,0x13F45B,0x13F4C2,0x13F459,0x13F459,0x13F483,0x13F459,0x13F4C2,0x13F4C2,0x13F45B,0x13F4C2],entries=original(0x2597E0,64);
for(let i=0;i<16;++i){assert.equal(entries.readUInt32LE(i*4),expected[i]);const h=expected[i].toString(16).padStart(8,'0').toUpperCase();assert(manual.includes(`if (xbox_va == 0x${h}u) return sub_${h};`));assert(source.includes(`void sub_${h}(void)`));}
assert.equal(original(0x259A50,10).toString('hex'),'00000000000000c0ffff');
const asm=fs.readFileSync(path.join(here,'../../disasm-seeded/asm/text.asm'),'utf8');
let instructions=0,total=0;
for(const [start,end] of [[0x13B5A0,0x13B5AE],[0x13F420,0x13F427],[0x13F459,0x13F4DF]]){let cursor=start;for(const m of asm.matchAll(/^\s*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]+(.*?)\r?$/gm)){const va=parseInt(m[1],16),bytes=Buffer.from(m[2],'hex');if(va<start||va>=end)continue;assert.equal(va,cursor);assert.deepEqual(original(va,bytes.length),bytes);cursor+=bytes.length;total+=bytes.length;++instructions;}assert.equal(cursor,end);}
console.log(`PASS ${instructions} original instructions/${total} bytes; all 16 fmod table slots dispatched`);
const temporary=fs.mkdtempSync(path.join(os.tmpdir(),'dah-fmod-test-'));
const oracle=path.join(temporary,'oracle.obj');
const assembled=spawnSync('ml64.exe',['/nologo','/c',`/Fo${oracle}`,path.join(here,'test_x87_classify_oracle.asm')],{cwd:temporary,encoding:'utf8',timeout:30000});assert.equal(assembled.status,0,assembled.stdout+assembled.stderr);
function test(label,fixture,status){const folder=path.join(temporary,label);fs.mkdirSync(folder);fs.writeFileSync(path.join(folder,'fmod_fixture.inc'),fixture);const exe=path.join(folder,'test.exe');
const build=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${folder}`,`/Fe:${exe}`,`/Fo:${path.join(folder,'test.obj')}`,path.join(here,'test_fmod_callbacks.c'),oracle],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(build.status,0,`${build.stdout}\n${build.stderr}`);
const result=spawnSync(exe,[],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(result.status,status,`${result.stdout}\n${result.stderr}`);console.log(status?`PASS negative control ${label}: ${result.stderr.trim()}`:result.stdout.trim());}
test('production',source,0);
test('wrong-remainder',source.replace('fmod(dividend, divisor)','remainder(dividend, divisor)'),1);
test('missing-pop',source.replace('g_fp_top = (int)next;','g_fp_top = (int)top;'),1);
test('wrong-error-sign',source.replace('(int8_t)MEM8(g_ebp - 0x90u) <= 0','MEM8(g_ebp - 0x90u) == 0'),1);
test('wrong-nan-priority',source.replace('if (aq != bq) selected = aq ? a : b;','if (aq != bq) selected = aq ? b : a;'),1);
console.log(`TEST_OUTPUT ${temporary}`);
