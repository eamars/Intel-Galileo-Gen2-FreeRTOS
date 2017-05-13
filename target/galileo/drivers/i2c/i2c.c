/**
 * @file i2c.h
 * @brief I2C controller driver
 * @author Ran Bao
 * @date May, 2017
 */


#include "i2c.h"
#include "pci.h"
#include "mm_register.h"
#include "quark.h"
#include "galileo_support.h"


#define PCI_CONFIG_BASE_BUS         0
#define PCI_CONFIG_BASE_DEVICE      21
#define PCI_CONFIG_BASE_FUNCTION    2
#define PCI_CONFIG_BASE_OFFSET      0x4

#define BAR0_BASE_BUS               0
#define BAR0_BASE_DEVICE            21
#define BAR0_BASE_FUNCTION          2
#define BAR0_BASE_OFFSET            0x10

#define IC_CON_OFFSET               0x0
#define IC_TAR_OFFSET               0x4
#define IC_DATA_CMD_OFFSET          0x10
#define IC_SS_SCL_HCNT_OFFSET       0x14
#define IC_SS_SCL_LCNT_OFFSET       0x18
#define IC_FS_SCL_HCNT_OFFSET       0x1C
#define IC_INTR_STAT_OFFSET         0x2C
#define IC_INTR_MASK_OFFSET         0x30
#define IC_RAW_INTR_STAT            0x34
#define IC_RX_TL_OFFSET             0x38
#define IC_TX_TL_OFFSET             0x3C
#define IC_CLR_INTR_OFFSET          0x40
#define IC_CLR_RX_UNDER_OFFSET      0x44
#define IC_CLR_RX_OVER_OFFSET       0x48
#define IC_CLR_TX_OVER_OFFSET       0x4C
#define IC_CLR_RD_REQ_OFFSET        0x50
#define IC_CLR_TX_ABRT_OFFSET       0x54
#define IC_CLR_ACTIVITY_OFFSET      0x5C
#define IC_CLR_STOP_DET_OFFSET      0x60
#define IC_CLR_START_DET_OFFSET     0x64
#define IC_ENABLE_OFFSET            0x6C
#define IC_STATS_OFFSET             0x70
#define IC_TXFLR_OFFSET             0x74
#define IC_RXFLR_OFFSET             0x78
#define IC_SDA_HOLD_OFFSET          0x7C
#define IC_TX_ABRT_SOURCE_OFFSET    0x80
#define IC_ENABLE_STATUS_OFFSET     0x9C
#define IC_FS_SPKLEN_OFFSET         0xA0

#define TI2C_POLL                   25 // 25 us
#define MAX_T_POLL_COUNT            100UL

extern void vMicroSecondDelay(uint32_t DelayTime);


static bool is_i2c_initialized = false;

static inline i2c_error_t i2c_controller_disable(uint32_t bar0_base_address)
{
	mm_register_modify_32(bar0_base_address + IC_ENABLE_OFFSET, 0x0, 0x1);

	for (uint32_t poll_count = 0; poll_count < MAX_T_POLL_COUNT, poll_count++)
	{
		// read from enable status
		uint32_t ic_en = mm_register_read_32(bar0_base_address + IC_ENABLE_STATUS_OFFSET) & 0x1;

		// if controller is disabled, then exit with success
		if (!ic_en)
		{
			return I2C_NO_ERROR;
		}
		else
		{
			vMicroSecondDelay(TI2C_POLL);
		}
	}

	// timeout
	return I2C_TIMEOUT;
}

static inline void i2c_controller_enable(uint32_t bar0_base_address)
{
	mm_register_modify_32(bar0_base_address + IC_ENABLE_OFFSET, 0x1, 0x1);
}

static void i2c_controller_init(void)
{
	// get base address
	pci_config_addr_t bar0_base_address_pci_addr =
			{
					.bus = BAR0_BASE_BUS,
					.device = BAR0_BASE_DEVICE,
					.function = BAR0_BASE_FUNCTION,
					.offset = BAR0_BASE_OFFSET
			};

	uint32_t bar0_base_address = pci_config_addr_read_32(bar0_base_address_pci_addr);

	// disable i2c controller at first place
	i2c_controller_disable(bar0_base_address);

	// enable master mode
	mm_register_modify_32(bar0_base_address + IC_CON_OFFSET, 1 << 0, 1 << 0);

	// set speed mode to standard
	mm_register_modify_32(bar0_base_address + IC_CON_OFFSET, 1 << 1, 3 << 1);

	// set 7 bit addressing mode
	mm_register_modify_32(bar0_base_address + IC_CON_OFFSET, 0 << 4, 1 << 4);

	// enable restart support
	mm_register_modify_32(bar0_base_address + IC_CON_OFFSET, 1 << 5, 1 << 5);

	// enable i2c controller
	i2c_controller_enable(bar0_base_address);
}

void i2c_init(i2c_t *obj)
{
	if (!is_i2c_initialized)
	{
		is_i2c_initialized = true;

		i2c_controller_init();
	}
}

void i2c_speed_mode(i2c_t *obj, i2c_speed_mode_t speed_mode)
{
	// get base address
	pci_config_addr_t bar0_base_address_pci_addr =
			{
					.bus = BAR0_BASE_BUS,
					.device = BAR0_BASE_DEVICE,
					.function = BAR0_BASE_FUNCTION,
					.offset = BAR0_BASE_OFFSET
			};

	uint32_t bar0_base_address = pci_config_addr_read_32(bar0_base_address_pci_addr);

	// disable i2c controller at first place
	i2c_controller_disable(bar0_base_address);

	// set speed mode
	mm_register_modify_32(bar0_base_address + IC_CON_OFFSET, speed_mode << 1, 3 << 1);

	// enable i2c controller
	i2c_controller_enable(bar0_base_address);
}

void i2c_address_mode(i2c_t *obj, i2c_address_t address_mode)
{
	// get base address
	pci_config_addr_t bar0_base_address_pci_addr =
			{
					.bus = BAR0_BASE_BUS,
					.device = BAR0_BASE_DEVICE,
					.function = BAR0_BASE_FUNCTION,
					.offset = BAR0_BASE_OFFSET
			};

	uint32_t bar0_base_address = pci_config_addr_read_32(bar0_base_address_pci_addr);

	// disable i2c controller at first place
	i2c_controller_disable(bar0_base_address);

	// set address mode
	mm_register_modify_32(bar0_base_address + IC_CON_OFFSET, address_mode << 4, 1 << 4);

	// enable i2c controller
	i2c_controller_enable(bar0_base_address);
}

void i2c_start(i2c_t *obj)
{

}

void i2c_stop(i2c_t *obj)
{

}

void i2c_reset(i2c_t *obj)
{

}

int32_t i2c_read(i2c_t *obj, i2c_address_t address, uint8_t *data, size_t length)
{
	// get base address
	pci_config_addr_t bar0_base_address_pci_addr =
			{
					.bus = BAR0_BASE_BUS,
					.device = BAR0_BASE_DEVICE,
					.function = BAR0_BASE_FUNCTION,
					.offset = BAR0_BASE_OFFSET
			};

	uint32_t bar0_base_address = pci_config_addr_read_32(bar0_base_address_pci_addr);

	// disable i2c controller
	i2c_controller_disable(bar0_base_address);

	// write slave address
	mm_register_modify_32(bar0_base_address + IC_TAR_OFFSET, address, 0x3FF);

	// enable i2c controller
	i2c_controller_enable(bar0_base_address);

	// write a "read" command to the slave

	// initialize a read command
	uint32_t ic_data_cmd = mm_register_read_32(bar0_base_address + IC_DATA_CMD_OFFSET);

	// write data
	ic_data_cmd = bit_modify(ic_data_cmd, 0x00, 0xFF);

	// set read command
	ic_data_cmd = bit_modify(ic_data_cmd, 1 << 8, 1 << 8);

	// write to register
	mm_register_write_32(bar0_base_address + IC_DATA_CMD_OFFSET, ic_data_cmd);

	// "read" command transmit complete

	// start receiving process

	// count number of bytes actually transmitted
	int32_t actual_length = 0;

	for (size_t i = 0; i < length; i++, data++)
	{
		// TODO: poll from fifo
	}
}

int32_t i2c_write(i2c_t *obj, i2c_address_t address, const uint8_t *data, size_t length, bool stop)
{
	// get base address
	pci_config_addr_t bar0_base_address_pci_addr =
			{
					.bus = BAR0_BASE_BUS,
					.device = BAR0_BASE_DEVICE,
					.function = BAR0_BASE_FUNCTION,
					.offset = BAR0_BASE_OFFSET
			};

	uint32_t bar0_base_address = pci_config_addr_read_32(bar0_base_address_pci_addr);

	// disable i2c controller
	i2c_controller_disable(bar0_base_address);

	// write slave address
	mm_register_modify_32(bar0_base_address + IC_TAR_OFFSET, address, 0x3FF);

	// enable i2c controller
	i2c_controller_enable(bar0_base_address);

	// count number of bytes actually transmitted
	int32_t actual_length = 0;

	for (size_t i = 0; i < length; i++, data++)
	{
		uint32_t ic_data_cmd = mm_register_read_32(bar0_base_address + IC_DATA_CMD_OFFSET);

		// write data
		ic_data_cmd = bit_modify(ic_data_cmd, *data, 0xFF);

		// set write command
		ic_data_cmd = bit_modify(ic_data_cmd, 0 << 8, 1 << 8);

		// set stop bit condition on last byte
		if (i == length - 1)
		{
			ic_data_cmd = bit_modify(ic_data_cmd, ((uint32_t) stop) << 9, 1 << 9);
		}

		// write to register
		mm_register_write_32(bar0_base_address + IC_DATA_CMD_OFFSET, ic_data_cmd);

		actual_length += 1;
	}

	// disable i2c controller after transmission
	i2c_error_t status = i2c_controller_disable(bar0_base_address);

	if (status != I2C_NO_ERROR)
	{
		return status;
	}

	return actual_length;
}