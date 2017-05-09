/**
 * @file legacy_gpio.c
 * @brief Legacy GPIO port
 * @author Ran Bao
 * @date May, 2017
 */

#include <stdio.h>
#include <stdbool.h>

#include "galileo_gen_defs.h"
#include "legacy_gpio.h"
#include "io_register.h"
#include "pci.h"

#define LEGACY_GPIO_BASE_BUS                0
#define LEGACY_GPIO_BASE_DEVICE             31
#define LEGACY_GPIO_BASE_FUNCTION           0
#define LEGACY_GPIO_BASE_OFFSET             0x44
#define LEGACY_GPIO_BASE_ADDRESS_MASK       0x0000FFC0

// Table 136 specifies definitions of these control registers
#define CGEN_OFFSET                         0x0
#define CGIO_OFFSET                         0x4
#define CGLVL_OFFSET                        0x8
#define CGTPE_OFFSET                        0xC
#define CGTNE_OFFSET                        0x10
#define CGGPE_OFFSET                        0x14
#define CGSMI_OFFSET                        0x18
#define CGTS_OFFSET                         0x1C
#define RGEN_OFFSET                         0x20
#define RGIO_OFFSET                         0x24
#define RGLVL_OFFSET                        0x28
#define RGTPE_OFFSET                        0x2C
#define RGTNE_OFFSET                        0x30
#define RGGPE_OFFSET                        0x34
#define RGSMI_OFFSET                        0x38
#define RGTS_OFFSET                         0x3C
#define CGNMIEN_OFFSET                      0x40
#define RGNMIEN_OFFSET                      0x44


static bool is_legacy_gpio_initialized = false;

static void legacy_gpio_controller_init(void)
{
	// get GPIO base address
	const pci_config_addr_t legacy_gpio_base_address_pci_addr =
			{
					.bus = LEGACY_GPIO_BASE_BUS,
					.device = LEGACY_GPIO_BASE_DEVICE,
					.function = LEGACY_GPIO_BASE_FUNCTION,
					.offset = LEGACY_GPIO_BASE_OFFSET
			};

	uint32_t legacy_gpio_base_address = pci_config_addr_read_32(legacy_gpio_base_address_pci_addr) & LEGACY_GPIO_BASE_ADDRESS_MASK;

	io_register_write_32(legacy_gpio_base_address + CGEN_OFFSET, 0x03);
	io_register_write_32(legacy_gpio_base_address + CGIO_OFFSET, 0x03);
	io_register_write_32(legacy_gpio_base_address + CGLVL_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + CGTPE_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + CGTNE_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + CGGPE_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + CGSMI_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + CGTS_OFFSET, 0x03);
	io_register_write_32(legacy_gpio_base_address + CGTS_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + RGEN_OFFSET, 0x3f);
	io_register_write_32(legacy_gpio_base_address + RGIO_OFFSET, 0x1c);
	io_register_write_32(legacy_gpio_base_address + RGLVL_OFFSET, 0x02);
	io_register_write_32(legacy_gpio_base_address + RGTPE_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + RGTNE_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + RGGPE_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + RGSMI_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + RGTS_OFFSET, 0x3f);
	io_register_write_32(legacy_gpio_base_address + CGNMIEN_OFFSET, 0x00);
	io_register_write_32(legacy_gpio_base_address + RGNMIEN_OFFSET, 0x00);
}

void legacy_gpio_init(legacy_gpio_t *obj, uint32_t pin, uint32_t direction, uint32_t value)
{
	// if legacy gpio is not yet initialized, then initialize the gpio port first
	if (!is_legacy_gpio_initialized)
	{
		is_legacy_gpio_initialized = true;

		legacy_gpio_controller_init();
	}

	// get GPIO base address
	const pci_config_addr_t legacy_gpio_base_address_pci_addr =
			{
					.bus = LEGACY_GPIO_BASE_BUS,
					.device = LEGACY_GPIO_BASE_DEVICE,
					.function = LEGACY_GPIO_BASE_FUNCTION,
					.offset = LEGACY_GPIO_BASE_OFFSET
			};

	uint32_t legacy_gpio_base_address = pci_config_addr_read_32(legacy_gpio_base_address_pci_addr) & LEGACY_GPIO_BASE_ADDRESS_MASK;

	// store pin
	obj->pin_mask = BIT(pin);

	// enable pin
	io_register_modify_32(legacy_gpio_base_address + RGEN_OFFSET, obj->pin_mask, obj->pin_mask);

	// set direction
	io_register_modify_32(legacy_gpio_base_address + RGIO_OFFSET, direction << pin, obj->pin_mask);

	// set output value
	io_register_modify_32(legacy_gpio_base_address + RGLVL_OFFSET, value << pin, obj->pin_mask);
}
