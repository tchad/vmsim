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
	TLB();
	STATUS getFrameNumber(const PAGENUM pageNumber, FRAMENUM* frameNumber) const;
	void setPageFrameNumber(const PAGENUM pageNumber,const FRAMENUM frameNumber);
//	void setInvalid(const PAGENUM pageNumber);
	void invalidate();
private:
	/**
	 * Initialization of this variable is on the constructor.
	 */
	PAGENUM pageNumber[TLB_ENTRY];
	FRAMENUM frameNumber[TLB_ENTRY];
	uint16_t validMarker; // Contains the valid bit for above array.
	                            // The rightmost bit is for pageNumber 0.
	uint8_t pointer;
	STATUS getPointer(const PAGENUM pageNumber, FRAMENUM* pointer) const;
};

#endif /* TLB_H_ */
