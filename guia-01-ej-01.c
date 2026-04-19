#include <stdio.h>

/*Factorial de un número 
Escriba un programa en C que calcule el factorial de un número entero positivo utilizando 
una función recursiva. */

int factorial(int n);

int main(int argc, char const *argv[])
{
    int x;
    printf("Ingrese un numero positivo: ");
    scanf("%d",&x);
    printf("El factorial de %d es %d\n", x, factorial(x));
    return 0;
}

int factorial (int n){
    return (n==1||n==0)? 1: n*factorial(n-1);
}