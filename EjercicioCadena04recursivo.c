#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int LargoCad(char *cad);
void Inverso(char orig[],int largo);

int main(){
    int l;
    char cad[80],mayu[80];
    printf("Ingrese una frase a analizar:\n");
    gets(cad); 
    l=LargoCad(cad);
    printf("La frase ingresada fue %s\nEl largo de la cadena fue de %d caracteres\n",cad,l);
    Inverso(cad,l);
    return 0;
}

int LargoCad(char *cad){
    int i=0;
    for(i;cad[i];i++){}
    return i;
}
/*
void Inverso(char orig[], int index){
    if(orig[index-1]){
        Inverso(orig,index+1);
        printf("%c",orig[index-1]);
    }
}
*/
void Inverso(char orig[], int largo){
    if(largo>0){
        printf("%c",orig[largo-1]);
        Inverso(orig,largo-1);
    }
}