#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    int *array;

    printf("Ingrese la cantidad de enteros: ");
    scanf("%d",&n); //cantidad de elementos

    array= (int *) malloc(n*sizeof(int)); //reserva de memoria en el heap

    if(array==NULL){
        printf("Error: No se pudo reservar memoria. \n");
        return 1;
    } //verificación del malloc

    for(int i=0;i<n;i++){
        printf("Ingrese el valor %d: ",i+1);
        scanf("%d",&array[i]);
    } //uso de la memoria para cargar valores

    printf("\nValores ingresados\n");
    for(int i=0;i<n;i++){
        printf("%d ", array[i]);
    } //mostrar valores

    printf("\n");

    free(array); //liberar memoria

    array=NULL; //buena práctica: evitar punteros colgantes

    return 0;
}
