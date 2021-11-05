#ifndef STM32FLASHACCESSOR_H_
#define STM32FLASHACCESSOR_H_

#include <NVMInterface.h>
#include <stm32f4xx_hal.h>
#include <cstring>

template<unsigned BUFFER_32BIT_WORDS=128>
class STM32FlashAccessor: public NVMInterface {
public:
	STM32FlashAccessor(uint32_t buffer_address, uint32_t flash_sector, uint32_t write_after_ms=0);
	virtual ~STM32FlashAccessor();
	virtual void initialize();
	virtual bool write(uint32_t offset, const uint8_t *data, uint32_t len);
	virtual bool read(uint32_t offset, uint8_t *data, uint32_t len);
	virtual bool synchronize();
	virtual uint32_t size();
protected:
	uint32_t last_write, sector, write_after;
	bool write_pending, data_valid;
	uint32_t local_buffer[BUFFER_32BIT_WORDS + 1];
	const uint32_t * flash_data;
	static const uint32_t MAGIC_WORD = 0xABCD1234;
};

template<unsigned BUFFER_32BIT_WORDS>
STM32FlashAccessor<BUFFER_32BIT_WORDS>::STM32FlashAccessor(uint32_t buffer_address, uint32_t flash_sector, uint32_t write_after_ms) :
		last_write(UINT32_MAX), sector(flash_sector), write_after(write_after_ms), write_pending(false),
		data_valid(false), flash_data((uint32_t *)buffer_address)
{
}

template<unsigned BUFFER_32BIT_WORDS>
STM32FlashAccessor<BUFFER_32BIT_WORDS>::~STM32FlashAccessor()
{
}

template<unsigned BUFFER_32BIT_WORDS>
void STM32FlashAccessor<BUFFER_32BIT_WORDS>::initialize()
{
	data_valid = (flash_data[0] == MAGIC_WORD);
	memcpy(local_buffer, flash_data, sizeof(local_buffer));
	local_buffer[0] = MAGIC_WORD;
}

template<unsigned BUFFER_32BIT_WORDS>
uint32_t STM32FlashAccessor<BUFFER_32BIT_WORDS>::size()
{
	return BUFFER_32BIT_WORDS * sizeof(uint32_t);
}

template<unsigned BUFFER_32BIT_WORDS>
bool STM32FlashAccessor<BUFFER_32BIT_WORDS>::write(uint32_t offset, const uint8_t* data, uint32_t len)
{
	if (offset + len > BUFFER_32BIT_WORDS * sizeof(uint32_t))
		return false;
	memcpy((uint8_t*)local_buffer + sizeof(uint32_t) + offset, data, len);
	this->data_valid = true;
	this->write_pending = true;
	this->last_write = HAL_GetTick();
	return true;
}

template<unsigned BUFFER_32BIT_WORDS>
bool STM32FlashAccessor<BUFFER_32BIT_WORDS>::read(uint32_t offset, uint8_t* data, uint32_t len)
{
	if (offset + len > BUFFER_32BIT_WORDS * sizeof(uint32_t))
		return false;
	if (!this->data_valid)
		return false;
	memcpy(data, (uint8_t*)local_buffer + sizeof(uint32_t) + offset, len);
	return true;
}

template<unsigned BUFFER_32BIT_WORDS>
bool STM32FlashAccessor<BUFFER_32BIT_WORDS>::synchronize()
{
	if (!this->write_pending)
		return true;
	if (HAL_GetTick() - this->last_write < write_after)
		return true;
	this->write_pending = false;
	//skip if identical
	if (memcmp(flash_data, local_buffer, sizeof(local_buffer)) == 0)
		return true;
	printf("*!*! Writing to flash memory\r\n");

	//disable interrupts
	__disable_irq();

	//erase flash
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInit = { 0 };
	EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInit.Sector = sector;
	EraseInit.NbSectors = 1;
	EraseInit.Banks = FLASH_BANK_1;
	EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	uint32_t pe;
	if (HAL_FLASHEx_Erase(&EraseInit, &pe) != HAL_OK)
		return false;

	//write to flash
	bool result = true;
	for (unsigned word = 0; word < BUFFER_32BIT_WORDS + 1; ++word)
	{
		HAL_FLASH_Program(TYPEPROGRAM_WORD, (uint32_t)&flash_data[word], local_buffer[word]);
		if (flash_data[word] != local_buffer[word])
		{
			result = false;
			printf("Error writing to flash\r\n");
			break;
		}
	}

	//re-enable interrupts
	__enable_irq();
	HAL_FLASH_Lock();
	printf("*!*! Flash memory write ended\r\n");
	return result;
}

#endif /* STM32FLASHACCESSOR_H_ */
