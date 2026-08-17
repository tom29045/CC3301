#include <stdio.h>
#include <math.h>

int decimal(int binario){
    int sum = 0;
    int i = 0;
    while (binario != 0) {
        if (binario % 10){
            sum += pow(2, i);
        }
        i++;
        binario /=10;
    }
    return sum;
}

int main(int argc, char *argv[]){
    int binario = 101010;
    int result = decimal(binario);
    printf("El numero binario %d en decimal es: %d\n", binario, result);
    return 0;
}