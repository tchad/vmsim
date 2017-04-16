#include "Constant.h"

uint32_t PAGE_TABLE_ENTRY_COUNT = 256;
uint32_t TLB_ENTRY = 16;
bool VERIFY_FRAME = false;
char BACKING_STORE_FILE[256] = "BACKING_STORE.bin";

char TEST_INPUT[256] = "";
char TEST_VALIDATION_DATA[256] = "";

bool SIMPLE_OUTPUT = false;
