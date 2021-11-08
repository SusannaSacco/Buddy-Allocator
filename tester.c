#include "buddy_allocator.h"
#include "bitmap.h"
#include <stdio.h>

#define BITMAP_SIZE 8
#define BLOCK_SIZE 8
#define MEM_SIZE 128

char buffer[BITMAP_SIZE];
char memory[MEM_SIZE];
BuddyAllocator* ba;

int main(int argc, char** argv) {
  BuddyAllocator_new(ba, memory, MEM_SIZE, BLOCK_SIZE, buffer, BITMAP_SIZE);
  printf("Inizializzato nuovo buddy allocator di dimensione 128 byte\n");
  Bitmap_print(ba->bitmap);
  printf("TEST PER LA FUNZIONE CHE ALLOCA MEMORIA:\n");
  printf("Alloco il blocco 1, di dimensione 3 byte\n");
  void* block_1=BuddyAllocator_alloc(ba, 3);
  Bitmap_print(ba->bitmap);
  printf("Alloco il blocco 2, di dimensione 50 byte\n");
  void* block_2=BuddyAllocator_alloc(ba, 50);
  Bitmap_print(ba->bitmap);
  printf("Alloco il blocco 3, di dimensione 10 byte\n");
  void* block_3=BuddyAllocator_alloc(ba, 10);
  Bitmap_print(ba->bitmap);
  printf("Alloco il blocco 4, di dimensione 20 byte\n");
  void* block_4=BuddyAllocator_alloc(ba, 20);
  Bitmap_print(ba->bitmap);
  printf("TESTIAMO L'ERRORE: alloco il blocco 5, di dimensione 10 byte (so già che questa operazione fallirà)\n");
  void* block_5=BuddyAllocator_alloc(ba, 10);
  printf("Alloco il blocco 6, di dimensione 3 byte\n");
  void* block_6=BuddyAllocator_alloc(ba, 3);
  Bitmap_print(ba->bitmap);
  printf("TEST PER LA FUNZIONE CHE LIBERA MEMORIA:\n");
  printf("Libero il blocco 2, di dimensione 50 byte\n");
  BuddyAllocator_free(ba, block_2);
  Bitmap_print(ba->bitmap);
  printf("Libero il blocco 1, di dimensione 3 byte\n");
  BuddyAllocator_free(ba, block_1);
  Bitmap_print(ba->bitmap);
  printf("Libero il blocco 6, di dimensione 3 byte\n");
  BuddyAllocator_free(ba, block_6);
  Bitmap_print(ba->bitmap);
  printf("Libero il blocco 4, di dimensione 20 byte\n");
  BuddyAllocator_free(ba, block_4);
  Bitmap_print(ba->bitmap);
  printf("Libero il blocco 3, di dimensione 10 byte\n");
  BuddyAllocator_free(ba, block_3);
  Bitmap_print(ba->bitmap);
  printf("TESTIAMO L'ERRORE: libero il blocco 5, di dimensione 10 byte (so già che questa operazione fallirà)\n");
  BuddyAllocator_free(ba, block_5);
  printf("Fine del test\n");
  return 0;
}
  
