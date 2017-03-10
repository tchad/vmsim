/*
 * UnitTest.h
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

namespace Test {

enum RESULT {
	PASS,
	FAIL
};

class UnitTest {
public:
	static RESULT test_BackingStorage();
	static void test();
};

} /* namespace Test */

#endif /* UNITTEST_H_ */
