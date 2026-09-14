import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const root=path.resolve(here,'../../..');
const xbe=fs.readFileSync(path.join(root,'work/default.xbe'));
const base=xbe.readUInt32LE(0x104),table=xbe.readUInt32LE(0x120)-base;
const sections=Array.from({length:xbe.readUInt32LE(0x11c)},(_,i)=>{
 const p=table+i*56;return {va:xbe.readUInt32LE(p+4),offset:xbe.readUInt32LE(p+12),size:xbe.readUInt32LE(p+16)};
});
const bytes=(va,n)=>{const s=sections.find(s=>va>=s.va&&va+n<=s.va+s.size);assert(s);return xbe.subarray(s.offset+va-s.va,s.offset+va-s.va+n);};
const asm=fs.readFileSync(path.join(root,'work/disasm-seeded/asm/D3D.asm'),'utf8');
let next=0x1e0420,count=0;
for(const m of asm.matchAll(/^\s*0x([0-9a-f]+)\s+([0-9a-f]+)\s+/gmi)) {
 const va=parseInt(m[1],16);if(va<0x1e0420||va>=0x1e04db)continue;
 const b=Buffer.from(m[2],'hex');assert.equal(va,next);assert.deepEqual(bytes(va,b.length),b);next+=b.length;count++;
}
assert.equal(next,0x1e04db);
const gen=path.join(here,'../src/recomp/gen');
const main=fs.readFileSync(path.join(gen,'recomp_0019.c'),'utf8');
const stubs=fs.readFileSync(path.join(gen,'recomp_stubs_unresolved.c'),'utf8');
const add=fs.readFileSync(path.join(gen,'recomp_d3d_format_callbacks.c'),'utf8');
const entries=[['001E0436',8,'001E043B'],['001E045D',8,'001E0462'],['001E0489',4,'001E043B'],['001E0497',3,'001E043B'],['001E049E',3,'001E0462'],['001E04AC',1,'001E0462'],['001E04B3',9,'001E0462'],['001E04BA',10,'001E0462']];
const body=(s,n)=>{const m=s.match(new RegExp(`^void sub_${n}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`,'m'));assert(m,n);return m[0];};
const norm=s=>s.replace(/\/\*[\s\S]*?\*\//g,'').replace(/\s/g,'');
for(const [entry,value,tail]of entries) {
 const va=parseInt(entry,16);assert.equal(bytes(va,5)[0],0xb8);assert.equal(bytes(va,5).readUInt32LE(1),value);
 if(va+5!==parseInt(tail,16)){assert.equal(bytes(va+5,2)[0],0xeb);assert.equal(va+7+bytes(va+5,2).readInt8(1),parseInt(tail,16));}
 assert.equal(norm(body(add,entry)),`voidsub_${entry}(void){eax=${value};sub_${tail}();}`);
}
assert.equal(norm(body(add,'001E04C1')),'voidsub_001E04C1(void){eax|=0x20;sub_001E04C4();}');
assert.equal(norm(body(add,'001E04D5')),'voidsub_001E04D5(void){eax|=0x10;esp+=12;}');
const names=['001E0420','001E043B','001E0462','001E0467','001E0490','001E04A5','001E04C4','001E04C7',...entries.map(e=>e[0]),'001E04C1','001E04D5'];
const fixture=names.map(n=>`void sub_${n}(void);`).join('\n')+'\n'+names.map(n=>body(main+'\n'+stubs+'\n'+add,n)).join('\n');
const manual=fs.readFileSync(path.join(here,'../src/recomp_manual.c'),'utf8');
for(const n of [...entries.map(e=>e[0]),'001E04C1','001E04C4','001E04D5']) assert(manual.includes(`if (xbox_va == 0x${n}u) return sub_${n};`));
console.log(`PASS: ${count} instructions / ${next-0x1e0420} original XBE bytes; all restored arms and dispatch entries verified`);
const temp=fs.mkdtempSync(path.join(os.tmpdir(),'dah-format-test-'));
for(const [label,source,status]of [['current',fixture,0],['wrong-ret',fixture.replaceAll('g_esp += 12;','g_esp += 4;'),1],['omitted-linear',fixture.replace('eax = eax | 0x100;','eax = eax | 0;'),1],['wrong-format',fixture.replace('eax = 8; /* 001E045D','eax = 4; /* 001E045D'),1]]) {
 const dir=path.join(temp,label);fs.mkdirSync(dir);fs.writeFileSync(path.join(dir,'d3d_format_fixture.inc'),source);
 fs.writeFileSync(path.join(dir,'tables.bin'),Buffer.concat([bytes(0x1e04dc,256),bytes(0x1e64b0,256)]));
 const exe=path.join(dir,'test.exe');
 const c=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${dir}`,`/Fe:${exe}`,`/Fo:${path.join(dir,'test.obj')}`,path.join(here,'test_d3d_format_callbacks.c')],{cwd:dir,encoding:'utf8',timeout:30000});
 assert.equal(c.status,0,c.stdout+c.stderr);
 const r=spawnSync(exe,[],{cwd:dir,encoding:'utf8',timeout:30000});assert.equal(r.status,status,r.stdout+r.stderr);
 console.log(label==='current'?r.stdout.trim():`PASS: rejected ${label}`);
}
