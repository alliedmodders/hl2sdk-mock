#!/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Usage: <objdir>"
    exit 1;
fi

set -x

rsync -av "${1}/lib/" "lib/"
