/**
 * @file legacy_gpio.h
 * @brief Legacy GPIO port
 * @author Ran Bao
 * @date May, 2017
 *
 * The GPIO base address (GBA) is defined in section 21.3.6 in Intel Quark X1000 datasheet
 * Definitions for Legacy GPIO couintmponents can be found in section 21.6
 */

#ifndef LEGACY_GPIO_H_
#define LEGACY_GPIO_H_

#include <stdint.h>

#define GPIO_SUS(x) (x)

typedef struct
{
	uint32_t pin;
} legacy_gpio_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize a leacy GPIO port
 * @param obj The GPIO object
 * @param pin Pin number [0 ... 5]
 * @param direction Input or output
 * @param value Output high or low, represented by 1 and 0
 */
void legacy_gpio_init(legacy_gpio_t *obj, uint32_t pin, uint32_t direction, uint32_t value);

/**
 * Read from a legacy GPIO port
 * @param obj The GPIO object
 * @return 0 for input low, non-zero for input high
 */
uint32_t legacy_gpio_read(legacy_gpio_t *obj);

/**
 * Write to a legacy GPIO port
 * @param obj The GPIO object
 * @param value 0 for output low, 1 for ouput high
 */
void legacy_gpio_write(legacy_gpio_t *obj, uint32_t value);

/**
 * Read data direction for a legacy GPIO port
 * @param obj The GPIO object
 * @return 0 for output, non-zero for input
 */
uint32_t legacy_gpio_get_direction(legacy_gpio_t *obj);

/**
 * Set data direction for a legacy GPIO port
 * @param obj The GPIO object
 * @param direction 0 for output, 1 for input
 */
void legacy_gpio_set_direction(legacy_gpio_t *obj, uint32_t direction);

#ifdef __cplusplus
}
#endif

#endif /* LEGACY_GPIO_H_ */