#include <string.h>
#include <stdlib.h>


typedef unsigned int uint32_t;
uint32_t mix(uint32_t a, uint32_t b, int k) {
    int elementosLeidos = 0;
    uint32_t r = 0;
    uint32_t u = 0;
    while (elementosLeidos <= 32) {
        uint32_t mascara = (1U << k) - 1;
        uint32_t compA = (a >> elementosLeidos) & mascara;
        uint32_t compB = (b >> elementosLeidos) & mascara;
        uint32_t prom = (compA + compB) >> 1;
        u = prom << elementosLeidos;
        r = r|u;
        elementosLeidos += k;
    }
    return r;
}

void decInc(char *num) {
    char *p = num + strlen(num) - 1;
    while (p >= num && *p == '9') {
        *p = '0';
        p--;
    } if (p >= num) {
        *p += 1;
    } else {
        *num = '1';
        p = num;
        while (*p != 0) {
            p++;
        }
        *p = '0';
        p++;
        *p = 0;
    }
}

typedef unsigned long long Decimal;
typedef unsigned long long int ullong;
ullong decimalToInt(Decimal x) {
    int nBits = 60;
    ullong r = 0;
    while (nBits >= 0){
        ullong d = (x >> nBits) & 0xf;
        ullong mult = (d << 3) + (d << 1) + d;
        r = r + mult;
        nBits -= 4;
    }
    return r;
}

int esVocal(char c){
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void invertirVocales(char *str){
    char *p = str;
    char *q = str;
    while (*q != 0){
        q++;
    }
    if (q > str){
        q--;
    }
    while (*p != 0 && p < q){
        if (esVocal(*p) && esVocal(*q)){
            char aux = *p;
            *p = *q;
            *q = aux;
            p++;
            q--;
        } else if (!esVocal(*p)){
            p++;
        } else {
            q--;
        }
    }
    return;
}

typedef struct nodo {
    int x;
    struct nodo *prox;
} Nodo;
void invertir(Nodo **plis) {
    if (*plis == NULL || (*plis)->prox == NULL) {
        return;
    }
    Nodo *prim = *plis;
    Nodo *seg = prim->prox;
    
    invertir(&seg);
    seg -> prox = prim;
    prim -> prox = NULL;
}