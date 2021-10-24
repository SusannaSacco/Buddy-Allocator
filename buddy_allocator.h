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

void BuddyAllocator_new(BuddyAllocator* a, unsigned  char* memory,  int max_size,  int block_size, unsigned char* bitmap_buffer,  int bitmap_size);

int Find_level(BuddyAllocator* a, int size);

void Set_children(BuddyAllocator* a, int bit, int value);

void Set_parent(BuddyAllocator* a, int bit, int value);

void* BuddyAllocator_alloc(BuddyAllocator* a, int size);

void BuddyAllocator_free(BuddyAllocator* a, void* ptr);
