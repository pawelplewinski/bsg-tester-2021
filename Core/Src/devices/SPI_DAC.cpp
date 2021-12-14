/*
 * SPI_DAC.cpp
 *
 *  Created on: Dec 14, 2021
 *      Author: Pawel
 */

#include <SPI_DAC.h>

SPI_DAC::SPI_DAC(SPI_HandleTypeDef &hspi, const Pin &cs_pin) :
		hspi(hspi), cs_pin(cs_pin) {
	// TODO Auto-generated constructor stub

}

SPI_DAC::~SPI_DAC() {
	// TODO Auto-generated destructor stub
}

void SPI_DAC::set_channel(uint8_t channel, uint16_t value) {
	uint8_t tx_buf[] = { channel << 3 | 0 << 1, 0x0, value & 0xFF };

	cs_pin.clear();
	HAL_SPI_Transmit(&hspi, tx_buf, 3, HAL_MAX_DELAY);
	cs_pin.set();
}
