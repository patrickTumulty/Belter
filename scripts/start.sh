#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR" || exit 1

if [[ "$1" == "--debug" ]]; then 
    shift 
    gdb ./bin/belter "$@"
else
    ./bin/belter "$@"
fi
