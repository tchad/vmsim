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

	if(argc < 2 && argc > 3 ) {
		cerr << "Invalid arguments\n";
	} else {
		VM::Result result = VM::simulate(string(argv[1]));

		if(result.status() != STATUS::OK) {
			cout << "Simulation failed!\n";
		} else {
			if(argc == 3) {
				//compare with control data
				cout << "Comparing with control data: ";
				VM::Result controlData(VM::controlDataFromFile(argv[2]));
				if(controlData == result) {
					cout << "MATCH!\n";
				} else {
					cout << "Results differ";
				}
			} else {
				//print on screen
				std::cout << "OK\n";
				for(VM::Result::size_type i=0; i<result.count(); ++i) {
					VM::Result::Itm itm = result.item(i);
					cout << "Virtual address: " << itm.vAddr
							<< " Physical address: " << itm.pAddr
							<< " Value: " << (int)itm.value
							<< endl;
				}
			}
		}
	}

#endif

	return 0;
}
