#include <stdio.h>

/*Suma de los primeros N números naturales 
Escriba un programa que calcule la suma de los primeros N números naturales utilizando 
recursividad.*/

int sumaRecursiva(int n);

int main(int argc, char const *argv[])
{
    int x;
    printf("Ingrese un numero natural: ");
    scanf("%d",&x);
    printf("La suma de todos los numeros hasta %d es %d\n",x,sumaRecursiva(x));
    return 0;
}

int sumaRecursiva(int n){
    return n==1? 1: n+sumaRecursiva(n-1);
}