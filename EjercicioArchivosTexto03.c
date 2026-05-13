#include <stdio.h>
#include <stdlib.h>
#define CARACTERES_POR_RENGLON 81

//3) Contar la cantidad de vocales por renglón que tiene un archivo de texto.

void imprimeCantVocalesPorRenglon(FILE *archivo);
int cantVocalesPorRenglon(char *renglon);

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char *nombreArch="ElPatitoFeo.txt";
    if((archivo=fopen(nombreArch,"r"))==NULL)
        printf("El archivo no pudo abrirse\n");
    else {
        imprimeCantVocalesPorRenglon(archivo);
        fclose(archivo);
    }
    free(nombreArch);
    return 0;
}

void imprimeCantVocalesPorRenglon(FILE *archivo){
    char renglon[CARACTERES_POR_RENGLON];
    int i=1;
    while(fgets(renglon,CARACTERES_POR_RENGLON,archivo)){
        printf("Hay %d vocales en el renglon #%d\n",cantVocalesPorRenglon(renglon),i);
        i++;
    }
}

int cantVocalesPorRenglon(char *renglon){
    int cant=0, pos=0;
    char min;
    printf("%s\n",renglon);
    while(renglon[pos]!='\n'&&pos<CARACTERES_POR_RENGLON){
        min=tolower(renglon[pos]);
        if(min=='a'||min=='e'||min=='i'||min=='o'||min=='u')//no pude contar las tildes
            cant++;
        pos++;
    }
    return cant;
}