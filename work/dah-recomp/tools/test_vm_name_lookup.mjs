import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const source=fs.readFileSync(path.join(here,'../src/recomp/gen/recomp_seeded.c'),'utf8');
const manual=fs.readFileSync(path.join(here,'../src/recomp_manual.c'),'utf8');
const match=source.match(/^void sub_00191FAA\(void\)\r?\n\{[\s\S]*?^\}/m);assert(match);
const xbe=fs.readFileSync(path.join(here,'../../default.xbe'));
const sections=xbe.readUInt32LE(0x11C), table=xbe.readUInt32LE(0x120)-xbe.readUInt32LE(0x104);
function original(va,size){for(let i=0;i<sections;++i){const p=table+i*56,start=xbe.readUInt32LE(p+4),n=xbe.readUInt32LE(p+16);if(va>=start&&va+size<=start+n){const offset=xbe.readUInt32LE(p+12)+va-start;return xbe.subarray(offset,offset+size);}}throw Error('Original bytes unavailable');}
assert.deepEqual(original(0x191FAA,5),Buffer.from('5f5e33c0c3','hex'));
const expected=[0x192022,0x19200C,0x191FAA,0x19203A,0x191FAA,0x19203A], entries=original(0x192050,24);
for(let i=0;i<6;++i){assert.equal(entries.readUInt32LE(i*4),expected[i]);const h=expected[i].toString(16).padStart(8,'0').toUpperCase();assert(manual.includes(`if (xbox_va == 0x${h}u) return sub_${h};`));}
console.log('PASS: original five-byte epilogue and all six name-lookup jump-table entries verified');
const temporary=fs.mkdtempSync(path.join(os.tmpdir(),'dah-vm-name-lookup-'));
function test(label,fixture,status){const folder=path.join(temporary,label);fs.mkdirSync(folder);fs.writeFileSync(path.join(folder,'vm_name_lookup_fixture.inc'),fixture);const exe=path.join(folder,'test.exe');
const build=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${folder}`,`/Fe:${exe}`,`/Fo:${path.join(folder,'test.obj')}`,path.join(here,'test_vm_name_lookup.c')],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(build.status,0,`${build.stdout}\n${build.stderr}`);
const result=spawnSync(exe,[],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(result.status,status,`${result.stdout}\n${result.stderr}`);console.log(status?`PASS negative control ${label}: ${result.stderr.trim()}`:result.stdout.trim());}
test('production',match[0],0);
test('missing-return-consumption',match[0].replace('esp += 4u;','/* omitted */'),1);
test('wrong-saved-register',match[0].replace('POP32(esp, edi);','POP32(esp, esi);'),1);
console.log(`TEST_OUTPUT ${temporary}`);
