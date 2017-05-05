#!/usr/bin/env bash

# generate makefile
cmake -trace -DBUILD_TARGET=galileo -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
