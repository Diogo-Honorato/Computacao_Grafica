#!/usr/bin/env bash

#compila e roda a engine sem debug.

set -e

BUILD_DIR="build"

if [ "$1" == "clean" ]; then
    echo ">> Limpando build"
    rm -rf "$BUILD_DIR"
fi

if [ ! -d "$BUILD_DIR" ]; then
    echo ">> Criando diretório de build de debug"
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=Release

make -j"$(nproc)"

./engine

cd ..