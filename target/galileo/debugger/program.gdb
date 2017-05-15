# OpenOCD port for GDB communications
target remote tcp:localhost:3333

monitor halt

monitor reg eflags 0x0
flushregs
file debug/FREERTOS_DEMO.elf
monitor load_image debug/FREERTOS_DEMO.elf 0

monitor reset
monitor halt
set $eip=_restart
continue
