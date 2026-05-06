#include <stdio.h>
#include <math.h>

/*Suma de dígitos de un número 
Escriba un programa que calcule la suma de los dígitos de un número entero utilizando 
recursividad.*/

int sumaDigitos(int n);

int main(int argc, char const *argv[])
{
    int x;
    printf("Ingrese un numero para sumar sus digitos: ");
    scanf("%d",&x);
    printf("La suma de sus digitos es %d\n",sumaDigitos(x));
    return 0;
}

int sumaDigitos(int n){
    return n==0? 0: n%10+sumaDigitos(n/10);
}