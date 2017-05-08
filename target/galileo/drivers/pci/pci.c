/**
 *
 */

#include "pci.h"

// assembly routine defined in startup.S
extern uint32_t inb( int32_t );
extern uint32_t inw( int32_t );
extern uint32_t inl( int32_t );
extern uint32_t outb( int32_t, int32_t );
extern uint32_t outw( int32_t, int32_t );
extern uint32_t outl( int32_t, int32_t) ;

// io port for pci config address
#define IO_PORT_CONFIG_ADDRESS          0xcf8
#define IO_PORT_CONFIG_DATA             0xcfc

uint32_t pci_config_addr_read(pci_config_addr_t addr)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// read from address
	return inl(IO_PORT_CONFIG_DATA);
}

void pci_config_addr_write(pci_config_addr_t addr, uint32_t value)
{
	// enable space mapping
	addr.enable_space_mapping = 1;

	// set address for indirect access mode
	outl(IO_PORT_CONFIG_ADDRESS, addr.address);

	// write to address
	outl(IO_PORT_CONFIG_DATA, value);
}