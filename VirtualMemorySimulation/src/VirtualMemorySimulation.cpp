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
#include <cstring>
#include <getopt.h>
#include <cstdlib>
#include <cmath>

#include "Constant.h"
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

void printUsage()
{
	cout << "Usage: ./vmsim [-t n] [-p n] [-v filename] [-h] [-b filename] [-f Y/N] testfile\n";
	cout << "\t t, tlb\t\t- number of TLB entries(power of 2) [Default: 16]\n";
	cout << "\t p, pt\t\t- number of Page Table entries(power of 2) [Default: 256]\n";
	cout << "\t v, verf\t- specify the file with verification data [Default: none]\n";
	cout << "\t h, help\t- print this dialog\n";
	cout << "\t b, bs\t\t- specify non-default backing storage [Default: BACKING_STORAGE.bin]\n";
	cout << "\t f, cmpframe\t- enable frame number comparison(test data must support that) [Default: N]\n";

}

int processArguments(int argc, char **argv)
{
	const char* const shortoptions = "t:p:v:hb:f:";

	const struct option long_options[] = {
			{"tlb", required_argument, NULL, 't'},
			{"pt", required_argument, NULL, 'p'},
			{"verf", required_argument, NULL, 'v'},
			{"help", no_argument, NULL, 'h'},
			{"bs", required_argument, NULL, 'b'},
			{"cmpframe", required_argument, NULL, 'f'},
			{NULL, 0, NULL, 0}
	};

	int option;
	do {
		int opt_idx;
		option = getopt_long(argc, argv, shortoptions, long_options, &opt_idx);

		switch(option) {
		case 't':
			{
				int result = atoi(optarg);
				if(result <= 0 || (log2(result) != int(log2(result)))) {
					cerr << "Invalid TLB size\n";
					return -1;
				}
				TLB_ENTRY = result;
			}
			break;
		case 'p':
			{
				int result = atoi(optarg);
				if(result <= 0 || (log2(result) != int(log2(result)))) {
					cerr << "Invalid Page Table size\n";
					return -1;
				}
				PAGE_TABLE_ENTRY_COUNT = result;
			}
			break;
		case 'v':
			{
				strcpy(TEST_VALIDATION_DATA, optarg);
			}
			break;
		case 'h':
			{
				printUsage();
				return -1;
			}
			break;
		case 'b':
			{
				strcpy(BACKING_STORE_FILE,optarg);
			}
			break;
		case 'f':
			{
				if(optarg[0] == 'Y' || optarg[0] == 'y') {
					VERIFY_FRAME = true;
				} else if (optarg[0] == 'N' || optarg[0] == 'n') {
					VERIFY_FRAME = false;
				} else {
					cerr << "Invalid argument for -f, can be [Y/N]\n";
					return -1;
				}
			}
			break;
		case -1:
			break;
		default:
			{
				//error
				return -1;
			}
		};
	} while (option != -1);


	//tlb < pt
	if(PAGE_TABLE_ENTRY_COUNT < TLB_ENTRY) {
		cerr << "TLB cannot be larger than Page Table\n";
		return -1;
	}

	//nonamed arg
	if(optind < argc) {
		strcpy(TEST_INPUT, argv[optind]);
	} else {
		cerr << "Missing test input data\n";
		return -1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if(processArguments(argc, argv) == 0) {
		VM::Result result = VM::simulate(string(TEST_INPUT));

		if(result.status() != STATUS::OK) {
			cout << "Simulation failed!\n";
		} else {
			if(strlen(TEST_VALIDATION_DATA) > 0) {
				//compare with control data
				cout << "Comparing with control data: ";
				VM::Result controlData(VM::controlDataFromFile(TEST_VALIDATION_DATA));
				if(controlData == result) {
					cout << "MATCH!\n";
				} else {
					cout << "MISSMATCH!\n";
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
