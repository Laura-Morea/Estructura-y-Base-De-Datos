#include <stdio.h>
#include <math.h>

//profe busca un número y forma su invertido por recursividad. Y luego en la función esCapicua sólo los compara

/*Verificar si un número es palíndromo 
Escriba un programa que determine si un número entero es palíndromo utilizando 
recursividad.*/

void esCapicua(int n,int dig, int *vVerdad);
int cuentaDigitos(int n);

int main(int argc, char const *argv[])
{
    int x, *v;
    (*v)=0;
    printf("Ingrese un numero a analizar: ");
    scanf("%d",&x);
    esCapicua(x,cuentaDigitos(x),v);
    (*v)==1? printf("%d es capicua",x): printf("%d no es capicua",x);
    return 0;
}

void esCapicua(int n,int dig, int *vVerdad){
    if(dig>(cuentaDigitos(n)+1)/2){
        if((n/pow(10,dig-1))==(n-(n%(int)pow(10,cuentaDigitos(n)-(dig-1)))*pow(10,cuentaDigitos(n)-(dig-1)))){//chequear esta condicion
            esCapicua(n,dig-1,vVerdad);
            *vVerdad=1;
        }
    }
}

int cuentaDigitos(int n){
    return n==0? 0: cuentaDigitos(n/10)+1;
}