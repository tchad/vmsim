#include <fstream>

#include "VM.h"
#include  "util.h"

VM::Result::Result(VM::Result&& r) :
	_data(std::move(r._data)),
	_status(r._status),
	_tlbStats(r._tlbStats),
	_bsStats(r._bsStats),
	_ptStats(r._ptStats),
	_mmStats(r._mmStats)
{}

VM::Result& VM::Result::operator =(VM::Result&& r)
{
	_status = r._status;
	_tlbStats = r._tlbStats;
	_bsStats = r._bsStats;
	_ptStats = r._ptStats;
	_mmStats = r._mmStats;
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

void VM::Result::append(VM::Result::Itm itm)
{
	_data.push_back(itm);
}

bool VM::Result::operator ==(const VM::Result& r) const
{
	if(this->count() != r.count()) {
		return false;
	}

	const VM::Result::RESULTDATA* rData = r.data();
	if(VERIFY_FRAME== true) {
		for(VM::Result::size_type i=0; i<_data.size(); ++i){
			/*
			 * NOTE: The verification set were based on page table containing 256 entries
			 * If we use smaller size cannot compare physical address as it will be different.
			 */
			if(_data[i].pAddr != (*rData)[i].pAddr ||
				_data[i].vAddr != (*rData)[i].vAddr ||
				_data[i].value != (*rData)[i].value) {
				return false;
			}
		}
	} else {
		for(VM::Result::size_type i=0; i<_data.size(); ++i){
			if( _data[i].vAddr != (*rData)[i].vAddr ||
				_data[i].value != (*rData)[i].value) {
				return false;
			}
		}
	}

	return true;
}

TLB::STATISTICS VM::Result::getTLBStats()
{
	return _tlbStats;
}

BackingStore::STATISTICS VM::Result::getBsStats()
{
	return _bsStats;
}

PageTable::STATISTICS VM::Result::getPtStats()
{
	return _ptStats;
}

MM::STATISTICS VM::Result::getMMStats()
{
	return _mmStats;
}

void VM::Result::setStatus(STATUS status)
{
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
			TLB tlb;

			while(result.status() == STATUS::OK && !istream.eof()) {
				VADDR vaddr;
				PADDR paddr;
				PAGENUM page;
				FRAMENUM frame;
				OFFSET offset;
				byte data;
				TLB::TLBSTATUS tlbstatus;
				std::string buff;

				istream >> buff;
				if(buff.empty())
					continue; //skip on last line which is empty
				vaddr = std::stoi(buff);
				page = getPageNumber(vaddr);
				offset = getOffsetNumber(vaddr);

				tlbstatus = tlb.getFrameNumber(page, &frame);

				if (tlbstatus == TLB::MISS)
				{
					status = pt.getFrameNumber(page, &frame);

					switch(status) {
					case STATUS::OK: //nothing to be done here
						tlb.setPageFrameNumber(page, frame);
						break;
					case STATUS::PAGEFAULT: //exception, pagefault
						status = VM::handlePageFault(bs, mm, pt, tlb, page, frame);
						if(status != STATUS::OK) {
							result.setStatus(STATUS::FAILED);
							continue;
						}
						break;
					default: // implementation error
						result.setStatus(STATUS::FAILED);
						continue;
					}
				}

				paddr = combineAddr(frame, offset);
				data = mm.getByte(paddr);
				result.append({vaddr, paddr, data});
			}

			result._bsStats = bs.getStats();
			result._tlbStats = tlb.getStats();
			result._mmStats = mm.getStats();
			result._ptStats = pt.getStats();
		} else {
			result.setStatus(STATUS::FAILED);
		}
	} else {
		result.setStatus(STATUS::FAILED);
	}

	return result;
}

VM::Result VM::controlDataFromFile(const std::string& ctrl) {
	VM::Result ret;
	ret.setStatus(STATUS::FAILED);

	std::ifstream istream(ctrl);
	if(istream.is_open()) {
		while(!istream.eof()) {
			std::string sink;
			VM::Result::Itm itm;

			istream >> sink; //"Virtual"
			if(sink.empty()) {
				continue; //quick hack to handle the end of file
			}
			istream >> sink; //"Address:"
			istream >> sink; //number
			itm.vAddr = std::stoi(sink);

			istream >> sink; //"Physical"
			istream >> sink; //"Address:"
			istream >> sink; //number
			itm.pAddr = std::stoi(sink);

			istream >> sink; //"Value:"
			istream >> sink; //number
			itm.value = std::stoi(sink);

			ret.append(itm);
		}
		ret.setStatus(STATUS::OK);
	}

	return ret;
}

STATUS VM::handlePageFault(BackingStore& bs, MM& mm, PageTable& pt, TLB& tlb,
		PAGENUM pagenum, FRAMENUM& framenum)
{
	//TODO: this implementation we assume that we will not ran out of free frames.
	STATUS ret = STATUS::FAILED;

	if(STATUS::OK != mm.obtainFreeFrame(framenum)){
		PAGENUM victimPage;
		framenum = pt.getLRUVictim(&victimPage);
		tlb.invalidate(victimPage);
	}

	byte* frameAddr = mm.frameAddr(framenum);
	if(STATUS::OK == bs.retriveFrame(pagenum, frameAddr)) {
		pt.setPageFrameNumber(pagenum, framenum);
		tlb.setPageFrameNumber(pagenum,framenum);
		ret = STATUS::OK;
	}

	return ret;
}
