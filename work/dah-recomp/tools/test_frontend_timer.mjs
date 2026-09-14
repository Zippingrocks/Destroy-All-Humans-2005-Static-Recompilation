import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const source=fs.readFileSync(path.join(here,'../src/recomp/gen/recomp_frontend_callbacks.c'),'utf8');
const manual=fs.readFileSync(path.join(here,'../src/recomp_manual.c'),'utf8');
const xbe=fs.readFileSync(path.join(here,'../../default.xbe'));
const sections=xbe.readUInt32LE(0x11C), table=xbe.readUInt32LE(0x120)-xbe.readUInt32LE(0x104);
function original(va,size){for(let i=0;i<sections;++i){const p=table+i*56,start=xbe.readUInt32LE(p+4),n=xbe.readUInt32LE(p+16);if(va>=start&&va+size<=start+n){const offset=xbe.readUInt32LE(p+12)+va-start;return xbe.subarray(offset,offset+size);}}throw Error('Original bytes unavailable');}
const asm=fs.readFileSync(path.join(here,'../../disasm-seeded/asm/text.asm'),'utf8');
const decoded=[...asm.matchAll(/^\s*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]+(.*?)\r?$/gm)].map(m=>({va:parseInt(m[1],16),bytes:Buffer.from(m[2],'hex')}));
let instructions=0,total=0;const bodies=[];
for(const [start,end]of [[0x8BA90,0x8BAD2],[0xE3BE0,0xE3BFD],[0x11C180,0x11C29E]]){let cursor=start;for(const{va,bytes}of decoded){if(va<start||va>=end)continue;assert.equal(va,cursor);assert.deepEqual(original(va,bytes.length),bytes);cursor+=bytes.length;total+=bytes.length;++instructions;}assert.equal(cursor,end);const h=start.toString(16).toUpperCase().padStart(8,'0');assert(manual.includes(`if (xbox_va == 0x${h}u) return sub_${h};`));const m=source.match(new RegExp(`^void sub_${h}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`,'m'));assert(m);bodies.push(m[0]);}
const fixture=bodies.join('\n\n');
for(const m of fixture.matchAll(/PUSH32\(esp, 0x([0-9A-F]+)u\); sub_([0-9A-F]+)\(\);/g)){const ret=parseInt(m[1],16),raw=original(ret-5,5);assert.equal(raw[0],0xE8);assert.equal((ret+raw.readInt32LE(1))>>>0,parseInt(m[2],16));}
assert.equal(original(0x225C20,4).readUInt32LE(),0);
console.log(`PASS ${instructions} original instructions/${total} bytes, zero constant, dispatch and every direct call/return PC`);
const temporary=fs.mkdtempSync(path.join(os.tmpdir(),'dah-frontend-timer-'));
function test(label,body,status){const folder=path.join(temporary,label);fs.mkdirSync(folder);fs.writeFileSync(path.join(folder,'frontend_timer_fixture.inc'),body);const exe=path.join(folder,'test.exe');const build=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${folder}`,`/Fe:${exe}`,`/Fo:${path.join(folder,'test.obj')}`,path.join(here,'test_frontend_timer.c')],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(build.status,0,build.stdout+build.stderr);const result=spawnSync(exe,[],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(result.status,status,result.stdout+result.stderr);console.log(status?`PASS negative control ${label}: ${result.stderr.trim()}`:result.stdout.trim());}
test('production',fixture,0);
test('wrong-native-result-count',fixture.replace('eax = 1u;','eax = 0u;'),1);
test('wrong-virtual-slot',fixture.replace('MEM32(esi + 0x20u)','MEM32(esi + 0x24u)'),1);
test('unordered-expiry',fixture.replace('if (HI8(eax) & 1u)','if (g_fp_cmp < 0)'),1);
test('rounded-live-sum',fixture.replace('MEMF(esi + 0x18u) = (float)g_fp_stack[g_fp_top];','MEMF(esi + 0x18u) = (float)g_fp_stack[g_fp_top]; g_fp_stack[g_fp_top] = MEMF(esi + 0x18u);'),1);
test('wrong-ret-cleanup',fixture.replace('esp += 8u; /* RET 4 */','esp += 4u;'),1);
console.log(`TEST_OUTPUT ${temporary}`);
