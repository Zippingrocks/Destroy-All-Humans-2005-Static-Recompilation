// Print a narrowly scoped apply_patch; never rewrite the generated file wholesale.
import fs from 'node:fs';
import path from 'node:path';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
const here=path.dirname(fileURLToPath(import.meta.url));
const file=path.resolve(here,'../src/recomp/gen/recomp_0019.c');
const source=fs.readFileSync(file,'utf8');
const asm=fs.readFileSync(path.resolve(here,'../../disasm-seeded/asm/D3D.asm'),'utf8');
const norm=s=>s.toLowerCase().replace(/\s+/g,'');
const changes=[];
for(const [start,end] of [[0x1d9ed0,0x1d9f72],[0x1d9f80,0x1da050]]) {
 const name=start.toString(16).toUpperCase().padStart(8,'0');
 const old=source.match(new RegExp(`^void sub_${name}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`,'m'))[0];
 let body=old;
 const ins=[...asm.matchAll(/^\s*0x([0-9A-F]+)\s+[0-9a-f]+\s+movq\s+(.*?)\s*\r?$/gm)].filter(m=>parseInt(m[1],16)>=start&&parseInt(m[1],16)<end);
 assert.equal(ins.length,start===0x1d9ed0?24:16);
 for(const m of ins) {
   const [dst,src]=m[2].split(/,\s*/);let code;
   if(/^mm\d$/.test(dst)) {const a=src.match(/\[(.*)\]/)[1];code=`${dst} = (uint64_t)MEM32((uint32_t)(${a})) | ((uint64_t)MEM32((uint32_t)(${a}) + 4u) << 32);`;}
   else {const a=dst.match(/\[(.*)\]/)[1];code=`MEM32((uint32_t)(${a})) = (uint32_t)${src}; MEM32((uint32_t)(${a}) + 4u) = (uint32_t)(${src} >> 32);`;}
   const comments=[...body.matchAll(/\/\* SSE: (.*?) \*\//g)];
   const found=comments.find(c=>norm(c[1])===norm('movq '+m[2]));assert(found,`${name} ${m[1]}`);
   body=body.replace(found[0],`${code} /* MMX 0x${m[1]}: movq ${m[2]} */`);
 }
 changes.push('@@\n'+old.replace(/\r/g,'').split('\n').map(l=>'-'+l).join('\n')+'\n'+body.replace(/\r/g,'').split('\n').map(l=>'+'+l).join('\n'));
}
console.log('*** Begin Patch\n*** Update File: '+file+'\n'+changes.join('\n')+'\n*** End Patch');
