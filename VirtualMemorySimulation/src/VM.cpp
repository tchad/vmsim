/*
 * VM.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */


#include <fstream>
#include <iostream>

#include "VM.h"
#include "TLB.h"
#include  "util.h"

VM::Result::Result(VM::Result&& r) :
		_data(std::move(r._data)),
		_status(r._status)
{
}

VM::Result& VM::Result::operator =(VM::Result&& r)
{
	_status = r._status;
	_data = std::move(r._data);
	return *this;
}

VM::Result::size_type VM::Result::count() const
{
	return _data.size();
}

const VM::Result::RESULTDATA* VM::Result::data() const
{
	return &_data;
}

STATUS VM::Result::status() const
{
	return _status;
}

void VM::Result::append(Itm itm) {
	_data.push_back(itm);
}

void VM::Result::setStatus(STATUS status) {
	_status = status;
}

VM::Result VM::simulate(const std::string& addresses)
{

	/*
	 * The assumption for this function is that the algorithm continue to execute as long as the status of result
	 * is maintained as ok. If at any point the status will change, the next iteration or stage will not execute
	 * and a failed result object will get returned.
	 */
	VM::Result result;
	result.setStatus(STATUS::OK);

	std::ifstream istream(addresses);
	if(istream.is_open()) {
		BackingStore bs;
		STATUS status = bs.open(BACKING_STORE_FILE);

		if(status == STATUS::OK) {
			MM mm;
			PageTable pt;

			while(result.status() == STATUS::OK && !istream.eof()) {
				VADDR vaddr;
				PADDR paddr;
				PAGENUM page;
				FRAMENUM frame;
				OFFSET offset;
				byte data;

				istream >> vaddr;
				page = getPageNumber(vaddr);
				offset = getOffsetNumber(vaddr);

				//TODO: TLB lookup, add here;
				status = pt.getFrameNumber(page, &frame);

				switch(status) {
				case STATUS::OK: //nothing to be done here
					break;
				case STATUS::PAGEFAULT: //exception, pagefault
					status = VM::handlePageFault(bs, mm, pt, page, frame);
					if(status != STATUS::OK) {
						result.setStatus(STATUS::FAILED);
						continue;
					}
					break;
				default: // implementation error
					result.setStatus(STATUS::FAILED);
					continue;
				}

				paddr = combineAddr(frame, offset);
				data = mm.getByte(paddr);

				result.append({vaddr, paddr, data});
			}
		} else {
			result.setStatus(STATUS::FAILED);
		}
	} else {
		result.setStatus(STATUS::FAILED);
	}

	return result;
}

STATUS VM::handlePageFault(BackingStore& bs, MM& mm, PageTable& pt,
		PAGENUM pagenum, FRAMENUM& framenum)
{
	//TODO: this is the very first implementation to memory management for now we assume that we will not ran out of memory
	STATUS ret = STATUS::FAILED;

	if(STATUS::OK == mm.obtainFreeFrame(framenum)){
		byte* frameAddr = mm.frameAddr(framenum);
		if(STATUS::OK == bs.retriveFrame(pagenum, frameAddr)) {
			pt.setPageFrameNumber(pagenum, framenum);
			ret = STATUS::OK;
		}
	}

	return ret;
}
