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
	FRAMENUM i = 0;
	do { // We use do while here, to prevent overflow
		pageTableElements[i] = NULL;
	} while (i++ < (PAGE_TABLE_ENTRY - 1));
}

/*
 * translate the pointer to frame number
 */
STATUS PageTable::getFrameNumber(const PAGENUM pageNumber, FRAMENUM* frameNumber) const {
	STATUS status = getPointer(pageNumber, frameNumber);
	if (status == STATUS::OK) {
		*frameNumber = (pageTableElements[*frameNumber]->frameNumber);
	}
	return status;
}

void PageTable::setPageFrameNumber(const PAGENUM pageNumber,
		const FRAMENUM frameNumber) {
	FRAMENUM i = 0;
	do { // We use do while here, to prevent overflow
		if(pageTableElements[i] == NULL){
			PageTableElement* pageTableElement=new PageTableElement();
			pageTableElement->pageNumber = pageNumber;
			pageTableElement->frameNumber = frameNumber;
			pageTableElement->valid = true;
			pageTableElements[i]=pageTableElement;
			break;
		}

	} while (i++ < (PAGE_TABLE_ENTRY - 1));
}

//void PageTable::invalidate() {
//	for (uint8_t i = 0; i < PAGE_TABLE_INVALIDATE; ++i) {
//		validMarker[i] = 0;
//	}
//}

/*
 * Get the pointer from page table
 */
STATUS PageTable::getPointer(const PAGENUM pageNumber, FRAMENUM* pointer) const {
	FRAMENUM i = 0;
		do { // We use do while here, to prevent overflow
			if (pageTableElements[i]!= NULL) {
				if ((pageTableElements[i]->pageNumber)==pageNumber) {
					if ((pageTableElements[i]->valid)) {
						*pointer = i;
						return STATUS::OK;
					}else{
						return STATUS::PAGEFAULT;
					}
					break;
				}
			}
		} while (i++ < (PAGE_TABLE_ENTRY - 1));
		return STATUS::PAGEFAULT;
}
