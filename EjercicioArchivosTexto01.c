#include <stdio.h>
#include <stdlib.h>
#define CARACTERES_LINEA 81

//1) Capturar un texto de varios renglones desde un archivo de orígen y guardarlo en su totalidad en un archivo de destino.

void copiarArchivo(FILE *source, FILE *target);

int main(int argc, char const *argv[])
{
    FILE *archFuente, *archDestino;
    char *nombreArchFuente="ElPatitoFeo.txt";
    char *nombreArchDestino="LaCopia.txt";

    archFuente=fopen(nombreArchFuente,"r");
    archDestino=fopen(nombreArchDestino,"w+");
    if(archFuente!=NULL&&archDestino!=NULL){
        copiarArchivo(archFuente,archDestino);
        fclose(archFuente);
        fclose(archDestino);
    } else {
        printf("Hubo un error al intentar abrir los archivos\n");
    }
    free(nombreArchDestino);
    free(nombreArchDestino);    
    return 0;
}

void copiarArchivo(FILE *source, FILE *target){
    char linea[CARACTERES_LINEA];
    while(fgets(linea,CARACTERES_LINEA,source))
        fputs(linea,target);
    printf("Copia realizada exitosamente\n");
}
