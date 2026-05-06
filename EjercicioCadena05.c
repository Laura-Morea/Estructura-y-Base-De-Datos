#include <stdio.h>

int suma(int a, int b);

int main(int argc, char const *argv[])
{
    int i,j;
    printf("Ingrese un primer valor natural: ");
    scanf("%d",&i);
    printf("Ingrese un segundo valor natural: ");
    scanf("%d",&j);
    printf("El resultado de la suma entre %d y %d es %d",i,j,suma(i,j));
    return 0;
}

int suma(int a, int b){
    return b==0? a:(suma(a,b-1))+1;
}