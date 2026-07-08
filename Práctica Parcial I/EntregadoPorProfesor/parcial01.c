#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 20
#define ARCH_TIEMPOS2 "tiempos2.dat"
#define ARCH_RESULTADOS "resultados2.dat"
#define ARCH_CORREDORES "corredores.dat"
#define ARCH_CONFIG "config.txt"

typedef struct
{
    int numcorredor;
    char nombre[15];
    char apellido[15];
    char escuderia[15];
} Corredor;

typedef struct
{
    int numvuelta;
    int numcorredor;
    float tiempo;
} tiempos;
// ++++++++++++++++++++++++++++++++++++
// chequear posibles struct a utilizar
// ++++++++++++++++++++++++++++++++++++
/*typedef struct
{
    int numcorredor;
    float tiempo;
    char nombre[15];
    char apellido[15];

}tiempoFinal;
typedef struct
{
    int numcorredor;
    float tiempodevuelta;
    float sumatiempo;
    char nombre[15];
    char apellido[15];

}tiempoParcial;
*/

void mostrarVersion(char *aplicacion, char *circuito, char *version);
void MostrarCorredores();
void MostrarTiempos();
void MostrarPromedioTiempoVuelta(); 
Corredor buscarCorredor(int n);
float calcularPromedioCorredor(int n);
void MostrarMejorTiempoVuelta();
int contarVueltas();
tiempos buscarMejorTiempo(int nVuelta); 
void Menu();

int main()
{
    int opcion;
    Menu();
    printf("Ingrese la opcion deseada:\n");
    scanf("%d", &opcion);

    while (opcion != -1)
    {
        switch (opcion)
        {
        case 1:
            MostrarCorredores();
            system("pause");
            break;
        case 2:
            MostrarTiempos();
            system("pause");
            break;
        case 3: 
            MostrarPromedioTiempoVuelta();
            break;
        case 4: 
            MostrarMejorTiempoVuelta();
            break;
        }
        Menu();
        printf("Ingrese la opcion deseada:\n");
        scanf("%d", &opcion);
    }
    printf("\n\nsaliendo del sistema .....!!!\n\n");
    //system("pause");
    return 0;
}


void MostrarPromedioTiempoVuelta()
{
    int numero;
    Corredor piloto;
    float promedio;
    printf("Ingrese el numero de corredor:");
    scanf("%d",&numero);
    piloto= buscarCorredor(numero);
    if(piloto.numcorredor==0){
        printf("No existe un piloto con ese numero\n");
    }   else {
        promedio= calcularPromedioCorredor(numero);
        printf("Corredor: %s, %s\tPromedio de vuelta: %.3f\n", piloto.apellido, piloto.nombre, promedio);
    }
    system("pause");
}

Corredor buscarCorredor(int n){
    Corredor piloto, c;
    piloto.numcorredor=0;
    FILE *archivo;
    archivo= fopen(ARCH_CORREDORES, "rb");
    if(archivo==NULL){
        printf("No pudo abrirse el archivo %s\n", ARCH_CORREDORES);
    } else{
        fread(&c,sizeof(Corredor),1,archivo);
        while(!feof(archivo)){
            if(n==c.numcorredor){
                piloto=c;
            }
            fread(&c,sizeof(Corredor),1,archivo);
        }
        fclose(archivo);   
    }
    return piloto;
}

float calcularPromedioCorredor(int n){
    float prom=0;
    int cantVueltas=0;
    tiempos t;
    FILE *archivo;
    archivo= fopen(ARCH_TIEMPOS2, "rb");
    if(archivo==NULL){
        printf("El archivo %s no pudo abrirse correctamente\n", ARCH_TIEMPOS2);
    } else {
        fread(&t,sizeof(tiempos),1,archivo);
        while(!feof(archivo)){
            if(t.numcorredor==n&&t.numvuelta!=0){
                prom+=t.tiempo;
                cantVueltas++;
            }
            fread(&t,sizeof(tiempos),1,archivo);
        }
        prom=prom/(float)cantVueltas;
        fclose(archivo);
    }
    return prom;
}

void MostrarMejorTiempoVuelta()
{
    int nVuelta, vueltasTotales;
    vueltasTotales= contarVueltas();
    tiempos mejor;
    Corredor pilotoRapido;
    printf("Ingrese el numero de vuelta a considerar:");
    scanf("%d", &nVuelta);
    while(nVuelta<=0||nVuelta>vueltasTotales){
        printf("Numero de vuelta incorrecto. Seleccione un valor entre %d y %d\n", 1, vueltasTotales);
        printf("Ingrese el numero de vuelta a considerar:");
        scanf("%d", &nVuelta);
    }
    mejor= buscarMejorTiempo(nVuelta);
    pilotoRapido= buscarCorredor(mejor.numcorredor);
    printf("Vuelta #%d:\nCorredor: %s %s\tEscuderia: %s\tTiempo de vuelta: %.3f\n",nVuelta,pilotoRapido.nombre,pilotoRapido.apellido,pilotoRapido.escuderia,mejor.tiempo);
    system("pause");
}

int contarVueltas(){
    FILE *archivo;
    tiempos t;
    int cant=0;
    archivo=fopen(ARCH_TIEMPOS2, "rb");
    if(archivo==NULL){
        printf("El archivo %s no pudo abrirse correctamente\n", ARCH_TIEMPOS2);
    } else{
        fread(&t,sizeof(tiempos),1,archivo);
        while(!feof(archivo)){
            if(cant<t.numvuelta){
                cant=t.numvuelta;
            }
            fread(&t,sizeof(tiempos),1,archivo); 
        }
        fclose(archivo);
    }
    return cant;
}

tiempos buscarMejorTiempo(int nVuelta){
    tiempos mejor, t;
    FILE *archivo;
    archivo=fopen(ARCH_TIEMPOS2,"rb");
    if(archivo==NULL){
        printf("El archivo %s no pudo abrirse correctamente\n", ARCH_TIEMPOS2);
    } else{
        mejor.tiempo=(float)TAM;
        fread(&t,sizeof(tiempos),1,archivo);
        while(!feof(archivo)){
            if(t.numvuelta==nVuelta&&t.tiempo<mejor.tiempo){
                mejor=t;
            }
            fread(&t,sizeof(tiempos),1,archivo);
        }
        fclose(archivo);
    }
    return mejor;
}

void mostrarVersion(char *aplicacion, char *circuito, char *version)
{
    FILE *archivo = NULL;
    archivo = fopen(ARCH_CONFIG, "r");
    if (archivo == NULL)
    {
        printf("El Archivo %s No pudo Abrirse!!\n", ARCH_CONFIG);
        printf("chequear la ruta donde se esta llamando, o si el archivo existe!!\n");
        printf("habitualmente en VS code , el archivo se encuentra en la carpeta output \n");
    }
    else
    {
        fgets(aplicacion, 15, archivo);
        puts(aplicacion);
        fgets(circuito, 15, archivo);
        puts(circuito);
        fgets(version, 5, archivo);
        puts(version);
    }
}

void Menu()
{
    char aplicacion[15];
    char circuito[15];
    char version[5];

    system("cls");
    mostrarVersion(aplicacion, circuito, version);
    printf("-------------------------------------\n");
    printf("\t\tMENU DE OPCIONES\n");
    printf("1.Mostrar Listado de corredores.\n");
    printf("2.Mostrar el Listado de Tiempos.\n");
    printf("3.Mostrar Promedio de tiempo de vuelta por corredor .\n");
    printf("4.Mostrar mejor tiempo de una determinada vuelta.\n");
    printf("Para Salir pulsa << -1 >>.\n");
    printf("-------------------------------------\n");
}

void MostrarCorredores()
{
    Corredor aux;
    FILE *Archivo;
    Archivo = fopen("corredores.dat", "rb");
    if (Archivo != NULL)
    {
        fread(&aux, sizeof(Corredor), 1, Archivo);
        while (!feof(Archivo))
        {
            printf("Numero de Corredor:|%d| Nombre: %s. Apellido: %s. Escuderia: %s\n", aux.numcorredor, aux.nombre, aux.apellido, aux.escuderia);
            fread(&aux, sizeof(Corredor), 1, Archivo);
        }
        fclose(Archivo);
    }
    else
    {
        printf("Error en la apertura del archivo");
    }
}

void MostrarTiempos()
{
    tiempos aux;
    FILE *Archivo;
    Archivo = fopen(ARCH_TIEMPOS2, "rb");
    if (Archivo != NULL)
    {
        fread(&aux, sizeof(tiempos), 1, Archivo);
        while (!feof(Archivo))
        {
            printf("Numero de Vuelta: %d, Numero de Corredor: %d, Tiempo: %.3f\n", aux.numvuelta, aux.numcorredor, aux.tiempo);
            fread(&aux, sizeof(tiempos), 1, Archivo);
        }
        fclose(Archivo);
    }
    else
    {
        printf("Error en la apertura del archivo %s",ARCH_TIEMPOS2);
    }
}
