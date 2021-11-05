/*
 * Protocol.h
 *
 *  Created on: 1 sie 2016
 *      Author: Pawe�
 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

#include <stdint.h>


class Protocol {
public:
	Protocol();
	virtual ~Protocol();
	void put_char(uint8_t character) volatile;
	void process();
protected:
};

#endif /* SRC_PROTOCOL_H_ */
