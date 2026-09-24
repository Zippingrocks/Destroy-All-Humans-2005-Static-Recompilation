const fs=require('fs'),path=require('path'),os=require('os'),{spawnSync}=require('child_process');
const root=path.resolve(__dirname,'../../..');
const s=fs.readFileSync(root+'/Repos/xboxrecomp-main/src/nv2a/nv2a_pgraph_d3d11.c','utf8');const a=s.indexOf('static void fetch_attr_float4'),b=s.indexOf('\n}',a)+2;
const c=`#include <stdint.h>\n#include <string.h>\n#include <math.h>\n#include <stdio.h>\n`+s.slice(a,b)+`
#define CHECK(x) do{if(!(x)){fprintf(stderr,"FAIL %d\\n",__LINE__);return 1;}}while(0)
int main(void){float o[4];uint8_t color[8]={0,0,255,64,255,0,0,255};fetch_attr_float4(color,4,0,0,4,o);CHECK(o[0]==1&&o[1]==0&&o[2]==0&&o[3]==64/255.0f);fetch_attr_float4(color,4,1,0,4,o);CHECK(o[0]==0&&o[1]==0&&o[2]==1&&o[3]==1);for(int i=-32768;i<=32767;++i){int16_t n=(int16_t)i;fetch_attr_float4((const uint8_t*)&n,2,0,1,1,o);float expected=i==-32768?-1.0f:(float)i/32767.0f;CHECK(o[0]==expected);}uint8_t rgb[]={17,93,201,0,255,64};fetch_attr_float4(rgb,3,1,4,3,o);CHECK(o[0]==0&&o[1]==1&&o[2]==64/255.0f);float values[]={1,2,3,4,5,6,7,8};fetch_attr_float4((const uint8_t*)values,16,1,2,4,o);CHECK(o[0]==5&&o[3]==8);puts("PASS: BGRA red/blue and stride, all 65536 signed-normalized values, float stride");return 0;}
`;const dir=fs.mkdtempSync(path.join(os.tmpdir(),'dah-attr-test-'));fs.writeFileSync(dir+'/test.c',c);let r=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11','test.c','/Fe:test.exe'],{cwd:dir,encoding:'utf8',timeout:120000});if(r.status!==0)throw Error(r.stdout+r.stderr);r=spawnSync(dir+'/test.exe',[],{encoding:'utf8',timeout:30000});console.log(r.stdout,r.stderr);process.exit(r.status);


