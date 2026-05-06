#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int LargoCad(char *cad);
void contar_vocales_consonantes(char orig[],int largo, int *v, int *c);
bool esConsonante(char x);
bool esVocal(char x);

int main(){
    int l,v=0,c=0;
    char cad[80];
    printf("Ingrese una frase a analizar:\n");
    gets(cad); 
    l=LargoCad(cad);
    printf("La frase ingresada fue %s\nEl largo de la cadena fue de %d caracteres\n",cad,l);
    contar_vocales_consonantes(cad,l,&v,&c);
    printf("La frase tiene %d vocales y %d consonantes",v,c);
    return 0;
}

int LargoCad(char *cad){
    int i=0;
    for(i;cad[i];i++){}
    return i;
}

void contar_vocales_consonantes(char orig[],int largo,int *v, int *c){
    if(largo>0){
        if(esVocal(orig[largo-1])){
            (*v)++;
        } else if(esConsonante(orig[largo-1])){
            (*c)++;
        }
        contar_vocales_consonantes(orig,largo-1,v,c);
    }
}//Si hay un arroba o un espacio lo toma como una consonante

bool esVocal(char x){
    x=tolower(x);
    return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u');
}

bool esConsonante(char x){
    x=tolower(x);
    return ((x>'a'&&x<'e')||(x>'e'&&x<'i')||(x>'i'&&x<'o')||(x>'o'&&x<'u')||(x>'u'&&x<='z')); 
}
