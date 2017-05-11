/**
 * @file gpio.h
 * @brief GPIO ports connecting to GPIO controller
 * @author Ran Bao
 * @date May, 2017
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef struct
{
	uint32_t pin;
} gpio_t;

#ifdef __cplusplus
extern "C" {
#endif

void gpio_init(gpio_t *obj, uint32_t pin, uint32_t direction, uint32_t value);
uint32_t gpio_read(gpio_t *obj);
void gpio_write(gpio_t *obj, uint32_t value);

uint32_t gpio_get_direction(gpio_t *obj);
void gpio_set_direction(gpio_t *obj, uint32_t value);


#ifdef __cplusplus
}
#endif

#endif /* GPIO_H_ */