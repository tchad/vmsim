#include "MM.h"

MM::MM()
{
	mainMemory = new byte [PAGE_TABLE_ENTRY_COUNT*FRAME_SIZE];

	FRAMENUM fnum = 0;
	do {
		_freeFrameList.push(fnum);
	} while(fnum++ < (PAGE_TABLE_ENTRY_COUNT-1));
}

MM::~MM()
{
	delete [] mainMemory;
}

byte* MM::memBase()
{
	return mainMemory;
}

byte MM::getByte(PADDR addr)
{
	return * (mainMemory+addr);
}

byte* MM::frameAddr(FRAMENUM num)
{
	return mainMemory+num*FRAME_SIZE;
}

STATUS MM::addFreeFrame(FRAMENUM framenum)
{
	_freeFrameList.push(framenum);

	STATS.addFreeFrameCount++;

	return STATUS::OK;
}

STATUS MM::obtainFreeFrame(FRAMENUM& framenum)
{
	STATUS ret= STATUS::FAILED;
	if(!_freeFrameList.empty()) {
		framenum = _freeFrameList.front();
		_freeFrameList.pop();
		ret = STATUS::OK;
	}

	STATS.obtainFreeFrameCount++;

	return ret;
}

MM::STATISTICS::STATISTICS()
{
	addFreeFrameCount=0;
	obtainFreeFrameCount=0;
}

MM::STATISTICS MM::getStats() const
{
	return STATS;
}
