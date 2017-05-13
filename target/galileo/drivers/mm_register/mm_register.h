/**
 * @file mm_register.h
 * @brief Memory Referenced Register access
 * @author Ran Bao
 * @date May, 2015
 */

#ifndef MM_REGISTER_H_
#define MM_REGISTER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t mm_register_read_32(uint32_t addr);
uint16_t mm_register_read_16(uint32_t addr);
uint8_t mm_register_read_8(uint32_t addr);

void mm_register_write_32(uint32_t addr, uint32_t value);
void mm_register_write_16(uint32_t addr, uint16_t value);
void mm_register_write_8(uint32_t addr, uint8_t value);

void mm_register_modify_32(uint32_t addr, uint32_t value, uint32_t mask);
void mm_register_modify_16(uint32_t addr, uint16_t value, uint16_t mask);
void mm_register_modify_8(uint32_t addr, uint8_t value, uint8_t mask);


#ifdef __cplusplus
}
#endif

#endif /* MM_REGISTER_H_ */