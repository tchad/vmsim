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

int main() {
	if (passCheck()) {
		/**
		 * Put your code here folks.
		 */
		cout << "Hello world" << endl; // prints
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
