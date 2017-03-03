//============================================================================
// Name        : VirtualMemorySimulation.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TLB.h"
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

bool passCheck();
bool init();
unsigned char getPageNumber(unsigned int logicalAddress);
unsigned char getOffsetNumber(unsigned int logicalAddress);
void internalGetFrameNumber(const unsigned int pageNumber, CharResult charFromTLB);
int main() {
	if (passCheck() && init()) {
		/**
		 * Put your code here folks.
		 */
		unsigned int logicalAddress = 576230045;
		// The int casting below is just for display!
		cout << (int) getPageNumber(logicalAddress) << endl;
		cout << (int) getOffsetNumber(logicalAddress) << endl;
	}
	return 0;
}

/**
 * The use of this function is to check whether the running system
 * capable of running the code as defined.
 */
bool passCheck() {
	if (sizeof(char) != 1) {
		cerr << "The size of char != 1 byte ,It's equal to " << sizeof(char)
				<< " byte, Aborting!";
		return false;
	}
	if (sizeof(int) != 4) {
		cerr << "The size of int != 4 byte,It's equal to " << sizeof(int)
				<< " byte, Aborting!";
		return false;
	}
	if (sizeof(short) != 2) {
		cerr << "The size of short != 2 byte,It's equal to " << sizeof(short)
				<< " byte, Aborting!";
		return false;
	}
	return true;
}

TLB tlb;
bool init() {
	return true;
}
/**
 * Return PageNumber
 */
unsigned char getPageNumber(const unsigned int logicalAddress) {
	return (unsigned char) ((logicalAddress & (0xff << 8)) >> 8);
}

/**
 * Return Offset
 */
unsigned char getOffsetNumber(const unsigned int logicalAddress) {
	return (unsigned char) (logicalAddress & 0xff);
}

CharResult getFrameNumber(const unsigned int pageNumber) {
	CharResult fromTLB;
	std::thread t1(internalGetFrameNumber, pageNumber, fromTLB);
	t1.join();
	return fromTLB;
}

void internalGetFrameNumber(const unsigned int pageNumber, CharResult charFromTLB) {
	charFromTLB = tlb.getFrameNumber(pageNumber);
}
