/*
 * ================================================================
 *  ESTRUCTURA Y BASE DE DATOS  —  Parcial 1
 *  Fecha    : 18 / 05 / 2026
 *  Profesores: Ing. Alejandro J. Behringer
 *              Prof. Juan Carlos Capia
 *  Sistema  : ColorAR S.A. — Gestión de Stock de Pinturas
 * ================================================================
 *
 *  INSTRUCCIONES AL ALUMNO
 *  ─────────────────────────────────────────────────────────────
 *  Este archivo contiene el programa base ya implementado.
 *  Su única tarea es completar las DOS funciones marcadas con:
 *
 *      COMPLETAR  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  NO modificar ninguna otra parte del código.
 *  El programa debe compilar sin errores ni warnings.
 *  Los archivos vendedores.dat y pinturas.dat ya están
 *  provistos en la misma carpeta que este archivo.
 * ================================================================
 */

#include "header_files/ffuncs.h"

#define CANT_COLORES 7

/* ================================================================
 *  ESTRUCTURAS
 * ================================================================ */

typedef struct {
    int   idVendedor;
    char  nombre[30];
    char  zona[20];           /* "Norte", "Sur", "Centro", "Este", "Oeste" */
    float comisionPorc;       /* porcentaje: 5.0, 7.5, 9.0, etc.           */
} Vendedor;

typedef struct {
    int   idPintura;
    int   idVendedor;         /* referencia al vendedor responsable         */
    char  codigoProducto[10]; /* "LAT01", "ESM03", "BAR02", etc.            */
    char  color[20];          /* "Rojo", "Azul", "Blanco", "Verde",         */
                              /* "Negro", "Amarillo", "Natural"              */
    char  tipoPintura[15];    /* "Latex", "Esmalte", "Barniz"               */
    int   litros;
    float costoPorLitro;
    int   despachado;         /* 0 = pendiente en deposito  1 = despachado  */
} Pintura;

/* ================================================================
 *  CONSTANTES — nombres de archivos
 * ================================================================ */
#define ARCHIVO_VENDEDORES  "vendedores.dat"
#define ARCHIVO_PINTURAS    "pinturas.dat"
#define ARCHIVO_CONFIG      "config.txt"
#define ARCHIVO_INFORME     "informe_pendientes.txt"

/* ================================================================
 *  PROTOTIPOS
 * ================================================================ */

/* Funciones ya implementadas */
void leerConfig(void);
int  menu(void);
void listarVendedores(FILE *vendedores);
void listarPinturas(FILE *pinturas);

/* Funciones a completar por el alumno */
void generarInformePendientes(FILE *pinturas, FILE *vendedores);
Vendedor buscarVendedor(int id_buscado, FILE *vendedores);

void valuacionStockPorColor(FILE *pinturas, FILE *vendedores);
void cargarDatosDeLaPintura(Pintura p, Pintura *pinturas);
void mostrarValuacion(Pintura *stock);
void vendedorConMayorValuacionPendiente(FILE* pinturas, FILE *vendedores);

/* ================================================================
 *  main  —  YA IMPLEMENTADO, no modificar
 * ================================================================ */
int main(void) 
{
    FILE *fVendedores = NULL;
    FILE *fPinturas   = NULL;
    int   opcion;

    utf8();

    /* Apertura de archivos binarios en modo solo lectura */
    if ((fVendedores = fopen(ARCHIVO_VENDEDORES, "rb+")) == NULL) 
    {
        printf("Error: no se pudo abrir %s\n", ARCHIVO_VENDEDORES);
        return 1;
    }
    if ((fPinturas = fopen(ARCHIVO_PINTURAS, "rb+")) == NULL) 
    {
        printf("Error: no se pudo abrir %s\n", ARCHIVO_PINTURAS);
        fclose(fVendedores);
        return 1;
    }

    do 
    {
        opcion = menu();
        switch (opcion) 
        {

            case 1:
                listarVendedores(fVendedores);
                rewind(fVendedores);
                waitInput(13, "\n[Enter] para continuar...");
                break;

            case 2:
                listarPinturas(fPinturas);
                rewind(fPinturas);
                waitInput(13, "\n[Enter] para continuar...");
                break;

            case 3:
                /* *** Opcion a desarrollar por el alumno *** */
                rewind(fPinturas);
                rewind(fVendedores);
                generarInformePendientes(fPinturas, fVendedores);
                waitInput(13, "\n[Enter] para continuar...");
                break;

            case 4:
                /* *** Opcion a desarrollar por el alumno *** */
                rewind(fPinturas);
                valuacionStockPorColor(fPinturas, fVendedores);
                waitInput(13, "\n[Enter] para continuar...");
                break;

            case 5:
                printf("\nSaliendo del sistema...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }
    } while (opcion != 5);

    fclose(fVendedores);
    fclose(fPinturas);
    return 0;
}


/* ================================================================
 *  FUNCIONES YA IMPLEMENTADAS
 * ================================================================ */

void leerConfig(void) 
{
    FILE *cfg;
    char empresa[40], temporada[20], version[10];

    if ((cfg = fopen(ARCHIVO_CONFIG, "r")) == NULL) {
        printf("ColorAR - Sistema de Stock  v1.0\n");
        return;
    }
    fgets(empresa,   sizeof(empresa),   cfg);
    fgets(temporada, sizeof(temporada), cfg);
    fgets(version,   sizeof(version),   cfg);
    fclose(cfg);

    empresa[strcspn(empresa,     "\n")] = '\0';
    temporada[strcspn(temporada, "\n")] = '\0';
    version[strcspn(version,     "\n")] = '\0';

    printf("\n");
    linea(60);
    printf("  %s  |  %s  |  Ver. %s\n", empresa, temporada, version);
    linea(60);
    printf("\n");
}

int menu(void) 
{
    int op;
    system("cls");
    leerConfig();
    printf("  MENU PRINCIPAL\n\n");
    printf("  1. Listar vendedores                        [implementado]\n");
    printf("  2. Listar pinturas (stock completo)         [implementado]\n");
    printf("  3. Informe de lotes pendientes              [implementado]\n");
    printf("  4. Valuacion de stock por color             [implementado]\n");
    printf("  5. Salir\n\n");
    op = leerEnteroEntre(1, 5, "  Opcion: ");
    return op;
}

void listarVendedores(FILE *vendedores) 
{
    Vendedor v;
    system("cls");
    printf("\n");
    printf("  %-4s  %-25s  %-10s  %s\n", "ID", "Nombre", "Zona", "Comision");
    linea(55);
    while (fread(&v, sizeof(Vendedor), 1, vendedores) == 1) 
    {
        printf("  %-4d  %-25s  %-10s  %.1f%%\n",v.idVendedor, v.nombre, v.zona, v.comisionPorc);
    }
}

void listarPinturas(FILE *pinturas) 
{
    Pintura p;
    system("cls");
    printf("\n");
    printf("  %-4s  %-4s  %-8s  %-10s  %-8s  %6s  %8s  %s\n","ID", "Vnd", "Codigo", "Color", "Tipo","Litros", "$/Litro", "Estado");
    linea(75);
    while (fread(&p, sizeof(Pintura), 1, pinturas) == 1) 
    {

        printf("  %-4d  %-4d  %-8s  %-10s  %-8s  %4d L  %7.2f  %s\n",
               p.idPintura,
               p.idVendedor,
               p.codigoProducto,
               p.color,
               p.tipoPintura,
               p.litros,
               p.costoPorLitro,
               (p.despachado == 0) ? "PENDIENTE" : "Despachado");
    }
}


/* ================================================================
 *
 *   >>>  COMPLETAR  —  FUNCION 1 de 2
 *
 *  generarInformePendientes
 *  ----------------------------------------------------------------
 *  Recorre pinturas.dat y filtra los lotes con despachado == 0.
 *  Por cada lote pendiente:
 *    - busca en vendedores.dat el nombre del vendedor usando
 *      el campo idVendedor del lote
 *    - escribe una linea en informe_pendientes.txt con el
 *      siguiente formato exacto:
 *
 *  [ID:  3] LAT03  - Blanco   - 30 lts - $ 2.80/lts - Vendedor: Maria Gonzalez
 *
 *  Al finalizar:
 *    - imprime en pantalla cuantos lotes se escribieron
 *    - imprime el nombre del archivo generado
 *
 *  RESTRICCIONES:
 *    - Verificar que informe_pendientes.txt abra correctamente
 *    - Cerrar informe_pendientes.txt antes de retornar
 *    - NO cerrar pinturas ni vendedores  (los cierra main)
 * ================================================================ */
void generarInformePendientes(FILE *pinturas, FILE *vendedores) 
{
    fseek(pinturas, 0, SEEK_SET); // Asegura que el puntero de pinturas esté al inicio
    Pintura p;
    Vendedor v;
    FILE *informe = fopen(ARCHIVO_INFORME, "w");
    if (informe == NULL) {
        printf("Error: no se pudo crear el archivo %s\n", ARCHIVO_INFORME);
        return;
    }

    fprintf(informe, "[%s] %-6s  %-10s  %-10s  %8s\n\n",
                "ID", "Codigo", "Color", "Litros", "$/Litro");
    while(fread(&p, sizeof(Pintura), 1, pinturas)){
        if(p.despachado == 0){
            v = buscarVendedor(p.idVendedor, vendedores);
            fprintf(informe, "[%-2.2d] %-6s - %-10s - %-10d - %.2f \t\t Vendedor: %s\n",
                p.idPintura, p.codigoProducto, p.color, p.litros, p.costoPorLitro, v.nombre);
        }
    }
    if(fclose(informe) == 0) printf("Se ha creado y cerrado correctamente '%s'\n", ARCHIVO_INFORME);
    rewind(pinturas);
    rewind(vendedores);
}

Vendedor buscarVendedor(int id_buscado, FILE *vendedores){
    rewind(vendedores); 
    Vendedor v, supuesto = {0, "****", "****", 0};
    bool encontrado= false;

    while(!encontrado && fread(&v, sizeof(Vendedor), 1, vendedores) == 1){
        encontrado = (v.idVendedor == id_buscado);
    }
    if(encontrado) supuesto = v;
return supuesto;
}


/* ================================================================
 *
 *   >>>  COMPLETAR  —  FUNCION 2 de 2
 *
 *  valuacionStockPorColor
 *  ----------------------------------------------------------------
 *  Recorre pinturas.dat procesando SOLO los lotes con
 *  despachado == 0.
 *
 *  Agrupa por color usando strcmp().
 *  Colores posibles: "Rojo" "Azul" "Blanco" "Verde"
 *                    "Negro" "Amarillo" "Natural"
 *
 *  Por cada color calcula:
 *    - total de litros acumulados
 *    - valuacion total  (litros * costoPorLitro)
 *
 *  Muestra en pantalla el siguiente formato:
 *
 *  ================================================
 *   VALUACION DE STOCK PENDIENTE POR COLOR
 *  ================================================
 *   Color           Litros       Valuacion
 *  ------------------------------------------------
 *   Rojo              143 lts   $    585.50
 *   Azul               90 lts   $    425.00
 *   ...
 *  ------------------------------------------------
 *   TOTAL             650 lts   $  2.722,40
 *  ================================================
 *
 *  RESTRICCIONES:
 *    - No mostrar colores con 0 litros pendientes
 *    - NO cerrar pinturas  (lo cierra main)
 *    - Usar strcmp() para comparar cadenas de color
 *    - Valuacion = litros * costoPorLitro
 * ================================================================ */
void valuacionStockPorColor(FILE *pinturas, FILE *vendedores) {
    Pintura p, stock[CANT_COLORES] = {  {0, 0, "****", "rojo", "****", 0, 0, 0},
                                        {0, 0, "****", "azul", "****", 0, 0, 0},
                                        {0, 0, "****", "blanco", "****", 0, 0, 0},
                                        {0, 0, "****", "verde", "****", 0, 0, 0},
                                        {0, 0, "****", "negro", "****", 0, 0, 0},
                                        {0, 0, "****", "amarillo", "****", 0, 0, 0},
                                        {0, 0, "****", "natural", "****", 0, 0, 0}  };
    while(fread(&p, sizeof(Pintura), 1, pinturas)){
        if(p.despachado == 0) cargarDatosDeLaPintura(p, stock);
    }
    mostrarValuacion(stock);
    vendedorConMayorValuacionPendiente(pinturas, vendedores);
    rewind(pinturas);
    rewind(vendedores);
}

void cargarDatosDeLaPintura(Pintura p, Pintura *pinturas){
    int i= 0, encontrada= 0;
    Pintura *actual;
    do{
        actual = (pinturas + i);
        stringToLower(actual->color);
        stringToLower(p.color);
        encontrada = (strcmp(actual->color, p.color) == 0);
        i++;
    }while(i < CANT_COLORES && !encontrada);

    if(encontrada){
        actual->litros += p.litros;
        actual->costoPorLitro = p.costoPorLitro;
        actual->idVendedor = p.idVendedor;
    }
}

void mostrarValuacion(Pintura *stock){
    pasarElTrapo();
    Pintura actual;
    int litrosTotales= 0;
    float valuacion, valuacionTotal= 0;
    linea(50);
    printf(" VALUACION DE STOCK PENDIENTE POR COLOR \n");
    linea(50);
    printf(" %-18s  %-5s  %s \n", "Color", "Litros", "Valuacion");
    linea(50);
    for(int i= 0; i < CANT_COLORES; i++){
        actual= *(stock+i);
        if(actual.litros != 0){
            valuacion= (actual.litros * actual.costoPorLitro);
            printf(" %-20s  %-5d  $%.2f\n", actual.color, actual.litros, valuacion);
            valuacionTotal += valuacion;
            litrosTotales += actual.litros;
        }
    }
    linea(50);
    printf(" %-20s  %-5d  $%.2f \n", "TOTAL", litrosTotales, valuacionTotal);
    linea(50);
}

void vendedorConMayorValuacionPendiente(FILE* pinturas, FILE *vendedores){
    float valuacionMax= INT_MIN, valuacion;
    Vendedor v, buscado;
    Pintura p;

    while(fread(&v, sizeof(Vendedor), 1, vendedores) == 1){
        fseek(pinturas, 0, SEEK_SET);
        valuacion= 0;
        while(fread(&p, sizeof(Pintura), 1, pinturas) == 1){
            if(p.despachado == 0 && v.idVendedor == p.idVendedor){
                valuacion += (p.litros * p.costoPorLitro);
                if(valuacion > valuacionMax){
                    valuacionMax = valuacion;
                    buscado = v;
                }
            }
        }
    }
    printf("\nVendedor con mayor stock pendiente: %s — $ %.2f\n",
                                    buscado.nombre, valuacionMax);
}


/*
 * ================================================================
 *  "Si no sabes resolver el problema sin computadora,
 *   menos le vas a poder explicar algo.
 *   Primero entendemos el problema gracias al analisis que hare
 *   con mi companero de equipo, y luego podemos escribir codigo
 *   para la solucion requerida."
 * ================================================================
 */
