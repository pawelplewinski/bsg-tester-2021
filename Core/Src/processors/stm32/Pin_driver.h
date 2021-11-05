/*
 * STM32Pin.h
 *
 *  Created on: 30 sty 2017
 *      Author: Pawe³
 */

#ifndef SRC_PROCESSORS_INTERFACE_PIN_DRIVER_H_
#define SRC_PROCESSORS_INTERFACE_PIN_DRIVER_H_

#include "Pin.h"

#include <stm32f1xx_hal.h>

class STM32_Pin: public Pin {
public:
	STM32_Pin(GPIO_TypeDef *port, uint16_t pin, uint32_t mode, uint32_t pull =
			GPIO_NOPULL, uint32_t alt_function = 0, uint32_t speed = GPIO_SPEED_FREQ_LOW);
	virtual ~STM32_Pin();
	void set(bool value = true) const;
	void clear() const;
	bool get() const;
	void toggle() const;
protected:
	GPIO_TypeDef *port;
	const uint16_t pin;
	static uint32_t clock_mask;
};

#endif /* SRC_PROCESSORS_INTERFACE_PIN_DRIVER_H_ */
