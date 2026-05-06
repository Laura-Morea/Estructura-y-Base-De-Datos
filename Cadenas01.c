#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int i;
    //char cad[80]="En un lugar de la mancha";
    char *cad="En un lugar de la mancha";
    printf("%30s\n",cad);
    printf("Largo de la cadena: %d\n",strlen(cad));
    for(i=0;i<strlen(cad);i++){
        printf("%c",cad[i]);
    }
    return 0;
}