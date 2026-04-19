#include <stdio.h>

/*Serie de Fibonacci 
Escriba un programa que imprima los primeros N términos de la serie de Fibonacci 
utilizando recursividad.*/
void Fibonacci(int N);

int main(int argc, char const *argv[])
{
    int x;
    printf("Ingrese la cantidad de terminos que quiera que se muestren: ");
    scanf("%d",&x);
    Fibonacci(x);
    return 0;
}

void Fibonacci(int N){
    int a=0,b=1,aux;
    for(int i=0;i<N;i++){
            printf("%d ", a+b);
            aux=b;
            b=a+b;
            a=aux;
        }
    }