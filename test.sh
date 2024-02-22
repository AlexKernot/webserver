#! /usr/bin/env bash

clear
cmake -DCMAKE_BUILD_TYPE=Debug -D CMAKE_CXX_COMPILER=clang++ -S. -Bbuild && cmake --build build && cd build && ctest --output-on-failure --gtest_break_on_failure