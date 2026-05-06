#include <stdio.h>
#include <conio.h>

//ingresar caracteres en un archivo hasta [Enter]
//verificar el archivo con el bloc de notas

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char ch;
    char *nombre= "ArchivoTexto.txt";//nombre fisico del archivo
    if((archivo=fopen(nombre,"w"))==NULL) //no olvidarse el parentesis al comparar con el NULL
        printf("\n\n**El archivo %s no pudo abrirse**\n", nombre);
    else {
        printf("Ingrese caracteres hasta el [Enter]:\n");
        while((ch=getchar())!='\n')
            putc(ch, archivo); //Almacena en el archivo hasta [Enter]
        fclose(archivo);
    }
    return 0;
}

