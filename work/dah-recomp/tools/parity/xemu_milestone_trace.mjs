#!/usr/bin/env node
import net from "node:net";
import fs from "node:fs";
import { performance } from "node:perf_hooks";

const args = process.argv.slice(2);
function option(name, fallback) {
  const index = args.indexOf(name);
  return index >= 0 ? args[index + 1] : fallback;
}
const host = option("--host", "127.0.0.1");
const gdbPort = Number(option("--gdb-port", "1235"));
const qmpPort = Number(option("--qmp-port", "4445"));
const seconds = Number(option("--seconds", "45"));
const outPath = option("--out", null);
if (!outPath) throw new Error("--out FILE is required");
if (!Number.isFinite(seconds) || seconds < 1 || seconds > 600) throw new Error("invalid --seconds");

const milestones = new Map([
  [0x00123180, { name: "movie_open", repeat: 12 }],
  [0x00122ca0, { name: "movie_close", repeat: 12 }]
]);

function checksum(payload) {
  let value = 0;
  for (const byte of Buffer.from(payload, "ascii")) value = (value + byte) & 0xff;
  return value.toString(16).padStart(2, "0");
}

class Rsp {
  constructor(socket) {
    this.socket = socket;
    this.buffer = Buffer.alloc(0);
    this.waiters = [];
    socket.on("data", data => { this.buffer = Buffer.concat([this.buffer, data]); this.pump(); });
  }
  pump() {
    for (;;) {
      while (this.buffer.length && (this.buffer[0] === 0x2b || this.buffer[0] === 0x2d)) this.buffer = this.buffer.subarray(1);
      const start = this.buffer.indexOf(0x24);
      if (start < 0) return;
      if (start) this.buffer = this.buffer.subarray(start);
      const end = this.buffer.indexOf(0x23, 1);
      if (end < 0 || this.buffer.length < end + 3) return;
      const payload = this.buffer.subarray(1, end).toString("ascii");
      const sum = this.buffer.subarray(end + 1, end + 3).toString("ascii").toLowerCase();
      this.buffer = this.buffer.subarray(end + 3);
      this.socket.write(sum === checksum(payload) ? "+" : "-");
      if (sum !== checksum(payload)) continue;
      const waiter = this.waiters.shift();
      if (waiter) waiter.resolve(payload);
    }
  }
  next(timeout = 10000) {
    return new Promise((resolve, reject) => {
      const entry = { resolve, reject };
      const timer = setTimeout(() => {
        const index = this.waiters.indexOf(entry);
        if (index >= 0) this.waiters.splice(index, 1);
        reject(new Error("RSP timeout"));
      }, timeout);
      entry.resolve = value => { clearTimeout(timer); resolve(value); };
      this.waiters.push(entry);
      this.pump();
    });
  }
  async packet(payload, timeout = 10000) {
    this.socket.write(`$${payload}#${checksum(payload)}`);
    return await this.next(timeout);
  }
  continue() {
    const payload = "c";
    this.socket.write(`$${payload}#${checksum(payload)}`);
  }
  step() {
    const payload = "s";
    this.socket.write(`$${payload}#${checksum(payload)}`);
  }
  interrupt() { this.socket.write(Buffer.from([3])); }
  close() { this.socket.destroy(); }
}

function connectRsp() {
  return new Promise((resolve, reject) => {
    const socket = net.createConnection({ host, port: gdbPort });
    socket.setNoDelay(true);
    socket.once("connect", () => resolve(new Rsp(socket)));
    socket.once("error", reject);
  });
}

async function readMemory(rsp, address, length) {
  const reply = await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);
  if (reply.startsWith("E")) throw new Error(`memory ${address.toString(16)}: ${reply}`);
  return Buffer.from(reply, "hex");
}

async function readCString(rsp, address, limit = 260) {
  if (address < 0x10000) return null;
  const bytes = await readMemory(rsp, address, limit);
  const end = bytes.indexOf(0);
  return bytes.subarray(0, end < 0 ? bytes.length : end).toString("latin1");
}

function decodeRegisters(hex) {
  const data = Buffer.from(hex, "hex");
  const names = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "eip", "eflags"];
  const result = {};
  names.forEach((name, index) => result[name] = data.readUInt32LE(index * 4));
  return result;
}

async function qmpCommand(execute) {
  const socket = net.createConnection({ host, port: qmpPort });
  socket.setEncoding("utf8");
  let buffer = "";
  const queue = [];
  const waiters = [];
  socket.on("data", chunk => {
    buffer += chunk;
    for (;;) {
      const end = buffer.indexOf("\n");
      if (end < 0) break;
      const line = buffer.slice(0, end).trim();
      buffer = buffer.slice(end + 1);
      if (!line) continue;
      const value = JSON.parse(line);
      if (value.event) continue;
      const waiter = waiters.shift();
      if (waiter) waiter(value); else queue.push(value);
    }
  });
  const next = () => queue.length ? Promise.resolve(queue.shift()) : new Promise(resolve => waiters.push(resolve));
  await new Promise((resolve, reject) => { socket.once("connect", resolve); socket.once("error", reject); });
  await next();
  socket.write(`${JSON.stringify({ execute: "qmp_capabilities" })}\r\n`);
  await next();
  socket.write(`${JSON.stringify({ execute })}\r\n`);
  const reply = await next();
  socket.destroy();
  if (reply.error) throw new Error(`QMP ${execute}: ${reply.error.desc}`);
}

const trace = {
  schema: 1,
  source: "xemu-retail",
  xbeSha256: "B9491B30EAEE82AF6C805D9B0036EC1119059B0660A0923803EBDB6219FA02EB",
  startedAt: new Date().toISOString(),
  durationLimitSeconds: seconds,
  milestones: []
};

let rsp;
let running = false;
try {
  rsp = await connectRsp();
  let supported = await rsp.packet("qSupported:multiprocess+;hwbreak+");
  if (/^[ST]/.test(supported)) supported = await rsp.packet("qSupported:multiprocess+;hwbreak+");
  // Xbox reset preserves much of RAM, so readability or a code hash alone can
  // mistake stale bytes for a freshly loaded XBE. Plant a disposable sentinel
  // in DAH BSS before reset. The retail loader must zero/replace it before any
  // breakpoint is armed; otherwise this run aborts before executing the game.
  const sentinelAddress = 0x0028681c;
  const sentinel = 0xdec0adde;
  const sentinelBytes = Buffer.alloc(4);
  sentinelBytes.writeUInt32LE(sentinel);
  const writeReply = await rsp.packet(`M${sentinelAddress.toString(16)},4:${sentinelBytes.toString("hex")}`);
  if (writeReply !== "OK") throw new Error(`could not plant XBE-load sentinel: ${writeReply}`);
  await qmpCommand("system_reset");
  const zero = performance.now();
  rsp.continue();
  running = true;
  let mapped = false;
  while (performance.now() - zero < 30000) {
    await new Promise(resolve => setTimeout(resolve, 100));
    await qmpCommand("stop");
    await rsp.packet("?", 2000);
    running = false;
    try {
      const value = (await readMemory(rsp, sentinelAddress, 4)).readUInt32LE(0);
      mapped = value !== sentinel;
      if (mapped) trace.sentinelReplacement = `0x${value.toString(16).padStart(8, "0")}`;
    } catch {}
    if (mapped) break;
    rsp.continue();
    running = true;
  }
  if (!mapped) throw new Error("DAH XBE mapping was not observed within 30 seconds");
  trace.xbeMappedMilliseconds = Number((performance.now() - zero).toFixed(3));
  // Software breakpoints are now safe because the retail code is live.
  for (const address of milestones.keys()) {
    const reply = await rsp.packet(`Z0,${address.toString(16)},1`);
    if (reply !== "OK") throw new Error(`software breakpoint 0x${address.toString(16)} rejected: ${reply}`);
  }
  rsp.continue();
  running = true;
  const deadline = zero + seconds * 1000;
  while (performance.now() < deadline && milestones.size) {
    let stop;
    try { stop = await rsp.next(Math.max(1000, deadline - performance.now())); }
    catch (error) { if (error.message === "RSP timeout") break; throw error; }
    running = false;
    if (!/^[ST]/.test(stop)) continue;
    const registers = decodeRegisters(await rsp.packet("g"));
    const descriptor = milestones.get(registers.eip);
    if (descriptor) {
      const stack = await readMemory(rsp, registers.esp, 32);
      const words = [];
      for (let index = 0; index < 8; index++) words.push(stack.readUInt32LE(index * 4));
      const event = {
        name: descriptor.name,
        address: `0x${registers.eip.toString(16).padStart(8, "0")}`,
        milliseconds: Number((performance.now() - zero).toFixed(3)),
        ecx: `0x${registers.ecx.toString(16).padStart(8, "0")}`,
        stack: words.map(value => `0x${value.toString(16).padStart(8, "0")}`)
      };
      if (descriptor.name === "movie_open") {
        try { event.path = await readCString(rsp, registers.ecx); }
        catch (error) { event.pathError = error.message; }
      }
      trace.milestones.push(event);
      descriptor.repeat--;
      // Raw RSP clients must restore the original instruction, single-step it,
      // then reinsert a software breakpoint. Otherwise `c` executes the same
      // INT3 again and records a fake duplicate hit.
      let reply = await rsp.packet(`z0,${registers.eip.toString(16)},1`);
      if (reply !== "OK") throw new Error(`remove breakpoint failed: ${reply}`);
      rsp.step();
      const stepStop = await rsp.next(5000);
      if (!/^[ST]/.test(stepStop)) throw new Error(`unexpected step reply: ${stepStop}`);
      if (descriptor.repeat === 0) {
        milestones.delete(registers.eip);
      } else {
        reply = await rsp.packet(`Z0,${registers.eip.toString(16)},1`);
        if (reply !== "OK") throw new Error(`reinsert breakpoint failed: ${reply}`);
      }
    }
    rsp.continue();
    running = true;
  }
} catch (error) {
  trace.error = error.message;
  process.exitCode = 1;
} finally {
  if (rsp) {
    if (running) {
      rsp.interrupt();
      try { await rsp.next(5000); } catch {}
      running = false;
    }
    for (const address of milestones.keys()) {
      try { await rsp.packet(`z0,${address.toString(16)},1`); } catch {}
    }
    rsp.continue();
    rsp.close();
  }
  trace.finishedAt = new Date().toISOString();
  fs.writeFileSync(outPath, `${JSON.stringify(trace, null, 2)}\n`, { flag: "wx" });
  console.log(JSON.stringify({ outPath, events: trace.milestones.length, error: trace.error || null }, null, 2));
}
