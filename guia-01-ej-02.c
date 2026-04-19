#include <stdio.h>

/*Serie de Fibonacci 
Escriba un programa que imprima los primeros N términos de la serie de Fibonacci 
utilizando recursividad.*/
void fibonacci(int n, int *a, int *b, int *c);

int main(int argc, char const *argv[])
{
    int x, a,b,c;
    a=0;
    b=1;
    printf("Ingrese la cantidad de terminos que quiera que se muestren: ");
    scanf("%d",&x);
    fibonacci(x,&a,&b,&c);
    return 0;
}

void fibonacci(int n, int *a, int *b, int *c){
    if(n>0){
        printf("%d ",*b);
        *c=*b;
        *b=((*a)+(*b));
        *a=*c;
        fibonacci(n-1,a,b,c);
    }
    }