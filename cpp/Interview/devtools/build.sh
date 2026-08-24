#!/usr/bin/env bash
# Build this project with pixi + CMake presets.
#
#   devtools/build.sh [debug|release]     (default: release)
#
# Steps: cmake configure -> cmake build, inside the pixi environment
# (pixi.toml provides the gcc toolchain, cmake, ninja and gtest).
# Safe to run repeatedly; CMake skips work that is already up to date.
#
# VSCode: run this once, then pick the "debug" / "release" configure preset
# in CMake Tools and build from the editor.

set -euo pipefail

DEVTOOLS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$DEVTOOLS_DIR")"
cd "$PROJECT_ROOT"

BUILD_TYPE="$(tr '[:upper:]' '[:lower:]' <<< "${1:-release}")"
case "$BUILD_TYPE" in
    debug|release) ;;
    *) echo "usage: $0 [debug|release]" >&2; exit 1 ;;
esac

# Outside a pixi shell, re-exec inside the project environment so cmake,
# ninja and the conda toolchain are the pixi-provided ones. The presets
# also reference the toolchain by absolute path, so this mainly guarantees
# the pixi env is installed and up to date.
if [[ -z "${PIXI_IN_SHELL:-}" ]]; then
    exec "${PIXI:-$HOME/.pixi/bin/pixi}" run --manifest-path "$PROJECT_ROOT/pixi.toml" \
        bash "$DEVTOOLS_DIR/build.sh" "$BUILD_TYPE"
fi

echo ">> CMake configure (preset: $BUILD_TYPE)..."
cmake --preset "$BUILD_TYPE"

echo ">> CMake build (preset: $BUILD_TYPE)..."
cmake --build --preset "$BUILD_TYPE"

echo ">> Done. Binaries are in cmake-build-$BUILD_TYPE/"
