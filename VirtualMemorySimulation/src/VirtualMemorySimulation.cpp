//============================================================================
// Name        : VirtualMemorySimulation.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>
#include <iostream>
#include <iomanip>

#include "VM.h"
#include "Timings.h"

using namespace std;

void printStats(VM::Result &result)
{
	cout << "TLB Hit: " << result.getTLBStats().hitCount
			<< " Miss: " << result.getTLBStats().missCount << endl;
	cout << "PT Hit: " << result.getPtStats().hitCount
			<< " Miss: " << result.getPtStats().missCount << endl;
	cout << "Average time: " << fixed << setprecision(3) <<
			totalTime(result)/(result.getTLBStats().hitCount +
					result.getTLBStats().missCount) / 1000 << "us" << endl;
}


int main(int argc, char **argv)
{
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
			printStats(result);
		}
	}

	return 0;
}
