#!/usr/bin/env bash

GDB_EXECUTABLE="../i686-elf/bin/i686-elf-gdb"

EXECUTABLE=debug/FREERTOS_DEMO.elf

${GDB_EXECUTABLE} -x target/galileo/debugger/debug.gdb ${EXECUTABLE} -tui
