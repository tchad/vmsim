/*
 * TLB.h
 *
 *  Created on: Mar 1, 2017
 *      Author: therangersolid
 */

#ifndef TLB_H_
#define TLB_H_
#include "Constant.h"
class CharResult {
public:
	unsigned char result;
	bool error;
};

class TLB {
public:
	TLB();
	CharResult getFrameNumber(const unsigned char pageNumber) const;
	void setPageFrameNumber(const unsigned char pageNumber,const unsigned char frameNumber);
//	void setInvalid(const unsigned char pageNumber);
	void invalidate();

private:
	/**
	 * Initialization of this variable is on the constructor.
	 */
	unsigned char pageNumber[TLB_ENTRY];
	unsigned char frameNumber[TLB_ENTRY];
	unsigned short validMarker; // Contains the valid bit for above array.
	                            // The rightmost bit is for pageNumber 0.
	unsigned char pointer;
	CharResult getPointer(const unsigned char pageNumber) const;
};

#endif /* TLB_H_ */
