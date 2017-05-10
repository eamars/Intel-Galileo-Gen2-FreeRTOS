/**
 * @file pci.c
 * @brief PCI configuration register access
 * @author Ran Bao
 * @date May, 2017
 *
 * For more details about PCI configuration register access method, check section 5.5 in quark x1000 datasheet.
 *
 * Furthermore, PCI configuration register access is a common way for accessing devices for x86 architecture CPUs.
 */

#include "pci.h"
#include "galileo_gen_defs.h"

// io port for pci config address
#define IO_PORT_CONFIG_ADDRESS          (uint32_t) 0xcf8
#define IO_PORT_CONFIG_DATA             (uint32_t) 0xcfc

uint32_t pci_config_addr_read_32(pci_config_addr_t addr)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// read from address
	return inl(IO_PORT_CONFIG_DATA);
}

uint16_t pci_config_addr_read_16(pci_config_addr_t addr)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// read from address
	return (uint16_t) inw(IO_PORT_CONFIG_DATA + addr.offset);
}

uint8_t pci_config_addr_read_8(pci_config_addr_t addr)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// read from address
	return (uint8_t) inb(IO_PORT_CONFIG_DATA + (addr.offset));
}

void pci_config_addr_write_32(pci_config_addr_t addr, uint32_t value)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// write to address
	outl(IO_PORT_CONFIG_DATA, value);
}

void pci_config_addr_write_16(pci_config_addr_t addr, uint16_t value)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// write to address
	outw(IO_PORT_CONFIG_DATA + (addr.offset), value);
}

void pci_config_addr_write_8(pci_config_addr_t addr, uint8_t value)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// write to address
	outb(IO_PORT_CONFIG_DATA + (addr.offset), value);
}