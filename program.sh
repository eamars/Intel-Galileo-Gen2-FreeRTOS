#!/usr/bin/env bash

GDB_EXECUTABLE="../i686-elf/bin/i686-elf-gdb"

${GDB_EXECUTABLE} -batch -x target/galileo/debugger/program.gdb
