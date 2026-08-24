#!/usr/bin/env bash
# Remove this project's CMake build output. The pixi environment (.pixi/)
# is kept; delete it manually if you want a fully fresh toolchain install.

set -euo pipefail

DEVTOOLS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$DEVTOOLS_DIR")"

rm -rf "$PROJECT_ROOT"/cmake-build-*

echo ">> Cleaned."
