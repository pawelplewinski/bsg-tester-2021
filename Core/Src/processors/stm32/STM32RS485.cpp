/*
 * STM32RS485.cpp
 *
 *  Created on: 24.09.2018
 *      Author: Pawe³
 */

#include <STM32RS485.h>

STM32_RS485::~STM32_RS485() {
	// TODO Auto-generated destructor stub
}

STM32_RS485::STM32_RS485(USART_TypeDef* uart, const Pin& driver_en_pin,
		uint32_t baudrate, uint32_t word_length, uint32_t stop_bits,
		uint32_t parity) :
		STM32_UART(uart, baudrate, word_length, stop_bits, parity), driver_en_pin(
				driver_en_pin) {
	driver_en_pin.set(false);
}


void STM32_RS485::init() {
	driver_en_pin.set(false);
	STM32_UART::init();
}

void STM32_RS485::interrupt_handler() {
	while (__HAL_UART_GET_FLAG(&huart, UART_FLAG_RXNE))
		rx_fifo.put(uart->DR);
	if (__HAL_UART_GET_IT_SOURCE(&huart, UART_IT_TXE))
	{
		while (__HAL_UART_GET_FLAG(&huart, UART_FLAG_TXE))
		{
			if (!tx_fifo.is_empty())
			{
				uart->DR = tx_fifo.get();
				driver_en_pin.set(true);
			}
			else
			{
				driver_en_pin.set(false);
				__HAL_UART_DISABLE_IT(&huart, UART_IT_TXE);
				break;
			}
		}
	}

	if (__HAL_UART_GET_FLAG(&huart, UART_FLAG_ORE))
		__HAL_UART_CLEAR_FLAG(&huart, UART_FLAG_ORE);
	if (__HAL_UART_GET_FLAG(&huart, UART_FLAG_FE))
		__HAL_UART_CLEAR_FLAG(&huart, UART_FLAG_FE);
	if (__HAL_UART_GET_FLAG(&huart, UART_FLAG_NE))
		__HAL_UART_CLEAR_FLAG(&huart, UART_FLAG_NE);
	if (__HAL_UART_GET_FLAG(&huart, UART_FLAG_PE))
		__HAL_UART_CLEAR_FLAG(&huart, UART_FLAG_PE);

}
