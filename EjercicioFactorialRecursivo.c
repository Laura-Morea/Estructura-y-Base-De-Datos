#include <stdio.h>

int Factorial(int n);

int main(int argc, char const *argv[])
{
    int n;
    printf("Dar un numero positivo:");
    scanf("%d",&n);
    printf("Su factorial es %d", Factorial(n));
    return 0;
}

int Factorial(int n){
    return (n==1||n==0)?1:n*Factorial(n-1);
}