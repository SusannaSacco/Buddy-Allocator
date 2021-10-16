#include "bit_map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void BitMap_new(BitMap* bitmap, int size, unsigned char* buffer){
 bitmap -> buffer = buffer;
bitmap -> size = size;
bitmap -> bits = size*8;
}
