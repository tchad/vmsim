#include "PageTable.h"

PageTable::PageTable()
{
	FRAMENUM i = 0;

	pageTableElements = new PageTableElement[PAGE_TABLE_ENTRY_COUNT];

	do { // We use do while here, to prevent overflow
		pageTableElements[i].valid = false;
		pageTableElements[i].counter = 0;
	} while (i++ < (PAGE_TABLE_ENTRY_COUNT - 1));
}

PageTable::STATISTICS::STATISTICS() :
	hitCount(0),
	missCount(0),
	getFrameCount(0),
	setFrameCount(0)
{}

/*
 * translate the pointer to frame number
 */
STATUS PageTable::getFrameNumber(const PAGENUM pageNumber,
		FRAMENUM* frameNumber)
{
	STATS.getFrameCount++;
	STATUS status = getPointer(pageNumber, frameNumber);

	if (status == STATUS::OK) {
		*frameNumber = (pageTableElements[*frameNumber].frameNumber);
		STATS.hitCount++;
	}else{
		STATS.missCount++;
	}

	return status;
}

FRAMENUM PageTable::getLRUVictim(PAGENUM *pageNumber)
{
	FRAMENUM i = 0;
	PAGENUM leastUsed = 0;

	do {
		//	This is to get the LRU. Only reachable if the "if" statement above is not fulfilled.
		if (pageTableElements[i].valid
				&& (pageTableElements[i].counter
						< pageTableElements[leastUsed].counter)) {
			leastUsed = i;
		}
	} while (i++ < (PAGE_TABLE_ENTRY_COUNT - 1));

	*pageNumber = pageTableElements[leastUsed].pageNumber;

	return pageTableElements[leastUsed].frameNumber;
}

void PageTable::setPageFrameNumber(const PAGENUM pageNumber,
		const FRAMENUM frameNumber)
{
	STATS.setFrameCount++;
	FRAMENUM i = 0;
	PAGENUM leastUsed = 0;

	do {
		if (!pageTableElements[i].valid) { // We just edit pageTableElements, no need to delete
			decreaseLRUCounter(pageTableElements[i].counter);
			pageTableElements[i].pageNumber = pageNumber;
			pageTableElements[i].frameNumber = frameNumber;
			pageTableElements[i].valid = true;
			pageTableElements[i].counter = (PAGE_TABLE_ENTRY_COUNT - 1);
			return;
		}
//	 This is to get the LRU. Only reachable if the "if" statement above is not fulfilled.
		if (pageTableElements[i].valid
				&& (pageTableElements[i].counter
						< pageTableElements[leastUsed].counter)) {
			leastUsed = i;
		}

	} while (i++ < (PAGE_TABLE_ENTRY_COUNT - 1));

	// If we reach here, there is no null or invalid elements in pageTableElements[], so we need
	// to use LRU
	decreaseLRUCounter(pageTableElements[leastUsed].counter);

	pageTableElements[leastUsed].pageNumber = pageNumber;
	pageTableElements[leastUsed].frameNumber = frameNumber;
	pageTableElements[leastUsed].valid = true;
	pageTableElements[leastUsed].counter = (PAGE_TABLE_ENTRY_COUNT - 1);
}

/**
 * This doesn't include the startFrom itself.
 */
void PageTable::decreaseLRUCounter(const uint8_t startFrom)
{
	FRAMENUM i = 0;

	do { // We use do while here, to prevent overflow
		if ((pageTableElements[i].counter != 0)
				&& (pageTableElements[i].counter > startFrom)) { // We just edit pageTableElements, no need to delete
			--(pageTableElements[i].counter);
		}
	} while (i++ < (PAGE_TABLE_ENTRY_COUNT - 1));
}

void PageTable::invalidate(const PAGENUM pageNumber)
{
	FRAMENUM i = 0;

	do { // We use do while here, to prevent overflow
		if ((pageTableElements[i].pageNumber) == pageNumber) { // We just edit pageTableElements, no need to delete
			pageTableElements[i].valid = false;
			break;
		}
	} while (i++ < (PAGE_TABLE_ENTRY_COUNT - 1));
}

PageTable::STATISTICS PageTable::getStats() const
{
	return STATS;
}

/*
 * Get the pointer from page table
 */
STATUS PageTable::getPointer(const PAGENUM pageNumber, FRAMENUM* pointer)
{
	FRAMENUM i = 0;

	do { // We use do while here, to prevent overflow
		if (pageTableElements[i].pageNumber == pageNumber) {
			if (pageTableElements[i].valid) {
				*pointer = i;
				decreaseLRUCounter(pageTableElements[i].counter);
				pageTableElements[i].counter = PAGE_TABLE_ENTRY_COUNT - 1;

				return STATUS::OK;
			} else {
				return STATUS::PAGEFAULT;
			}
		}
	} while (i++ < (PAGE_TABLE_ENTRY_COUNT - 1));

	return STATUS::PAGEFAULT;
}
