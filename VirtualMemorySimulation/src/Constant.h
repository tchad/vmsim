/*
 * Constant.h
 *
 *  Created on: Feb 16, 2017
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <cstdint>

/*
 * 2 ^ 8 PAGE_TABLE_ENTRY
 */
constexpr uint32_t PAGE_TABLE_ENTRY = 256;

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
constexpr uint32_t TLB_ENTRY = 16;

/*
 * 2 ^ 8 * 8 PAGE_SIZE = 256 Bytes = 2048 bit
 */
constexpr uint32_t PAGE_SIZE = 256;

/*
 * 2 ^ 8 * 8 PAGE_SIZE = 256 Bytes = 2048 bit
 */
constexpr uint32_t FRAME_SIZE = 256;

constexpr uint32_t PHYSICAL_MEMORY_ENTRY = 256; // Thus total is 256 frames x 256-byte frame size

using FRAMENUM = uint8_t;
using PAGENUM = uint8_t;
using OFFSET =  uint8_t;
using VADDR = uint32_t;
using byte = char;

enum STATUS {
	OK,
	FAILED
};

#endif /* CONSTANT_H_ */
