#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "comprimir.h"

uint comprimir(uint a[], int nbits) {
  uint r = 0;
  int i = 0;
  int espacio = sizeof(uint) << 3;
  while (espacio >= nbits) {
    uint movimiento = (1 << (nbits - 1) << 1) - 1;
    uint trozo = a[i] & (movimiento);
    r <<= nbits;
    r |= trozo;
    i += 1;
    espacio -= nbits;
  }
  return r;
}
