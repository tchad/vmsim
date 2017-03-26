/*
 * TLB.h
 *
 *  Created on: Mar 1, 2017
 *      Author: therangersolid
 */

#ifndef TLB_H_
#define TLB_H_
#include "Constant.h"
class TLB {
public:
	enum TLBSTATUS{
		HIT,
		MISS
	};
	struct STATISTICS{
		uint32_t hitCount;
		uint32_t missCount;
		uint32_t getFrameCount;
		uint32_t setFrameCount;
		STATISTICS();

	};

	TLB();
	TLBSTATUS getFrameNumber(const PAGENUM pageNumber, FRAMENUM* frameNumber);
	void setPageFrameNumber(const PAGENUM pageNumber,const FRAMENUM frameNumber);
//	void setInvalid(const PAGENUM pageNumber);
	void invalidate();
	void invalidate(const PAGENUM pageNumber);
	STATISTICS getStats() const;
private:
	/**
	 * Initialization of this variable is on the constructor.
	 * tlb hits, misses, getframenumber and setpageframenumber
	 */
	struct {
		bool validMarker;
		PAGENUM pageNumber;
		FRAMENUM frameNumber;

	} data[TLB_ENTRY];
	uint32_t replacementIdx;
	bool replaceActive;
	STATISTICS STATS;

};

#endif /* TLB_H_ */
