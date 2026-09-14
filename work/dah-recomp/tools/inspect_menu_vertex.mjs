/* Decode the actual rejected program using field positions from the local
 * xemu reference. Read-only; no generated pixels or game execution. */
import fs from 'node:fs';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const here=path.dirname(fileURLToPath(import.meta.url));
const pid=process.argv[2] || '16548';
const submission=Number(process.argv[3] || 771);
const log=fs.readFileSync(path.join(here,`../build-internal/recomp-internal-${pid}.log`),'utf8');
const marker=`[DAH-REJECTED-STATE] submit=${submission}`;
const start=log.indexOf(marker);
if(start<0) throw new Error(`submission ${submission} not found in PID ${pid} log`);
const next=log.indexOf('[DAH-REJECTED-STATE] submit=',start+marker.length);
const segment=log.slice(start,next<0?log.length:next);
const program=[...segment.matchAll(/\[DAH-REJECTED-SHADER\] instruction=\d+ raw=([0-9A-F,]+)/g)].map(m=>m[1].split(',').map(n=>parseInt(n,16)));
const ref=fs.readFileSync(path.join(here,'../../../Repos/xemu/hw/xbox/nv2a/pgraph/glsl/vsh-prog.c'),'utf8');
const fields=Object.fromEntries([...ref.matchAll(/\{\s*(FLD_\w+),\s*(\d+),\s*(\d+),\s*(\d+)\s*\}/g)].map(m=>[m[1],m.slice(2).map(Number)]));
const get=(p,n)=>{const[w,s,b]=fields['FLD_'+n];return (p[w]>>>s)&((1<<b)-1);};
const mac=['NOP','MOV','MUL','ADD','MAD','DP3','DPH','DP4','DST','MIN','MAX','SLT','SGE','ARL'];
const ilu=['NOP','MOV','RCP','RCC','RSQ','EXP','LOG','LIT'];
const sw=['X','Y','Z','W'];
const mask=n=>sw.filter((_,i)=>n&(8>>i)).join('').toLowerCase();
function src(p,n){const m=get(p,n+'_MUX'),r=n==='C'?(get(p,'C_R_HIGH')<<2)|get(p,'C_R_LOW'):get(p,n+'_R');return (get(p,n+'_NEG')?'-':'')+(m===1?'R'+r:m===2?'v'+get(p,'V'):m===3?'c'+get(p,'CONST'):'?')+'.'+sw.map(s=>'xyzw'[get(p,n+'_SWZ_'+s)]).join('');}
for(let i=0;i<program.length;i++) {const p=program[i];console.log(i,mac[get(p,'MAC')],src(p,'A'),src(p,'B'),src(p,'C'),'MAC:R'+get(p,'OUT_R')+'.'+mask(get(p,'OUT_MAC_MASK')),ilu[get(p,'ILU')],'ILU:R'+get(p,'OUT_R')+'.'+mask(get(p,'OUT_ILU_MASK')),'OUT'+get(p,'OUT_ORB')+':'+get(p,'OUT_ADDRESS')+'.'+mask(get(p,'OUT_O_MASK')),'MUX',get(p,'OUT_MUX'),'REL',get(p,'A0X'));}
