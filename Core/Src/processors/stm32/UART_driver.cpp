#include "UART_driver.h"
#include "funcutil.hpp"
#include "CLK_driver.h"
#include "Interrupt_driver.h"
#include <stm32f1xx_hal.h>
#include <cstdio>

STM32_UART::STM32_UART(USART_TypeDef *uart, uint32_t baudrate, uint32_t word_length, uint32_t stop_bits, uint32_t parity) :
		uart(uart), initialized(false)
{
	huart.Instance = this->uart;
	huart.Init.BaudRate = baudrate;
	huart.Init.WordLength = word_length;
	huart.Init.StopBits = stop_bits;
	huart.Init.Parity = parity;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;

}

STM32_UART::~STM32_UART(void)
{

}

void STM32_UART::init()
{
	STM32_CLK::enable(uart);

	HAL_UART_Init(&huart);

	__HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart, UART_IT_ERR);

    HAL_NVIC_SetPriority(STM32_Interrupts::get_UART_int_no(uart), 5, 0);
    HAL_NVIC_EnableIRQ(STM32_Interrupts::get_UART_int_no(uart));
    initialized = true;
}

int STM32_UART::num_avail()
{
	NVIC_DisableIRQ(STM32_Interrupts::get_UART_int_no(uart));
	unsigned avail = rx_fifo.is_empty() ? 0 : 1;
	NVIC_EnableIRQ(STM32_Interrupts::get_UART_int_no(uart));
	return avail;
  }

int STM32_UART::get()
{
	NVIC_DisableIRQ(STM32_Interrupts::get_UART_int_no(uart));
	int ret = rx_fifo.get();
	NVIC_EnableIRQ(STM32_Interrupts::get_UART_int_no(uart));
	return ret;
}

void STM32_UART::put(char c)
{
	if (!initialized)
		return;
	int cnt = 0;
	while (1)
	{
		NVIC_DisableIRQ(STM32_Interrupts::get_UART_int_no(uart));
		if (!tx_fifo.is_full())
			break;
		NVIC_EnableIRQ(STM32_Interrupts::get_UART_int_no(uart));
		if (cnt++ > 2000)
			return;
	}
	tx_fifo.put(c);
	__HAL_UART_ENABLE_IT(&huart, UART_IT_TXE);
	NVIC_EnableIRQ(STM32_Interrupts::get_UART_int_no(uart));
}

void STM32_UART::write(char * s, unsigned len)
{
	//Put as much as possible in the queue
	NVIC_DisableIRQ(STM32_Interrupts::get_UART_int_no(uart));
	while (len && !tx_fifo.is_full())
	{
		tx_fifo.put(*s);
		s++;
		len--;
	}
	__HAL_UART_ENABLE_IT(&huart, UART_IT_TXE);
	NVIC_EnableIRQ(STM32_Interrupts::get_UART_int_no(uart));
	//Put the rest byte-by-byte
	while (len--)
		put(*s++);
}

void STM32_UART::interrupt_handler()
{
	while (__HAL_UART_GET_FLAG(&huart, UART_FLAG_RXNE))
		rx_fifo.put(uart->DR);
	if (__HAL_UART_GET_IT_SOURCE(&huart, UART_IT_TXE))
	{
		while (__HAL_UART_GET_FLAG(&huart, UART_FLAG_TXE))
		{
			if (!tx_fifo.is_empty())
			{
				uart->DR = tx_fifo.get();
			}
			else
			{
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
