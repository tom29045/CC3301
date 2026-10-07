#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

typedef struct {
  unsigned char tamLlave;
  char llaveYDef[99];
} Fila;

int main(int argc, char *argv[]) {
  if (argc!=4) {
    fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n");
    exit(1);
  }

  char *dicc = argv[1];
  char *lla = argv[2];
  char *def = argv[3];

  int largoLla = strlen(lla);
  int largoDef = strlen(def);
  int total = largoLla + largoDef;

  if (total > 99) {
    fprintf(stderr, "Tamanno de la llave mas tamanno de la definicion (%d) exceden maximo permitido (%d)\n", total, 99);
    exit(1);
  }

  FILE *f = fopen(dicc, "r+");
  if (f == NULL) {
    perror(dicc);
    exit(1);
  }
  
  fseek(f, 0, SEEK_END);
  long tamArchivo = ftell(f);
  int nFilas = tamArchivo / sizeof(Fila);

  int indiceInicial = hash_string(lla) % nFilas;
  int i = 0;
  int indiceEscogido = -1;
  while (i < nFilas) {
    int indice = (indiceInicial + i) % nFilas;
    fseek(f, (long)indice * sizeof(Fila), SEEK_SET);
    Fila fil;
    if (fread(&fil, sizeof(Fila), 1, f) != 1) {
      perror(dicc);
      exit(1);
    }
    if (fil.tamLlave == 0){
      indiceEscogido = indice;
      break;
    }
    if (fil.tamLlave == largoLla) {
      int iguales = 1;
      for (int j = 0; j < largoLla; j++) {
        if (fil.llaveYDef[j] != lla[j]){
          iguales = 0;
          break;
        }
      }
      if (iguales) {
        fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", lla);
        fclose(f);
        exit(1);
      }
    }
    i++;
  }
  if (indiceEscogido == -1) {
    fprintf(stderr, "%s: el diccionario esta lleno\n", dicc);
    fclose(f);
    exit(1);
  }
  Fila nueva;
  nueva.tamLlave = largoLla;

  int pos = 0;

  for (int j = 0; j < largoLla; j++) {
    nueva.llaveYDef[pos++] = lla[j];
  }
  for (int j = 0; j < largoDef; j++) {
    nueva.llaveYDef[pos++] = def[j];
  }
  while (pos < 99) {
    nueva.llaveYDef[pos++] = ' ';
  }
  fseek(f, (long)indiceEscogido * sizeof(Fila), SEEK_SET);
  if (fwrite(&nueva, sizeof(Fila), 1, f) != 1) {
    perror(dicc);
    exit(1);
  }

  fclose(f);
  return 0;

}