#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stm32f1xx_hal.h>
#include "UART_interface.h"
#include "Fifo.h"

class STM32_UART: public IUART
{
public:
	STM32_UART(USART_TypeDef *uart, uint32_t baudrate =
			115200, uint32_t word_length = UART_WORDLENGTH_8B,
			uint32_t stop_bits = UART_STOPBITS_1, uint32_t parity =
					UART_PARITY_NONE);
	virtual ~STM32_UART(void);
	virtual void init();
	virtual int num_avail();
	virtual int get();
	virtual void put(char c);
	virtual void write(char * s, unsigned len);
	void interrupt_handler();

protected:
	enum
	{
		TX_BUF_SIZE = 128, RX_BUF_SIZE = 2048,
	};

	USART_TypeDef * uart;
	UART_HandleTypeDef huart;
	Fifo<uint8_t, TX_BUF_SIZE> tx_fifo;
	Fifo<uint8_t, RX_BUF_SIZE> rx_fifo;
	bool initialized;
};

#endif /* UART_DRIVER_H_ */
