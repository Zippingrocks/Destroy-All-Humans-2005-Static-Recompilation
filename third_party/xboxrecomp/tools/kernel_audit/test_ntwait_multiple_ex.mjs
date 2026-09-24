/* Run in a Visual Studio x64 developer prompt:
 *   node tools/kernel_audit/test_ntwait_multiple_ex.mjs
 * Extracts current production function bodies into a temporary test fixture;
 * no copied implementation can silently diverge from the checked-in bridge.
 */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import crypto from 'node:crypto';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, '../..');
const bridgePath = path.join(root, 'src/kernel/kernel_bridge.c');
const syncPath = path.join(root, 'src/kernel/kernel_sync.c');
const bridgeSource = fs.readFileSync(bridgePath, 'utf8');
const syncSource = fs.readFileSync(syncPath, 'utf8');
const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-ntwait-test-'));

function extract(source, signature) {
  const definitions = [];
  for (let candidate = source.indexOf(signature); candidate >= 0;
       candidate = source.indexOf(signature, candidate + signature.length)) {
    const brace = source.indexOf('{', candidate);
    const semicolon = source.indexOf(';', candidate);
    if (brace >= 0 && (semicolon < 0 || brace < semicolon)) definitions.push(candidate);
  }
  if (definitions.length !== 1)
    throw new Error(`Expected one definition: ${signature}`);
  const start = definitions[0];
  const bodyStart = source.indexOf('{', start);
  if (bodyStart < 0) throw new Error(`No body: ${signature}`);
  let depth = 0, mode = 'code';
  for (let i = bodyStart; i < source.length; ++i) {
    const c = source[i], n = source[i + 1];
    if (mode === 'line') { if (c === '\n') mode = 'code'; continue; }
    if (mode === 'block') { if (c === '*' && n === '/') { mode = 'code'; ++i; } continue; }
    if (mode === 'string' || mode === 'char') {
      if (c === '\\') { ++i; continue; }
      if (c === (mode === 'string' ? '"' : "'")) mode = 'code';
      continue;
    }
    if (c === '/' && n === '/') { mode = 'line'; ++i; continue; }
    if (c === '/' && n === '*') { mode = 'block'; ++i; continue; }
    if (c === '"') { mode = 'string'; continue; }
    if (c === "'") { mode = 'char'; continue; }
    if (c === '{') ++depth;
    if (c === '}' && --depth === 0) return source.slice(start, i + 1);
  }
  throw new Error(`Unterminated body: ${signature}`);
}

const functions = [
  extract(syncSource, 'static DWORD xbox_nt_timeout_to_ms('),
  extract(syncSource, 'static NTSTATUS xbox_wait_result_to_ntstatus('),
  extract(syncSource, 'NTSTATUS __stdcall xbox_NtWaitForMultipleObjectsEx('),
  extract(bridgeSource, 'static void bridge_NtWaitForMultipleObjectsEx(void)'),
  extract(bridgeSource, 'static int stdcall_args_for_ordinal('),
  (() => {
    const declarations = bridgeSource.match(/^static\s+(?:RECOMP_TLS\s+)?int\s+g_kernel_dispatch_slot\s*=\s*-1\s*;/gm);
    if (declarations?.length !== 1) throw new Error('Expected one exact dispatch slot declaration');
    return declarations[0];
  })(),
  extract(bridgeSource, 'static void kernel_thunk_dispatch(void)'),
  extract(bridgeSource, 'recomp_func_t recomp_lookup_kernel('),
];
const fixture = functions.join('\n\n') + '\n';
const digest = crypto.createHash('sha256').update(fixture).digest('hex');
console.log(`SOURCE_FIXTURE sha256=${digest} functions=${functions.length}`);

function compileAndRun(label, source, mustPass) {
  const directory = path.join(tempDir, label);
  fs.mkdirSync(directory);
  fs.writeFileSync(path.join(directory, 'ntwait_multiple_ex_fixture.inc'), source, 'utf8');
  const executable = path.join(directory, 'ntwait_multiple_ex_test.exe');
  const compile = spawnSync('cl.exe', [
    '/nologo', '/W4', '/WX', '/O2', '/std:c11', '/utf-8',
    `/I${directory}`, `/Fe:${executable}`, `/Fo:${path.join(directory, 'test.obj')}`,
    path.join(here, 'test_ntwait_multiple_ex.c'),
  ], { cwd: directory, encoding: 'utf8', timeout: 30000 });
  if (compile.error || compile.status !== 0) {
    process.stdout.write(compile.stdout || '');
    process.stderr.write(compile.stderr || '');
    throw new Error(`Compile failed (${label}): ${compile.error || compile.status}`);
  }
  const run = spawnSync(executable, [], { cwd: directory, encoding: 'utf8', timeout: 10000 });
  if (run.error) throw run.error;
  if (mustPass && run.status !== 0) {
    process.stderr.write(run.stderr || '');
    throw new Error(`Production source regression failed: ${run.status}`);
  }
  if (!mustPass && run.status !== 1)
    throw new Error(`Regression control ${label} must be rejected by assertions, got ${run.status}`);
  console.log(mustPass ? run.stdout.trim() : `PASS: rejected ${label}: ${run.stderr.trim()}`);
}

function replaceOnce(source, pattern, replacement) {
  const matches = [...source.matchAll(new RegExp(pattern.source, 'g'))];
  if (matches.length !== 1) throw new Error(`Expected one mutation target: ${pattern}`);
  return source.replace(pattern, replacement);
}

compileAndRun('current', fixture, true);
let oldArguments = replaceOnce(fixture, /alertable\s*=\s*STACK_ARG\(4\)/,
  'alertable = STACK_ARG(3)');
oldArguments = replaceOnce(oldArguments, /timeout_va\s*=\s*STACK_ARG\(5\)/,
  'timeout_va = STACK_ARG(4)');
compileAndRun('old-five-argument-mapping', oldArguments, false);
const oldCleanup = replaceOnce(fixture, /case 235: return 24;/, 'case 235: return 20;');
compileAndRun('old-twenty-byte-cleanup', oldCleanup, false);
const unbounded = replaceOnce(fixture, /if \(count > 64\) count = 64;/,
  '/* regression control: missing count clamp */');
compileAndRun('missing-native-array-bound', unbounded, false);
const sharedSelector = replaceOnce(fixture,
  /static RECOMP_TLS int g_kernel_dispatch_slot = -1;/,
  'static int g_kernel_dispatch_slot = -1;');
compileAndRun('shared-dispatch-selector', sharedSelector, false);
console.log(`TEST_OUTPUT ${tempDir}`);
