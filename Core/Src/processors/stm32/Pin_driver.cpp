/*
 * STM32Pin.cpp
 *
 *  Created on: 30 sty 2017
 *      Author: Pawe³
 */

#include <Pin_driver.h>
#include <cstdint>
#include <cassert>

#include <processors/stm32/CLK_driver.h>

uint32_t STM32_Pin::clock_mask = 0;

STM32_Pin::STM32_Pin(GPIO_TypeDef *port, uint16_t pin, uint32_t mode,
		uint32_t pull, uint32_t alt_function, uint32_t speed) :
		Pin(), port(port), pin(pin) {

	STM32_CLK::enable(port);
	//enable clock for port
#ifdef GPIOA
	if (port == GPIOA)
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
#endif
#ifdef GPIOB
		if (port == GPIOB)
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
#endif
#ifdef GPIOC
		if (port == GPIOC)
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
#endif
#ifdef GPIOD
		if (port == GPIOD)
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
#endif
#ifdef GPIOE
		if (port == GPIOE)
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
#endif



	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = speed;
//	GPIO_InitStruct.Alternate = alt_function;
	HAL_GPIO_Init(port, &GPIO_InitStruct);

}

STM32_Pin::~STM32_Pin() {

}

void STM32_Pin::set(bool value) const {
	HAL_GPIO_WritePin(port, pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void STM32_Pin::clear() const {
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

bool STM32_Pin::get() const {
	return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
}

void STM32_Pin::toggle() const {
	set(!get());
}
