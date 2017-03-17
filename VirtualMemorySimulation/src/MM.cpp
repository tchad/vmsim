/*
 * MM.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#include "MM.h"
#include <iostream>

MM::MM() {

	mainMemory = new byte [PHYSICAL_MEMORY_ENTRY*FRAME_SIZE];

	FRAMENUM fnum = 0;
	do{
		_freeFrameList.push(fnum);
		++fnum;

	} while(fnum != (PHYSICAL_MEMORY_ENTRY-1));
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

STATUS MM::addFreeFrame(FRAMENUM framenum) {
	//TODO: add duplicates detection
	_freeFrameList.push(framenum);
	return STATUS::OK;
}

STATUS MM::obtainFreeFrame(FRAMENUM& framenum) {
	//TODO add proper status
	STATUS ret= STATUS::FAILED;
	if(!_freeFrameList.empty()) {
		framenum = _freeFrameList.front();
		_freeFrameList.pop();
		ret = STATUS::OK;
	}

	return ret;
}
