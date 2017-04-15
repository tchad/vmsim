#ifndef BACKINGSTORE_H_
#define BACKINGSTORE_H_

#include <string>
#include <stdio.h>
#include "Constant.h"

class BackingStore {
public:
	struct STATISTICS {
		uint32_t frameRetrive;

		STATISTICS();
	};

	BackingStore();
	virtual ~BackingStore();

	STATUS open(const std::string& filepath);
	void close();

	STATUS retriveFrame(PAGENUM page, byte* dst);

	STATISTICS getStats();

private:
	std::string filepath;
	FILE* backingStoreFile = NULL;

	STATISTICS STATS;
};

#endif /* BACKINGSTORE_H_ */
