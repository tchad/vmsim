/*
 * Constant.h
 *
 *  Created on: Feb 16, 2017
 *      Author: therangersolid
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

/*
 * 2 ^ 8 PAGE_TABLE_ENTRY
 */
#define PAGE_TABLE_ENTRY 256

#define TLB_ENTRY 16

/*
 * 2 ^ 8 * 8 PAGE_SIZE = 256 Bytes = 2048 bit
 */
#define PAGE_SIZE 256

/*
 * 2 ^ 8 * 8 PAGE_SIZE = 256 Bytes = 2048 bit
 */
#define FRAME_SIZE 256

#define PHYSICAL_MEMORY_ENTRY 256 // Thus total is 256 frames x 256-byte frame size

#endif /* CONSTANT_H_ */
