#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int LargoCad(char *cad);
void MAYU(char orig[],char dest[]);

int main(){
    int l;
    char cad[80],mayu[80];
    printf("Ingrese una frase a analizar:\n");
    gets(cad); //sirve para tomar cadenas de cualquier longitud
    //scanf("%[^\n]", cad); // toma la cadena hasta el \n
    //fgets(cad,sizeof(cad),stdin);//no está sirviendo con la cadena definida como un vector porque toma sus 80 caracteres
                                    //tampoco está funcionando con puntero sin memoria dinámica, ni con dinamica :(
    l=LargoCad(cad);
    MAYU(cad,mayu);
    printf("La frase ingresada fue %s\nEl largo de la cadena fue de %d caracteres\n",cad,l);
    printf("Frase en mayusculas: %s",mayu);
    return 0;
}

int LargoCad(char *cad){
    int i=0;
    for(i;cad[i];i++){}
    return i;
}

void MAYU(char orig[],char dest[]){
    int i;
    for(i=0;orig[i];i++){
        dest[i]=toupper(orig[i]);
    }
    dest[i]='\0';
}