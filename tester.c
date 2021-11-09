#include "buddy_allocator.h"
#include "bitmap.h"
#include <stdio.h>

#define BITMAP_SIZE 8
#define BLOCK_SIZE 8
#define MEM_SIZE 128

char buffer[BITMAP_SIZE];
char memory[MEM_SIZE];
BuddyAllocator ba;

int main(int argc, char** argv) {
  printf("------Inizio test------\n\n");
  BuddyAllocator_new(&ba, memory, MEM_SIZE, BLOCK_SIZE, buffer, BITMAP_SIZE);
  printf("TEST PER LA FUNZIONE CHE ALLOCA MEMORIA:\n\n");
  printf("---BLOCK 1---\n");
  void* block_1=BuddyAllocator_alloc(&ba, 3);
  printf("---BLOCK 2---\n");
  void* block_2=BuddyAllocator_alloc(&ba, 50);
  printf("---BLOCK 3---\n");
  void* block_3=BuddyAllocator_alloc(&ba, 10);
  printf("---BLOCK 4---\n");
  void* block_4=BuddyAllocator_alloc(&ba, 10);
  printf("---TESTIAMO L'ERRORE: BLOCK 5---\n");
  void* block_5=BuddyAllocator_alloc(&ba, 18);
  printf("---BLOCK 6---\n");
  void* block_6=BuddyAllocator_alloc(&ba, 3);
  printf("TEST PER LA FUNZIONE CHE LIBERA MEMORIA:\n\n");
  printf("---BLOCK 2---\n");
  BuddyAllocator_free(&ba, block_2);
  printf("---BLOCK 1---\n");
  BuddyAllocator_free(&ba, block_1);
  printf("---BLOCK 6---\n");
  BuddyAllocator_free(&ba, block_6);
  printf("---BLOCK 4---\n");
  BuddyAllocator_free(&ba, block_4);
  printf("---TESTIAMO L'ERRORE: BLOCK 5---\n");
  BuddyAllocator_free(&ba, block_5);
  printf("---BLOCK 3---\n");
  BuddyAllocator_free(&ba, block_3);
  printf("------Fine test------\n"); 
  return 0; 
  }
  
