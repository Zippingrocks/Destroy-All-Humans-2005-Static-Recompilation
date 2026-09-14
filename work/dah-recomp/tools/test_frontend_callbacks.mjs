/* Run from a VS developer environment. Compiles only isolated tests. */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const workspace=path.resolve(here,'../../..');
const source=fs.readFileSync(path.join(here,'../src/recomp/gen/recomp_frontend_callbacks.c'),'utf8');
const manual=fs.readFileSync(path.join(here,'../src/recomp_manual.c'),'utf8');
const asm=fs.readFileSync(path.join(workspace,'work/disasm-seeded/asm/text.asm'),'utf8');
const xbe=fs.readFileSync(path.join(workspace,'work/default.xbe'));
const sectionBase=xbe.readUInt32LE(0x120)-xbe.readUInt32LE(0x104);
const sections=Array.from({length:xbe.readUInt32LE(0x11C)},(_,i)=>{
    const p=sectionBase+i*56;return{va:xbe.readUInt32LE(p+4),offset:xbe.readUInt32LE(p+12),size:xbe.readUInt32LE(p+16)};
});
function original(va,size){const s=sections.find(s=>va>=s.va&&va+size<=s.va+s.size);assert(s);return xbe.subarray(s.offset+va-s.va,s.offset+va-s.va+size);}
const ranges=[[0x1022D0,0x10236E],[0x1023E0,0x102419],[0x103F20,0x103F59],
    [0x101220,0x1012B9],[0x104480,0x104510],[0x104510,0x104546]];
const instructions=[...asm.matchAll(/^\s*0x([0-9A-Fa-f]+)[ \t]+([0-9a-f]+)[ \t]+(\w+)[ \t]+(.*?)\r?$/gm)]
    .map(m=>({va:parseInt(m[1],16),bytes:Buffer.from(m[2],'hex')}));
let count=0,bytes=0;
for(const[start,end]of ranges){let next=start;for(const i of instructions.filter(i=>i.va>=start&&i.va<end)){
    assert.equal(i.va,next);assert.deepEqual(original(i.va,i.bytes.length),i.bytes);next+=i.bytes.length;++count;bytes+=i.bytes.length;
}assert.equal(next,end);}
for(const [start]of ranges){const h=start.toString(16).toUpperCase().padStart(8,'0');assert(manual.includes(`if (xbox_va == 0x${h}u) return sub_${h};`));}
// 104480 is byte/call verified here; its special two-vector branch is assigned
// to the root for an independent argument-layout test.
const allBodies=ranges.map(([start])=>{const h=start.toString(16).toUpperCase().padStart(8,'0');const m=source.match(new RegExp(`^void sub_${h}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`,'m'));assert(m);return m[0];});
const bodies=allBodies.filter(body=>!body.startsWith('void sub_00104480')).join('\n\n');
for(const m of allBodies.join('\n').matchAll(/PUSH32\(esp, 0x([0-9A-F]+)u\); sub_([0-9A-F]+)\(\);/g)){
    const ret=parseInt(m[1],16),raw=original(ret-5,5);assert.equal(raw[0],0xE8);assert.equal((ret+raw.readInt32LE(1))>>>0,parseInt(m[2],16));
}
console.log(`PASS: ${count} original instructions match ${bytes} XBE bytes; all direct return PCs and dispatch verified`);
const temporary=fs.mkdtempSync(path.join(os.tmpdir(),'dah-frontend-callbacks-'));
function run(label,fixture,expected){
    const folder=path.join(temporary,label);fs.mkdirSync(folder);fs.writeFileSync(path.join(folder,'frontend_callbacks_fixture.inc'),fixture);
    const exe=path.join(folder,'test.exe');const build=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${folder}`,`/Fe:${exe}`,`/Fo:${path.join(folder,'test.obj')}`,path.join(here,'test_frontend_callbacks.c')],{cwd:folder,encoding:'utf8',timeout:30000});
    assert.equal(build.status,0,`${build.error||''}\n${build.stdout}\n${build.stderr}`);
    const test=spawnSync(exe,[],{cwd:folder,encoding:'utf8',timeout:30000});assert.equal(test.status,expected,`${test.error||''}\n${test.stdout}\n${test.stderr}`);
    console.log(expected?`PASS negative control ${label}: ${test.stderr.trim()}`:test.stdout.trim());
}
run('production',bodies,0);
run('wrong-property-cleanup',bodies.replace('esp += 12u; /* ret 8 */','esp += 8u; /* negative control */'),1);
run('wrong-virtual-slot',bodies.replace('target = MEM32(edx + 4u);','target = MEM32(edx + 8u);'),1);
run('omitted-fpu-pop',bodies.replace('g_fp_top = (g_fp_top + 1u) & 7u;','/* negative control */'),1);
run('wrong-dirty-flag-width',bodies.replaceAll('MEM8(esi + 0x10u) = 1u;','MEM32(esi + 0x10u) = 1u;'),1);
console.log(`TEST_OUTPUT ${temporary}`);
