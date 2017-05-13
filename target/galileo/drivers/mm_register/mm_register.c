/**
 * @file mm_register.h
 * @brief Memory Referenced Register access
 * @author Ran Bao
 * @date May, 2015
 */

#include "mm_register.h"

uint32_t mm_register_read_32(uint32_t addr)
{
	return *((uint32_t *) addr);
}

uint16_t mm_register_read_16(uint32_t addr)
{
	return *((uint16_t *) addr);
}

uint8_t mm_register_read_8(uint32_t addr)
{
	return *((uint8_t *) addr);
}

void mm_register_write_32(uint32_t addr, uint32_t value)
{
	*((uint32_t *) addr) = value;
}

void mm_register_write_16(uint32_t addr, uint16_t value)
{
	*((uint16_t *) addr) = value;
}

void mm_register_write_8(uint32_t addr, uint8_t value)
{
	*((uint8_t *) addr) = value;
}

void mm_register_modify_32(uint32_t addr, uint32_t value, uint32_t mask)
{
	uint32_t temp_value = mm_register_read_32(addr) & mask;

	temp_value = (temp_value & ~mask) | (value & mask);

	mm_register_write_32(addr, temp_value);
}

void mm_register_modify_16(uint32_t addr, uint16_t value, uint16_t mask)
{
	uint16_t temp_value = mm_register_read_16(addr) & mask;

	temp_value = (temp_value & ~mask) | (value & mask);

	mm_register_write_16(addr, temp_value);
}

void mm_register_modify_8(uint32_t addr, uint8_t value, uint8_t mask)
{
	uint8_t temp_value = mm_register_read_8(addr) & mask;

	temp_value = (temp_value & ~mask) | (value & mask);

	mm_register_write_8(addr, temp_value);
}