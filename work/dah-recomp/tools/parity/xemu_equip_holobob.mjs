/* Equip Holobob through the retail playerCharacter.SetWeapon manager path.
 * Register state and borrowed stack bytes are restored before resuming. */
import net from 'node:net';
import {RspClient} from './rsp_client.mjs';
const args=process.argv.slice(2),option=(n,f)=>args.includes(n)?args[args.indexOf(n)+1]:f;
const port=Number(option('--port','1235'));
const socket=net.createConnection({host:'127.0.0.1',port});socket.setNoDelay(true);
await new Promise((resolve,reject)=>{socket.once('connect',resolve);socket.once('error',reject);});
const rsp=new RspClient(socket);
const read=async(address,length)=>{const value=await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
 if(!/^[0-9a-f]+$/i.test(value)||value.length!==length*2)throw new Error(`guest read failed at ${address.toString(16)}: ${value}`);
 return Buffer.from(value,'hex');};
const write=async(address,data)=>{for(let offset=0;offset<data.length;offset+=512){const part=data.subarray(offset,Math.min(data.length,offset+512));
 if(await rsp.packet(`M${(address+offset).toString(16)},${part.length.toString(16)}:${part.toString('hex')}`)!=='OK')throw new Error('guest write failed');}};
const setRegisters=async r=>{if(await rsp.packet(`G${r.toString('hex')}`)!=='OK')throw new Error('register write failed');};
let savedRegisters=null,savedStack=null,stackBase=0,breakpoint=false,running=false;
const result={schema:1,source:'xemu-retail-call',operation:'equip-holobob'};
try{
 let supported=await rsp.packet('qSupported:multiprocess+;swbreak+');let stopped=/^[ST]/.test(supported);
 if(stopped)supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 if(!stopped){socket.write(Buffer.from([3]));const stop=await rsp.nextPacket(10000);if(!/^[ST]/.test(stop))throw new Error(`guest did not stop: ${stop}`);}
 const backend=(await read(0x25b1d0+0x4a28,4)).readUInt32LE();
 const backendName=(await read(backend+0x50c,128)).toString('latin1').split('\0',1)[0].toLowerCase().replaceAll('/','\\');
 if(backendName!=='blocks\\sites\\rockwell'||(await read(backend+0x10,4)).readUInt32LE()!==22)throw new Error('Rockwell is not ready');
 const system=(await read(0x25fcec,4)).readUInt32LE();
 const player=(await read(system+0x38,4)).readUInt32LE();
 const character=(await read(player+0x38,4)).readUInt32LE();
 const manager=(await read(character+0x138,4)).readUInt32LE();
 if(!manager)throw new Error('weapon manager unavailable');
 const slotsBefore=await read(manager+0x4c,16);
 result.before={backendName,system,player,character,manager,slots:[0,1,2,3].map(i=>slotsBefore.readUInt32LE(i*4))};
 savedRegisters=Buffer.from(await rsp.packet('g'),'hex');
 const originalEsp=savedRegisters.readUInt32LE(16);stackBase=(originalEsp-0x1000)>>>0;
 savedStack=await read(stackBase,0x1000);
 const callEsp=(originalEsp-0xc00)>>>0,scratch=(originalEsp-0x400)>>>0,returnAddress=0xdaca0;
 await write(scratch,Buffer.from('holobob\0','ascii'));
 const stack=Buffer.alloc(16);stack.writeUInt32LE(returnAddress,0);stack.writeUInt32LE(scratch,4);
 stack.writeUInt32LE(0,8);stack.writeUInt32LE(0,12);await write(callEsp,stack);
 if(await rsp.packet('Z0,daca0,1')!=='OK')throw new Error('return breakpoint rejected');breakpoint=true;
 const callRegisters=Buffer.from(savedRegisters);callRegisters.writeUInt32LE(manager,4);
 callRegisters.writeUInt32LE(callEsp,16);callRegisters.writeUInt32LE(0x9df10,32);await setRegisters(callRegisters);
 rsp.resume();running=true;const stop=await rsp.nextPacket(10000);running=false;
 if(!/^[ST]/.test(stop))throw new Error(`unexpected call stop: ${stop}`);
 const afterRegisters=Buffer.from(await rsp.packet('g'),'hex');
 if(afterRegisters.readUInt32LE(32)!==returnAddress)throw new Error('SetWeapon returned unexpectedly');
 const slotsAfter=await read(manager+0x4c,16);
 result.after={accepted:Boolean(afterRegisters.readUInt32LE(0)&0xff),slots:[0,1,2,3].map(i=>slotsAfter.readUInt32LE(i*4))};
 result.complete=result.after.accepted&&result.after.slots[0]!==0&&result.after.slots[3]===result.after.slots[0];
 if(!result.complete)throw new Error('retail weapon manager did not activate Holobob');
}finally{
 try{if(running){socket.write(Buffer.from([3]));await rsp.nextPacket(10000);}
  if(savedStack)await write(stackBase,savedStack);if(savedRegisters)await setRegisters(savedRegisters);
  if(breakpoint)await rsp.packet('z0,daca0,1');rsp.resume();}catch(error){result.restoreError=error.message;}
 rsp.close();
}
console.log(JSON.stringify(result,null,2));
