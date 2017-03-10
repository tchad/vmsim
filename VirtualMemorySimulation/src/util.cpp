#include "util.h"

PAGENUM getPageNumber(const VADDR logicalAddress) {
	return (PAGENUM) ((logicalAddress & (0xff << 8)) >> 8);
}

OFFSET getOffsetNumber(const VADDR logicalAddress) {
	return (OFFSET) (logicalAddress & 0xff);
}



