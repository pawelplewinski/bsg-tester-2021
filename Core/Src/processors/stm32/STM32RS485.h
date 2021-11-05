/*
 * STM32RS485.h
 *
 *  Created on: 24.09.2018
 *      Author: Pawe³
 */

#ifndef SRC_PROCESSORS_STM32_STM32RS485_H_
#define SRC_PROCESSORS_STM32_STM32RS485_H_

#include "UART_driver.h"
#include "Pin.h"

class STM32_RS485 : public STM32_UART {
public:
	STM32_RS485(USART_TypeDef *uart, const Pin &driver_en_pin, uint32_t baudrate =
			115200, uint32_t word_length = UART_WORDLENGTH_8B,
			uint32_t stop_bits = UART_STOPBITS_1, uint32_t parity =
					UART_PARITY_NONE);
	virtual ~STM32_RS485();
	virtual void init();
	void interrupt_handler();
protected:
	const Pin &driver_en_pin;
};

#endif /* SRC_PROCESSORS_STM32_STM32RS485_H_ */
