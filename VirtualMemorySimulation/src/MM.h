/*
 * MM.h
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#ifndef MM_H_
#define MM_H_
#include "Constant.h"


class MM {
public:
	MM();
	virtual ~MM();
	byte* memBase();
	byte getByte(PADDR addr);
	byte* frameAddr(FRAMENUM num);

private:
	byte* mainMemory;

};

#endif /* MM_H_ */
