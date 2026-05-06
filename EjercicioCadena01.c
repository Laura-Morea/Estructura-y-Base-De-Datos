#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int LargoCad(char *cad);

int main(){
    int l;
    char cad[80];
    printf("Ingrese una frase a analizar:\n");
    gets(cad); //sirve para tomar cadenas de cualquier longitud
    //scanf("%[^\n]", cad); // toma la cadena hasta el \n
    //fgets(cad,sizeof(cad),stdin);//no está sirviendo con la cadena definida como un vector porque toma sus 80 caracteres
                                    //tampoco está funcionando con puntero sin memoria dinámica.
    l=LargoCad(cad);
    printf("La frase ingresada fue %s\nEl largo de la cadena fue de %d caracteres",cad,l);
    return 0;
}

int LargoCad(char *cad){
    int i=0;
    for(i;cad[i];i++){}
    return i;
}