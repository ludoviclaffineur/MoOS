// Batterie d'intégration MoOS : lance le vrai binaire et le pilote comme le ferait
// l'interface web (HTTP .snf + WebSocket JSON), en vérifiant la sortie OSC.
//
//   MOOS_BIN=build/MoOS node --test --test-concurrency=1 tests/integration/moos.test.mjs
//   (ou : ctest --test-dir build -L integration --output-on-failure)
//
// Nécessite Node >= 22 (WebSocket global). Les sorties OSC par défaut de MoOS visent
// 127.0.0.1:20000 : ce port UDP doit être libre.

import { test, describe, before, after } from 'node:test';
import assert from 'node:assert/strict';
import { spawn } from 'node:child_process';
import dgram from 'node:dgram';
import http from 'node:http';
import net from 'node:net';
import os from 'node:os';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '../..');
const BIN = process.env.MOOS_BIN ?? path.join(ROOT, 'build', 'MoOS');
const OSC_PORT = 20000;
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

let nextPort = 18080 + (process.pid % 500) * 4;

// ---------------------------------------------------------------- helpers

async function startServer() {
  const httpPort = nextPort++;
  const wsPort = nextPort++;
  const proc = spawn(BIN, [String(httpPort), '127.0.0.1', String(wsPort)], { cwd: ROOT });
  let logs = '';
  proc.stdout.on('data', (d) => (logs += d));
  proc.stderr.on('data', (d) => (logs += d));
  const exited = new Promise((r) => proc.on('exit', (code, signal) => r({ code, signal })));
  const srv = { proc, httpPort, wsPort, exited, logs: () => logs, alive: () => proc.exitCode === null && proc.signalCode === null };
  // Attend que les deux ports acceptent des connexions
  for (let i = 0; i < 100; i++) {
    if (!srv.alive()) throw new Error(`MoOS s'est arrêté au démarrage:\n${logs}`);
    if ((await canConnect(httpPort)) && (await canConnect(wsPort))) return srv;
    await sleep(100);
  }
  proc.kill('SIGKILL');
  throw new Error(`MoOS ne répond pas:\n${logs}`);
}

async function stopServer(srv) {
  if (!srv || !srv.alive()) return;
  srv.proc.kill('SIGKILL');
  await srv.exited;
}

function canConnect(port, host = '127.0.0.1') {
  return new Promise((resolve) => {
    const s = net.connect({ port, host });
    s.once('connect', () => { s.destroy(); resolve(true); });
    s.once('error', () => resolve(false));
    s.setTimeout(1000, () => { s.destroy(); resolve(false); });
  });
}

function httpGet(port, pathname) {
  return new Promise((resolve, reject) => {
    const req = http.get({ host: '127.0.0.1', port, path: pathname, timeout: 15000 }, (res) => {
      let body = '';
      res.on('data', (d) => (body += d));
      res.on('end', () => resolve({ status: res.statusCode, body }));
    });
    req.on('timeout', () => req.destroy(new Error(`timeout ${pathname}`)));
    req.on('error', reject);
  });
}

// Handshake WebSocket brut, pour contrôler l'en-tête Origin. Renvoie le code HTTP.
function wsHandshake(port, origin) {
  return new Promise((resolve, reject) => {
    const headers = {
      Connection: 'Upgrade',
      Upgrade: 'websocket',
      'Sec-WebSocket-Version': '13',
      'Sec-WebSocket-Key': 'dGhlIHNhbXBsZSBub25jZQ==',
    };
    if (origin) headers.Origin = origin;
    const req = http.request({ host: '127.0.0.1', port, path: '/', headers, timeout: 5000 });
    req.on('upgrade', (res, socket) => { socket.destroy(); resolve(res.statusCode); });
    req.on('response', (res) => { res.resume(); resolve(res.statusCode); });
    req.on('timeout', () => req.destroy(new Error('timeout handshake')));
    req.on('error', reject);
    req.end();
  });
}

async function openWs(port) {
  const ws = new WebSocket(`ws://127.0.0.1:${port}`);
  const received = [];
  ws.onmessage = (e) => received.push(String(e.data));
  await new Promise((resolve, reject) => { ws.onopen = resolve; ws.onerror = () => reject(new Error('ws error')); });
  return { ws, received, send: (o) => ws.send(typeof o === 'string' ? o : JSON.stringify(o)) };
}

// Écoute OSC : dernière valeur float reçue par adresse
function oscListener() {
  const sock = dgram.createSocket('udp4');
  const last = {};
  let count = 0;
  sock.on('message', (msg) => {
    count++;
    const addr = msg.toString('latin1', 0, msg.indexOf(0));
    last[addr] = msg.readFloatBE(msg.length - 4);
  });
  return new Promise((resolve, reject) => {
    sock.once('error', reject);
    sock.bind(OSC_PORT, '127.0.0.1', () => resolve({ last, count: () => count, close: () => sock.close() }));
  });
}

async function waitFor(cond, timeoutMs, label) {
  const end = Date.now() + timeoutMs;
  while (Date.now() < end) {
    if (await cond()) return;
    await sleep(50);
  }
  assert.fail(`condition non atteinte en ${timeoutMs} ms : ${label}`);
}

function lanAddress() {
  for (const ifs of Object.values(os.networkInterfaces())) {
    for (const i of ifs ?? []) if (i.family === 'IPv4' && !i.internal) return i.address;
  }
  return null;
}

// ---------------------------------------------------------------- sécurité

describe('sécurité', () => {
  let srv;
  before(async () => { srv = await startServer(); });
  after(async () => { await stopServer(srv); });

  test("n'écoute que sur 127.0.0.1 par défaut", { skip: !lanAddress() && 'aucune interface réseau' }, async () => {
    const lan = lanAddress();
    assert.equal(await canConnect(srv.httpPort, lan), false, `HTTP joignable via ${lan}`);
    assert.equal(await canConnect(srv.wsPort, lan), false, `WebSocket joignable via ${lan}`);
  });

  test("refuse les WebSocket ouverts depuis un autre site", async () => {
    assert.notEqual(await wsHandshake(srv.wsPort, 'http://evil.example.com'), 101);
    assert.notEqual(await wsHandshake(srv.wsPort, 'null'), 101);
  });

  test('accepte les pages locales et les clients sans Origin', async () => {
    assert.equal(await wsHandshake(srv.wsPort, `http://127.0.0.1:${srv.httpPort}`), 101);
    assert.equal(await wsHandshake(srv.wsPort, 'http://localhost:8080'), 101);
    assert.equal(await wsHandshake(srv.wsPort, null), 101);
  });

  test('rejette la remontée de répertoire', async () => {
    assert.equal((await httpGet(srv.httpPort, '/../CMakeLists.txt')).status, 400);
    assert.equal((await httpGet(srv.httpPort, '/%2e%2e/CMakeLists.txt')).status, 400);
  });
});

// ---------------------------------------------------------------- robustesse

describe('robustesse : requêtes malformées ou prématurées', () => {
  let srv;
  before(async () => { srv = await startServer(); });
  after(async () => { await stopServer(srv); });

  test('WebSocket : JSON invalide, champs manquants, actions sans capture device', async () => {
    const c = await openWs(srv.wsPort);
    const messages = [
      'hello',
      '{"action":"setRow"}',
      '{"action":"trig"}',
      '{"action":"setRow","parameters":"3"}',
      '{"action":"setMidiPort","parameters":{"id":0}}',
      '{"action":"setConfigurationPcap","parameters":{"id":99}}',
      '{"action":"setOutput","parameters":{"identifier":999,"Name":"x"}}',
      '{"action":"sendWeight","parameters":{"inputName":"nope","outputName":"nope","weight":1}}',
      '{"action":"setCaptureDevice"}',
      '{"action":"unknownAction"}',
    ];
    for (const m of messages) { c.send(m); await sleep(100); }
    c.ws.close();
    await sleep(300);
    assert.ok(srv.alive(), `MoOS est mort:\n${srv.logs()}`);
    assert.equal((await httpGet(srv.httpPort, '/index.html')).status, 200);
  });

  const snf = [
    ['trig.snf', 200],                                     // base de données NULL
    ['updateCell.snf?input=x&output=y&coeff=0.5', 200],   // cellule inconnue
    ['getOutput.snf?output=nope', 200],
    ['updateOutput.snf?Identifier=999&', 200],
    ['setOutputValue.snf?name=nope&value=0.5', 200],
    ['setConstain.snf', 200],                              // < 2 inputs
    ['setConstain.snf', 200],
    ['kymaOutput.snf?ip=1.2.3.4', 200],                    // paramètres manquants
    ['load.snf?filename=does_not_exist', null],            // fichier absent : 200 ou 500, pas de crash
    ['rateGrid.snf?rate=3', 200],
    ['getInputs.snf', 200],
    ['getCells.snf', 200],
  ];
  for (const [uri, expected] of snf) {
    test(`HTTP /${uri}`, async () => {
      const res = await httpGet(srv.httpPort, `/${uri}`);
      if (expected !== null) assert.equal(res.status, expected);
      assert.ok(srv.alive(), `MoOS est mort sur /${uri}:\n${srv.logs()}`);
    });
  }

  test('HTTP : une exception dans un handler renvoie 500 sans tuer le process', async () => {
    await httpGet(srv.httpPort, '/addOutput.snf');
    const res = await httpGet(srv.httpPort, '/updateOutput.snf?Identifier=0&x=Name&');
    assert.equal(res.status, 500);
    assert.ok(srv.alive());
    assert.equal((await httpGet(srv.httpPort, '/getOutputs.snf')).status, 200);
  });
});

// ---------------------------------------------------------------- pipeline

describe('pipeline : input WAV -> grille -> sorties OSC', () => {
  let srv, osc, client;
  before(async () => {
    osc = await oscListener();
    srv = await startServer();
    client = await openWs(srv.wsPort);
    client.send({ action: 'init' });
    await sleep(300);
    client.send({ action: 'setCaptureDevice', parameters: { id: 3 } });   // ReadWave Handler
    await sleep(800);
    client.send({ action: 'setDefaultOutput', parameters: { id: 0 } });   // OSC
    await sleep(500);
  });
  after(async () => {
    client?.ws.close();
    await stopServer(srv);
    osc?.close();
  });

  test('init renvoie la liste des capture devices', () => {
    assert.ok(client.received.some((m) => m.includes('capture_device_list') && m.includes('ReadWave Handler')));
  });

  test('les sorties OSC /osc et /osc1 émettent en continu', async () => {
    await waitFor(() => osc.count() > 20 && '/osc' in osc.last && '/osc1' in osc.last, 3000, 'messages OSC');
  });

  test("la grille est partagée : l'API HTTP voit les inputs du WebSocket", async () => {
    const res = await httpGet(srv.httpPort, '/getInputs.snf');
    assert.equal(res.status, 200);
    assert.equal((res.body.match(/<name>/g) ?? []).length, 512, 'bins FFT attendus');
    assert.match((await httpGet(srv.httpPort, '/getOutputs.snf')).body, /<name>TEST<\/name>/);
  });

  test('un poids posé en WebSocket fait bouger la sortie OSC', async () => {
    const bin = (i) => String(Math.trunc(i * (44100 / 1024)));
    for (let i = 1; i <= 20; i++) {
      client.send({ action: 'sendWeight', parameters: { inputName: bin(i), outputName: 'TEST2', weight: 1 } });
    }
    await waitFor(() => osc.last['/osc1'] > 0, 3000, '/osc1 > 0');
  });

  test('un poids posé en HTTP fait bouger la sortie OSC', async () => {
    for (let i = 1; i <= 20; i++) {
      await httpGet(srv.httpPort, `/updateCell.snf?input=${Math.trunc(i * (44100 / 1024))}&output=TEST&coeff=1`);
    }
    await waitFor(() => osc.last['/osc'] > 0, 3000, '/osc > 0');
  });

  test('setConstain avec de vrais inputs : répond, sans exit() ni boucle infinie', async () => {
    for (let i = 0; i < 4; i++) {
      assert.equal((await httpGet(srv.httpPort, '/setConstain.snf')).status, 200);
    }
    assert.ok(srv.alive(), srv.logs());
  });

  test('le capture device ne peut être choisi qu\'une fois', async () => {
    client.send({ action: 'setCaptureDevice', parameters: { id: 0 } });
    await sleep(300);
    assert.ok(srv.alive());
    assert.equal((await httpGet(srv.httpPort, '/getInputs.snf')).body.match(/<name>/g).length, 512);
  });
});

// ---------------------------------------------------------------- arrêt

describe('arrêt', () => {
  test('SIGINT arrête proprement un serveur au repos', async () => {
    const srv = await startServer();
    srv.proc.kill('SIGINT');
    const res = await Promise.race([srv.exited, sleep(5000).then(() => null)]);
    if (!res) await stopServer(srv);
    assert.ok(res, "MoOS ne s'est pas arrêté en 5 s");
    assert.equal(res.code, 0, `code ${res.code} / signal ${res.signal}\n${srv.logs()}`);
  });

  test('SIGINT avec un client WebSocket connecté', async () => {
    const srv = await startServer();
    const c = await openWs(srv.wsPort);
    c.send({ action: 'init' });
    await sleep(200);
    srv.proc.kill('SIGINT');
    const res = await Promise.race([srv.exited, sleep(5000).then(() => null)]);
    if (!res) await stopServer(srv);
    c.ws.close();
    assert.ok(res, "MoOS ne s'est pas arrêté en 5 s");
    assert.equal(res.code, 0, `code ${res.code} / signal ${res.signal}\n${srv.logs()}`);
  });
});
