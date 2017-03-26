/*
 * TLB.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: therangersolid
 */

#include "TLB.h"
#include <iostream>



TLB::TLB():replacementIdx(0), replaceActive(false) {

	invalidate();

}

TLB::STATISTICS::STATISTICS() :
		hitCount(0),
		missCount(0),
		getFrameCount(0),
		setFrameCount(0)
{}

/**
 * This function will get the frame number from TLB. If not exist, it
 * will return 0, and false for boolean.
 * @param  pageNumber  a page you use to get the frame number
 * @return   CharResult   The result + error code with boolean
 */
TLB::TLBSTATUS TLB::getFrameNumber(const PAGENUM pageNumber,
		FRAMENUM* frameNumber) {
		TLBSTATUS ret = TLBSTATUS::MISS;
		STATS.getFrameCount++;

		for (uint32_t i=0; i < TLB_ENTRY; ++i){
			if (pageNumber == data[i].pageNumber && data[i].validMarker == true){
				*frameNumber = data[i].frameNumber;
				ret = TLBSTATUS::HIT;
			}
		}

		if(ret == TLBSTATUS::HIT){
			STATS.hitCount++;
		}else{
			STATS.missCount++;
		}

		return ret;
}

/**
 * This function will set the page number and frame number for TLB.
 * @param  pageNumber  a page you use to get the frame number
 * @param  frameNumber  a frame number
 */
void TLB::setPageFrameNumber(const PAGENUM pageNumber,
		const FRAMENUM frameNumber) {

	// If page number already exists, then update without moving index
	// If tlb is unpopulated then we fill it
	// If fully populated then replace data and move index
	STATS.setFrameCount++;
	uint32_t idx = (replaceActive == true) ? TLB_ENTRY : replacementIdx;
	bool duplicate = false;

	for (uint32_t i = 0; i < idx; ++i){
		if (data[i].pageNumber == pageNumber && data[i].validMarker == true){
			duplicate = true;
			break;
		}
	}

	if (duplicate == false){
		idx = replacementIdx;
		if(replaceActive == false){
			replacementIdx++;
			if (replacementIdx >= TLB_ENTRY){
				replacementIdx = 0;
				replaceActive = true;
			}
		}else{
			replacementIdx = (replacementIdx++) % TLB_ENTRY;
		}

	}

	data[idx].validMarker = true;
	data[idx].pageNumber = pageNumber;
	data[idx].frameNumber = frameNumber;
}

/*
 * This is for delete function where one can set a byte invalid
 * @param  pageNumber  a page you use to set invalid value
 */
//void setInvalid(const PAGENUM pageNumber){
//	CharResult charResult = getPointer(pageNumber);
//	if (!charResult.error) {
//		validMarker &= ~(1 << charResult.result);
//	}
//}
/*
 * This is for delete function where one can set a byte invalid
 * @param  pageNumber  a page you use to set invalid value
 */
void TLB::invalidate() {
	for (uint32_t i = 0; i < TLB_ENTRY; ++i)
	{
		data[i].validMarker = false;
	}
}

TLB::STATISTICS TLB::getStats() const {
	return STATS;
}
