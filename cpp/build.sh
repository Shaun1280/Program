#!/usr/bin/env bash
# Build the cpp workspace with Conan + CMake presets.
#
#   ./build.sh [debug|release]     (default: release)
#
# Steps: conan install -> cmake configure -> cmake build.
# Safe to run repeatedly; Conan/CMake skip work that is already up to date.
#
# CLion: run this once from the terminal, then select the "debug" / "release"
# CMake profile (loaded from CMakePresets.json) and build as usual.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

BUILD_TYPE="$(tr '[:upper:]' '[:lower:]' <<< "${1:-release}")"
case "$BUILD_TYPE" in
    debug)   CMAKE_BUILD_TYPE=Debug ;;
    release) CMAKE_BUILD_TYPE=Release ;;
    *) echo "usage: $0 [debug|release]" >&2; exit 1 ;;
esac

# First-time Conan setup: create a default profile if there isn't one.
if ! conan profile path default &>/dev/null; then
    echo ">> No default Conan profile found, detecting..."
    conan profile detect --force
fi

# Use gcc-15 to match the Conan profile (compiler.version=15, cppstd=26).
# Requires CMake >= 3.30 for gcc-15's -std=c++26 flag (pipx cmake provides it).
# Conan honors CC/CXX for package builds; CMake honors them at first configure.
# (Override by exporting CC/CXX before calling this script.)
export CC="${CC:-gcc-15}"
export CXX="${CXX:-g++-15}"

echo ">> Conan install ($CMAKE_BUILD_TYPE, $CXX)..."
conan install . \
    --output-folder="cmake-build-$BUILD_TYPE" \
    --settings=build_type="$CMAKE_BUILD_TYPE" \
    --build=missing

echo ">> CMake configure (preset: $BUILD_TYPE)..."
cmake --preset "$BUILD_TYPE"

echo ">> CMake build (preset: $BUILD_TYPE)..."
cmake --build --preset "$BUILD_TYPE"

echo ">> Done. Binaries are in cmake-build-$BUILD_TYPE/"
