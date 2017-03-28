#include <cstdint>

#ifndef TIMINGS_H_
#define TIMINGS_H_

//All units are in nanoseconds
constexpr uint32_t BS_FRAME_RETRIVE = 10000000; //10ms
constexpr uint32_t MM_ADD_FRAME_POOL = 100; //100ns
constexpr uint32_t MM_OBTAIN_FREE_FRAME = 100; //100ns
constexpr uint32_t PT_SEARCH = 100000; //100us
constexpr uint32_t TLB_SEARCH = 10000; //10us
constexpr uint32_t MM_ACCESS = 10000; //10us

uint32_t whenTlbHits(uint32_t tlbHits);
uint32_t whenTlbMisses(uint32_t tlbMisses, uint32_t ptHits);
uint32_t whenPageFault(uint32_t tlbMisses, uint32_t ptMisses);
float totalTime(VM::Result &result);

#endif /* TIMINGS_H_ */
