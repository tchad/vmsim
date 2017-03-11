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

//#define UNIT_TEST

#ifdef UNIT_TEST
#include "UnitTest.h"
#endif  //UNIT_TEST

using namespace std;


int main(int argc, char **argv)
{

#ifdef UNIT_TEST
	Test::UnitTest::test();
#else


//	TLB tlb;
//	PageTable pageTable;
	/**
	 * Put your code here folks.
	 */
	uint32_t logicalAddress = 576230045;
	// The int casting below is just for display!
	cout << (int) getPageNumber(logicalAddress) << endl;
	cout << (int) getOffsetNumber(logicalAddress) << endl;

#endif

	return 0;
}
