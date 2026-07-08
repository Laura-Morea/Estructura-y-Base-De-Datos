#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef char cadena[160]; // Para tratar a los arrays de chars como 'cadena'

///////////////////////////////////////////////////////////////////////////
////////////////////////////  PROTOTIPOS  /////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void saltoDeLinea(){
    printf("\n");
}

void pasarElTrapo(){
    printf("\033[2J\033[H");
}

void limpiarBufferDeEntrada(){
    while(getchar()!='\n');         //'!= EOF' (¿necesario?)
}

void utf8(){
#ifdef _WIN32
    system("chcp 65001");
    pasarElTrapo();
#endif
}

bool esPar(int value){
return value % 2 == 0;
}

bool esMultiplo(int divisor, int supuestMult){
return supuestMult % divisor == 0;
}

int cantDivisores(int value){
    int cont= 0;
    for(int i = 1; i <= value; i++){
        if(esMultiplo(i, value)) cont++;
    }
return cont;
}

bool esPrimo(int value){
return cantDivisores(value) == 2;
}

int factorial(int nNatural){
    int factorial= 1;
    for(int i= 2; i <= nNatural; i++){
        factorial = factorial * i;
    }
return factorial;
}

bool esPalindromo(char* palabra){
    int in = 0, fin = strlen(palabra)-1;
    bool esPali = true;
    while(in < fin){
        if(palabra[in] != palabra[fin]) esPali = false;
        in++;
        fin--;
    }
return esPali;
}

//srand(time(NULL));
int randomIntegerEntre(int since, int until){
return (rand() % (until - since + 1) + since);
}

void linea(int length){
    for(int i= 0; i < length; i++){
        printf("=");
    }
    saltoDeLinea();
}

void suspenso(float segs){
    int puntos= 3;
	printf("Cargando");
	for(int i = 0; i < puntos; i++){
		sleep(segs);
		printf(".");
	}
	sleep(segs);
    pasarElTrapo();
}

int leerEntero(cadena text);
float leerFloat(cadena text);
char leerCaracter(cadena text);
void leerCadena(cadena text, cadena string);

int leerEnteroEntre(int minValue, int maxValue, cadena text);
float leerFloatEntre(float minValue, float maxValue, cadena text);
void leerCadenaDe(cadena text, cadena string, int length);
void leerCadenaEntre(int minLength, int maxLength, cadena text, cadena string);

void stringToUpper(char string[]);
void stringToLower(char string[]);
void formatoNombre(cadena string);
int areTheSame(char *string1, char *string2);
bool seguir();
void waitInput(int ingresoEsperado_Ascii, cadena text);
// waitInput(13, "\n[Enter] para continuar...");

void swapOfIntegers(int *a, int *b);
void swapOfFloats(float *a, float *b);
void swapOfChars(char *a, char *b);

/* void swapOfStructs([struct]* a, [struct]* b){
    [struct] aux = *a;
    *a = *b;
    *b = aux;
} */

//////////////////////////////// para Vectores ////////////////////////////////

void leerVectorDeEnteros(cadena text, int vec[], int size);
void leerVectorDeFloats(cadena text, float vec[], int size);
void leerVectorDeCaracteres(cadena text, char vec[], int size);

void leerVectorDeEnterosEntre(int minValue, int maxValue, cadena text, int vec[], int size);
void leerVectorDeFloatsEntre(float minValue, float maxValue, cadena text, float vec[], int size);

void mostrarVectorDeEnteros(int vec[], int size);
void mostrarVectorDeFloats(float vec[], int size);
void mostrarVectorDeCaracteres(char vec[], int size);

int sumatoriaVectorDeEnteros(int vec[], int size);
float sumatoriaVectorDeFloats(float vec[], int size);
//¿Promedio?

bool estaElInt(int vec[], int size, int intBuscado);
bool estaElFloat(float vec[], int size, float floatBuscado);
bool estaElChar(char vec[], int size, char charBuscado);

void ordenarVectorDeEnterosAscendente(int vec[], int size);
void ordenarVectorDeEnterosDescendente(int vec[], int size);
void ordenarVectorDeFloatsAscendente(float vec[], int size);
void ordenarVectorDeFloatsDescendente(float vec[], int size);

//////////////////////////////// para Matrices ////////////////////////////////

void leerMatrizDeEnteros(cadena text, int f, int c, int mat[f][c]);
void leerMatrizDeFloats(cadena text, int f, int c, float mat[f][c]);
void leerMatrizDeCaracteres(cadena text, int f, int c, char mat[f][c]);

void leerMatrizDeEnterosEntre(cadena text, int minValue, int maxValue, int f, int c, int mat[f][c]);
void leerMatrizDeFloatsEntre(cadena text, float minValue, float maxValue, int f, int c, float mat[f][c]);

void mostrarMatrizDeEnteros(int f, int c, int mat[f][c]);
void mostrarMatrizDeFloats(int f, int c, float mat[f][c]);
void mostrarMatrizDeCaracteres(int f, int c, char mat[f][c]);

///////////////////////////////////////////////////////////////////////////
/////////////////////////  IMPLEMENTACIONES  //////////////////////////////
///////////////////////////////////////////////////////////////////////////

int leerEntero(cadena text){
    int value;
    printf("%s", text);
    scanf("%d", &value);
    limpiarBufferDeEntrada();
return value;
}

float leerFloat(cadena text){
    float value;
    printf("%s", text);
    scanf("%f", &value);
    limpiarBufferDeEntrada();
return value;
}

char leerCaracter(cadena text){
    char caracter;
    printf("%s", text);
    scanf("%c", &caracter);
    limpiarBufferDeEntrada();
return caracter= toupper(caracter);
}

void leerCadena(cadena text, cadena string){
    printf("%s", text);
    gets(string);

    while(string == NULL){
        printf("Error: no hubo ingreso.\n");
        leerCadena(text, string);
    }
}

int leerEnteroEntre(int minValue, int maxValue, cadena text){
    int value = leerEntero(text);
    while(value < minValue || value > maxValue){
        pasarElTrapo();
        printf("Ingreso invalido...\n"
               "Se esperaba valor entre [%d] y [%d]\n\n", minValue, maxValue);
        value = leerEntero(text);
    }
return value;
}

float leerFloatEntre(float minValue, float maxValue, cadena text){
    float value = leerFloat(text);
    while(value < minValue || value > maxValue){
        pasarElTrapo();
        printf("Ingreso invalido...\n"
               "Se esperaba valor entre [%.2f] y [%.2f]\n\n", minValue, maxValue);
        value = leerFloat(text);
    }
return value;
}

void leerCadenaDe(cadena text, cadena string, int length){
    leerCadena(text, string);
    int largo = strlen(string);
    while(largo < length){
        pasarElTrapo();
        printf("Ingreso invalido...\n"
               "Se esperaba una cadena de [%d] caracteres.\n\n", length);
        leerCadena(text, string);
        largo = strlen(string);
    }
}

void leerCadenaEntre(int minLength, int maxLength, cadena text, cadena string){
    leerCadena(text, string);
    int length = strlen(string);
    while(length < minLength || length > maxLength){
        pasarElTrapo();
        printf("Ingreso invalido...\n"
               "Se esperaba una cadena de entre [%d] y [%d] caracteres.\n\n", minLength, maxLength);
        leerCadena(text, string);
        length = strlen(string);
    }
}

void stringToUpper(char string[]){
    int tam = strlen(string), i= 0;
    while(i < tam && string[i] != '\0'){
        string[i] = toupper(string[i]);
        i++;
    }
}

void stringToLower(char string[]){
    int tam = strlen(string), i= 0;
    while(i < tam && string[i] != '\0'){
        string[i] = tolower(string[i]);
        i++;
    }
}

void formatoNombre(cadena string){
    stringToLower(string);
    string[0] = toupper(string[0]);
}

int areTheSame(char *string1, char *string2){
return (strcmp(string1, string2) == 0);
}

bool seguir(){
    char eleccion = leerCaracter("Desea continuar? [S/N]... ");

    while(eleccion != 'S' && eleccion != 'N'){
        pasarElTrapo();
        printf("|Ingreso invalido!!\n");
        eleccion = leerCaracter("Desea continuar? [S/N]... ");
    }
    saltoDeLinea();
return eleccion == 'S';
}

void waitInput(int ingresoEsperado_Ascii, cadena text){
    printf("%s", text);
    while(getch() != ingresoEsperado_Ascii){
        pasarElTrapo();
        printf("|Error en el ingreso!!\n%s", text);
    }
saltoDeLinea();
}

void swapOfIntegers(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void swapOfFloats(float *a, float *b){
    float aux = *a;
    *a = *b;
    *b = aux;
}

void swapOfChars(char *a, char *b){
    char aux = *a;
    *a = *b;
    *b = aux;
}

//////////////////////////////// para Vectores ////////////////////////////////

void leerVectorDeEnteros(cadena text, int vec[], int size){
    printf("%s\n", text);
    for(int i= 0; i < size; i++){
        printf(" %d. ", i+1);
        vec[i] = leerEntero("");
    }
}

void leerVectorDeFloats(cadena text, float vec[], int size){
    printf("%s\n", text);
    for(int i= 0; i < size; i++){
        printf(" %d. ", i+1);
        vec[i] = leerFloat("");
    }
}

void leerVectorDeCaracteres(cadena text, char vec[], int size){
    printf("%s\n", text);
    for(int i= 0; i < size; i++){
        printf(" %d. ", i+1);
        vec[i] = leerCaracter("");
    }
}

void leerVectorDeEnterosEntre(int minValue, int maxValue, cadena text, int vec[], int size){
    printf("%s\n", text);
    for(int i= 0; i < size; i++){
        printf("%d. ", i+1);
        vec[i] = leerEnteroEntre(minValue, maxValue, "");
    }
}

void leerVectorDeFloatsEntre(float minValue, float maxValue, cadena text, float vec[], int size){
    printf("%s\n", text);
    for(int i= 0; i < size; i++){
        printf("%d. ", i+1);
        vec[i] = leerFloatEntre(minValue, maxValue, "");
    }
}

void mostrarVectorDeEnteros(int vec[], int size){
    for(int i= 0; i < size; i++){
        printf("%d| %d\n", i+1, vec[i]);
    }
}

void mostrarVectorDeFloats(float vec[], int size){
    for(int i= 0; i < size; i++){
        printf("%d| %.2f\n", i+1, vec[i]);
    }
}

void mostrarVectorDeCaracteres(char vec[], int size){
    for(int i= 0; i < size; i++){
        printf("%d| %c\n", i+1, vec[i]);
    }
}

int sumatoriaVectorDeEnteros(int vec[], int size){
    int sumatoria = 0;
    for(int i= 0; i < size; i++){
        sumatoria += vec[i];
    }
return sumatoria;
}

float sumatoriaVectorDeFloats(float vec[], int size){
    float sumatoria = 0;
    for(int i= 0; i < size; i++){
        sumatoria += vec[i];
    }
return sumatoria;
}

bool estaElInt(int vec[], int size, int intBuscado){
    int i = 0;
    while(vec[i] != intBuscado && i < size) i++;
return i != size;
}

bool estaElFloat(float vec[], int size, float floatBuscado){
    int i = 0;
    while(vec[i] != floatBuscado && i < size) i++;
return i != size;
}

bool estaElChar(char vec[], int size, char charBuscado){
    int i = 0;
    while(vec[i] != charBuscado && i < size) i++;
return i != size;
}

void ordenarVectorDeEnterosAscendente(int vec[], int size){
    int j, aux;
    for(int i = 1; i < size; i++){
        j = i;
        aux = vec[i];
        while(j > 0 && aux < vec[j - 1]){
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = aux;
    }
}

void ordenarVectorDeEnterosDescendente(int vec[], int size){
    int j, aux;
    for(int i = 1; i < size; i++){
        j = i;
        aux = vec[i];
        while(j > 0 && aux > vec[j - 1]){
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = aux;
    }
}

void ordenarVectorDeFloatsAscendente(float vec[], int size){
    int j, aux;
    for(int i = 1; i < size; i++){
        j = i;
        aux = vec[i];
        while(j > 0 && aux < vec[j - 1]){
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = aux;
    }
}

void ordenarVectorDeFloatsDescendente(float vec[], int size){
    int j, aux;
    for(int i = 1; i < size; i++){
        j = i;
        aux = vec[i];
        while(j > 0 && aux > vec[j - 1]){
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = aux;
    }
}

//////////////////////////////// para Matrices ////////////////////////////////

void leerMatrizDeEnteros(cadena text, int f, int c, int mat[f][c]){
    printf("%s\n", text);
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("[%d][%d]. ", i+1, j+1);
            mat[i][j] = leerEntero("");   
        }
        saltoDeLinea();
    }
}

void leerMatrizDeFloats(cadena text, int f, int c, float mat[f][c]){
    printf("%s\n", text);
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("[%d][%d]. ", i+1, j+1);
            mat[i][j] = leerFloat("");
        }
        saltoDeLinea();
    }
}

void leerMatrizDeCaracteres(cadena text, int f, int c, char mat[f][c]){
    printf("%s\n", text);
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("[%d][%d]. ", i+1, j+1);
            mat[i][j] = leerCaracter("");
        }
        saltoDeLinea();
    }
}

void leerMatrizDeEnterosEntre(cadena text, int minValue, int maxValue, int f, int c, int mat[f][c]){
    printf("%s\n", text);
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("[%d][%d]. ", i+1, j+1);
            mat[i][j] = leerEnteroEntre(minValue, maxValue, "");
        }
        saltoDeLinea();
    }
}

void leerMatrizDeFloatsEntre(cadena text, float minValue, float maxValue, int f, int c, float mat[f][c]){
    printf("%s\n", text);
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("[%d][%d]. ", i+1, j+1);
            mat[i][j] = leerFloatEntre(minValue, maxValue, "");
        }
        saltoDeLinea();
    }
}

void mostrarMatrizDeEnteros(int f, int c, int mat[f][c]){
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("%d ", mat[i][j]);
        }
        saltoDeLinea();
    }
}

void mostrarMatrizDeFloats(int f, int c, float mat[f][c]){
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("%.2f ", mat[i][j]);
        }
        saltoDeLinea();
    }
}

void mostrarMatrizDeCaracteres(int f, int c, char mat[f][c]){
    for(int i= 0; i < f; i++){
        for(int j= 0; j < c; j++){
            printf("%c ", mat[i][j]);
        }
        saltoDeLinea();
    }
}