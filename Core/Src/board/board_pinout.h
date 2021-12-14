/*
 * board_pinout.h
 *
 *  Created on: 19 kwi 2017
 *      Author: Pawe�
 */

#ifndef SRC_BOARD_BOARD_PINOUT_H_
#define SRC_BOARD_BOARD_PINOUT_H_


#include "processors/stm32/Pin_driver.h"

//SPI
extern const STM32_Pin SPI_CS;


extern const STM32_Pin UART_DBG_TX_PIN;
extern const STM32_Pin UART_DBG_RX_PIN;


extern const STM32_Pin RS485_TX_PIN;
extern const STM32_Pin RS485_RX_PIN;
extern const STM32_Pin RS485_DIR_PIN;

extern const STM32_Pin IBIS_TX_PIN;
extern const STM32_Pin IBIS_RX_PIN;


//LED
extern const STM32_Pin USER_LED;
extern const STM32_Pin USER_LED2;


//LCD
extern const STM32_Pin LCD_CLK;
extern const STM32_Pin LCD_ENABLE;
extern const STM32_Pin LCD_RST2;
extern const STM32_Pin LCD_DATA;
extern const STM32_Pin LCD_REFRESH;

extern const STM32_Pin LCD_MISO;
extern const STM32_Pin LCD_INPUT;
extern const STM32_Pin VLCD_IN;


#endif /* SRC_BOARD_BOARD_PINOUT_H_ */
