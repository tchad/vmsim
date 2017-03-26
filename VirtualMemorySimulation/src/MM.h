/*
 * MM.h
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#ifndef MM_H_
#define MM_H_

#include <queue>
#include <list>

#include "Constant.h"


class MM {
public:
	struct STATISTICS{
		uint32_t addFreeFrameCount;
		uint32_t obtainFreeFrameCount;
		STATISTICS();
	};
	MM();
	virtual ~MM();
	byte* memBase();
	byte getByte(PADDR addr);
	byte* frameAddr(FRAMENUM num);

	STATUS addFreeFrame(FRAMENUM framenum);
	STATUS obtainFreeFrame(FRAMENUM &framenum);
	STATISTICS getStats() const;

private:
	byte* mainMemory;
	std::queue<FRAMENUM, std::list<FRAMENUM> > _freeFrameList;
	STATISTICS STATS;

};

#endif /* MM_H_ */
