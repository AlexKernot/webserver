#! /usr/bin/env bash

cmake -D CMAKE_CXX_COMPILER=clang++ -S. -Bbuild
cmake --build build
cd build && ctest --output-on-failure