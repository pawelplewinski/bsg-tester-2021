#include "board/board.h"
#include "board/board_pinout.h"

#include "stm32f1xx_hal.h"

#include "util/util.h"
#include "util/Fifo.h"

#include "usart.h"
#include "spi.h"

#include <cstdlib>
#include <cstdio>
#include <cstdint>
unsigned counter = 0;
Fifo<uint8_t, 256> fifo;

/* Handle printf actions */
extern "C" int _write(int file, char *ptr, int len) {

//	dbg_uart.write(ptr, len);
	return len;
}

void microdelay() {
	for (volatile unsigned i = 0; i < 5; ++i)
		;
//		asm("nop");
}

void board_loop() {
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		if (counter % 150 == 0) {
			//150 ms
			USER_LED.toggle();
		}


		if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == SET) {
			uint8_t value;
			HAL_UART_Receive(&huart1, &value, 1, 100);
			fifo.put(value);
		}

		{
			//przetwarzanie
		}

		{

		}

		counter++;
		HAL_Delay(1);
	}
}

void dac_write(uint8_t pin, uint8_t value)
{
	uint8_t tx_buf[] = { pin<<3 | 0 << 1, 0x0, value };

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buf, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
}

void board_init() {

	printf("START\r\n");
	HAL_Delay(10);
//	BSP_SD_Init();

	HAL_Delay(100);

	printf("UID %08X%08X%08X\r\n", (unsigned int) HAL_GetUIDw0(),
			(unsigned int) HAL_GetUIDw1(), (unsigned int) HAL_GetUIDw2());

}

