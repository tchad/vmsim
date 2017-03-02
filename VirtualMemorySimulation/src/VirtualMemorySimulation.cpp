//============================================================================
// Name        : VirtualMemorySimulation.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

bool passCheck();
unsigned char getPageNumber(int logicalAddress);
unsigned char getOffsetNumber(int logicalAddress);

int main() {
	if (passCheck()) {
		/**
		 * Put your code here folks.
		 */
		int logicalAddress = 576230045;
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

/**
 * Return PageNumber
 */
unsigned char getPageNumber(int logicalAddress) {
	return (unsigned char) ((logicalAddress & (0xff << 8)) >> 8);
}

/**
 * Return Offset
 */
unsigned char getOffsetNumber(int logicalAddress) {
	return (unsigned char) (logicalAddress & 0xff);
}
