#include <stdio.h>
#include <conio.h>

//leer el archivo en la consola linea a linea

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char cadena[81];
    char *nombre= "ArchivoTexto.txt";//nombre fisico del archivo
    if((archivo=fopen(nombre,"r"))==NULL) //no olvidarse el parentesis al comparar con el NULL
        printf("\n\n**El archivo %s no pudo abrirse**\n", nombre);
    else {
        printf("Contenido del archivo %s linea a linea:\n", nombre);
        while(fgets(cadena,81,archivo)) //lee hasta \n (salto de linea) o hasta n-1 (80 caracteres)
            printf("%s",cadena); //printea la linea
        printf("\n\n**FIN**\n");
        fclose(archivo);
    }
    return 0;
}