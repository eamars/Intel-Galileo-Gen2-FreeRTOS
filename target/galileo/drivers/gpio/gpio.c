/**
 * @file gpio.c
 * @brief GPIO ports connecting to GPIO controller
 * @author Ran Bao
 * @date May, 2017
 */

#include <stdbool.h>
#include "gpio.h"
#include "pci.h"
#include "io_register.h"
#include "galileo_support.h"

#define PCI_CONFIG_BASE_BUS         0
#define PCI_CONFIG_BASE_DEVICE      21
#define PCI_CONFIG_BASE_FUNCTION    2
#define PCI_CONFIG_BASE_OFFSET      0x4

#define BAR1_BASE_BUS               0
#define BAR1_BASE_DEVICE            21
#define BAR1_BASE_FUNCTION          2
#define BAR1_BASE_OFFSET            0x14

#define GPIO_SWPORTA_DR_OFFSET      0x0
#define GPIO_SWPORTA_DDR_OFFSET     0x4
#define GPIO_INTEN_OFFSET           0x30
#define GPIO_INTMASK_OFFSET         0x34
#define GPIO_INTTYPE_LEVEL_OFFSET   0x38
#define GPIO_INT_POLARITY_OFFSET    0x3C
#define GPIO_INTSTATUS_OFFSET       0x40
#define GPIO_RAW_INTSTATUS_OFFSET   0x44
#define GPIO_DEBOUNCE_OFFSET        0x48
#define GPIO_PORTA_EOI_OFFSET       0x4C
#define GPIO_EXT_PORTA_OFFSET       0x50
#define GPIO_LS_SYNC_OFFSET         0x60


static bool is_gpio_initialized = false;

void gpio_controller_init(void)
{
	// get base address
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	io_register_write_32(bar1_base_address + GPIO_SWPORTA_DR_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_SWPORTA_DDR_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_INTEN_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_INTMASK_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_INTTYPE_LEVEL_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_INT_POLARITY_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_INTSTATUS_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_RAW_INTSTATUS_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_DEBOUNCE_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_PORTA_EOI_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_EXT_PORTA_OFFSET, 0x0);
	io_register_write_32(bar1_base_address + GPIO_LS_SYNC_OFFSET, 0x0);
}

void gpio_init(gpio_t *obj, uint32_t pin, uint32_t direction, uint32_t value)
{
	if (!is_gpio_initialized)
	{
		is_gpio_initialized = true;

		gpio_controller_init();
	}

	// get base address
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	// calculate pin mask
	uint32_t pin_mask = 1UL << pin;

	// store pin
	obj->pin = pin;

	// set direction
	io_register_modify_32(bar1_base_address + GPIO_SWPORTA_DDR_OFFSET, direction << pin, pin_mask);

	// set output value
	io_register_modify_32(bar1_base_address + GPIO_SWPORTA_DR_OFFSET, value << pin, pin_mask);
}


uint32_t gpio_read(gpio_t *obj)
{
	// get base address
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	uint32_t pin_mask = 1UL << obj->pin;

	return (io_register_read_32(bar1_base_address + GPIO_SWPORTA_DR_OFFSET) & pin_mask);
}

void gpio_write(gpio_t *obj, uint32_t value)
{
	// get base address
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	uint32_t pin_mask = 1UL << obj->pin;

	io_register_modify_32(bar1_base_address + GPIO_SWPORTA_DR_OFFSET, value << obj->pin, pin_mask);
}

uint32_t gpio_get_direction(gpio_t *obj)
{
	// get base address
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	uint32_t pin_mask = 1UL << obj->pin;

	return (io_register_read_32(bar1_base_address + GPIO_SWPORTA_DDR_OFFSET) & pin_mask);
}

void gpio_set_direction(gpio_t *obj, uint32_t value)
{
	// get base address
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	uint32_t pin_mask = 1UL << obj->pin;

	io_register_modify_32(bar1_base_address + GPIO_SWPORTA_DDR_OFFSET, value << obj->pin, pin_mask);
}