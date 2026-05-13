#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define CANT_BITS 8
#define BINARIO 2
#define CHAR_SALTO 2

//4) Leer cifras binarias de 8 bits desde un archivo de texto y calcular su valor en decimal a través del teorema fundamental.

void imprimirValorEnDecimal(FILE *archivo);

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char *nombreArch="textoEnBinario.txt";
    if((archivo=fopen(nombreArch,"r"))==NULL)
        printf("No se pudo abrir el archivo\n");
    else {
        imprimirValorEnDecimal(archivo);
        fclose(archivo);
    }
    free(nombreArch);
    return 0;
}

void imprimirValorEnDecimal(FILE *archivo){
    char numBin[CANT_BITS+CHAR_SALTO];
    int n;
    while(fgets(numBin,CANT_BITS+CHAR_SALTO,archivo)){
        n=0;
        printf("%s", numBin);
        for(int i=1;i<=CANT_BITS;i++){
            if(numBin[i-1]=='1')
               n+=pow(BINARIO, CANT_BITS-i);
        }
        printf("%d\n",n);
    }
}