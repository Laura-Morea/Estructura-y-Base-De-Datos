#include <stdio.h>
#include <string.h>

/* Inversión de una cadena de caracteres 
Escriba un programa que invierta una cadena de texto utilizando recursividad.*/

void invertidor(char cadOrig[],int largo, char cadDest[]);
int largoCad(char *cad);

int main(int argc, char const *argv[])
{
    char cadS[80], cadD[80]="";
    int l;
    printf("Ingrese una cadena a modificar:\n");
    gets(cadS);
    l=largoCad(cadS);
    invertidor(cadS,l,cadD);
    printf("La cadena invertida es: %s", cadD);
    return 0;
}

void invertidor(char cadOrig[], int largo, char cadDest[]){
    if(cadOrig[largo-1]){
        cadDest[strlen(cadOrig)-largo]=cadOrig[largo-1];
        invertidor(cadOrig,largo-1,cadDest);
    }
}

int largoCad(char *cad){
    int i=0;
    for(i;cad[i];i++){}
    return i;
}