/*
 * MM.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#include "MM.h"

MM::MM() {

	mainMemory = new byte [PHYSICAL_MEMORY_ENTRY*FRAME_SIZE];
}

MM::~MM() {
	delete [] mainMemory;
}

byte* MM::memBase() {
	return mainMemory;
}

byte MM::getByte(PADDR addr) {
	return *(mainMemory+addr);
}

byte* MM::frameAddr(FRAMENUM num) {
	return mainMemory+num*FRAME_SIZE;
}
