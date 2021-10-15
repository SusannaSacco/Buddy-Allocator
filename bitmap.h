#pragma once
#include <stdint.h>

typedef struct {
  unsigned char *buffer; 
  int size;
  int bits;
} BitMap;

void BitMap_new(BitMap *bitmap, int size, unsigned char* buffer);

void BitMap_set(BitMap *bitmap, int n, int value);

int BitMap_get(const BitMap *bitmap, int n);

void BitMap_print(BitMap* bitmap);    
