#!/usr/bin/env bash

#compila e roda a engine em modo Debug com AddressSanitizer (ASan) UndefinedBehaviorSanitizer (UBSan) ativados.

set -e

BUILD_DIR="build_debug"

if [ "$1" == "clean" ]; then
    echo ">> Limpando build de debug"
    rm -rf "$BUILD_DIR"
fi

if [ ! -d "$BUILD_DIR" ]; then
    echo ">> Criando diretório de build de debug"
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

echo ">> Configurando CMake (Debug + sanitizers)"
cmake .. -DCMAKE_BUILD_TYPE=Debug

echo ">> Compilando"
make -j"$(nproc)"

echo ""
echo "   [[Qualquer erro de memória ou comportamento indefinido vai aparecer abaixo]]"
echo ""

ASAN_OPTIONS=abort_on_error=1:detect_leaks=1:symbolize=1 ./engine

cd ..