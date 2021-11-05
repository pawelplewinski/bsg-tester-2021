#ifndef SRC_PROCESSORS_UART_INTERFACE_H_
#define SRC_PROCESSORS_UART_INTERFACE_H_

#include <cstdint>

class IUART
{
public:
	virtual ~IUART() {}
	virtual void init() = 0;		// one-time initialization function
	virtual int num_avail() = 0;	// number of characters ready to be read
	virtual int get() = 0;			// get next byte from UART (or -1 if not available)
	virtual void put(char c) = 0;	// store next byte to be sent (may block if queue full)
	virtual void write(char * s, unsigned len) = 0;	// write a sequence of bytes
};

#endif /* SRC_PROCESSORS_UART_INTERFACE_H_ */
