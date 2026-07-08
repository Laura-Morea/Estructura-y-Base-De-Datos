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

typedef struct {
    char color[20];
    int litrosAcumulados;
    float valuacion;
} Color;

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
Vendedor buscarVendedor(int codVendedor,FILE *vendedores);
void guardarEnArchTexto(Pintura p, Vendedor v, int idx);

void valuacionStockPorColor(FILE *pinturas, FILE *vendedores);
void guardarInformacion(Color c[CANT_COLORES], Pintura p);
void imprimirResultados(Color c[CANT_COLORES]);
void lineaSimple(int length);

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
                /* *** Opcion a desarrollar por el alumno ****/ 
                rewind(fPinturas);
                rewind(fVendedores);
                generarInformePendientes(fPinturas, fVendedores);
                waitInput(13, "\n[Enter] para continuar...");
                break;

            case 4:
                /* *** Opcion a desarrollar por el alumno ****/ 
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
  Pintura p;
  Vendedor v;
  int cant=0;
  fread(&p,sizeof(Pintura),1,pinturas);
  while(!feof(pinturas)){
    if(p.despachado==0){
        v=buscarVendedor(p.idVendedor, vendedores);
        if(v.idVendedor==0){
            printf("Hubo un problema al intentar encontrar el vendedor #%d\n", p.idVendedor);
        }   else{
            guardarEnArchTexto(p,v, cant);
            cant++;
        }
    }
    fread(&p,sizeof(Pintura),1,pinturas);
  }
  printf("Se escribieron %d lotes pendientes en el archivo %s\n", cant,ARCHIVO_INFORME);
}

Vendedor buscarVendedor(int codVendedor,FILE *vendedores){
    Vendedor v,encontrado;
    encontrado.idVendedor=0;
    fseek(vendedores,0,SEEK_SET);
    fread(&v,sizeof(Vendedor),1,vendedores);
    while(!feof(vendedores)&&encontrado.idVendedor==0){
        if(v.idVendedor==codVendedor){
            encontrado=v;
        }
        fread(&v,sizeof(Vendedor),1,vendedores);
    }
    return encontrado;
}

void guardarEnArchTexto(Pintura p, Vendedor v, int idx){
    FILE *archT;
    char s[80];
    if(idx==0){
        archT=fopen(ARCHIVO_INFORME,"w");
    } else{
        archT=fopen(ARCHIVO_INFORME,"a");
    }
    if(archT==NULL){
        printf("Hubo un problema al intentar escribir el archivo %s\n", ARCHIVO_INFORME);
    }   else{
        sprintf(&s,"[ID: %d] %s  - %s   - %d lts - $ %.2f/lts - Vendedor: %s\n",p.idPintura, p.codigoProducto, p.color, p.litros, p.costoPorLitro, v.nombre);
        fputs(&s,archT);
        fclose(archT);
    }
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
    Pintura p;
    Color c[CANT_COLORES]={{"Rojo",0,0.0},{"Azul",0,0.0},{"Blanco",0,0.0},{"Verde",0,0.0},{"Negro",0,0.0},{"Amarillo",0,0.0},{"Natural",0,0.0}};
    fread(&p,sizeof(Pintura),1,pinturas);
    while(!feof(pinturas)){
        if(p.despachado==0){
            guardarInformacion(&c,p);
        }
        fread(&p,sizeof(Pintura),1,pinturas);
    }
    imprimirResultados(c);
}

void guardarInformacion(Color c[CANT_COLORES], Pintura p){
    int codColor=0;
    while(codColor<CANT_COLORES&&codColor!=-1){
        if(strcmp(p.color,c[codColor].color)==0){
            c[codColor].litrosAcumulados+=p.litros;
            c[codColor].valuacion=(float)(c[codColor].litrosAcumulados)*(p.costoPorLitro);
        }
        codColor++;
    }
}

void imprimirResultados(Color c[CANT_COLORES]){
    Color total={"TOTAL",0,0.0};
    linea(45);
    printf("VALUACION DE STOCK PENDIENTE POR COLOR\n");
    linea(45);
    printf("Color\t\tLitros\t    Valuacion\n");
    lineaSimple(45);
    for(int i=0; i<CANT_COLORES;i++){
        total.litrosAcumulados+=c[i].litrosAcumulados;
        total.valuacion+=c[i].valuacion;
        if(c[i].litrosAcumulados!=0){
            printf("%-15s %-4d lts  $ %.2f\n",c[i].color,c[i].litrosAcumulados,c[i].valuacion);
        }
    }
    lineaSimple(45);
    printf("%-15s %-4d lts  $ %.2f\n",total.color,total.litrosAcumulados,total.valuacion);
    linea(45);
}

void lineaSimple(int length){
    for(int i= 0; i < length; i++){
        printf("-");
    }
    saltoDeLinea();
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
