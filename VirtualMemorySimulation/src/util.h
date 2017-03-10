/*
 * util.h
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "Constant.h"

/**
 * Return PageNumber
 */
PAGENUM getPageNumber(const VADDR logicalAddress);

/**
 * Return Offset
 */
OFFSET getOffsetNumber(const VADDR logicalAddress);


#endif /* UTIL_H_ */
