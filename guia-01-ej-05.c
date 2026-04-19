#include <stdio.h>

/*Número elevado a una potencia 
Escriba un programa que calcule la potencia de un número base elevado a un exponente 
usando recursividad. */

int potenciacion(int base, int exp);

int main(int argc, char const *argv[])
{
    int b,x;
    printf("Ingrese un valor para la base: ");
    scanf("%d",&b);
    printf("Ingrese un valor para el exponente: ");
    scanf("%d",&x);
    printf("La potencia de %d elevado a la %d es %d", b, x, potenciacion(b,x));
    return 0;
}

int potenciacion (int base, int exp){
    return exp==0? 1: base*potenciacion(base,exp-1);
}