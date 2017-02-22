#include "Constant.h"
#include "PageTable.h"

/*
 * Inside of this is the frame.
 */
unsigned char pageTable[PAGE_TABLE_ENTRY] = { };

/*
 * This will return frame number!
 */
unsigned char process(const unsigned char pageNumber) {
	return pageTable[pageNumber];
}
