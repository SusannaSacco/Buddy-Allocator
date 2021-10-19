#include <assert.h>
#include <math.h
#include <stdio.h>
#include <stdlib.h>
#include "buddy_allocator.h"

void BuddyAllocator_new(BuddyAllocator* a, unsigned  char* memory,  int max_size,  int block_size, unsigned char* bitmap_buffer,  int bitmap_size){
  a->memory = memory;
  a->max_size  = max_size;
  a->block_size = block_size;
  a->levels = log2(max_size / block_size);
 //grandezza, espressa in bytes, necessaria per la bitmap a gestire tutti i livelli, considerando che ogni bit rappresenta un blocco
  int bytes = ((1<<(levels+1)) – 1) / 8 + 1;
  Assert(bitmap_size>=bytes);
  BitMap_new(a->bitmap, bytes, bitmap_buffer);
