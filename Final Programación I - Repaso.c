#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h> 
#include <string.h> 
 
// Definición de la estructura Asiento 
typedef struct { 
    int fila; 
    char columna; 
    int ocupado; // 0 = libre, 1 = ocupado 
    char pasajero[50]; 
} Asiento; 
 
// Definición de la matriz de asientos 
#define FILAS 25 
#define COLUMNAS 4 
Asiento avion[FILAS][COLUMNAS]; 
 
// Prototipos de funciones 
void inicializarAsientos(Asiento avion[][COLUMNAS]); 
void pausa(void); 
int menu(void); 
void reservarAsiento(Asiento avion[][COLUMNAS]); 
void cancelarReserva(Asiento avion[][COLUMNAS]); 
void mostrarEstado(Asiento avion[][COLUMNAS]); 
void consultarReservas(Asiento avion[][COLUMNAS]);
int validarEnteroEntre(char mensaje[150], int min, int max); 
//ARMAR UNA FUNCION DE PEDIDO Y VALIDACION DE FILA Y COLUMNA 
int main() { 
    int op; 
    inicializarAsientos(avion); 
    do { 
        op = menu(); 
        system("cls"); 
        switch (op) { 
            case 1: 
                reservarAsiento(avion);
                pausa(); 
                break; 
            case 2: 
                cancelarReserva(avion);
                pausa(); 
                break; 
            case 3: 
                mostrarEstado(avion); 
                pausa();
                break; 
            case 4: 
                consultarReservas(avion); 
                pausa();
                break; 
        } 
    } while (op != 5); 
    system("cls");
    printf("Gracias por su visita!");
    return 0; 
} 
 
void inicializarAsientos(Asiento avion[][COLUMNAS]) { 
    for (int i = 0; i < FILAS; i++) { 
        for (int j = 0; j < COLUMNAS; j++) { 
            avion[i][j].fila = i + 1; 
            avion[i][j].columna = 'A' + j; 
            avion[i][j].ocupado = 0; 
            strcpy(avion[i][j].pasajero, ""); 
        } 
    } 
} 
 
int menu(void) { 
    int op; 
    //do { 
        system("cls"); 
        printf("\n\t\t\t MENU DE RESERVAS DE AEROSKY AIRLINES\n"); 
        printf("\n 1. Reservar un asiento\n"); 
        printf(" 2. Cancelar una reserva\n"); 
        printf(" 3. Mostrar asientos ocupados y libres\n"); 
        printf(" 4. Consultar reservas por pasajero\n"); 
        printf(" 5. Salir\n");
        op=validarEnteroEntre("Ingrese una opcion [1-5]: ",1,5);
        /*printf(" Ingrese una opcion [1-5]:  "); 
        scanf("%d", &op);*/ 
    //} while (op < 1 || op > 5); 
    return op; 
} 

int validarEnteroEntre(char mensaje[150], int min, int max){
    int x;
    printf(mensaje);
    scanf("%d",&x);
    fflush(stdin);
    while(x>max||x<min){
        printf("El valor ingresado es incorrecto. Debe estar entre %d y %d\n",min, max);
        printf(mensaje);
        scanf("%d",&x);
        fflush(stdin);
    }
    return x;
}

void reservarAsiento(Asiento avion[][COLUMNAS]){
    int f,c;
    char col;
    f=validarEnteroEntre("\nIngrese el numero de fila:\n",1,FILAS)-1;
    printf("\nIngrese la letra correspondiente a su asiento\n");
    scanf("%c",&col);
    fflush(stdin);
    col=toupper(col);
    while(col>'D'||col<'A'){
        printf("El valor ingresado es incorrecto. Debe estar entre A y D");
        printf("\nIngrese la letra correspondiente a su asiento\n");
        scanf("%c",&col);
        fflush(stdin);
        col=toupper(col);
    }
    c=col-'A';
    while(avion[f][c].ocupado==1){
        printf("\nEl asiento correspondiente se encuentra ocupado. Seleccione otro asiento por favor:\n");
        f=validarEnteroEntre("\nIngrese el numero de fila:\n",1,FILAS)-1;
        printf("\nIngrese la letra correspondiente a su asiento\n");
        scanf("%c",&col);
        fflush(stdin);
        col=toupper(col);
        while(col>'D'||col<'A'){
            printf("El valor ingresado es incorrecto. Debe estar entre A y D");
            printf("\nIngrese la letra correspondiente a su asiento\n");
            scanf("%c",&col);
            fflush(stdin);
            col=toupper(col);
        }
        c=col-'A';
        }
    char nombrePasajero[50];
    printf("\nIngrese el nombre del pasajero:\n");
    scanf("%s",&nombrePasajero);
    fflush(stdin);
    strcpy(avion[f][c].pasajero,nombrePasajero);
    avion[f][c].ocupado=1;
    printf("Asiento %d%c reservado a nombre de %s\n",avion[f][c].fila,avion[f][c].columna,avion[f][c].pasajero);
}

void cancelarReserva(Asiento avion[][COLUMNAS]){
    int f,c;
    char col;
    f=validarEnteroEntre("\nIngrese el numero de fila:\n",1,FILAS)-1;
    printf("\nIngrese la letra correspondiente a su asiento\n");
    scanf("%c",&col);
    fflush(stdin);
    col=toupper(col);
    while(col>'D'||col<'A'){
        printf("El valor ingresado es incorrecto. Debe estar entre A y D");
        printf("\nIngrese la letra correspondiente a su asiento\n");
        scanf("%c",&col);
        fflush(stdin);
        col=toupper(col);
    }
    c=col-'A';
    if(avion[f][c].ocupado==0){
        printf("\nEl asiento correspondiente ya estaba libre.\n");
        } else {
        strcpy(avion[f][c].pasajero,"");
        avion[f][c].ocupado=0;
        printf("La reserva del asiento %d%c fue cancelada con exito",avion[f][c].fila,avion[f][c].columna);
        }
}

void mostrarEstado(Asiento avion[][COLUMNAS]){
    system("cls");
    printf("ESTADO DEL AVION\n\n");
    printf("\t     A\t\t\t\t     B\t\t\t\t     C\t\t\t\t     D\n");
    for(int i=0;i<FILAS;i++){
        printf("%d\t",i+1);
        for(int j=0;j<COLUMNAS;j++){
            if(avion[i][j].ocupado==0){
                printf("DISPONIBLE\t\t\t");
            } else {
                printf(avion[i][j].pasajero);
                printf("\t\t\t\t");
            }
        }
        printf("\n");
    }
}

void consultarReservas(Asiento avion[][COLUMNAS]){
    system("cls");
    int libres=0,flag=0;
    char nombre[50], laSlibres='s',laSocupados='s';
    printf("\n\nIngrese el nombre de la persona que quiere consultar reserva: ");
    scanf("%s",&nombre);
    fflush(stdin);
    for(int i=0;i<FILAS;i++){
    for(int j=0;j<COLUMNAS;j++){
        if(avion[i][j].ocupado==0){
            libres++;
        } else {
            if(strcmp(avion[i][j].pasajero,nombre)==0){
                printf("Asiento en fila %d, columna %c\n",avion[i][j].fila,avion[i][j].columna);
                flag=1;
            }
        }
    }
    }
    if(flag==0)printf("No hay reservas a nombre de %s\n",nombre);
    if(libres==1){
        laSlibres=' ';
    } else if(FILAS*COLUMNAS-libres==1){
        laSocupados=' ';
    }
    printf("En total hay %d asiento%c libre%c y %d asiento%c reservado%c",libres,laSlibres,laSlibres,FILAS*COLUMNAS-libres,laSocupados,laSocupados); 
}

void pausa(void){
    char p;
    printf("\nPresione una tecla para continuar para continuar...\n");
    getch();
    fflush(stdin);
}