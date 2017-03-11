//============================================================================
// Name        : VirtualMemorySimulation.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TLB.h"
#include "PageTable.h"
#include <iostream>
#include  "util.h"

#define UNIT_TEST
#ifdef UNIT_TEST
#include "UnitTest.h"
#endif  //UNIT_TEST

using namespace std;

bool init();

int main() {

#ifdef UNIT_TEST
	Test::UnitTest::test();
#endif  //UNIT_TEST
	TLB tlb;
	PageTable pageTable;
	/**
	 * Put your code here folks.
	 */
	uint32_t logicalAddress = 576230045;
	// The int casting below is just for display!
	cout << (int) getPageNumber(logicalAddress) << endl;
	cout << (int) getOffsetNumber(logicalAddress) << endl;

	return 0;
}
