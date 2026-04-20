#include <stdio.h>

/*MCD (Máximo Común Divisor) 
Escribir un programa que calcule el MCD de dos números utilizando el algoritmo de 
Euclides de forma recursiva.*/

int mcd(int a, int b);
int devolverMayor(int a, int b);

int main(int argc, char const *argv[])
{
    int a,b,c;
    printf("Ingrese un primer valor: ");
    scanf("%d",&a);
    printf("Ingrese un segundo valor: ");
    scanf("%d",&b);
    c=a;
    a=devolverMayor(a,b);
    b=(c==devolverMayor(a,b))? b:c;
    printf("El mcd entre %d y %d es %d", a, b, mcd(a,b));
    return 0;
}

int mcd(int a, int b){
    return b==0? a: mcd(b,a%b);
}

int devolverMayor(int a,int b){
    return a>b? a: b;
}