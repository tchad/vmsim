/*
 * PageTable.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: therangersolid
 */

#include "PageTable.h"
#include "stdlib.h"

PageTable::PageTable() {
	// TODO Auto-generated constructor stub
	unsigned char i = 0;
	do { // We use do while here, to prevent overflow
		frameNumber[i] = 0;
	} while (i++ < (PAGE_TABLE_ENTRY - 1));
	for (i = 0; i < PAGE_TABLE_INVALIDATE; ++i) {
		validMarker[i] = 0;
	}
}

/*
 * translate the pointer to frame number
 */
STATUS PageTable::getFrameNumber(const PAGENUM pageNumber, FRAMENUM* frameNumber) const {
//	CharResult charResult = getPointer(pageNumber);
//	if (!charResult.error) {
//		charResult.result = frameNumber[pageNumber];
//	}
//	return charResult;
	return STATUS::OK;
}

void PageTable::setPageFrameNumber(const PAGENUM pageNumber,
		const FRAMENUM frameNumber) {
	/*
	 * Set the validity to one
	 */
	div_t invalidateLocation = div(pageNumber, 32);
	validMarker[invalidateLocation.quot] = validMarker[invalidateLocation.quot]
			| (1 << invalidateLocation.rem);

	/*
	 * Set the frame numbers
	 */
	this->frameNumber[pageNumber] = frameNumber;
}

void PageTable::invalidate() {
	for (uint8_t i = 0; i < PAGE_TABLE_INVALIDATE; ++i) {
		validMarker[i] = 0;
	}
}

/*
 * Get the pointer from page table
 */
STATUS PageTable::getPointer(const PAGENUM pageNumber, FRAMENUM* pointer) const {
//	CharResult charResult;
//	div_t invalidateLocation = div(pageNumber, 32);
//	unsigned char valid = (validMarker[invalidateLocation.quot]
//			>> invalidateLocation.rem) & 1;
//
//	if (valid == 1) {
//		charResult.result = pageNumber;
//		charResult.error = false;
//	}
//	charResult.result = 0;
//	charResult.error = true;
//	return charResult;
	return STATUS::OK;
}
