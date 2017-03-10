/*
 * UnitTest.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#include "UnitTest.h"
#include "BackingStore.h"
#include <iostream>
#include "util.h"


namespace Test {

RESULT Test::UnitTest::test_BackingStorage()
{
	std::cout << "RUNNING BACKING STORE TEST" << std::endl;
	bool ret = true;
	BackingStore bs;

	byte buff[PAGE_SIZE];
	bs.open("BACKING_STORE.bin");
	VADDR vaddr;
	byte expected;
	PAGENUM page;
	OFFSET offset;

	vaddr = 30198;
	expected = 29;
	page = getPageNumber(vaddr);
	offset = getOffsetNumber(vaddr);
	bs.retriveFrame(page,buff);

	ret &= buff[offset] == expected;
	std::cout << "VADDR: " << vaddr << " Expected: 29, result: " << (int)buff[offset] << std::endl;

	vaddr = 53683;
	expected = 108;
	page = getPageNumber(vaddr);
	offset = getOffsetNumber(vaddr);
	bs.retriveFrame(page,buff);

	ret &= buff[offset] == expected;
	std::cout << "VADDR: " << vaddr << " Expected: 108, result: " << (int)buff[offset] << std::endl;

	std::cout << ((ret) ? "PASSED\n" : "FAILED\n");

	return (ret)? RESULT::PASS : RESULT::FAIL;

}

void UnitTest::test() {
	RESULT res = UnitTest::test_BackingStorage();
	if(res == RESULT::PASS) {
		std::cout << "All unit tests passed\n";
	} else {
		std::cout << "Some unit tests failed\n";
	}
}

} /* namespace Test */
