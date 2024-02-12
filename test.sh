#! /usr/bin/env bash

cmake -S. -Bbuild
cmake --build build
cd build && ctest