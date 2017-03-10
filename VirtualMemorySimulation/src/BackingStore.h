/*
 * BackingStore.h
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#ifndef BACKINGSTORE_H_
#define BACKINGSTORE_H_

#include <string>
#include <stdio.h>
#include "Constant.h"

class BackingStore {
public:
	BackingStore();
	virtual ~BackingStore();

	STATUS open(const std::string& filepath);
	void close();

	STATUS retriveFrame(PAGENUM page, byte* dst);

private:
	std::string filepath;
	FILE* backingStoreFile = NULL;

};

#endif /* BACKINGSTORE_H_ */
