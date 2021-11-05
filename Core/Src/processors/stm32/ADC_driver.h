#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include <stm32f4xx_hal.h>
#include "ADC_interface.h"

template <unsigned COUNT, unsigned OVERSAMPLING = 1>
class STM32_ADC : public IADC {
public:
	STM32_ADC(ADC_HandleTypeDef *adc, DMA_HandleTypeDef *dma);
	virtual ~STM32_ADC(void);
	float getChannelVoltage(unsigned int channel);
	void init();
	void update();
	void stop();
	void start();
	unsigned size();
	const volatile void * buffer();
protected:
	ADC_HandleTypeDef *hadc;
	DMA_HandleTypeDef *hdma;
	volatile uint16_t data[COUNT * OVERSAMPLING];
};

template <unsigned COUNT, unsigned OVERSAMPLING>
STM32_ADC<COUNT, OVERSAMPLING>::STM32_ADC(ADC_HandleTypeDef *adc, DMA_HandleTypeDef *dma)
: IADC()
{
	hadc = adc;
	hdma = dma;
}

template <unsigned COUNT, unsigned OVERSAMPLING>
void STM32_ADC<COUNT, OVERSAMPLING>::init()
{
	start();
}

//Retrigger the conversion, if in single scan mode
template <unsigned COUNT, unsigned OVERSAMPLING>
void STM32_ADC<COUNT, OVERSAMPLING>::update()
{
	stop();
	start();
}

template <unsigned COUNT, unsigned OVERSAMPLING>
void STM32_ADC<COUNT, OVERSAMPLING>::stop(void)
{
	HAL_ADC_Stop_DMA(hadc);
}

template <unsigned COUNT, unsigned OVERSAMPLING>
void STM32_ADC<COUNT, OVERSAMPLING>::start(void)
{
	HAL_ADC_Start_DMA(hadc, (uint32_t*)data, COUNT * OVERSAMPLING);
}

template <unsigned COUNT, unsigned OVERSAMPLING>
float STM32_ADC<COUNT, OVERSAMPLING>::getChannelVoltage(unsigned int channel)
{
	if(channel >= COUNT)
		return 0;
	float val = 0.0f;
	for(unsigned sample = 0; sample < OVERSAMPLING; sample++)
	{
		val += data[channel];
		channel += COUNT;
	}
	return val / (OVERSAMPLING * 32000.0f); //equivalently: (ADC_READOUT * 2.048) / 2^16;
}

template<unsigned COUNT, unsigned OVERSAMPLING>
inline unsigned STM32_ADC<COUNT, OVERSAMPLING>::size()
{
	return COUNT * OVERSAMPLING;
}

template <unsigned COUNT, unsigned OVERSAMPLING>
const volatile void * STM32_ADC<COUNT, OVERSAMPLING>::buffer(void)
{
	return data;
}

template <unsigned COUNT, unsigned OVERSAMPLING>
STM32_ADC<COUNT, OVERSAMPLING>::~STM32_ADC(void)
{
	stop();
}

#endif /* ADC_DRIVER_H_ */
