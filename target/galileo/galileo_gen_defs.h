/*--------------------------------------------------------------------
 Copyright(c) 2015 Intel Corporation. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in
 the documentation and/or other materials provided with the
 distribution.
 * Neither the name of Intel Corporation nor the names of its
 contributors may be used to endorse or promote products derived
 from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 --------------------------------------------------------------------*/

#ifndef __GALILEO_GEN_DEFS_H__
#define __GALILEO_GEN_DEFS_H__

#ifdef __cplusplus
	extern "C" {
#endif

/*-----------------------------------------------------------------------
 * Any required includes
 *------------------------------------------------------------------------
 */
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>

//---------------------------------------------------------------------
// Prototypes (assembly language functions in startup.S)
//---------------------------------------------------------------------
extern void halt( void );

extern uint32_t inb( uint32_t );
extern uint32_t inw( uint32_t );
extern uint32_t inl( uint32_t );
extern uint32_t outb( uint32_t, uint32_t );
extern uint32_t outw( uint32_t, uint32_t );
extern uint32_t outl( uint32_t, uint32_t) ;

//---------------------------------------------------------------------
// GP definitions
//---------------------------------------------------------------------
#ifndef TRUE
	#define TRUE ( 1 )
#endif

#ifndef FALSE
	#define FALSE ( 0 )
#endif

#ifndef true
	#define true  TRUE
#endif

#ifndef false
	#define false FALSE
#endif

#ifndef OK
	#define OK TRUE
#endif

//---------------------------------------------------------------------
// General bit pattern definitions
//---------------------------------------------------------------------
#ifndef BIT
    #define BIT(x) (1U << (x))
#endif

//---------------------------------------------------------------------
// MMIO support definitions
//---------------------------------------------------------------------
#define EC_BASE			0xE0000000	/* Base of MMConfig space */
#define MMCONFIG_BASE	EC_BASE

static inline uint32_t MMIO_PCI_ADDRESS(uint32_t bus, uint32_t dev, uint32_t fn, uint32_t reg)
{
    return (EC_BASE) +
            (bus << 20) +
            (dev << 15) +
            (fn << 12) +
            (reg);
}

//---------------------------------------------------------------------
// MMIO read/write/set/clear/modify macros
//---------------------------------------------------------------------
static inline uint64_t mem_read(uint32_t base, uint32_t offset, uint32_t size)
{
    volatile uint32_t addr = base + offset;
    volatile uint64_t value;

    switch(size)
    {
        case 1:
            value = (uint8_t)(*((uint8_t *)addr));
            break;
        case 2:
            value = (uint16_t)(*((uint16_t *)addr));
            break;
        case 4:
            value = (uint32_t)(*((uint32_t *)addr));
            break;
        case 8:
            value = (uint64_t)(*((uint64_t *)addr));
            break;
        default:
            halt();
    }

    return value;
}

// No cache bypass necessary -- MTRRs should handle this
static inline void mem_write(uint32_t base, uint32_t offset, uint32_t size, uint32_t value)
{
    volatile uint32_t addr = base + offset;

    switch (size)
    {
        case 1:
            *((uint8_t *)addr) = (uint8_t)(value);
            break;
        case 2:
            *((uint16_t *)addr) = (uint16_t)(value);
            break;
        case 4:
            *((uint32_t *)addr) = (uint32_t)(value);
            break;
        case 8:
            *((uint64_t *)addr) = (uint64_t)(value);
            break;
        default:
            halt();
    }
}

static inline void mem_set(uint32_t base, uint32_t offset, uint32_t size, uint32_t mask)
{
    volatile uint32_t addr = base + offset;

    switch (size) {
    case 1:
        *((uint8_t *)addr) = (uint8_t)((*((uint8_t *)addr)) | (mask));
        break;
    case 2:
        *((uint16_t *)addr) = (uint16_t)((*((uint16_t *)addr)) | (mask));
        break;
    case 4:
        *((uint32_t *)addr) = (uint32_t)((*((uint32_t *)addr)) | (mask));
        break;
    case 8:
        *((uint64_t *)addr) = (uint64_t)((*((uint64_t *)addr)) | (mask));
        break;
    }
}

static inline void mem_clear(uint32_t base, uint32_t offset, uint32_t size, uint32_t mask)
{
    volatile uint32_t addr = base + offset;

    switch (size) {
        case 1:
            *((uint8_t *)addr) = (uint8_t)((*((uint8_t *)addr)) & ~(mask));
            break;
        case 2:
            *((uint16_t *)addr) = (uint16_t)((*((uint16_t *)addr)) & ~(mask));
            break;
        case 4:
            *((uint32_t *)addr) = (uint32_t)((*((uint32_t *)addr)) & ~(mask));
            break;
        case 8:
            *((uint64_t *)addr) = (uint64_t)((*((uint64_t *)addr)) & ~(mask));
            break;
    }
}

static inline void mem_modify(uint32_t base, uint32_t offset, uint32_t size, uint32_t cmask, uint32_t smask)
{
    volatile uint32_t addr = base + offset;
    switch (size) {
    case 1:
        *((uint8_t *)addr) = (uint8_t)((*((uint8_t *)addr) & ~(cmask)) | (smask));
        break;
    case 2:
        *((uint16_t *)addr) = (uint16_t)((*((uint16_t *)addr) & ~(cmask)) | (smask));
        break;
    case 4:
        *((uint32_t *)addr) = (uint32_t)((*((uint32_t *)addr) & ~(cmask)) | (smask));
        break;
    case 8:
        *((uint64_t *)addr) = (uint64_t)((*((uint64_t *)addr) & ~(cmask)) | (smask));
        break;
    }
}

#ifdef __cplusplus
	} /* extern C */
#endif

#endif /* GALILEO_GEN_DEFS */

