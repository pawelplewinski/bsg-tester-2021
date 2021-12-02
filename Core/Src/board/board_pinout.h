/*
 * board_pinout.h
 *
 *  Created on: 19 kwi 2017
 *      Author: Pawe�
 */

#ifndef SRC_BOARD_BOARD_PINOUT_H_
#define SRC_BOARD_BOARD_PINOUT_H_


#include "processors/stm32/Pin_driver.h"

extern const STM32_Pin UART_DBG_TX_PIN;
extern const STM32_Pin UART_DBG_RX_PIN;


extern const STM32_Pin RS485_TX_PIN;
extern const STM32_Pin RS485_RX_PIN;
extern const STM32_Pin RS485_DIR_PIN;

extern const STM32_Pin IBIS_TX_PIN;
extern const STM32_Pin IBIS_RX_PIN;

//FP2800
extern const STM32_Pin FP2800_A0_PIN;
extern const STM32_Pin FP2800_A1_PIN;
extern const STM32_Pin FP2800_A2_PIN;
extern const STM32_Pin FP2800_B0_PIN;
extern const STM32_Pin FP2800_B1_PIN;
extern const STM32_Pin FP2800_DATA_PIN;


extern const STM32_Pin FD_SET_DATA_PIN;
extern const STM32_Pin FD_SET_RCLK_PIN;
extern const STM32_Pin FD_SET_SRCLK_PIN;
extern const STM32_Pin FD_SET_OE_PIN;
extern const STM32_Pin FD_SET_MR_PIN;

extern const STM32_Pin FD_CLR_DATA_PIN;
extern const STM32_Pin FD_CLR_RCLK_PIN;
extern const STM32_Pin FD_CLR_SRCLK_PIN;
extern const STM32_Pin FD_CLR_OE_PIN;
extern const STM32_Pin FD_CLR_MR_PIN;


extern const STM32_Pin BRD_ADDR_EN_PIN;
extern const STM32_Pin BRD_ADDR_0_PIN;
extern const STM32_Pin BRD_ADDR_1_PIN;
extern const STM32_Pin BRD_ADDR_2_PIN;
extern const STM32_Pin BRD_ADDR_3_PIN;
extern const STM32_Pin BRD_ADDR_4_PIN;
extern const STM32_Pin BRD_ADDR_5_PIN;
extern const STM32_Pin BRD_ADDR_6_PIN;
extern const STM32_Pin BRD_ADDR_7_PIN;

//SPI
extern const STM32_Pin SPI_CS_PIN;
extern const STM32_Pin SPI_CK_PIN;
extern const STM32_Pin SPI_MISO_PIN;
extern const STM32_Pin SPI_MOSI_PIN;

//SD
extern const STM32_Pin SDIO_CMD;
extern const STM32_Pin SDIO_D0;
extern const STM32_Pin SDIO_D1;
extern const STM32_Pin SDIO_D2;
extern const STM32_Pin SDIO_D3;
extern const STM32_Pin SDIO_CLK;

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
