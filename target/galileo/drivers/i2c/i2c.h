/**
 * @file i2c.h
 * @brief I2C controller driver
 * @author Ran Bao
 * @date May, 2017
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint16_t i2c_address_t;

typedef struct
{

} i2c_t;

typedef enum
{
	I2C_FAST_MODE = 0x2,            // 400 kbit/s
	I2C_STANDARD_MODE = 0x1         // 100 kbit/s
} i2c_speed_mode_t;

typedef enum
{
	I2C_7BIT_ADDRESSING = 0x0,
	I2C_10BIT_ADDRESSING = 0x1
} i2c_addressing_mode_t;

typedef enum
{
	I2C_NO_ERROR = 0,
	I2C_TIMEOUT = -1
} i2c_error_t;

#ifdef __cplusplus
extern "C" {
#endif

void i2c_init(i2c_t *obj);

void i2c_speed_mode(i2c_t *obj, i2c_speed_mode_t speed_mode);

void i2c_address_mode(i2c_t *obj, i2c_address_t address_mode);

void i2c_start(i2c_t *obj);

void i2c_stop(i2c_t *obj);

void i2c_reset(i2c_t *obj);

int32_t i2c_read(i2c_t *obj, i2c_address_t address, uint8_t *data, size_t length);

int32_t i2c_write(i2c_t *obj, i2c_address_t address, const uint8_t *data, size_t length, bool stop);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H_ */