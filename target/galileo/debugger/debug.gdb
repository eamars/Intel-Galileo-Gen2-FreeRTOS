# OpenOCD port for GDB communications
target remote tcp:localhost:3333

set breakpoint pending on

monitor halt
