/*
 * BackingStore.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: udntneed2knw
 */

#include "BackingStore.h"

BackingStore::BackingStore() :
	filepath(""),
	backingStoreFile(NULL)
{
}

BackingStore::~BackingStore()
{
	close();
}

STATUS BackingStore::open(const std::string& filepath)
{
	STATUS ret = STATUS::FAILED;
	if(!filepath.empty()) {
		FILE *f = fopen(filepath.c_str(), "rb");
		if(f != NULL) {
			backingStoreFile = f;
			this->filepath = filepath;
			ret = STATUS::OK;
		}
	}

	return ret;
}

void BackingStore::close()
{
	if(backingStoreFile) {
		fclose(backingStoreFile);
		backingStoreFile = NULL;
		filepath = "";
	}
}

STATUS BackingStore::retriveFrame(PAGENUM page, byte* dst)
{
	STATUS ret = STATUS::FAILED;

	if((backingStoreFile != NULL) && (page < PHYSICAL_MEMORY_ENTRY)) {
		long fileoffset = page * PAGE_SIZE;
		if(0 == fseek(backingStoreFile, fileoffset, SEEK_SET)) {
			if( PAGE_SIZE == fread(dst, sizeof(byte), PAGE_SIZE, backingStoreFile)) {
				ret = STATUS::OK;
			}
		}
	}

	return ret;
}
