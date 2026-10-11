#!/usr/bin/env node
import net from "node:net";
import crypto from "node:crypto";
import fs from "node:fs";

function usage(message) {
  if (message) console.error(`error: ${message}`);
  console.error(`usage:
  node xemu_rsp_probe.mjs probe [--host 127.0.0.1] [--port 1235]
  node xemu_rsp_probe.mjs snapshot --range ADDRESS:LENGTH [--range ...] [--out FILE]

ADDRESS and LENGTH accept hexadecimal (0x...) or decimal. snapshot briefly halts
the isolated guest, reads only the requested bytes and registers, then resumes it.`);
  process.exit(message ? 2 : 0);
}

function parseNumber(value, label) {
  if (!value || !/^(?:0x[0-9a-f]+|[0-9]+)$/i.test(value)) usage(`invalid ${label}: ${value}`);
  const parsed = Number(value);
  if (!Number.isSafeInteger(parsed) || parsed < 0 || parsed > 0xffffffff) usage(`${label} is outside uint32: ${value}`);
  return parsed;
}

const argv = process.argv.slice(2);
const command = argv.shift() || "probe";
let host = "127.0.0.1";
let port = 1235;
let outPath = null;
const ranges = [];
while (argv.length) {
  const option = argv.shift();
  if (option === "--host") host = argv.shift() || usage("--host needs a value");
  else if (option === "--port") port = parseNumber(argv.shift(), "port");
  else if (option === "--out") outPath = argv.shift() || usage("--out needs a value");
  else if (option === "--range") {
    const spec = argv.shift() || usage("--range needs ADDRESS:LENGTH");
    const match = /^([^:]+):([^:]+)$/.exec(spec);
    if (!match) usage(`invalid range: ${spec}`);
    const address = parseNumber(match[1], "range address");
    const length = parseNumber(match[2], "range length");
    if (!length || address + length > 0x100000000) usage(`invalid range extent: ${spec}`);
    ranges.push({ address, length });
  } else if (option === "--help" || option === "-h") usage();
  else usage(`unknown option: ${option}`);
}
if (!new Set(["probe", "snapshot"]).has(command)) usage(`unknown command: ${command}`);
if (command === "snapshot" && ranges.length === 0) usage("snapshot requires at least one --range");

function checksum(payload) {
  let value = 0;
  for (const byte of Buffer.from(payload, "ascii")) value = (value + byte) & 0xff;
  return value.toString(16).padStart(2, "0");
}

class RspClient {
  constructor(socket) {
    this.socket = socket;
    this.buffer = Buffer.alloc(0);
    this.waiters = [];
    socket.on("data", data => { this.buffer = Buffer.concat([this.buffer, data]); this.pump(); });
    socket.on("error", error => this.rejectAll(error));
    socket.on("close", () => this.rejectAll(new Error("GDB connection closed")));
  }
  rejectAll(error) { while (this.waiters.length) this.waiters.shift().reject(error); }
  pump() {
    for (;;) {
      while (this.buffer.length && (this.buffer[0] === 0x2b || this.buffer[0] === 0x2d)) this.buffer = this.buffer.subarray(1);
      const start = this.buffer.indexOf(0x24);
      if (start < 0) return;
      if (start) this.buffer = this.buffer.subarray(start);
      const hash = this.buffer.indexOf(0x23, 1);
      if (hash < 0 || this.buffer.length < hash + 3) return;
      const payload = this.buffer.subarray(1, hash).toString("ascii");
      const received = this.buffer.subarray(hash + 1, hash + 3).toString("ascii").toLowerCase();
      this.buffer = this.buffer.subarray(hash + 3);
      this.socket.write(received === checksum(payload) ? "+" : "-");
      if (received !== checksum(payload)) continue;
      const waiter = this.waiters.shift();
      if (waiter) waiter.resolve(payload);
    }
  }
  nextPacket(timeoutMs = 5000) {
    return new Promise((resolve, reject) => {
      const waiter = { resolve, reject };
      this.waiters.push(waiter);
      const timer = setTimeout(() => {
        const index = this.waiters.indexOf(waiter);
        if (index >= 0) this.waiters.splice(index, 1);
        reject(new Error(`GDB response timed out after ${timeoutMs} ms`));
      }, timeoutMs);
      waiter.resolve = value => { clearTimeout(timer); resolve(value); };
      waiter.reject = error => { clearTimeout(timer); reject(error); };
      this.pump();
    });
  }
  async packet(payload, timeoutMs = 5000) {
    this.socket.write(`$${payload}#${checksum(payload)}`, "ascii");
    return await this.nextPacket(timeoutMs);
  }
  async halt() {
    const status = await this.packet("?", 5000);
    if (/^[STW]/.test(status)) return status;
    this.socket.write(Buffer.from([0x03]));
    const stop = await this.nextPacket(15000);
    if (!/^[STW]/.test(stop)) throw new Error(`unexpected stop reply: ${stop}`);
    return stop;
  }
  resume() {
    const payload = "c";
    this.socket.write(`$${payload}#${checksum(payload)}`, "ascii");
  }
  close() { this.socket.destroy(); }
}

function connect() {
  return new Promise((resolve, reject) => {
    const socket = net.createConnection({ host, port });
    socket.setNoDelay(true);
    const timer = setTimeout(() => socket.destroy(new Error(`connect timed out after 3000 ms`)), 3000);
    socket.once("connect", () => { clearTimeout(timer); resolve(new RspClient(socket)); });
    socket.once("error", error => { clearTimeout(timer); reject(error); });
  });
}

async function readMemory(client, address, length) {
  const chunks = [];
  for (let offset = 0; offset < length; offset += 0x400) {
    const count = Math.min(0x400, length - offset);
    const reply = await client.packet(`m${(address + offset).toString(16)},${count.toString(16)}`);
    if (reply.startsWith("E")) throw new Error(`memory read failed at 0x${(address + offset).toString(16)}: ${reply}`);
    const bytes = Buffer.from(reply, "hex");
    if (bytes.length !== count) throw new Error(`short memory read at 0x${(address + offset).toString(16)}`);
    chunks.push(bytes);
  }
  return Buffer.concat(chunks);
}

let client;
let halted = false;
try {
  client = await connect();
  let supported = await client.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  if (/^[STW]/.test(supported)) {
    halted = true;
    supported = await client.packet("qSupported:multiprocess+;swbreak+;hwbreak+");
  }
  if (command === "probe") {
    console.log(JSON.stringify({ ok: true, host, port, supported }, null, 2));
    // QEMU pauses the guest when a debugger attaches even when qSupported
    // returns normally. A connectivity probe must never leave the reference
    // stalled after disconnecting.
    client.resume();
    halted = false;
  } else {
    const stop = await client.halt();
    halted = true;
    const registers = await client.packet("g");
    if (registers.startsWith("E")) throw new Error(`register read failed: ${registers}`);
    const result = {
      schema: 1,
      capturedAt: new Date().toISOString(),
      host,
      port,
      stop,
      registers,
      x86: {},
      ranges: []
    };
    const registerNames = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "eip", "eflags"];
    const registerBytes = Buffer.from(registers, "hex");
    if (registerBytes.length >= registerNames.length * 4) {
      registerNames.forEach((name, index) => {
        result.x86[name] = `0x${registerBytes.readUInt32LE(index * 4).toString(16).padStart(8, "0")}`;
      });
    }
    for (const range of ranges) {
      const item = { address: `0x${range.address.toString(16).padStart(8, "0")}`, length: range.length };
      try {
        const data = await readMemory(client, range.address, range.length);
        item.sha256 = crypto.createHash("sha256").update(data).digest("hex");
        item.dataBase64 = data.toString("base64");
      } catch (error) {
        item.error = error.message;
      }
      result.ranges.push(item);
    }
    const serialized = `${JSON.stringify(result, null, 2)}\n`;
    if (outPath) fs.writeFileSync(outPath, serialized, { flag: "wx" });
    else process.stdout.write(serialized);
  }
} catch (error) {
  console.error(`xemu-rsp: ${error.message}`);
  process.exitCode = 1;
} finally {
  if (client) {
    if (halted) client.resume();
    setTimeout(() => client.close(), 50);
  }
}
