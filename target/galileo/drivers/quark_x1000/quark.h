/**
 * @file quark.h
 * @brief General defintions for Intel Quark SoC X1000 processor
 * @author Ran Bao
 * @date May, 2017
 */

#ifndef QUARK_X1000_H_
#define QUARK_X1000_H_

#include <stdint.h>

static inline uint32_t bit_modify(uint32_t target, uint32_t value, uint32_t mask)
{
	return (target & ~mask) | (value & mask);
}


#endif /* QUARK_X1000_H_ */