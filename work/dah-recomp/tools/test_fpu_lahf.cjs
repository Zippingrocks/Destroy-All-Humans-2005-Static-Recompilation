const fs=require('fs'),path=require('path'),os=require('os'),cp=require('child_process'),assert=require('assert/strict');
const root=String.raw`D:\Black Ops 3 Builds (Organize)\Workspace\Destroy All Huamans! 2005 Recomp`;
const source=fs.readFileSync(root+'/work/dah-recomp/src/recomp/gen/recomp_0009.c','utf8');
const xbe=fs.readFileSync(root+'/work/default.xbe');
const base=xbe.readUInt32LE(0x104),table=xbe.readUInt32LE(0x120)-base;
for(const va of [0xd5818,0xd7ba8]){
 let found=false;
 for(let i=0;i<xbe.readUInt32LE(0x11c);i++){
  const p=table+i*56,start=xbe.readUInt32LE(p+4),size=xbe.readUInt32LE(p+16);
  if(va>=start&&va+10<=start+size){const off=xbe.readUInt32LE(p+12)+va-start;assert.equal(xbe.subarray(off,off+10).toString('hex'),'dfe9ddd89ff6c4447b10');found=true;}
 }assert(found);
}
const statements=['000D581C','000D7BAC'].map(id=>{const m=source.match(new RegExp('    SET_HI8\\(eax, [^\\r\\n]+ /\\* FUCOMIP/LAHF 0x'+id+' \\*/'));assert(m);return m[0];});
const dir=fs.mkdtempSync(path.join(os.tmpdir(),'dah-x87-flags-'));
fs.writeFileSync(dir+'/oracle.asm',`.code\nnative_flags PROC\n movsd qword ptr [rsp+8],xmm0\n movsd qword ptr [rsp+16],xmm1\n fld qword ptr [rsp+16]\n fld qword ptr [rsp+8]\n fucomip st,st(1)\n fstp st(0)\n lahf\n movzx eax,ah\n ret\nnative_flags ENDP\nEND\n`);
function run(exe,args){let r=cp.spawnSync(exe,args,{cwd:dir,encoding:'utf8'});assert.equal(r.status,0,r.stdout+r.stderr);return r.stdout;}
run('ml64.exe',['/nologo','/c','/Fooracle.obj','oracle.asm']);
let c=`#include <stdint.h>\n#include <stdio.h>\n#include <math.h>\n#include <string.h>\nextern unsigned native_flags(double,double);\n#define SET_HI8(v,x) ((v)=((v)&0xffff00ffu)|(((uint32_t)(x)&255u)<<8))\n`;
statements.forEach((s,i)=>c+=`static uint32_t site${i}(double a,double b,uint32_t eax){int g_fp_cmp=(isnan(a)||isnan(b))?2:a<b?-1:a>b?1:0;\n${s}\nreturn eax;}\n`);
c+=`int main(void){uint32_t state=12345;double edge[]={0.,-0.,1.,-1.,INFINITY,-INFINITY,NAN,1e-300,-1e-300,1e300,-1e300};unsigned cases=0;for(unsigned i=0;i<100121;i++){double a,b;if(i<121){a=edge[i/11];b=edge[i%11];}else{uint64_t u=0;for(unsigned j=0;j<2;j++){state=state*1664525u+1013904223u;u=(u<<32)|state;}memcpy(&a,&u,8);for(unsigned j=0;j<2;j++){state=state*1664525u+1013904223u;u=(u<<32)|state;}memcpy(&b,&u,8);}unsigned f=native_flags(a,b);uint32_t initial=state,expected=(initial&0xffff00ffu)|(f<<8);if(site0(a,b,initial)!=expected||site1(a,b,initial)!=expected){fprintf(stderr,"Mismatch at %u\\n",i);return 1;}cases+=2;}printf("PASS: %u original rotation comparison cases against native x87 FUCOMIP/LAHF\\n",cases);return 0;}\n`;
fs.writeFileSync(dir+'/test.c',c);run('cl.exe',['/nologo','/O2','/std:c11','test.c','oracle.obj','/Fe:test.exe']);console.log(run(dir+'/test.exe',[]));
fs.writeFileSync(dir+'/negative.c',c.replace(statements[0],'/* missing LAHF */'));run('cl.exe',['/nologo','/O2','/std:c11','negative.c','oracle.obj','/Fe:negative.exe']);assert.equal(cp.spawnSync(dir+'/negative.exe',[],{cwd:dir}).status,1);console.log('PASS: original missing-flags negative control rejected; original XBE bytes verified');
