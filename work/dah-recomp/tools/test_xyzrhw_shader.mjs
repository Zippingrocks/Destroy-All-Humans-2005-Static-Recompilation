/* VS x64 developer prompt: node work/dah-recomp/tools/test_xyzrhw_shader.mjs */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, '../../..');
const source = fs.readFileSync(path.join(root, 'Repos/xboxrecomp-main/src/d3d/d3d8_shaders.c'), 'utf8');
const declaration = source.match(/static const char g_vs_source\[\] =[\s\S]*?^    "}\\n";/m);
assert(declaration, 'Exact production embedded vertex shader');
const temp = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-xyzrhw-warp-'));
function run(label, shader, wanted, args = []) {
  const directory = path.join(temp, label);
  fs.mkdirSync(directory);
  fs.writeFileSync(path.join(directory, 'xyzrhw_shader_fixture.inc'), shader);
  const executable = path.join(directory, 'test.exe');
  const compiled = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11',
    `/I${directory}`, `/Fe:${executable}`, `/Fo:${path.join(directory, 'test.obj')}`,
    path.join(here, 'test_xyzrhw_shader.c'), 'd3d11.lib', 'd3dcompiler.lib', 'dxgi.lib'],
    { cwd: directory, encoding: 'utf8', timeout: 30000 });
  assert.equal(compiled.status, 0, compiled.error || compiled.stdout || compiled.stderr);
  const result = spawnSync(executable, args, { cwd: directory, encoding: 'utf8', timeout: 30000 });
  assert.equal(result.status, wanted, `${label}: ${result.error || result.stdout || result.stderr}`);
  console.log(wanted ? `PASS: rejected ${label}: ${result.stderr.trim()}` : result.stdout.trim());
}
run('current', declaration[0], 0);
const old = declaration[0].replace(/    \/\* D3D8 XYZRHW[\s\S]*?mixed valid\/invalid primitive before clipping\. \*\/\r?\n/, '');
assert.notEqual(old, declaration[0], 'Negative control must remove only RHW reconstruction');
run('old-w1-stream-output', old, 1);
run('old-w1-perspective-raster', old, 1, ['--raster-only']);
console.log(`TEST_OUTPUT ${temp}`);
