# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

MoOS (historical names: LibLoAndCap, LibPcapAndLiblo) is a 2013–2015 C++ app that maps live data streams (network packets, audio FFT, serial, Leap Motion, DB rows, video) onto sound-control outputs (OSC, MIDI, a built-in granular synth) through a weighted input×output matrix, configured from a web UI. It was revived in 2026 to build with modern CMake on macOS/Homebrew; the code itself is largely original.

## Build & run

**MoOS is always started with Docker** (Ubuntu 24.04). Multi-stage `Dockerfile`: `build` → `test` (runs the whole ctest suite; the runtime image is built from it, so it only exists if tests pass) → `runtime` (non-root, ~140 MB).

```sh
docker compose up --build -d          # build + test + run; UI on http://localhost:8080/v2/index.html
docker compose logs -f moos
docker compose restart moos           # fresh state (a capture device can only be chosen once per process)
docker compose down
docker build --target test .          # build and run the test suite only
```

- Ports are published on the host's `127.0.0.1` only (no authentication). Inside the container MoOS binds `0.0.0.0` (`CMD ["8080", "0.0.0.0", "9002"]`).
- Default OSC outputs go to the host via `MOOS_OSC_HOST=host.docker.internal`, on UDP 20000. `MOOS_RESOURCE_DIR` overrides `CURRENT_PATH` (`/opt/moos/share/moos` in the image). Saves are written to the `moos-data` volume (`/var/lib/moos`).
- The build context is a whitelist (`.dockerignore`). New top-level source dirs must be added there.
- Linux has a case-sensitive filesystem and libstdc++ is stricter about transitive includes than macOS/libc++: include file names exactly, and include `<cstring>` etc. explicitly.
- `cmake/FindGecode.cmake` uses Homebrew's GecodeConfig when present, otherwise locates the Debian/Ubuntu libraries itself.
- Documentation site: `docs/manuel.md` (the manual, French) → `python docs/build.py` (python-markdown, `docs/template.html`, assets incl. `pipeline.svg`) → `docs/_site/`. `.github/workflows/pages.yml` publishes it to the `gh-pages` branch (https://ludoviclaffineur.github.io/MoOS/) on every push to `master` touching `docs/`. Edit the manual there, not the generated output.
- CI (`.github/workflows/ci.yml`) builds the Docker image on `ubuntu-latest` only. Never use macOS runners to build or test Linux.

Native build (optional, for quick iteration on macOS). Homebrew deps: `cmake boost@1.85 gecode liblo websocketpp portaudio rtmidi pkgconf`.

```sh
cmake -S . -B build && cmake --build build -j8
./build/MoOS 8080          # MoOS [httpPort=80] [bindAddress=127.0.0.1] [wsPort=9002]
ctest --test-dir build --output-on-failure        # all tests
ctest --test-dir build -L unit                    # Boost.Test units only
ctest --test-dir build -R unit.grid               # a single suite
./build/tests/test_grid --run_test=compute_sends_weighted_sum_when_active   # a single test case
```

- **Boost must be < 1.87**: websocketpp 0.8 and `view/server` use `boost::asio::io_service`, removed in 1.87. CMakeLists prefers `/opt/homebrew/opt/boost@1.85` and fails loudly on a newer Boost.
- Optional components, OFF by default: `-DMOOS_WITH_OPENCV=ON`, `-DMOOS_WITH_LEAP=ON` (Leap SDK v2, no longer distributed), `-DMOOS_WITH_ODBC=ON` (SOCI). When OFF, the `.cpp` is excluded and the header (`capture/{VideoOpenCv,LeapMotion,Odbc}Handler.h`) provides an inert stub class under `#ifndef MOOS_HAS_*`, so callers compile unchanged.
- Sources are globbed recursively from the module dirs; `rtmidi/` (an Xcode template stub) and `lib/` (vendored Boost/liblo/WinPcap copies) are **not** used. Never add `lib/` to include paths, it would shadow the Homebrew Boost.
- Everything except `main.cpp` builds into the static lib `moos_core`, which both `MoOS` and the tests link.
- Tests live in `tests/`.
  - `tests/unit/test_*.cpp` use Boost.Test in its header-only variant (`included/unit_test.hpp`, no extra lib). `TestHelpers.h` provides `RecordingOutput` (an output that records what `compute()` sends) and `writeWav()`.
  - `tests/integration/moos.test.mjs` (Node ≥ 22, `node:test`) spawns the real binary on per-run ports and drives it over HTTP/WebSocket while listening for OSC on UDP 20000, so that port must be free. ctest passes the binary via `MOOS_BIN`.
  - There is no linter.
- Crashes are best diagnosed with `lldb --batch -o 'run 8080' -o 'thread backtrace all' -- ./build/MoOS`.
- `ReadWavFileHandler` playback threads never stop, so tests that start one deliberately leak their `Grid`.
- `CURRENT_PATH` (`Constant.h`) is the resource root (`www/`, `data/`), injected by CMake as the repo root via `MOOS_SOURCE_DIR`. Several files still contain hard-coded `/Users/ludoviclaffineur/Documents/LibLoAndCap/...` paths (SnfHandler, PcapLocation/Kiss processings, SaveXml, PcapGrabAndStorePictures): features using them won't find their files.

Legacy, unused build files remain at the root: `Makefile`, `CMakeFiles/`, `cmake_install.cmake` (generated on a Raspberry Pi), `*.sln/*.vcxproj`, `Debug/`, `LibLoAndCap.xcodeproj`. Don't build in-source; it would overwrite them.

## Architecture

The data flow is **CaptureDevice → Processings → Input (Setter) → Grid cells → OutputsHandler → OSC/MIDI/synth**.

- **`mapping/Grid`**: the core. It holds `Input`s, `OutputsHandler`s and one `Cell` per (input, output) pair with a coefficient in [-1, 1] (default 0, so outputs send 0 until weights are set). `Grid::compute()` runs only when the grid is active (`switchActive()`). It accumulates `input.extrapolated × coeff` into each output, then calls `extrapolate()`, `sendData()` and `reset()`. `addOutput` creates the cells for the inputs already present, but `addInput` creates **none**: inputs must be registered (by choosing the capture device) **before** the outputs, otherwise they have no cells. Capture threads call `compute()` after each processing pass. `Grid` owns a `std::recursive_mutex`: its own methods lock it, and both servers hold it for a whole request (`SnfHandler::computeRequest`, `WebSocketServer::dispatchRequest`). Any new code that iterates `getInputs()/getOutputs()/getCells()` outside those paths must lock `getMutex()` itself.
- **`capture/`**: `CaptureDevice` subclasses (Pcap, Serial, Leap, ReadWav, Odbc, VideoOpenCv) own a list of `Processings` and run their own thread on `init()`. The device enum and display names live in `AppIncludes.h` (`CONSTANCES::CaptureDeviceType`, `OutputType`). Keep the enum order in sync with the switch statements in `WebSocketServer::setCaptureDevice`/`setDefaultOutput` and with the web UI ids.
- **`processings/`**: `Processings::process(void*)` is the virtual entry point. Implementations cast the `void*` themselves; `FFTprocessing` expects a `float**`, Pcap ones a packet struct. Processings register their `Input`s in the grid in their constructor (e.g. FFT adds one input per bin, named by its integer frequency in Hz). Then they push values through `Setter<float>::setValue`.
- **`outputs/`**: `OutputsHandler` (named, with an id, a `Converter` for range mapping, and introspectable `Parameter<T>` lists used by the UI to edit outputs). Concrete outputs: `OscHandler` (liblo), `MidiHandler` + `outputs/Midi/*` (rtmidi), `outputs/GranularSynth/*` (portaudio; each GS*Handler drives one synth parameter).
- **`mapping/Genetic`, `ConstrainGenetic`**: two ways to set the grid coefficients automatically. `Genetic` is an interactive genetic algorithm driven by user ratings (`rateGrid`). `ConstrainGenetic` solves the coefficients from captured (input snapshot → output values) constraint pairs; it needs ≥ 2 inputs. `MagicGrid`/`GrilleOptions` (Gecode) are dead code, kept compiling against Gecode 6.
- **`save/`**: Boost.Serialization XML save/load of grid configurations.

### Two control servers (both started in `LibLoAndCap/main.cpp`)

1. **HTTP (`view/server/`)**: a Boost.Asio HTTP server example that serves static files from `www/`. Any request whose extension is `.snf` is routed to `SnfHandler::computeRequest(method, params)` (e.g. `getInputs.snf`, `addOutput.snf`, `updateCell.snf?input=..&output=..&coeff=..`, `setConstain.snf` (sic), `rateGrid.snf?rate=N`, `save/load`). The legacy UI is `www/index.html`.
2. **WebSocket on port 9002 (`view/websocket/WebSocketServer`, websocketpp)**: JSON messages `{"action": ..., "parameters": ...}` such as `init`, `setCaptureDevice {id}`, `setDefaultOutput {id}` (0 = OSC: two outputs `TEST`/`TEST2` → `127.0.0.1:20000` `/osc` `/osc1`), `sendWeight {inputName, outputName, weight}`, `setOutput`, `setMidiPort`, `trig`, `setRow`. The newer UI using it is **`www/v2/index.html`** (`www/v2/script.js`). A capture device can only be set once per process (`mCaptureDevice` guard).

`main.cpp` creates a single `Grid` and passes it to the HTTP server, to `Genetic`/`ConstrainGenetic` and to `WebSocketServer`. The `OdbcHandler*` passed to the HTTP server is always `NULL`.

Both servers have no authentication. They bind to `127.0.0.1` by default; pass `0.0.0.0` as the 2nd arg to expose them on the LAN. The WebSocket validate handler rejects browser `Origin`s other than localhost/127.0.0.1 (or the bind address); clients that send no Origin are accepted. HTTP actions are still plain GETs, so they remain CSRF-able. Exceptions thrown while handling a request are caught: the WebSocket logs and ignores it, HTTP replies 500. Segfaults (null derefs, out-of-bounds `[]`) are not caught, so request handlers still need explicit guards.

### Code conventions and pitfalls

- Lookups such as `Grid::getOutputWithId/WithName`, `getInputWithName` and `getCellWithName` return `NULL` when nothing matches. Request handlers must null-check them (several crashes came from this).
- `Grid::getNbrInputs()/getNbrOutputs()` return `size_t`, so subtracting from them underflows.
- Heavy use of raw `new`, `char*` names (copied with `strcpy`) and pthreads mixed with boost::thread. Match the surrounding style instead of refactoring wholesale.
- Comments and user-facing strings are a mix of French and English.
