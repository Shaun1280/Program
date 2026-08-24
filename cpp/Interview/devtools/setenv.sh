#!/usr/bin/env bash
# Activate this project's pixi environment in the CURRENT shell:
#
#   source devtools/setenv.sh
#
# Afterwards cmake, ninja, clangd and the conda gcc are on PATH, and
# CONDA_PREFIX / CC / CXX point into the pixi env — so plain
# `cmake --preset debug`, `ctest --preset debug`, or ad-hoc g++ calls
# all use the pixi toolchain. Deactivate by opening a new shell.

# Must be sourced, not executed.
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    echo "usage: source $0   (this script modifies your current shell environment)" >&2
    exit 1
fi

_DEVTOOLS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
_PROJECT_ROOT="$(dirname "$DEVTOOLS_DIR")"
_PIXI="${PIXI:-$HOME/.pixi/bin/pixi}"

# Install the environment on first use.
if [[ ! -d "$_PROJECT_ROOT/.pixi/envs/default" ]]; then
    echo ">> pixi environment not found, installing..."
    "$_PIXI" install --manifest-path "$_PROJECT_ROOT/pixi.toml" || return 1
fi

# pixi's shell-hook is the equivalent of `conda activate` (sets PATH,
# CONDA_PREFIX, PIXI_* and runs package activation scripts).
eval "$("$_PIXI" shell-hook --manifest-path "$_PROJECT_ROOT/pixi.toml")"

# The compiler packages only ship triple-prefixed binaries; export CC/CXX
# so tools that consult them (e.g. a bare `cmake -B build`) pick the
# conda gcc instead of the system one.
export CC="$CONDA_PREFIX/bin/x86_64-conda-linux-gnu-cc"
export CXX="$CONDA_PREFIX/bin/x86_64-conda-linux-gnu-c++"

echo ">> pixi env '$PIXI_PROJECT_NAME' activated: $(cmake --version | head -1), gcc $("$CXX" -dumpfullversion)"

unset _DEVTOOLS_DIR _PROJECT_ROOT _PIXI
