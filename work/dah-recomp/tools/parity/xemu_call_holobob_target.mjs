/* Call the retail Holobob target selector in a stopped xemu guest.  The
 * debugger register set and borrowed stack page are restored before resume. */
import net from 'node:net';
import {RspClient} from './rsp_client.mjs';
const args=process.argv.slice(2),option=(n,f)=>args.includes(n)?args[args.indexOf(n)+1]:f;
const port=Number(option('--port','1235'));
const socket=net.createConnection({host:'127.0.0.1',port});socket.setNoDelay(true);
await new Promise((resolve,reject)=>{socket.once('connect',resolve);socket.once('error',reject);});
const rsp=new RspClient(socket);
let stage='connected';
const mark=value=>{stage=value;console.error(`[xemu-holobob-target] ${value}`);};
const packet=(payload,timeout=30000)=>rsp.packet(payload,timeout);
const read=async(address,length)=>{const value=await packet(`m${address.toString(16)},${length.toString(16)}`);
 if(!/^[0-9a-f]+$/i.test(value)||value.length!==length*2)throw new Error(`guest read failed at ${address.toString(16)}: ${value}`);
 return Buffer.from(value,'hex');};
const write=async(address,data)=>{for(let offset=0;offset<data.length;offset+=512){const part=data.subarray(offset,Math.min(data.length,offset+512));
 if(await packet(`M${(address+offset).toString(16)},${part.length.toString(16)}:${part.toString('hex')}`)!=='OK')throw new Error('guest write failed');}};
const u32=async address=>(await read(address,4)).readUInt32LE();
const setRegisters=async r=>{if(await packet(`G${r.toString('hex')}`)!=='OK')throw new Error('register write failed');};
let savedRegisters=null,savedStack=null,stackBase=0,breakpoints=[],running=false;
const result={schema:1,source:'xemu-retail-call',operation:'holobob-target'};
try{
 mark('halting guest');
 // This diagnostic is only invoked against the normally running comparison
 // VM.  Interrupt it directly so an asynchronous stop reply cannot be
 // mistaken for qSupported and leave a stale feature packet in the queue.
 socket.write(Buffer.from([3]));
 const initialStop=await rsp.nextPacket(30000);
 if(!/^[ST]/.test(initialStop))throw new Error(`guest did not stop: ${initialStop}`);
 mark('reading Rockwell context');
 const backend=await u32(0x25b1d0+0x4a28),backendName=(await read(backend+0x50c,128)).toString('latin1').split('\0',1)[0].toLowerCase().replaceAll('/','\\');
 if(backendName!=='blocks\\sites\\rockwell'||await u32(backend+0x10)!==22)throw new Error('Rockwell is not ready');
 const system=await u32(0x25fcec),player=await u32(system+0x38),character=await u32(player+0x38),manager=await u32(character+0x138);
 const slots=await read(manager+0x4c,16);let holobob=0;
 for(let i=0;i<4;i++){const weapon=slots.readUInt32LE(i*4);if(weapon&&await u32(weapon)===0x22fd50)holobob=weapon;}
 if(!holobob)throw new Error('Holobob weapon object unavailable');
 result.context={backendName,system,player,character,manager,holobob,
  holobobState:await u32(holobob+0x44),holobobActive:(await read(holobob+0x34,1))[0],
  holobobTarget:await u32(holobob+0x178),holobobToken:await u32(holobob+0x17c),
  focus:[await u32(manager+0x144),await u32(manager+0x148),await u32(manager+0x14c)],focusHandle:await u32(manager+0x154)};
 mark('saving registers and stack');
 savedRegisters=Buffer.from(await packet('g'),'hex');const originalEsp=savedRegisters.readUInt32LE(16);stackBase=(originalEsp-0x1000)>>>0;
 savedStack=await read(stackBase,0x1000);const callEsp=(originalEsp-0xc00)>>>0,returnAddress=0xdaca0;
 const stack=Buffer.alloc(16);stack.writeUInt32LE(returnAddress,0);await write(callEsp,stack);
 mark('installing selector-exit breakpoints');
 for(const address of [0xa30a8,0xa31d1,0xa33a9,0x183f40]){if(await packet(`Z0,${address.toString(16)},1`)!=='OK')throw new Error('selector breakpoint rejected');breakpoints.push(address);}
 const callRegisters=Buffer.from(savedRegisters);callRegisters.writeUInt32LE(holobob,4);callRegisters.writeUInt32LE(callEsp,16);callRegisters.writeUInt32LE(0xa3000,32);await setRegisters(callRegisters);
 mark('running retail selector');
 rsp.resume();running=true;let after=null,stopAddress=0;result.spatialDispatches=[];
 for(let stops=0;stops<64;stops++){
  const stop=await rsp.nextPacket(60000);running=false;if(!/^[ST]/.test(stop))throw new Error(`unexpected call stop: ${stop}`);
  after=Buffer.from(await packet('g'),'hex');stopAddress=after.readUInt32LE(32);
  if(stopAddress===0xa30a8||stopAddress===0xa33a9)break;
  if(stopAddress===0xa31d1){
   const esp=after.readUInt32LE(16),stack=await read(esp,0x80),f=offset=>stack.readFloatLE(offset);
   result.geometry={origin:[f(0x30),f(0x34),f(0x38)],forward:[f(0x3c),f(0x40),f(0x44)],
    spread:f(0x4c),step:f(0x10),limit:f(0x14)};
   if(await packet('z0,a31d1,1')!=='OK')throw new Error('geometry breakpoint removal failed');
   rsp.resume();running=true;continue;
  }
  if(stopAddress!==0x183f40)throw new Error(`target selector stopped unexpectedly at ${stopAddress.toString(16)}`);
  const core=after.readUInt32LE(4),context=await u32(core+8);
  result.spatialDispatches.push({core,parts:await u32(core+0xc4),partList:await u32(core+0xc0),
   context,contextCC:await u32(context+0xcc),mode:await u32(core+0x54)});
  if(await packet('z0,183f40,1')!=='OK')throw new Error('spatial breakpoint removal failed');
  rsp.step();running=true;const stepped=await rsp.nextPacket(30000);running=false;if(!/^[ST]/.test(stepped))throw new Error(`unexpected spatial step: ${stepped}`);
  if(await packet('Z0,183f40,1')!=='OK')throw new Error('spatial breakpoint reinsertion failed');
  rsp.resume();running=true;
 }
 running=false;
 mark('reading selector result');
 if(!after)throw new Error('selector produced no stop');
 if(stopAddress!==0xa30a8&&stopAddress!==0xa33a9)throw new Error(`target selector stopped unexpectedly at ${stopAddress.toString(16)}`);
 const target=stopAddress===0xa30a8?after.readUInt32LE(20):after.readUInt32LE(24);result.target=target;result.selectorExit=`0x${stopAddress.toString(16)}`;
 if(target){const meta=await u32(target+0x1c);result.targetVtable=await u32(target);result.targetMeta=meta;result.holobobAllowed=Boolean((await read(meta+0x51b,1))[0]);}
 result.complete=true;
}finally{
 try{mark(`restoring guest after ${stage}`);if(running){socket.write(Buffer.from([3]));await rsp.nextPacket(30000);}if(savedStack)await write(stackBase,savedStack);if(savedRegisters)await setRegisters(savedRegisters);for(const address of breakpoints)await packet(`z0,${address.toString(16)},1`);rsp.resume();mark('guest resumed');}catch(error){result.restoreError=error.message;}
 rsp.close();
}
console.log(JSON.stringify(result,null,2));
