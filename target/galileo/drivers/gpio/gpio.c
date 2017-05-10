/**
 * @file gpio.c
 * @brief GPIO ports connecting to GPIO controller
 * @author Ran Bao
 * @date May, 2017
 */

#include "gpio.h"
#include "pci.h"
#include "galileo_support.h"

#define GPIO_BASE_BUS               0
#define GPIO_BASE_DEVICE            21
#define GPIO_BASE_FUNCTION          2

#define BAR1_BASE_BUS               0
#define BAR1_BASE_DEVICE            21
#define BAR1_BASE_FUNCTION          2
#define BAR1_BASE_OFFSET            0x14

void gpio_controller_init(void)
{
	// read BAR1 address from pci for GPIO controller as defined in section 18.5.11
	pci_config_addr_t bar1_base_address_pci_addr =
			{
					.bus = BAR1_BASE_BUS,
					.device = BAR1_BASE_DEVICE,
					.function = BAR1_BASE_FUNCTION,
					.offset = BAR1_BASE_OFFSET
			};

	uint32_t bar1_base_address = pci_config_addr_read_32(bar1_base_address_pci_addr);

	g_printf_rcc( 7, 2, DEFAULT_SCREEN_COLOR, "BAR1 Address = 0x%x%\r\n", bar1_base_address);
}