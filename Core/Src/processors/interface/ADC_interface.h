#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include <cstdint>

class IADC {
public:
	virtual float getChannelVoltage(unsigned int channel) = 0;
	virtual void init() = 0;
	virtual void update() = 0;		//request ADC to perform another scan
	virtual void stop() = 0;
	virtual void start() = 0;
	virtual unsigned size() = 0;	// size of the buffer, expressed in 16-bit words
	virtual const volatile void * buffer() = 0;
	virtual ~IADC() {}
};

#endif /* ADC_INTERFACE_H_ */
