#ifndef TIMINGS_H_
#define TIMINGS_H_

#include <cstdint>

#include "VM.h"

//All units are in nanoseconds
constexpr uint32_t PAGE_REPLACE_COST = 8000000; //8ms
constexpr uint32_t TLB_SEARCH = 20; //20ns
constexpr uint32_t MM_ACCESS = 100; //100ns

uint32_t whenTlbHits(uint32_t tlbHits);
uint32_t whenTlbMisses(uint32_t tlbMisses, uint32_t ptHits);
uint32_t whenPageFault(uint32_t tlbMisses, uint32_t ptMisses);
float totalTime(VM::Result &result);

#endif /* TIMINGS_H_ */
