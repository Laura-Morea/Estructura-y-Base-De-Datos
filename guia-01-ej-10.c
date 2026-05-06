#include <stdio.h>

/*Imprimir números del 1 al N 
Escriba un programa que imprima los números del 1 hasta N utilizando recursividad. */

void impresoraHastaN(int n);

int main(int argc, char const *argv[])
{
    int x;
    printf("Ingrese un numero maximo para imprimir: ");
    scanf("%d",&x);
    impresoraHastaN(x);
    return 0;
}

void impresoraHastaN(int n){
    if(n>0){
        impresoraHastaN(n-1);
        printf("%d ",n);
    }
}