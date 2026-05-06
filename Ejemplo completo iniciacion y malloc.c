#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *cadena=NULL; //inicializa puntero a char a NULL
    char caracter;
    int longitud=0; //longitud actual de la cadena
    int capacidad=10; //capacidad inicial del bloque

    cadena=(char *)malloc(capacidad * sizeof(char));

    if(cadena==NULL){
        printf("Error: No se pudo asignar memoria dinamica\n");
        return 1;
    }

    printf("Ingresa caracteres (presiona enter para finalizar):\n");//lee caracteres hasta que se presiona un enter
    while((caracter=getchar())!='\n'){
        longitud++;
        if(longitud >= capacidad){
            //si la longitud supera la capacidad actual, se duplica la memoria reservada
            capacidad*=2;
            cadena=(char *)realloc(cadena,capacidad * sizeof(char));

            if(cadena==NULL){
                printf("Error: No se pudo asignar memoria.\n");
                return 1;
            }
        }
        //agrega el nuevo caracter a la cadena
        cadena[longitud-1]=caracter;
    }

    //agrega el caracter nulo para formar una cadena válida en c
    cadena[longitud]='\n';
    printf("La cadena ingresada es: %s\n", cadena);
    //liberar la memoria dinámica cuando ya no se necesite
    free(cadena);

    return 0;
}
