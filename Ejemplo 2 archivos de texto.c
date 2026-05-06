#include <stdio.h>
#include <conio.h>

//leer el archivo en la consola caracter a caracter

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char ch;
    char *nombre= "ArchivoTexto.txt";//nombre fisico del archivo
    if((archivo=fopen(nombre,"r"))==NULL) //no olvidarse el parentesis al comparar con el NULL
        printf("\n\n**El archivo %s no pudo abrirse**\n", nombre);
    else {
        printf("Contenido del archivo %s caracter a caracter:\n", nombre);
        while((ch=getc(archivo))!=EOF) //getc(archivo) captura caracteres del archivo
            printf("%c",ch); //printea caracter a caracter
        fclose(archivo);
    }
    return 0;
}