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
	pageTableElements = new PageTableElement[PAGE_TABLE_ENTRY];
	do { // We use do while here, to prevent overflow
		pageTableElements[i].valid = false;
	} while (i++ < (PAGE_TABLE_ENTRY - 1));
}

/*
 * translate the pointer to frame number
 */
STATUS PageTable::getFrameNumber(const PAGENUM pageNumber,
		FRAMENUM* frameNumber) {
	STATUS status = getPointer(pageNumber, frameNumber);
	if (status == STATUS::OK) {
		*frameNumber = (pageTableElements[*frameNumber].frameNumber);
	}
	return status;
}

void PageTable::setPageFrameNumber(const PAGENUM pageNumber,
		const FRAMENUM frameNumber) {
	FRAMENUM i = 0;
	PAGENUM leastUsed = 0;
	do {
		if (!pageTableElements[i].valid) { // We just edit pageTableElements, no need to delete
			decreaseLRUCounter(pageTableElements[i].counter);
			pageTableElements[i].pageNumber = pageNumber;
			pageTableElements[i].frameNumber = frameNumber;
			pageTableElements[i].valid = true;
			pageTableElements[i].counter = (PAGE_SIZE - 1);
			return;
		}
//			 This is to get the LRU. Only reachable if the "if" statement above is not fulfilled.
		if (pageTableElements[i].valid&&(pageTableElements[i].counter > pageTableElements[leastUsed].counter)) {
			leastUsed = i;
		}

	} while (i++ < (PAGE_TABLE_ENTRY - 1));
	// If we reach here, there is no null or invalid elements in pageTableElements[], so we need
	// to use LRU
	decreaseLRUCounter(leastUsed);
	pageTableElements[leastUsed].pageNumber = pageNumber;
	pageTableElements[leastUsed].frameNumber = frameNumber;
	pageTableElements[leastUsed].valid = true;
	pageTableElements[leastUsed].counter = (PAGE_SIZE - 1);
}

/**
 * This doesn't include the startFrom itself.
 */
void PageTable::decreaseLRUCounter(const uint8_t startFrom) {
	FRAMENUM i = 0;
	do { // We use do while here, to prevent overflow
		if (pageTableElements[i].valid
				&& (pageTableElements[i].counter > startFrom)) { // We just edit pageTableElements, no need to delete
			--(pageTableElements[i].counter);
		}
	} while (i++ < (PAGE_TABLE_ENTRY - 1));
}

void PageTable::invalidate(const PAGENUM pageNumber) {
	FRAMENUM i = 0;
	do { // We use do while here, to prevent overflow
		if ((pageTableElements[i].pageNumber) == pageNumber) { // We just edit pageTableElements, no need to delete
			pageTableElements[i].valid = false;
			break;
		}
	} while (i++ < (PAGE_TABLE_ENTRY - 1));
}

/*
 * Get the pointer from page table
 */
STATUS PageTable::getPointer(const PAGENUM pageNumber, FRAMENUM* pointer) {
	FRAMENUM i = 0;
	do { // We use do while here, to prevent overflow
			if (pageTableElements[i].pageNumber == pageNumber) {
				if (pageTableElements[i].valid) {
					*pointer = i;
					decreaseLRUCounter(pageTableElements[i].counter);
					pageTableElements[i].counter = PAGE_SIZE - 1;
					return STATUS::OK;
				} else {
					return STATUS::PAGEFAULT;
				}
//				break; // An unreachable code.
			}
	} while (i++ < (PAGE_TABLE_ENTRY - 1));
	return STATUS::PAGEFAULT;
}

//PageTableElement* PageTable::getLRU() {
//	FRAMENUM i = 0;
//	PageTableElement* minLRU = NULL;
//	do { // We use do while here, to prevent overflow
//		if (pageTableElements[i] != NULL || (!(pageTableElements[i]->valid))) { // We just edit pageTableElements, no need to delete
//			if (minLRU == NULL) {
//				minLRU = pageTableElements[i];
//			} else {
//				if ((minLRU->counter) > (pageTableElements[i]->counter)) {
//					minLRU = pageTableElements[i];
//				}
//			}
//		}
//	} while (i++ < (PAGE_TABLE_ENTRY - 1));
//	return minLRU;
//}
