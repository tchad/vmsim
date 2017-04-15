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
	STATS.frameRetrive++;
	STATUS ret = STATUS::FAILED;

	if((backingStoreFile != NULL) && (page < BACKING_STORE_FRAME_COUNT)) {
		long fileoffset = page * PAGE_SIZE;
		if(0 == fseek(backingStoreFile, fileoffset, SEEK_SET)) {
			if( PAGE_SIZE == fread(dst, sizeof(byte), PAGE_SIZE, backingStoreFile)) {
				ret = STATUS::OK;
			}
		}
	}

	return ret;
}

BackingStore::STATISTICS::STATISTICS():
	frameRetrive(0)
{}

BackingStore::STATISTICS BackingStore::getStats()
{
	return STATS;
}
