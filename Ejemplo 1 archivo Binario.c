#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[25];
    int edad;
} Registro;

int main(int argc, char const *argv[])
{
    Registro persona;
    FILE *archivo;
    char tecla;

    archivo = fopen("datos.dat","wb");
    // "ab"= append binary: agrega al final sin borrar datos previos

    if(archivo!=NULL){
        do{
            fflush(stdin); //vacia el buffer de teclado
            printf("\nIntroduzca el nombre: ");
            scanf("%s", &(persona.nombre));

            if(strlen(persona.nombre)>0){
                printf("Introduzca la edad: ");
                scanf("%d",&(persona.edad));

                //Dir. variable| tamaño struct | 1 registro | archivo
                fwrite(&persona, sizeof(persona),1,archivo);

                printf("\nDesea continuar (s/n): ");
                fflush(stdin);
                tecla=getchar();
            }
        } while(tecla =='s');
    } else {
        printf("Error en la apertura del archivo");
    }
            fclose(archivo); //movi el fclose
    system("pause");
    return 0;
}
