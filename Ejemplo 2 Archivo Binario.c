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

    archivo= fopen("datos.dat","rb");
    //"rb"= read binary: no modifica el archivo

    if(archivo!=NULL){
        printf("Registros (Nombre y edad) del archivo binario \n\n");

        fread(&persona,sizeof(Registro),1,archivo);//lectura adelantada para ver si existe algún registro antes de imprimir

        while(!feof(archivo)){
            printf("Nombre: %s, Edad: %s\n", persona.nombre, persona.edad);
            fread(&persona,sizeof(Registro),1,archivo);
        }
        fclose(archivo);
    } else {
        printf("Error en la apertura del archivo");
    }

    system("pause");
    return 0;
}
