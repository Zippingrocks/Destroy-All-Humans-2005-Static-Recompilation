#!/usr/bin/env node
import net from "node:net";

const portIndex = process.argv.indexOf("--port");
const port = portIndex >= 0 ? Number(process.argv[portIndex + 1]) : 4445;
const commands = new Set(["probe", "commands", "stop", "cont", "reset"]);
const command = process.argv.find(value => commands.has(value)) || "probe";
if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error("invalid --port");

const socket = net.createConnection({ host: "127.0.0.1", port });
socket.setEncoding("utf8");
let buffer = "";
const replies = [];
const events = [];
const waiters = [];
socket.on("data", chunk => {
  buffer += chunk;
  for (;;) {
    const newline = buffer.indexOf("\n");
    if (newline < 0) break;
    const line = buffer.slice(0, newline).trim();
    buffer = buffer.slice(newline + 1);
    if (!line) continue;
    const message = JSON.parse(line);
    if (message.event) events.push(message);
    else {
      const waiter = waiters.shift();
      if (waiter) waiter(message);
      else replies.push(message);
    }
  }
});

function nextReply(timeout = 5000) {
  if (replies.length) return Promise.resolve(replies.shift());
  return new Promise((resolve, reject) => {
    const timer = setTimeout(() => reject(new Error("QMP response timeout")), timeout);
    waiters.push(value => { clearTimeout(timer); resolve(value); });
  });
}

function send(execute, args) {
  socket.write(`${JSON.stringify({ execute, ...(args ? { arguments: args } : {}) })}\r\n`);
  return nextReply();
}

try {
  await new Promise((resolve, reject) => {
    socket.once("connect", resolve);
    socket.once("error", reject);
    setTimeout(() => reject(new Error("QMP connect timeout")), 3000);
  });
  const greeting = await nextReply();
  const capabilities = await send("qmp_capabilities");
  let action = null;
  if (command === "commands") action = await send("query-commands");
  if (command === "stop") action = await send("stop");
  if (command === "cont") action = await send("cont");
  if (command === "reset") action = await send("system_reset");
  const status = await send("query-status");
  let block = null;
  if (command === "probe") {
    try { block = await send("query-block"); }
    catch (error) { block = { error: error.message }; }
  }
  console.log(JSON.stringify({ greeting, capabilities, command, action, status, block, events }, null, 2));
} catch (error) {
  console.error(`xemu-qmp: ${error.message}`);
  process.exitCode = 1;
} finally {
  socket.destroy();
}
