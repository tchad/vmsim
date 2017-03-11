/*
 * PageTableElement.h
 *
 *  Created on: Mar 10, 2017
 *      Author: therangersolid
 */

#ifndef PAGETABLEELEMENT_H_
#define PAGETABLEELEMENT_H_
#include "Constant.h"

class PageTableElement {
public:
	PAGENUM pageNumber;
	FRAMENUM frameNumber;
	bool valid;
private:

};
#endif /* PAGETABLEELEMENT_H_ */
