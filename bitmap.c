#include "bit_map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void BitMap_new(BitMap* bitmap, int size, unsigned char* buffer){
 bitmap -> buffer = buffer;
bitmap -> size = size;
bitmap -> bits = size*8;
}

void BitMap_set(BitMap* bitmap, int n, int value) {
    byte = i / 8;
    assert(byte < bitmap->size);
    if (value) {
    bitmap->buffer[byte] |= 1 << (i & 7);
} else {
    bitmap->buffer[byte] &= ~(1 << (i & 7));
}

 int BitMap_get(BitMap* bitmap, int n) {
    int byte = i / 8;
    assert(byte < bitmap->size);
    return bitmap->buffer[byte] & (1 << (i & 7)) ? 1 : 0;
}
