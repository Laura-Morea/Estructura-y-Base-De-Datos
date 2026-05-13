#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
// Dimensiones de la tabla de traducci�n Morse
#define FILAS_MORSE 37 // Incluye letras (26) + n�meros (10) + terminador NULL o sea 37
#define COLUMNAS_MORSE 2
#define LARGO_CADENA 81

typedef struct
{
    const char *morse;
    char letra;
} Traduccion;


void mostrar(FILE *); // esta funcion muestra el archivo tal cual esta
char ConvierteMorse(char [], Traduccion[FILAS_MORSE]);
// esta funcion seria la unica que tenes qeu desarrollar
int error(char *);
void pausa(void);
// Tabla de traducci�n Morse a ASCII ( esta tabla que es una simple matriz estructurada, tienen todo para que
// puedas averiguar que cosa hay en el archivo y la compares con el si llega al NULL algo paso,
// espero te des cuenta de que la tabla esta ordenada de la siguiente manera: (Morse, ASCII)

int main()
{
    FILE *archivo;
    // Abrir archivo, lee desde donde yo lo tengo, pero vos ponele la ruta donde vos lo tenes
    // no te olvides de separar con doble barra \\ invertida como el mio sino, no te lee nada
    char nom1[LARGO_CADENA] = "morse.txt", cad[LARGO_CADENA];
    char mensaje[LARGO_CADENA];
    char letra;
    char Letratemp[2]; // me sirve para guardar un caracter en forma temporal
    // y verlo como un string
    Traduccion morseTabla[FILAS_MORSE] = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'}, {"..-.", 'F'},
        {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
        {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},
        {"...", 'S'}, {"-", 'T'}, {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
        {"-.--", 'Y'}, {"--..", 'Z'}, {"-----", '0'},
        {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'}, {".....", '5'},
        {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'},
        {NULL, '\0'} // Fin de la tabla
    };
    system("cls");
    if ((archivo = fopen(nom1, "r")) == NULL)
        exit(error(nom1));
    printf("\n El archivo %s se ha abierto satisfactoriamente", nom1);
    printf("\n Presione una tecla para visualizar el contenido del archivo:%s\n\n", nom1);
    pausa();
    system("cls");

    rewind(archivo);
    printf("\n El contenido del archivo %s es:\n\n", nom1);
    mostrar(archivo);
    pausa();

    mensaje[0] = '\0';
    rewind(archivo);
    printf("\nDecodificamos el mensaje:\n\n");
    while (fgets(cad, LARGO_CADENA, archivo) != NULL)
    {
        // Eliminar el salto de l�nea ya que del archivo trae el barra n
        // y lo cambiamos por el barra cero sino falla!!
        cad[strcspn(cad, "\n")] = '\0';
        letra = ConvierteMorse(cad, morseTabla);
        Letratemp[0]=letra;
        strncat(mensaje, &Letratemp, 1);
        if (strlen(cad) == 0)
        {
            Letratemp[0] = ' ';
            Letratemp[1] = '\0';
            strncat(mensaje, &Letratemp, 1);
            printf(" ");
        }
        else
        {
            printf("%c", letra);
        }
    }
}

void mostrar(FILE *arch){
    char cad[LARGO_CADENA];
    while(fgets(cad, LARGO_CADENA, arch)){
        printf("%s", cad);
    }
}

char ConvierteMorse(char cad[], Traduccion tabla[FILAS_MORSE]){
    char retorno ='?';
    int i=0;
    while(i<FILAS_MORSE&&retorno=='?'){
        if(tabla[i].morse!=NULL&&strcmp(cad,tabla[i].morse)==0){ //tenía problemas con el strcmp y el null, 
            retorno=tabla[i].letra;                             //por eso lo hice así. Alguna forma más eficiente?
        } else if(tabla[i].morse==NULL){
            retorno=tabla[i].letra;
        }
        i++;
    }
    return retorno;
}

int error(char *x){
    printf("Se ha producido un error con %s\n", x);
    return -1;
}
void pausa(void){
    printf("Presione una tecla para continuar...\n");
    fflush(stdin);
    getch();
}