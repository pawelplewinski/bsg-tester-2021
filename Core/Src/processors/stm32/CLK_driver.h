#include "stm32f1xx_hal.h"

class STM32_CLK {
public:
	inline static void enable(const void * periph) {
		if (periph == TIM2)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
		else if (periph == TIM3)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
		else if (periph == WWDG)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);
		else if (periph == SPI1)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
//		if (periph == SPI3)		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);
		else if (periph == USART2)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
//		if (periph == UART4)		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);
//		if (periph == UART5)		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);
		else if (periph == I2C1)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
		else if (periph == CAN1)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);
		else if (periph == PWR)
			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
//		if (periph == DAC)			SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);

		else if (periph == TIM1)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
		else if (periph == USART1)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
		else if (periph == ADC1)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);
		else if (periph == ADC2)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);
//		if (periph == SDIO)		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);
//		if (periph == SPI4)		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);
//		if (periph == TIM9)		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN);
//		if (periph == TIM10)		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);
//		if (periph == TIM11)		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM11EN);

		else if (periph == GPIOA)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
		else if (periph == GPIOB)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
		else if (periph == GPIOC)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
		else if (periph == GPIOD)
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

		else if (periph == CRC)
			SET_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN);
		else if (periph == DMA1)
			SET_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN);
		else
		{
			while(1)
				;
		}

		for (volatile int i = 0; i < 3; i++)
			; // following the design pattern from HAL library
	}
};
