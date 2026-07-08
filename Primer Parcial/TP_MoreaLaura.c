#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 20

#define ARCH_PARTIDAS  "partidas_ajedrez.dat"
#define ARCH_JUGADORES "jugadores.dat"
#define ARCH_CONFIG    "config_ajedrez.txt"

typedef struct
{
    int numjugador;
    char nombre[16];
    char apellido[16];
    char pais[16];
} Jugador;

typedef struct
{
    int numronda;
    int numjugador;
    float tiempo;
} Partida;

void pausar();
void limpiarPantalla();

void mostrarVersion(char *aplicacion, char *torneo, char *version);
void MostrarJugadores();
void MostrarPartidas();
void MostrarPromedioTiempoJugador();   // opción 3
void MostrarMejorTiempoRonda();        // opción 4
void Menu();

int buscarJugador(int numero, Jugador *jugador);
float calcularPromedio(Jugador *j);
int existeRonda(int n);
float buscarMejorTiempo(int r, Jugador *j);

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
            MostrarJugadores();
            pausar();
            break;

        case 2:
            MostrarPartidas();
            pausar();
            break;

        case 3:
            MostrarPromedioTiempoJugador();
            pausar();
            break;

        case 4:
            MostrarMejorTiempoRonda();
            pausar();
            break;

        default:
            printf("Opcion invalida.\n");
            pausar();
            break;
        }

        Menu();
        printf("Ingrese la opcion deseada:\n");
        scanf("%d", &opcion);
    }

    printf("\n\nSaliendo del sistema .....!!!\n\n");
    pausar();

    return 0;
}

void pausar()
{
#ifdef _WIN32
    system("pause");
#else
    printf("\nPresione ENTER para continuar...");
    getchar();
    getchar();
#endif
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarVersion(char *aplicacion, char *torneo, char *version)
{
    FILE *archivo = fopen(ARCH_CONFIG, "r");

    if (archivo == NULL)
    {
        printf("El archivo %s no pudo abrirse.\n", ARCH_CONFIG);
        printf("Verifique que exista y que se encuentre en la misma carpeta del ejecutable.\n");
    }
    else
    {
        fgets(aplicacion, 16, archivo);
        fgets(torneo, 16, archivo);
        fgets(version, 6, archivo);

        printf("%s", aplicacion);
        printf("%s", torneo);
        printf("%s", version);

        fclose(archivo);
    }
}

void Menu()
{
    char aplicacion[16] = "";
    char torneo[16] = "";
    char version[6] = "";

    limpiarPantalla();

    mostrarVersion(aplicacion, torneo, version);

    printf("-------------------------------------\n");
    printf("\tMENU DE OPCIONES\n");
    printf("1. Mostrar listado de jugadores.\n");
    printf("2. Mostrar listado de partidas.\n");
    printf("3. Mostrar promedio de tiempo por jugador.\n");
    printf("4. Mostrar mejor tiempo de una determinada ronda.\n");
    printf("Para salir pulsa << -1 >>.\n");
    printf("-------------------------------------\n");
}

void MostrarJugadores()
{
    Jugador aux;
    FILE *archivo = fopen(ARCH_JUGADORES, "rb");

    if (archivo != NULL)
    {
        while (fread(&aux, sizeof(Jugador), 1, archivo) == 1)
        {
            printf("Numero de Jugador: |%d| Nombre: %s. Apellido: %s. Pais: %s\n",
                   aux.numjugador, aux.nombre, aux.apellido, aux.pais);
        }

        fclose(archivo);
    }
    else
    {
        printf("Error en la apertura del archivo %s\n", ARCH_JUGADORES);
    }
}

void MostrarPartidas()
{
    Partida aux;
    FILE *archivo = fopen(ARCH_PARTIDAS, "rb");

    if (archivo != NULL)
    {
        while (fread(&aux, sizeof(Partida), 1, archivo) == 1)
        {
            printf("Numero de Ronda: %d, Numero de Jugador: %d, Tiempo: %.3f\n",
                   aux.numronda, aux.numjugador, aux.tiempo);
        }

        fclose(archivo);
    }
    else
    {
        printf("Error en la apertura del archivo %s\n", ARCH_PARTIDAS);
    }
}

int buscarJugador(int numero, Jugador *jugador)
{
    FILE *archivo = fopen(ARCH_JUGADORES, "rb");
    Jugador aux;

    if (archivo == NULL)
    {
        printf("Error en la apertura del archivo %s\n", ARCH_JUGADORES);
        return 0;
    }

    while (fread(&aux, sizeof(Jugador), 1, archivo) == 1)
    {
        if (aux.numjugador == numero)
        {
            *jugador = aux;
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

void MostrarPromedioTiempoJugador()
{
    int n;
    Jugador j;
    float prom;
    printf("Ingrese el numero de jugador\n");
    scanf("%d",&n);
    if(buscarJugador(n,&j)){
        prom=calcularPromedio(&j);
        printf("Jugador: %s %s, tiempo promedio: %.3f\n",j.nombre,j.apellido,prom);
    } else{
        printf("No se encontro ningun jugador con ese numero\n");
    }
}

float calcularPromedio(Jugador *j){
    FILE *archP;
    Partida p;
    float acum=0;
    int cant=0;
    archP=fopen(ARCH_PARTIDAS,"rb");
    if(archP==NULL){
        printf("No pudo abrirse el archivo %s para su lectura\n", ARCH_PARTIDAS);
    } else{
        fread(&p,sizeof(Partida),1,archP);
        while(!feof(archP)){
            if(p.numjugador==(j->numjugador)){
                acum+=p.tiempo;
                cant++;
            }
            fread(&p,sizeof(Partida),1,archP);
        }
        acum=acum/cant;
        fclose(archP);
    }
    return acum;
}

void MostrarMejorTiempoRonda()
{
    int n;
    float mejorTiempo;
    Jugador j;
    printf("Ingrese un numero de ronda\n");
    scanf("%d",&n);
    if(existeRonda(n)){
        mejorTiempo=buscarMejorTiempo(n,&j);
        printf("El mejor tiempo de la ronda #%d\nJugador: %s %s, Pais: %s, Tiempo: %.3f\n",n, j.nombre, j.apellido, j.pais,mejorTiempo);
    } else {
        printf("No existe ese numero de ronda en ninguna partida\n");
    }
}

int existeRonda(int n){
    FILE *archP;
    Partida p;
    int encontrado;
    archP=fopen(ARCH_PARTIDAS, "rb");
    if(archP==NULL){
        printf("No pudo abrirse el archivo %s para su lectura\n", ARCH_PARTIDAS);
    } else {
        fread(&p, sizeof(Partida),1,archP);
        while(!feof(archP)&&p.numronda!=n){
            fread(&p, sizeof(Partida),1,archP);
            encontrado=(p.numronda==n);
        }
        fclose(archP);
    }
    return encontrado;
}

float buscarMejorTiempo(int r,Jugador *j){
    FILE *archP, *archJ;
    Partida p;
    float tiempo=1000;
    archP=fopen(ARCH_PARTIDAS,"rb");
    archJ=fopen(ARCH_JUGADORES,"rb");
    if(archP==NULL||archJ==NULL){
        printf("No pudieron abrirse correctamente los archivos\n");
    } else {
        fread(&p,sizeof(Partida),1,archP);
        while(!feof(archP)){
            if(p.numronda==r){
                if(p.tiempo<tiempo){
                    tiempo=p.tiempo;
                    buscarJugador(p.numjugador,j);
                }
            }
            fread(&p,sizeof(Partida),1,archP);
        }
        fclose(archP);
        fclose(archJ);
    }
    return tiempo;
}