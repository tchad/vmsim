/*
 * PageTable.h
 *
 *  Created on: Mar 8, 2017
 *      Author: therangersolid
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_
#include "Constant.h"
class PageTable {
public:
	PageTable();
	STATUS getFrameNumber(const PAGENUM pageNumber,
			FRAMENUM* frameNumber) const;
	void setPageFrameNumber(const PAGENUM pageNumber,
			const FRAMENUM frameNumber);
	void invalidate();
private:
	/**
	 * Initialization of this variable is on the constructor.
	 */
	FRAMENUM frameNumber[PAGE_TABLE_ENTRY];
	uint32_t validMarker[PAGE_TABLE_INVALIDATE]; // Contains the valid bit for above array.
//                                                   // The rightmost bit is for pageNumber 0.
//	unsigned int referenceBit[PAGE_TABLE_REFERENCE_Y][PAGE_TABLE_REFERENCE_X]; // Contains the reference counting
//	unsigned char pointer;
	STATUS getPointer(const PAGENUM pageNumber, FRAMENUM* pointer) const;
//	CharResult setReferenceBit(const unsigned int table_reference_y,const unsigned int table_reference_x);
};

#endif /* PAGETABLE_H_ */
