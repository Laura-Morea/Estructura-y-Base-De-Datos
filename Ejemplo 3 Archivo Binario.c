#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char nombre[25];
    int edad;
} Registro;

int main(int argc, char const *argv[])
{
    int cantReg;
    Registro persona;
    FILE *archivo;

    archivo = fopen("datos.dat","rb"); //abrimos para lectura
    if(archivo!=NULL){
        fseek(archivo,0,SEEK_END); //vamos al final del archivo
        cantReg = ftell(archivo)/sizeof(Registro);
        //ftell devuelve la posición actual del puntero como su tamaño en bytes

        printf("\nCantidad de registros en el archivo = %d\n", cantReg);
        fclose(archivo);
    } else {
        printf("Error en la apertura del archivo\n");
    }

    system("pause");
    return 0;
}
