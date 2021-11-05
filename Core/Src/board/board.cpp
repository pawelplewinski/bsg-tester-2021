#include "board/board.h"
#include "board/board_pinout.h"

#include "stm32f1xx_hal.h"

#include "util/util.h"

#include <cstdlib>
#include <cstdio>

unsigned counter = 0;

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
		}

		counter++;
		HAL_Delay(1);
	}
}

void board_init() {

	printf("START\r\n");
	HAL_Delay(10);
//	BSP_SD_Init();

	HAL_Delay(100);

	printf("UID %08X%08X%08X\r\n", (unsigned int) HAL_GetUIDw0(), (unsigned int) HAL_GetUIDw1(),
			(unsigned int) HAL_GetUIDw2());

}



