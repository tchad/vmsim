/*
 * PageTable.h
 *
 *  Created on: Mar 8, 2017
 *      Author: therangersolid
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_
#include "Constant.h"
#include "PageTableElement.h"
class PageTable {
public:
	PageTable();
	STATUS getFrameNumber(const PAGENUM pageNumber,
			FRAMENUM* frameNumber) const;
	void setPageFrameNumber(const PAGENUM pageNumber,
			const FRAMENUM frameNumber);
private:
	STATUS getPointer(const PAGENUM pageNumber, FRAMENUM* pointer) const;
	PageTableElement* pageTableElements[PAGE_TABLE_ENTRY];
};

#endif /* PAGETABLE_H_ */
