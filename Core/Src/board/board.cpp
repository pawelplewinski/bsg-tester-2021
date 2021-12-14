#include "board/board.h"
#include "board/board_pinout.h"

#include "stm32f1xx_hal.h"

#include "util/util.h"

#include <cstdlib>
#include <cstdio>
#include "usart.h"
#include <stdio.h>
#include <string.h>

unsigned counter = 0;
char str[4] = "";

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

	int status, counter = 0;
//status 0 - ready to receive
//status 1 - currently receiving
//status 2 - received
	int cmdLen = 64;
	char cmd[cmdLen] = "";
	uint8_t lastByte = 0;

	char RW;
	int pin, value;

	while (1) {

//sekcja mrugajacej diody
//		USER_LED.toggle();

//sekcja kontroli odbierania komendy
		if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == SET) {
			HAL_UART_Receive(&huart1, &lastByte, 1, 1);
			if (lastByte == 0x02) {
				status = 1;
			} else if (lastByte == 0x03) {
				status = 2;
				cmd[counter] = '\0';
				counter = 0;
			} else {
				cmd[counter] = lastByte;
				counter++;
			}
		}

//sekcja parsowania komendy i drzewka poleceń
		if (status == 2) {

			sscanf(cmd, "%c %d %d", &RW, &pin, &value);
			memset(cmd, 0, strlen(cmd));
			status = 0;

//00-09 - GPIO read
//10-19 - GPIO write
//20-29 - ADC
//30-39 - DAC
//40-49 - PWM

			if (RW == 'R' || RW == 'r') {
				switch (pin) {
				case 0:
					//STEROWANIE POMPY
					//odczyt pinu PB8
					if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET)
						printf("pump controller 2: 1");
					else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET)
						printf("pump controller 2: 1");
					break;
				case 1:
					//STEROWANIE POMPY
					//odczyt pinu PB9
					if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET)
						printf("pump controller 2: 1");
					else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET)
						printf("pump controller 2: 1");
					break;
				case 20:
					//SYGNAL PREDKOSCI KOLA TOCZNEGO
					//odczyt ADC pinu PA5
					//printf odczytu
					break;
				case 21:
					//SYGNALY STERUJACE ZAWORAMI
					//odczyt ADC pinow PA1, PA2, PA3, PA4
					//printf odczytu
					break;
				default:
					printf("an error occured, please try again");
					break;
				}
			} else if (RW == 'W' || RW == 'w') {
				switch (pin) {
				case 10:
					//ZADAJNIK JAZDY TRYB JAZDY
					//sygnal na pin PB12
					if(value == 0)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
					else if(value == 1)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
					break;
				case 11:
					//ZADAJNIK JAZDY TRYB HAMOWANIA
					//sygnal na pin PB13
					if(value == 0)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
					else if(value == 1)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
					break;
				case 12:
					//RAUMFAHRT
					//sygnal na pin PB14
					if(value == 0)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
					else if(value == 1)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
					break;
				case 13:
					//BREMSCOSTAM
					//sygnal na pin PB15
					if(value == 0)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
					if(value == 1)
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
					break;
				case 14:
					//AWARYJNE LUZOWANIE TWOJEJ STAREJ NA SNIADANIE
					//sygnal na pin A0
					if(value == 0)
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
					if(value == 1)
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
					break;
				case 30:
					//CISNIENIE ZACISKU HAMULCOWEGO
					//4 x DAC
					break;
				case 31:
					//WARTOSC CISNIENIA POMPY
					//2 x DAC
					break;
				case 40:
					//PREDKOSC KOLA
					//4 x PWM PA6 PA7 PB0 PB1
					if(value > 0) {
						TIM2->CNT = 0;
						TIM2->ARR = value - 1;
					} else {
						printf("value too high");
					}
					break;
				default:
					printf("an error occured, please try again");
					break;
				}
			} else {
					printf("an error occured, please try again");
			}

		}

	}
}


void board_init() {

	printf("START\r\n");
	HAL_Delay(10);
//	BSP_SD_Init();

	HAL_Delay(100);

	printf("UID %08X%08X%08X\r\n", (unsigned int) HAL_GetUIDw0(),
			(unsigned int) HAL_GetUIDw1(), (unsigned int) HAL_GetUIDw2());

}

