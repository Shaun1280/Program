#!/usr/bin/env bash
# Remove all CMake build output (root workspace and standalone
# Interview builds). The pixi environments (.pixi/) are kept; delete
# them manually if you want a fully fresh toolchain install.

set -euo pipefail

DEVTOOLS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$DEVTOOLS_DIR")"

rm -rf "$PROJECT_ROOT"/cmake-build-* "$PROJECT_ROOT"/Interview/cmake-build-* "$PROJECT_ROOT/build"

echo ">> Cleaned."
