#ifndef FUNCUTIL_HPP_
#define FUNCUTIL_HPP_

#include <stm32f1xx_hal.h>
#include <algorithm>

template<typename F> bool repeat_until_true(F fun, unsigned times)
{
	for (unsigned i = 0; i < times; ++i)
	{
		if (fun())
			return true;
	}
	return false;
}

template<typename F> int repeat_until_timeout(F fun, uint32_t timeout)
{
	volatile auto tickstart = HAL_GetTick();

	for (;;)
	{
		if (fun())
			return true;
		if ((timeout == 0U) || ((HAL_GetTick() - tickstart) > timeout))
		{
			return false;
		}
	}
	return false;
}

uint32_t __attribute__((optimize("O0"))) inline read_register(
		volatile uint32_t *reg)
{
	volatile uint32_t *reg_v = (volatile uint32_t *) reg;
	return *reg_v;
}

template<typename T>
T clip(const T& n, const T& lower, const T& upper)
{
	return std::max(lower, std::min(n, upper));
}

#endif /* FUNCUTIL_HPP_ */
