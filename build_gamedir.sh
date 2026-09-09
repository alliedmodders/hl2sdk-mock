#!/bin/bash
# vim: set ts=8 sts=4 sw=4 tw=99 et:

if [ $# -ne 2 ]; then
    echo "Usage: <game_dir> <src_dir>"
    exit 1;
fi

mkdir -p "${1}"
for i in $(cd "${2}" && find . -mindepth 1 | sed 's|^\./||'); do
    srcpath=$(realpath ${2}/${i})
    dstpath=${1}/${i}
    if [[ -d "${srcpath}" ]]; then
        mkdir -p "$dstpath"
    elif [ ! -f $dstpath ] && [ ! -L $dstpath ]; then
        ln -s "${srcpath}" "$dstpath"
    fi
done
