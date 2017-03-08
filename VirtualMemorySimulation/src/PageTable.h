/*
 * PageTable.h
 *
 *  Created on: Mar 8, 2017
 *      Author: therangersolid
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_
#include "Constant.h"
#include "CharResult.h"
class PageTable {
public:
	PageTable();
	CharResult getFrameNumber(const unsigned char pageNumber) const;
	void setPageFrameNumber(const unsigned char pageNumber,
			const unsigned char frameNumber);
	void invalidate();
private:
	/**
	 * Initialization of this variable is on the constructor.
	 */
	unsigned char frameNumber[PAGE_TABLE_ENTRY];
	unsigned int validMarker[PAGE_TABLE_INVALIDATE]; // Contains the valid bit for above array.
//                                                   // The rightmost bit is for pageNumber 0.
//	unsigned int referenceBit[PAGE_TABLE_REFERENCE_Y][PAGE_TABLE_REFERENCE_X]; // Contains the reference counting
//	unsigned char pointer;
	CharResult getPointer(const unsigned char pageNumber) const;
//	CharResult setReferenceBit(const unsigned int table_reference_y,const unsigned int table_reference_x);
};

#endif /* PAGETABLE_H_ */
