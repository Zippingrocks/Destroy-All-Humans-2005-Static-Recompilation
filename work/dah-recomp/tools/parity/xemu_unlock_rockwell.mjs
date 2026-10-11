/* Inject the retail UnlockSite key sequence into a stopped DAH profile by
 * calling the XBE's own hash and Progress::AddKey functions. This is parity
 * setup only: it does not queue a level, alter UI selection, or fabricate a
 * loader state. The guest register file and borrowed stack bytes are restored
 * before execution resumes. */
import net from 'node:net';
import {RspClient} from './rsp_client.mjs';

const args=process.argv.slice(2);
const option=(name,fallback)=>args.includes(name)?args[args.indexOf(name)+1]:fallback;
const port=Number(option('--port','1235'));
if(!Number.isInteger(port)||port<1||port>65535)throw new Error('invalid --port');

const keys=[
 'farm','farm.mission.t1','rank.scout.alpha','awareness.nolowlimit',
 'weapon.cortex','ability.jetpack',
 'rockwell','rockwell.mission.m2','weapon.brainextractor','weapon.zapomatic',
 'weapon.analprobe','weapon.mattermove','weapon.abducto','weapon.holobob',
 'weapon.holobobhelper','weapon.hypnoray','weapon.deathray',
 'farm.mission.t1','default'
];

const socket=net.createConnection({host:'127.0.0.1',port});
socket.setNoDelay(true);
await new Promise((resolve,reject)=>{socket.once('connect',resolve);socket.once('error',reject);});
const rsp=new RspClient(socket);
const read=async(address,length)=>{
 const value=await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
 if(!/^[0-9a-f]+$/i.test(value)||value.length!==length*2)throw new Error(`guest read failed at ${address.toString(16)}: ${value}`);
 return Buffer.from(value,'hex');
};
const write=async(address,data)=>{
 for(let offset=0;offset<data.length;offset+=512){
  const part=data.subarray(offset,Math.min(data.length,offset+512));
  if(await rsp.packet(`M${(address+offset).toString(16)},${part.length.toString(16)}:${part.toString('hex')}`)!=='OK')
   throw new Error(`guest write failed at ${(address+offset).toString(16)}`);
 }
};
const setRegisters=async registers=>{
 const reply=await rsp.packet(`G${registers.toString('hex')}`);
 if(reply!=='OK')throw new Error(`register write failed: ${reply}`);
};

let savedRegisters=null,savedStack=null,stackBase=0,breakpoint=false,running=false;
const result={schema:1,source:'xemu-retail-call',port,site:'rockwell',keys:[],
 limitation:'Progression setup only; navigation and loading remain retail UI/controller operations'};
try{
 let supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 let stopped=/^[ST]/.test(supported);
 if(stopped)supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 if(!stopped){
  socket.write(Buffer.from([0x03]));
  const stop=await rsp.nextPacket(10000);
  if(!/^[ST]/.test(stop))throw new Error(`guest did not stop: ${stop}`);
 }
 const code=await read(0xdaca0,5);
 if(code.toString('hex')!=='e85bd6ffff')throw new Error(`unexpected retail loop bytes ${code.toString('hex')}`);
 const backend=(await read(0x25b1d0+0x4a28,4)).readUInt32LE();
 const backendState=(await read(backend+0x10,4)).readUInt32LE();
 const backendName=(await read(backend+0x50c,128)).toString('latin1').split('\0',1)[0].toLowerCase().replaceAll('/','\\');
 const pending=(await read(0x25b1d0+0x4a2c,4)).readUInt32LE();
 const slot=(await read(0x2637c4,4)).readUInt32LE();
 const store=(await read(0x249ae4,4)).readUInt32LE();
 if(backendName!=='blocks\\shell\\main'||backendState!==22||pending)throw new Error('retail shell is not idle');
 if(slot>=3)throw new Error(`no selected profile slot: ${slot.toString(16)}`);
 if(!store)throw new Error('progression store unavailable');
 const counts=await read(store+0x3a50,8);
 if(counts.readUInt32LE()>counts.readUInt32LE(4))throw new Error('invalid progression key table');
 result.before={backend,backendState,backendName,pending,slot,store,count:counts.readUInt32LE(),capacity:counts.readUInt32LE(4)};

 savedRegisters=Buffer.from(await rsp.packet('g'),'hex');
 if(savedRegisters.length<40)throw new Error('short register file');
 const originalEsp=savedRegisters.readUInt32LE(16);
 stackBase=(originalEsp-0x1000)>>>0;
 savedStack=await read(stackBase,0x1000);
 const callEsp=(originalEsp-0xc00)>>>0;
 const scratch=(originalEsp-0x400)>>>0;
 const record=(scratch+0x100)>>>0;
 const returnAddress=0xdaca0;
 if(await rsp.packet(`Z0,${returnAddress.toString(16)},1`)!=='OK')throw new Error('return breakpoint rejected');
 breakpoint=true;

 async function call(address,{ecx=0,edx=0,args=[]}={}){
  const stack=Buffer.alloc(4+args.length*4);
  stack.writeUInt32LE(returnAddress,0);
  args.forEach((value,index)=>stack.writeUInt32LE(value>>>0,4+index*4));
  await write(callEsp,stack);
  const registers=Buffer.from(savedRegisters);
  registers.writeUInt32LE(ecx>>>0,4);
  registers.writeUInt32LE(edx>>>0,8);
  registers.writeUInt32LE(callEsp,16);
  registers.writeUInt32LE(address>>>0,32);
  await setRegisters(registers);
  rsp.resume();running=true;
  const stop=await rsp.nextPacket(10000);running=false;
  if(!/^[ST]/.test(stop))throw new Error(`unexpected call stop: ${stop}`);
  const after=Buffer.from(await rsp.packet('g'),'hex');
  if(after.readUInt32LE(32)!==returnAddress)throw new Error(`call returned to ${after.readUInt32LE(32).toString(16)}`);
  return after.readUInt32LE(0);
 }

 for(const key of keys){
  const text=Buffer.from(`${key}\0`,'ascii');
  await write(scratch,text);
  const hash=await call(0xd54a0,{ecx:scratch,edx:0});
  const entry=Buffer.alloc(8);entry.writeUInt32LE(hash,0);entry[4]=1;
  await write(record,entry);
  const accepted=await call(0x8b230,{ecx:store,args:[record]});
  if(!(accepted&0xff))throw new Error(`Progress::AddKey rejected ${key}`);
  result.keys.push({key,hash:`0x${hash.toString(16).padStart(8,'0')}`,accepted:true});
 }
 const afterCounts=await read(store+0x3a50,8);
 result.after={count:afterCounts.readUInt32LE(),capacity:afterCounts.readUInt32LE(4)};
 result.complete=true;
}finally{
 try{
  if(running){socket.write(Buffer.from([0x03]));await rsp.nextPacket(10000);running=false;}
  if(savedStack)await write(stackBase,savedStack);
  if(savedRegisters)await setRegisters(savedRegisters);
  if(breakpoint)await rsp.packet('z0,daca0,1');
  rsp.resume();
 }catch(error){result.restoreError=error.message;}
 rsp.close();
}
console.log(JSON.stringify(result,null,2));
