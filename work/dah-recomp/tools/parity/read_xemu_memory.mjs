#!/usr/bin/env node
/* Read a bounded guest-memory range from a stopped private xemu GDB server. */
import fs from 'node:fs';
import net from 'node:net';
import {RspClient} from './rsp_client.mjs';

const args=process.argv.slice(2);
const option=(name,fallback)=>args.includes(name)?args[args.indexOf(name)+1]:fallback;
const port=Number(option('--port','1235'));
const address=Number(option('--address'));
const length=Number(option('--length'));
const out=option('--out');
if(!Number.isInteger(port)||port<1||port>65535)throw new Error('invalid --port');
if(!Number.isSafeInteger(address)||address<0)throw new Error('invalid --address');
if(!Number.isSafeInteger(length)||length<1||length>0x10000)throw new Error('invalid --length');
if(!out||fs.existsSync(out))throw new Error('new --out path is required');

const socket=net.createConnection({host:'127.0.0.1',port});
await new Promise((resolve,reject)=>{socket.once('connect',resolve);socket.once('error',reject);});
const rsp=new RspClient(socket);
try{
 let supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 if(/^[ST]/.test(supported))supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 const value=await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
 if(!/^[0-9a-f]+$/i.test(value)||value.length!==length*2)throw new Error(`guest read failed: ${value}`);
 fs.writeFileSync(out,Buffer.from(value,'hex'),{flag:'wx'});
 console.log(JSON.stringify({schema:1,source:'xemu',port,address,length,out,supported}));
}finally{
 rsp.close();
}
