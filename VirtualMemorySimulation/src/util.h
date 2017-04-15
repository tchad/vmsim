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

/**
 * This function can also be used to combine the virtual address if needed
 */
PADDR combineAddr(FRAMENUM p, OFFSET o);


#endif /* UTIL_H_ */
