/**
 *
 */

#ifndef PCI_H_
#define PCI_H_

#include <stdint.h>

typedef union
{
	struct __attribute__((packed)) // no data alignment
	{
		uint32_t offset         : 8;
		uint32_t function       : 3;
		uint32_t device         : 5;
		uint32_t bus            : 8;
		uint32_t reserved       : 7;
		uint32_t enable_space_mapping : 1;
	};

	uint32_t address;
} pci_config_addr_t;

uint32_t pci_config_addr_read(pci_config_addr_t addr);
void pci_config_addr_write(pci_config_addr_t addr, uint32_t value);


#endif /* PCI_H_ */