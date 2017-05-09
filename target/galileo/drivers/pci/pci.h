/**
 * @file pci.h
 * @brief PCI configuration register access
 * @author Ran Bao
 * @date May, 2017
 *
 * For more details about PCI configuration register access method, check section 5.5 in quark x1000 datasheet.
 *
 * Furthermore, PCI configuration register access is a common way for accessing devices for x86 architecture CPUs.
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

#ifdef __cplusplus
extern "C" {
#endif

uint32_t pci_config_addr_read_32(pci_config_addr_t addr);
uint16_t pci_config_addr_read_16(pci_config_addr_t addr);
uint8_t pci_config_addr_read_8(pci_config_addr_t addr);

void pci_config_addr_write_32(pci_config_addr_t addr, uint32_t value);
void pci_config_addr_write_16(pci_config_addr_t addr, uint16_t value);
void pci_config_addr_write_8(pci_config_addr_t addr, uint8_t value);



#ifdef __cplusplus
}
#endif

#endif /* PCI_H_ */