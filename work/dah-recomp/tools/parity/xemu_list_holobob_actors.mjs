/* Read-only inventory of retail Rockwell character objects.  The guest is
 * interrupted only for a coherent RAM read and is always resumed. */
import net from 'node:net';
import {RspClient} from './rsp_client.mjs';
const args=process.argv.slice(2),option=(n,f)=>args.includes(n)?args[args.indexOf(n)+1]:f;
const port=Number(option('--port','1235'));
const socket=net.createConnection({host:'127.0.0.1',port});socket.setNoDelay(true);
await new Promise((resolve,reject)=>{socket.once('connect',resolve);socket.once('error',reject);});
const rsp=new RspClient(socket);
const read=async(address,length)=>{const chunks=[];for(let offset=0;offset<length;offset+=0x400){
 const size=Math.min(0x400,length-offset),reply=await rsp.packet(`m${(address+offset).toString(16)},${size.toString(16)}`,30000);
 if(!/^[0-9a-f]+$/i.test(reply)||reply.length!==size*2)throw new Error(`read failed at ${(address+offset).toString(16)}`);
 chunks.push(Buffer.from(reply,'hex'));}return Buffer.concat(chunks);};
let halted=false;
try{
 socket.write(Buffer.from([3]));const stop=await rsp.nextPacket(30000);
 if(!/^[ST]/.test(stop))throw new Error(`guest did not stop: ${stop}`);halted=true;
 // Retail Xbox object pointers use the 0x80000000 cached virtual alias.  The
 // recomp strips that alias and therefore reports the corresponding 0x01-
 // 0x02xxxxxx addresses in its diagnostics.
 const base=0x81800000,size=0x00c00000,ram=await read(base,size),actors=[];
 for(let offset=0;offset<=size-0x2c;offset+=4){
  if(ram.readUInt32LE(offset)!==0x00226c60)continue;
  const object=base+offset,meta=ram.readUInt32LE(offset+0x1c),transform=ram.readUInt32LE(offset+0x28);
  let position=null;
  if(transform>=base&&transform+0x38<base+size){const p=transform-base+0x2c;position=[ram.readFloatLE(p),ram.readFloatLE(p+4),ram.readFloatLE(p+8)];}
  actors.push({object,meta,holobobAllowed:meta>=base&&meta+0x51c<base+size?ram[meta-base+0x51b]:null,transform,position});
 }
 for(const actor of actors){
  if(actor.holobobAllowed===null&&actor.meta>=0x80010000&&actor.meta<0x84000000)
   actor.holobobAllowed=(await read(actor.meta+0x51b,1))[0];
 }
 const system=(await read(0x25fcec,4)).readUInt32LE(),player=(await read(system+0x38,4)).readUInt32LE();
 const character=(await read(player+0x38,4)).readUInt32LE(),positionBytes=await read(character+0x14c,12);
 const playerPosition=[positionBytes.readFloatLE(0),positionBytes.readFloatLE(4),positionBytes.readFloatLE(8)];
 console.log(JSON.stringify({schema:1,source:'xemu',system,player,character,playerPosition,actors},null,2));
}finally{if(halted)rsp.resume();rsp.close();}
