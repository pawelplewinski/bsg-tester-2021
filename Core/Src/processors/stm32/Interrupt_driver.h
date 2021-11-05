/*
 * Interrupt_driver.h
 *
 *  Created on: 16 lut 2017
 *      Author: Pawe�
 */

#ifndef STM32_INTERRUPT_DRIVER_H_
#define STM32_INTERRUPT_DRIVER_H_

#include <stm32f1xx_hal.h>

class STM32_Interrupts {
public:
	STM32_Interrupts();
	static inline constexpr IRQn_Type get_UART_int_no(USART_TypeDef *uart) {
		if (uart == USART1)
			return USART1_IRQn;
		else if (uart == USART2)
			return USART2_IRQn;
		else
			while (1)
				;
	}

	enum class I2C_Interrupt_Type {
		EVENT_INT, ERROR_INT
	};

	static inline constexpr IRQn_Type get_I2C_int_no(void *i2c,
			I2C_Interrupt_Type type) {
		if (i2c == I2C1) {
			if (type == I2C_Interrupt_Type::EVENT_INT)
				return I2C1_EV_IRQn;
			else
				return I2C1_ER_IRQn;
		}
//		case (uint32_t) FMPI2C1:
//			if (type == I2C_Interrupt_Type::EVENT_INT)
//				return FMPI2C1_EV_IRQn;
//			else
//				return FMPI2C1_ER_IRQn;
	}

	static inline constexpr IRQn_Type get_TIM_int_no(TIM_TypeDef *timer) {
	}

};

#endif /* STM32_INTERRUPT_DRIVER_H_ */
