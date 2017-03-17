/*
 * VM.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */


#include <fstream>
#include <iostream>

#include "VM.h"
#include "BackingStore.h"
/*
#include "MM.h"
#include "PageTable.h"
#include "TLB.h"
*/

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
	VM::Result result;
	result.setStatus(STATUS::FAILED);

	std::ifstream istream(addresses);
	if(istream.is_open()) {
		BackingStore bs;
		STATUS bsStatus = bs.open(BACKING_STORE_FILE);

		if(bsStatus == STATUS::OK) {
			result.setStatus(STATUS::OK);
		}
	}


	return result;
}
