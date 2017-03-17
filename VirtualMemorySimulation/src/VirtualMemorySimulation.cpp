//============================================================================
// Name        : VirtualMemorySimulation.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>
#include <iostream>

#include "VM.h"


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

	if(argc != 2) {
		cerr << "Invalid arguments\n";
	} else {
		VM::Result result = VM::simulate(string(argv[1]));
		if(result.status() == STATUS::OK) {
			std::cout << "OK\n";
		} else {
			std::cout << "FAILED\n";
		}

		//compare and print results here;
	}
#endif

	return 0;
}
