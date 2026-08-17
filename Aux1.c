#include <stdio.h>
//P1
int CelciusAFahrenheit(int argc, char *argv[]){
    int celcius = 23;
    long double fahrenheit = (celcius * 9.0/5.0) + 32;
    printf("%d Cº equivalen a %.2Lf Fº\n", celcius, fahrenheit);
    return 0;
}


int FactorialRec(int n, char *argv[]){
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * FactorialRec(n - 1, argv);
    }
}


int main(int argc, char *argv[]){
    CelciusAFahrenheit(argc, argv);
    int result = FactorialRec(9, argv);
    printf("El factorial de 9 es: %d\n", result);
    return 0;
}