#include <stdio.h>

/*Contar dígitos de un número 
Escriba un programa que cuente cuántos dígitos tiene un número entero utilizando una 
función recursiva. */

int cuentaDigitos(int n);

int main(int argc, char const *argv[])
{
    int x;
    printf("Ingrese un numero para contabilizar sus digitos: ");
    scanf("%d",&x);
    printf("El numero %d tiene %d digitos", x, cuentaDigitos(x));
    return 0;
}

int cuentaDigitos(int n){
    return n==0? 0: cuentaDigitos(n/10)+1;
}
