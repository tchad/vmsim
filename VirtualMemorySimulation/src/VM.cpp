/*
 * VM.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#include "VM.h"

VM::Result::Result(const VM::Result::RESULTDATA& data, STATUS status)
{
	_data = data;
	_status = status;
}

VM::Result::Result(VM::Result&& r) :
		_status(r._status),
		_data(std::move(r._data))
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

STATUS VM::Result::status() const {
	return _status;
}

VM::VM() {
}

VM::Result VM::simulate(const std::string& addresses) {
	//TODO: Placeholder;
	return Result();
}
