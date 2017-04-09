/*
 * Constant.h
 *
 *  Created on: Feb 16, 2017
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <cstdint>
#include <string>

/*
 * 2 ^ 8 PAGE_TABLE_ENTRY
 */
extern uint32_t PAGE_TABLE_ENTRY_COUNT;

/**
 * Number of int required for invalidate fields
 */
#define PAGE_TABLE_INVALIDATE 8

/**
 * Number of int required for aditional reverence fields
 */
#define PAGE_TABLE_REFERENCE_Y 8
#define PAGE_TABLE_REFERENCE_X 2
/**
 * You cannot change the TLB_ENTRY, otherwise you need to
 * change the length of unsigned short validMarker; in the TLB.h
 */
extern uint32_t TLB_ENTRY;

/*
 * 2 ^ 8 * 8 PAGE_SIZE = 256 Bytes = 2048 bit
 */
constexpr uint32_t PAGE_SIZE = 256;

/*
 * 2 ^ 8 * 8 PAGE_SIZE = 256 Bytes = 2048 bit
 */
constexpr uint32_t FRAME_SIZE = 256;

constexpr uint32_t BACKING_STORE_FRAME_COUNT = 256;

using FRAMENUM = uint8_t;
using PAGENUM = uint8_t;
using OFFSET =  uint8_t;
using VADDR = uint32_t;
using PADDR = uint32_t;
using byte = char;

enum STATUS {
	OK,
	FAILED,
	PAGEFAULT
};



extern char BACKING_STORE_FILE[256];
extern bool VERIFY_FRAME;
extern char TEST_INPUT[256];
extern char TEST_VALIDATION_DATA[256];

#endif /* CONSTANT_H_ */
