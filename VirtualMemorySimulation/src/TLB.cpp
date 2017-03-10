/*
 * TLB.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: therangersolid
 */

#include "TLB.h"

TLB::TLB() {
	unsigned char i = 0;
	do {
		pageNumber[i] = 0;
		frameNumber[i] = 0;

	} while (i++ < (TLB_ENTRY - 1));
	validMarker = 0;
	pointer = 0;
}

/**
 * This function will get the frame number from TLB. If not exist, it
 * will return 0, and false for boolean.
 * @param  pageNumber  a page you use to get the frame number
 * @return   CharResult   The result + error code with boolean
 */
CharResult TLB::getFrameNumber(const unsigned char pageNumber) const {
	CharResult charResult = getPointer(pageNumber);
	if (!charResult.error) {
		charResult.result = frameNumber[charResult.result]; // Replace the pointer with frameNumber
	}
	return charResult;
}

/**
 * This function will set the page number and frame number for TLB.
 * @param  pageNumber  a page you use to get the frame number
 * @param  frameNumber  a frame number
 */
void TLB::setPageFrameNumber(const unsigned char pageNumber,
		const unsigned char frameNumber) {
	(*this).pageNumber[pointer] = pageNumber;
	(*this).frameNumber[pointer] = frameNumber;
	validMarker |= (1 << pointer);
	pointer = (pointer + 1) % TLB_ENTRY;

}

/*
 * This is for delete function where one can set a byte invalid
 * @param  pageNumber  a page you use to set invalid value
 */
//void TLB::setInvalid(const unsigned char pageNumber) {
//	CharResult charResult = getPointer(pageNumber);
//	if (!charResult.error) {
//		validMarker &= ~(1 << charResult.result);
//	}
//}
/*
 * This is for delete function where one can set a byte invalid
 * @param  pageNumber  a page you use to set invalid value
 */
void TLB::invalidate() {
	validMarker = 0;
}

/**
 * This function will get the position of pageNumber from TLB. If not exist, it
 * will return 0, and false for boolean. (Internal use only!)
 * @param  pageNumber  a page you use to get the frame number
 * @return   CharResult   The result + error code with boolean
 */
CharResult TLB::getPointer(const unsigned char pageNumber) const {
// This for loops will search from the newest added item at pointer to 0
	unsigned char i = pointer - 1;
	CharResult charResult;
	for (; i >= 0; --i) {
		if ((validMarker >> i) & 1) { // only enter when the valid is 1.
			if ((*this).pageNumber[i] == pageNumber) { // TLB Hit.
				charResult.result = i;
				charResult.error = false;
				return charResult;
			}
		}
	}
	for (i = TLB_ENTRY; i >= pointer; --i) {
		if ((validMarker >> i) & 1) { // only enter when the valid is 1.
			if ((*this).pageNumber[i] == pageNumber) { // TLB Hit.
				charResult.result = i;
				charResult.error = false;
				return charResult;
			}
		}

	}
	charResult.result = 0;
	charResult.error = true;
	return charResult;
}
