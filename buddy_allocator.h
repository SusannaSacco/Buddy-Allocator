#pragma once
#include <stdint.h>
#include "bitmap.h"


typedef struct {
  unsigned char* memory;
  int levels;
  int max_size;
  int block_size;
  BitMap* bitmap;
  } BuddyAllocator;
