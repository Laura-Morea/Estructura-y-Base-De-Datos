#include <stdio.h>
#include <stdlib.h>
#define CARACTERES_RENGLON 81

//2) Contar la cantidad de palabras por renglón que tiene un archivo de texto.

void imprimeCantPalabrasPorReglon(FILE *archivo);
int contarPalabras(char *renglon);

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char *nombreArch="ElPatitoFeo.txt";
    if((archivo=fopen(nombreArch,"r"))==NULL)
        printf("El archivo no pudo abrirse.\n");
    else{
        imprimeCantPalabrasPorReglon(archivo);
        fclose(archivo);
    }
    free(nombreArch);
    return 0;
}

void imprimeCantPalabrasPorReglon(FILE *archivo){
    char renglon[CARACTERES_RENGLON];
    int i=1;
    while(fgets(renglon, CARACTERES_RENGLON,archivo)){
        printf("Hay %d palabras en el renglon #%d\n", contarPalabras(renglon), i);
        i++;
    }
}

int contarPalabras(char *renglon){
    int cant=0,pos=0, enPalabra=0;
    printf("\n%s", renglon);
    while(renglon[pos]!='\n'&&pos<CARACTERES_RENGLON){
        if((renglon[pos]>='a'&&renglon[pos]<='z')||(renglon[pos]>='A'&&renglon[pos]<='Z')||renglon[pos]=='é'||(renglon[pos]>='á'&&renglon[pos]<='ú')){
            if(enPalabra==0)
                cant++;
            enPalabra=1;
        } else 
            enPalabra=0;
        pos++;
    }
    return cant;
}