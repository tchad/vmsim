/*
 * PageTable.h
 *
 *  Created on: Mar 8, 2017
 *      Author: therangersolid
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_
#include "Constant.h"
#include "PageTableElement.h"
class PageTable { // the "get" function is not const. This is because they need to modify the counter for LRU.
public:
	struct STATISTICS{
		uint32_t hitCount;
		uint32_t missCount;
		uint32_t getFrameCount;
		uint32_t setFrameCount;
		STATISTICS();

	};

	PageTable();
	STATUS getFrameNumber(const PAGENUM pageNumber,
			FRAMENUM* frameNumber);
	void setPageFrameNumber(const PAGENUM pageNumber,
			const FRAMENUM frameNumber);
	FRAMENUM getLRUVictim(PAGENUM *pageNumber);
//	PageTableElement* getLRU();
	void decreaseLRUCounter(const uint8_t startFrom);
	void invalidate(const PAGENUM pageNumber);
	STATISTICS getStats() const;
private:
	STATUS getPointer(const PAGENUM pageNumber, FRAMENUM* pointer);
	PageTableElement *pageTableElements;
	STATISTICS STATS;
};

#endif /* PAGETABLE_H_ */
