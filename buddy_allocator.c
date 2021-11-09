#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "buddy_allocator.h"

void BuddyAllocator_new(BuddyAllocator* a, char* memory,  int max_size,  int block_size, char* bitmap_buffer,  int bitmap_size){
  a->memory = memory;
  a->max_size  = max_size;
  a->block_size = block_size;
  //calcolo il numero di livelli totali necessari 
  a->levels = log2(max_size / block_size);
  //calcolo il numero di bit necessari per rappresentare tutti i livelli, livello 0 incluso, e controllo che la bitmap sia abbastanza grande
  int bits = pow(2, a->levels+1)-1;
  assert(bitmap_size>=(bits/8+1));
  BitMap_new(&a->bitmap, bits, bitmap_buffer);
  printf("Nuovo Buddy Allocator creato:\nMemory size: %d\nMinimum block size: %d\nBitmap size: %d\n\n", max_size, block_size, bitmap_size);
}
  
  int Find_level(BuddyAllocator* a, int size){
     assert(size < a->max_size);
     //se il blocco è più piccolo della dimensione minima, si troverà nell'ultimo livello
     if (size <= a->block_size) return a->levels;
     else {
        int lvl= 0;
        int comp = a->max_size / 2;
      	while (size <= comp){
		      lvl++;
		      comp = comp / 2;
        }
   	return lvl;
    }
}


void Set_children(BuddyAllocator* a, int bit, int value) {
	//si ferma quando arriva alla fine dell'array
	if (bit < (&a->bitmap)->bits) {
		BitMap_set(&a->bitmap, bit, value);
		Set_children(a, bit*2+1, value);
		Set_children(a, bit*2+2, value);
	}
}


void Set_parent(BuddyAllocator* a, int bit, int value) {
	BitMap_set(&a->bitmap, bit, value);
	//si ferma quando arriva alla radice
	if (bit != 0) {
	  //indice genitore == (indice figlio sx - 1)/2 == (indice figlio dx - 2)/2
	  if (bit%2 == 0) bit--;
          bit = (bit-1)/2;
	  Set_parent(a, bit, value);
	}
}


void* BuddyAllocator_alloc(BuddyAllocator* a, int size) {
   printf("Allocazione di un blocco di dimensione %d in memoria...\n", size);
   //aggiungo un intero per salvarmi l'indice
   size += sizeof(int);
   int level = Find_level(a, size);
   printf("Il blocco potrebbe essere allocato al livello %d...\n", level);
   //calcolo gli indici più piccoli appartenenteial livello trovato e a quello successivo
   int from = pow(2,level)-1;
   int to = pow(2,level+1)-1;
   //from è l'indice del bit contando come 0 la radice, i è l'indice contando come 0 il primo bit del suo livello
   int i = 0;
   for(; from<to; from++) {
	   //cerco un blocco libero scorrendo il livello
       if(BitMap_get(&a->bitmap, from)==0) {
           Set_parent(a, from, 1);
           Set_children(a, from, 1);
           int block = a->max_size/(pow(2,level));
           //salvo il puntatore, e in esso memorizzo il relativo indice della bitmap 
           char* ptr=a->memory+i*block;
           *((int*)ptr)=from; 
           printf("Blocco di dimensione totale %d allocato con successo all'indice %d.\n",block, from);
           BitMap_print2(&a->bitmap);
           BitMap_print(&a->bitmap);
           return (void*)(ptr + 4);
           } 
       i++;
    }
    printf("ERRORE: Non c’è memoria libera disponibile\n\n");
    return NULL;
}


void BuddyAllocator_free(BuddyAllocator* a, void* ptr) {
	//controllo che la memoria da liberare sia stata precedentemente allocata
    if (ptr==NULL){
        printf("ERRORE: puntatore vuoto\n\n");
        return;
    }
    //ricavo l'indice della bitmap
    int i=*(int*)((char*)ptr-sizeof(int));
    int aux=log2(i+1);
    int block = a->max_size/pow(2, aux);
    printf("Liberazione del blocco di dimensione totale %d salvato all'indice della bitmap %d...\n", block, i);
    BitMap_set(&a->bitmap, i, 0);
    Set_children(a, i, 0);
    //libero il genitore se il blocco fratello è già vuoto, così si riuniscono
    int iBuddy = i;
    if(i%2==0) {
       iBuddy--; 
    } else {
       iBuddy++; 
    }
    while (i!=0 &&  BitMap_get(&a->bitmap,iBuddy)==0){
       int iParent = (i-1)/2;
       BitMap_set(&a->bitmap,iParent,0);
       i=iParent;
       iBuddy = i;
       if(i%2==0) {
          iBuddy--; 
       } else {
          iBuddy++; 
       }
    }
    printf("Memoria liberata con successo.\n");
    BitMap_print2(&a->bitmap);
    BitMap_print(&a->bitmap);
} 
