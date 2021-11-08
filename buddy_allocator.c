#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "buddy_allocator.h"

void BuddyAllocator_new(BuddyAllocator* a, char* memory,  int max_size,  int block_size, char* bitmap_buffer,  int bitmap_size){
  a->memory = memory;
  a->max_size  = max_size;
  a->block_size = block_size;
  a->levels = log2(max_size / block_size);
  int bits = (1<<(a->levels+1)) – 1;
  assert(bitmap_size>=(bits/8+1));
  BitMap_new(a->bitmap, bits, bitmap_buffer);
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
   size += sizeof(int)
   int level = find_level(a, size);
   from = pow(2,level)-1;
   to = pow(2,level+1)-1;
   int i = 0;
   for(; from<to, from++) {
       if(Bitmap_get(a->bitmap, from)) {
           Set_parent(a, from, 1);
           Set_children(a, from, 1);
           int block = a->max_size/(pow(2,level)); 
           char* ptr=a->memory+i*block;
           *((int*)ptr)=from; 
           return (void*)(ptr + 4);
           } 
       i++;
    }
    printf("ERRORE: Non c’è memoria libera disponibile\n");
    return NULL;
}


void BuddyAllocator_free(BuddyAllocator* a, void* ptr) {
    if (ptr==NULL){
        printf("ERRORE: puntatore vuoto\n");
        return;
    }
    int i=*(int*)((char*)ptr-sizeof(int));
    if (i>pow(2,a->levels+1)){
       printf("ERRORE: Indice non valido\n");
       return;
    }
    Bitmap_set(a->bitmap, i, 0);
    Set_children(a, i, 0);
    //libero il genitore se il blocco fratello è già vuoto, così si riuniscono
    int iBuddy = i;
    if(i%2==0) {
       iBuddy--; 
    } else {
       iBuddy++; 
    }
   while (i==0 &&  Bitmap_get(a->bitmap,iBuddy)==0){
      iParent = (i-1)/2;
      Bitmap_set(a->bitmap,iParent,0);
      i=iParent;
  }
}
