/*
 * SPI_DAC.h
 *
 *  Created on: Dec 14, 2021
 *      Author: Pawel
 */

#ifndef SRC_DEVICES_SPI_DAC_H_
#define SRC_DEVICES_SPI_DAC_H_

#include <Pin.h>
#include "stm32f1xx_hal.h"

class SPI_DAC {
public:
	SPI_DAC(SPI_HandleTypeDef &hspi, const Pin &cs_pin);
	virtual ~SPI_DAC();
	void set_channel(uint8_t channel, uint16_t value);
private:
	SPI_HandleTypeDef &hspi;
	const Pin &cs_pin;
};

#endif /* SRC_DEVICES_SPI_DAC_H_ */
