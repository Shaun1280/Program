#!/usr/bin/env bash
# Remove all CMake/Conan build output (root workspace and standalone
# Interview builds). Conan-generated CMakeUserPresets.json files are removed
# too, since they reference the deleted build dirs; `conan install`
# (via build.sh) recreates them.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

rm -rf "$SCRIPT_DIR/build" "$SCRIPT_DIR/Interview/build"
rm -f "$SCRIPT_DIR/CMakeUserPresets.json" "$SCRIPT_DIR/Interview/CMakeUserPresets.json"

echo ">> Cleaned."
