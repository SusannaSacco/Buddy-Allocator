#include "bit_map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void BitMap_new(BitMap* bitmap, int bits, char* buffer){
   bitmap->buffer = buffer;
   bitmap->bits = bits;
   if (bits % 8 == 0) {
      bitmap->size = bits/8; }
   else {
      bitmap->size = bits/8 + 1;
      }
}

void BitMap_set(BitMap* bitmap, int n, int value) {
    byte = n / 8;
    assert(byte < bitmap->size);
    if (value) {
    bitmap->buffer[byte] |= 1 << (n & 7);
} else {
    bitmap->buffer[byte] &= ~(1 << (n & 7));
}
}

 int BitMap_get(BitMap* bitmap, int n) {
    int byte = n / 8;
    assert(byte < bitmap->size);
    return bitmap->buffer[byte] & (1 << (n & 7)) ? 1 : 0;
}


void Bitmap_print(Bitmap* bitmap) {
int lvl = 0;
for (int i=0; i<bitmap->bits; i++){
    if (i==(pow(2,lvl)-1)){
      printf("level %d: ",lvl);
    }
    if (i==(pow(2,lvl+1)-2)){
      printf("%d ", Bitmap_get(bitmap,i));
      printf("\n");
      lvl++;
    }
    else{ 
     printf("%d ", Bitmap_get(bitmap,i));
     for (int n=0; n<bitmap->bits/pow(2,lvl+1); n++){
        printf("  ");
      }
    }
  }
printf("\n\n");
  }
