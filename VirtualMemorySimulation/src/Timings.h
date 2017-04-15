#include <cstdint>

#ifndef TIMINGS_H_
#define TIMINGS_H_

//All units are in nanoseconds
constexpr uint32_t PAGE_REPLACE_COST = 100000; //100us
constexpr uint32_t TLB_SEARCH = 100; //100ns
constexpr uint32_t MM_ACCESS = 1000; //1us

uint32_t whenTlbHits(uint32_t tlbHits);
uint32_t whenTlbMisses(uint32_t tlbMisses, uint32_t ptHits);
uint32_t whenPageFault(uint32_t tlbMisses, uint32_t ptMisses);
float totalTime(VM::Result &result);

#endif /* TIMINGS_H_ */
