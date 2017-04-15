#ifndef PAGETABLEELEMENT_H_
#define PAGETABLEELEMENT_H_

#include "Constant.h"

class PageTableElement {
public:
	PAGENUM pageNumber;
	FRAMENUM frameNumber;
	bool valid;
	PAGENUM counter;
};

#endif /* PAGETABLEELEMENT_H_ */
