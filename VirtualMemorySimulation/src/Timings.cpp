/*
 * Timings.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: bouyu
 */

#include "VM.h"
#include "Timings.h"

// Time it takes for MM to get page if page is found in TLB
// Algorithm: (TLB search time + main memory access time) * times page is found in TLB
uint32_t whenTlbHits(uint32_t tlbHits) {
	uint32_t result;
	result = (TLB_SEARCH + MM_ACCESS) * tlbHits;
	return result;
}

// Time it takes for MM to get page if page is found in page table
// Algorithm: (TLB search time + 2 * main memory access time) *
//				times page is not found in TLB
uint32_t whenTlbMisses(uint32_t tlbMisses, uint32_t ptHits) {
	uint32_t result;
	result = (TLB_SEARCH + 2*MM_ACCESS) * tlbMisses;
	return result;
}

///Time it takes for MM to get page if there was a page fault
uint32_t whenPageFault(uint32_t tlbMisses, uint32_t ptMisses) {
	uint32_t result;
	result = (PAGE_REPLACE_COST + 2*MM_ACCESS + TLB_SEARCH) * ptMisses;
	return result;
}

float totalTime(VM::Result &result) {
	float totalTime;
	totalTime = whenTlbHits(result.getTLBStats().hitCount) +
			 whenTlbMisses(result.getTLBStats().missCount, result.getPtStats().hitCount) +
			 whenPageFault(result.getTLBStats().missCount, result.getPtStats().missCount);
	return totalTime;
}

