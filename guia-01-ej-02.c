#include <stdio.h>

/*Serie de Fibonacci 
Escriba un programa que imprima los primeros N términos de la serie de Fibonacci 
utilizando recursividad.*/
void Fibonacci(int N, int *a, int *b, int *c);

int main(int argc, char const *argv[])
{
    int x, *a=0,*b=1, *c;
    printf("Ingrese la cantidad de terminos que quiera que se muestren: ");
    scanf("%d",&x);
    Fibonacci(x,&a,&b,&c);
    return 0;
}

void Fibonacci(int N, int *a, int *b, int *c){
    if(N>0){
        printf("%d ",*b);
        *c=*b;
        *b=((*a)+(*b));
        *a=*c;
        Fibonacci(N-1,&a,&b,&c);
    }
    }