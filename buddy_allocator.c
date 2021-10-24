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
  int bytes = ((1<<(a->levels+1)) – 1) / 8 + 1;
  assert(bitmap_size>=bytes);
  BitMap_new(a->bitmap, bytes, bitmap_buffer);
}
  
  int Find_level(BuddyAllocator* a, int size){
     assert(size < a->max_size);
     if (size <= a->block_size) return a->levels;
     else {
        int lvl= 0;
        int comp = buff->max_size / 2;
      	while (size <= comp){
		      lvl++;
		      comp = comp / 2;
        }
   	return lvl;
    }
}


void Set_children(BuddyAllocator* a, int bit, int value) {
	if (bit < (1<<(a->levels+1)-1)) {
		Bitmap_set(a->bitmap, bit, value);
		Set_child(a, bit*2+1, value);
		Set_child(a, bit*2+2, value);
	}
}


void Set_parent(BuddyAllocator* a, int bit, int value) {
	Bitmap_set(a->bitmap, bit, value);
	if (bit != 0) {
	  if (bit%2 == 0) bit--;
          bit = (bit-1)/2;
	  Set_parent(a, bit, value);
	}
}


void* BuddyAllocator_alloc(BuddyAllocator* a, int size) {
int level = find_level(a, size);
from = pow(2, level)-1;
to = pow(2, level+1)-1;
for(; from<to, from++) {
    }
}
