/**
 * @file io_register.c
 * @brief Access register using I/O register method
 * @author Ran Bao
 * @date May, 2015
 */

#include "io_register.h"
#include "galileo_gen_defs.h"

uint32_t io_register_read_32(uint32_t addr)
{
	return inl(addr);
}

uint16_t io_register_read_16(uint32_t addr)
{
	return (uint16_t) inw(addr);
}

uint8_t io_register_read_8(uint32_t addr)
{
	return (uint8_t) inb(addr);
}


void io_register_write_32(uint32_t addr, uint32_t value)
{
	outl(addr, value);
}

void io_register_write_16(uint32_t addr, uint16_t value)
{
	outw(addr, value);
}

void io_register_write_8(uint32_t addr, uint8_t value)
{
	outb(addr, value);
}

void io_register_modify_32(uint32_t addr, uint32_t value, uint32_t mask)
{
	uint32_t temp_value = io_register_read_32(addr) & mask;

	temp_value = (temp_value & ~mask) | (value & mask);

	io_register_write_32(addr, temp_value);
}

void io_register_modify_16(uint32_t addr, uint16_t value, uint16_t mask)
{
	uint16_t temp_value = io_register_read_16(addr) & mask;

	temp_value = (temp_value & ~mask) | (value & mask);

	io_register_write_16(addr, temp_value);
}

void io_register_modify_8(uint32_t addr, uint8_t value, uint8_t mask)
{
	uint8_t temp_value = io_register_read_8(addr) & mask;

	temp_value = (temp_value & ~mask) | (value & mask);

	io_register_write_8(addr, temp_value);
}