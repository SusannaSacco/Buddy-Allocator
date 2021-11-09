#include "bitmap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void BitMap_new(BitMap* bitmap, int bits, char* buffer){
   bitmap->buffer = buffer;
   bitmap->bits = bits;
   //calcolo la dimensione in byte
   if (bits % 8 == 0) {
      bitmap->size = bits/8; }
   else {
      bitmap->size = bits/8 + 1;
      }
}

void BitMap_set(BitMap* bitmap, int n, int value) {
    int byte = n / 8;
    assert(byte < bitmap->size);
    if (value) {
    bitmap->buffer[byte] |= 1 << (n & 7);
}   else {
    bitmap->buffer[byte] &= ~(1 << (n & 7));
}
}

 int BitMap_get(BitMap* bitmap, int n) {
    int byte = n / 8;
    assert(byte < bitmap->size);
    return bitmap->buffer[byte] & (1 << (n & 7)) ? 1 : 0;
}


void BitMap_print(BitMap* bitmap) {
    printf("Rappresentazione della bitmap come albero binario:\n");
    int lvl = 0;
    for (int i=0; i<bitmap->bits; i++){
	//primi bit di ciascun livello
    if (i==(pow(2,lvl)-1)){
      printf("livello %d: ",lvl);
      for (int n=1; n<bitmap->bits/pow(2,lvl+1); n++){
        printf(" ");
      }
    }
    //ultimi bit di ciascun livello
    if (i==(pow(2,lvl+1)-2)){
      printf("%d ", BitMap_get(bitmap,i));
      printf("\n");
      lvl++;
    }
    //tutti i bit esclusi gli ultimi di ciascun livello
    else{ 
     printf("%d ", BitMap_get(bitmap,i));
     for (int n=1; n<bitmap->bits/pow(2,lvl+1); n++){
        printf("  ");
      }
    }
  }
printf("\n\n");
  }
  
void BitMap_print2(BitMap* bitmap) {
    printf("Stato corrente della bitmap:\n");
    for (int i=0; i<bitmap->bits; i++){
      printf("%d ", BitMap_get(bitmap,i));
      }
printf("\n");
  }
