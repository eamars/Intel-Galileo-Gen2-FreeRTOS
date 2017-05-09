/**
 * @file legacy_gpio.h
 * @brief Legacy GPIO port
 * @author Ran Bao
 * @date May, 2017
 *
 * The GPIO base address (GBA) is defined in section 21.3.6 in Intel Quark X1000 datasheet
 * Definitions for Legacy GPIO components can be found in section 21.6
 */

#ifndef LEGACY_GPIO_H_
#define LEGACY_GPIO_H_

#include <stdint.h>

typedef struct
{
	uint32_t pin_mask;
} legacy_gpio_t;

#ifdef __cplusplus
extern "C" {
#endif

void legacy_gpio_init(legacy_gpio_t *obj, uint32_t pin, uint32_t direction, uint32_t value);

uint32_t legacy_gpio_read(legacy_gpio_t *obj);
void legacy_gpio_write(legacy_gpio_t *obj);

uint32_t legacy_gpio_get_direction(legacy_gpio_t *obj);
void legacy_gpio_set_direction(legacy_gpio_t *obj, uint32_t direction);

#ifdef __cplusplus
}
#endif

#endif /* LEGACY_GPIO_H_ */