#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "desescapar.h"

void desescapar(char *s) {
  char *r = s;
  char *w = s;
  while (*r) {
    if (*r != '\\') {
      *w++ = *r++;
    } else {
      char *s1 = r + 1;
      if (*s1 == 'n') {
        *w++ = '\n';
        r += 2;
      } else if (*s1 == 't') {
        *w++ = '\t';
        r += 2;
      } else if (*s1 == '\\') {
        *w++ = '\\';
        r += 2;
      } else if (*s1 == '"') {
        *w++ = '\"';
        r += 2;
      } else if (*s1 == 'x' ) {
        char *s2 = s1 + 1;
        char *s3 = s2 + 1;
        *w++ = convertir_hexadecimal(s2, s3);
        r += 4;
      } else {
        r++;
      }
    } 

  }
}

char *desescapado(const char *s) {
  char *result = malloc(strlen(s) + 1);
  strcpy(result, s);
  desescapar(result);
  return result;
}

char hex2char(const char *s1, const char *s2) {

}
