#pragma once
#include <stdint.h>

typedef struct {
  char *buffer; 
  int size;
  int bits;
} BitMap;

//crea una nuova bitmap con un buffer costituito da un array di char
void BitMap_new(BitMap *bitmap, int bits, char* buffer);

//imposta il bit n-esimo della bitmap al valore 0 o 1
void BitMap_set(BitMap *bitmap, int n, int value);

//restituisce il valore del n-esimo bit della bitmap
int BitMap_get(BitMap *bitmap, int n);

//stampa la bitmap come albero binario
void BitMap_print(BitMap* bitmap);    

//stampa la bitmap in una sola riga
void BitMap_print2(BitMap* bitmap);
