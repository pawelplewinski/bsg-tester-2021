#ifndef NVMINTERFACE_H_
#define NVMINTERFACE_H_

#include <cstdint>

class NVMInterface {
public:
	virtual ~NVMInterface() {}
	virtual void initialize() = 0;
	virtual bool write(uint32_t offset, const uint8_t *data, uint32_t len) = 0;
	virtual bool read(uint32_t offset, uint8_t *data, uint32_t len) = 0;
	virtual bool synchronize() = 0;
	virtual uint32_t size() = 0;
protected:

};

#endif /* NVMINTERFACE_H_ */
