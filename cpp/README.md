# cpp workspace

C++ learning/interview workspace. Toolchain and dependencies are managed by
**[pixi](https://pixi.sh)** (gcc, cmake, ninja, gtest, clangd from conda-forge —
no Conan, no system packages required), builds are driven by **CMake presets**
(Ninja generator), and the editor setup is **VSCode** (CMake Tools + clangd).

```
pixi.toml / pixi.lock   toolchain + dependency definition (lock file is committed)
CMakePresets.json       debug / release configure, build and test presets
devtools/build.sh       one-shot CLI build (works from any shell)
devtools/clean.sh       remove all CMake build output
devtools/setenv.sh      source to activate the pixi env in your current shell
.vscode/                editor config (cmake/clangd paths, recommended extensions)
```

The `Interview/` subdirectory is also a **standalone project** with the same
layout (its own `pixi.toml`, presets, `devtools/`) — everything below applies
equally when working inside `Interview/` directly.

---

## 1. Prerequisites

- Linux x86-64 (WSL2 works fine).
- `gdb` for debugging: `sudo apt install gdb`
- Install pixi:

  ```bash
  curl -fsSL https://pixi.sh/install.sh | sh
  source ~/.bashrc   # adds ~/.pixi/bin to PATH
  ```

That's all — compiler, cmake, ninja, gtest and clangd come from pixi.

## 2. Build from the command line

```bash
cd cpp
./devtools/build.sh debug      # first run installs the pixi environment, then configures + builds
./devtools/build.sh release
```

Equivalent pixi tasks (defined in `pixi.toml`):

```bash
pixi run build-debug      # or build-release
pixi run test-debug       # or test-release
pixi run clean
```

Binaries land in `cmake-build-<config>/` (e.g.
`cmake-build-debug/Interview/lock_free/lock_free_test`).

### Activating the environment in your shell

For ad-hoc work (direct `cmake`/`ctest`/g++ calls), source `setenv.sh` once
per shell — pixi's equivalent of `conda activate`:

```bash
source devtools/setenv.sh
cmake --preset debug && ctest --preset debug
```

It runs `pixi shell-hook` (PATH, `CONDA_PREFIX`, `PIXI_*`) and additionally
exports `CC`/`CXX` pointing at the conda gcc, so even preset-less cmake
invocations use the pixi toolchain. Open a new shell to deactivate.
Handy alias: `alias cppenv='source ~/dev/Program/cpp/devtools/setenv.sh'`.

## 3. Run tests

```bash
ctest --preset debug      # or: pixi run test-debug
```

## 4. VSCode setup

1. **Install VSCode.** On WSL the smoothest option is VSCode on the Windows
   side plus the **WSL extension** (`ms-vscode-remote.remote-wsl`); then open
   the folder from a WSL terminal:

   ```bash
   cd ~/dev/Program/cpp
   code .
   ```

   (First launch auto-installs the VSCode Server inside WSL.)

2. **Install the recommended extensions** when prompted (list lives in
   `.vscode/extensions.json`):
   - `ms-vscode.cmake-tools` — preset-driven configure/build/test/debug
   - `llvm-vs-code-extensions.vscode-clangd` — IntelliSense
   - `ms-vscode.cpptools` — only used for its gdb debug backend (its
     IntelliSense is disabled in `.vscode/settings.json` so it won't conflict
     with clangd)

3. **Configure & build:** pick the `debug` or `release` configure preset in
   the bottom status bar (CMake Tools reads `CMakePresets.json` automatically),
   then build with **F7**.

4. **Run/debug tests:** Testing sidebar (populated from ctest), or the 🐞
   button in the CMake Tools status bar to debug the selected target with gdb.
   **F5** builds & debugs the currently open file as a standalone program
   (uses the pixi g++).

No manual configuration is needed: `.vscode/settings.json` points cmake and
clangd at the pixi environment by absolute path.

## 5. Standalone Interview project

`Interview/` mirrors the root setup, so it can be opened on its own:

```bash
cd cpp/Interview
./devtools/build.sh debug   # uses Interview/pixi.toml and Interview/.pixi
code .                      # or open the Interview folder directly in VSCode
```

Building from the root workspace builds Interview's targets as subdirectories;
both entry points share nothing, so build dirs never collide
(`cpp/cmake-build-*` vs `cpp/Interview/cmake-build-*`).

## 6. Adding a dependency

```bash
pixi add <package>      # from conda-forge, e.g. `pixi add boost`
```

then `find_package(...)` / `target_link_libraries(...)` in the relevant
`CMakeLists.txt`. CMake finds the package because the presets set
`CMAKE_PREFIX_PATH` to the pixi environment. `pixi.lock` is updated
automatically — commit it.

## How it works (internals, for when something looks magic)

- The `base` preset in `CMakePresets.json` sets `CC`/`CXX`/`PATH` to the
  toolchain inside `.pixi/envs/default` **by absolute path**, and
  `CMAKE_PREFIX_PATH` to the same prefix. Result: `cmake --preset debug`
  works from any shell with no activation.
- `devtools/build.sh` re-execs itself through `pixi run` when invoked outside
  a pixi shell — this mainly guarantees the environment is installed and
  matches `pixi.lock` before cmake runs.
- `CMAKE_EXPORT_COMPILE_COMMANDS=ON` writes
  `cmake-build-debug/compile_commands.json`, which clangd consumes
  (`--compile-commands-dir` in `.vscode/settings.json`).
- The default C++ standard is declared in `CMakeLists.txt`
  (`CMAKE_CXX_STANDARD 26`); individual targets may override it.
- Targets using threads link `Threads::Threads` — required with the conda
  toolchain, whose sysroot glibc predates the glibc-2.34 pthread merge.

## Troubleshooting

| Symptom | Fix |
| --- | --- |
| Weird cache errors after pulling preset changes | `devtools/clean.sh`, then rebuild |
| Want a fully fresh toolchain | `rm -rf .pixi Interview/.pixi`, then `devtools/build.sh` |
| clangd shows stale errors | Command Palette → "clangd: Restart language server" |
| clangd can't find new build dir | it reads the **debug** compile DB; build debug once |
| `cmake --preset` fails outside pixi | presets need `.pixi/envs/default` to exist — run `devtools/build.sh` once |

Note: the presets hardcode the `x86_64-conda-linux-gnu` compiler triple, so
`platforms = ["linux-64"]` in `pixi.toml` is a hard requirement.
