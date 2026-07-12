#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <ctype.h>
#include <time.h>
#define DEFAULT_TOTAL_PALITOS 30
#define DEFAULT_PALITOS_TURNO 3

typedef struct nodo
{
    char valor;
   struct nodo* siguiente;
}nodo;

nodo* ingresarDato(void);
int pilaVacia(nodo*);
void apilar(nodo**,nodo*);
nodo desapilar(nodo**);
void listarPila(nodo*);
int contarPila(nodo*);
void vaciarPila(nodo*);
int menu(void);
void jugar(nodo** p,int total,int turno,int contraCPU);
char* jugarVSJugador(nodo** p,int turno);
char* jugarVSCPU(nodo** p,int turno);
void jugarTurno(nodo** p, int turno);
void jugarTurnoCPU(nodo** p, int turno);

int main(void)
{
	nodo *p;
   int op;
   int jugadorOMaquina;
   int total_palitos=DEFAULT_TOTAL_PALITOS;
   int palitos_por_turno=DEFAULT_PALITOS_TURNO;
   char si;
   p=NULL;
   srand(time(NULL));
   do
   {
   	op=menu();
      switch(op)
      {
      	case 1:
            do{
                system("cls");
                printf("Deseas jugar contra otro jugador o contra la maquina?\n");
                printf("1- Vs otro jugador\n");
                printf("2- Vs CPU\n");
                printf("3- Volver\n");
                scanf("%d",&jugadorOMaquina);
            } while(jugadorOMaquina<1||jugadorOMaquina>3);
            if(jugadorOMaquina!=3){
                jugar(&p,total_palitos,palitos_por_turno,jugadorOMaquina-1);
            }
            do{
                printf("Desea volver al menu? [s/n]");
                fflush(stdin);
                scanf("%c",&si);
                si=tolower(si);
            } while(si!='s'&&si!='n');
            if(si=='n')
                op=0;
            break;
         case 2:
         	printf("CAMBIAR CANTIDAD TOTAL DE PALITOS\n");
            printf("Ingrese un numero entero mayor o igual a 30:");
            scanf("%d",&total_palitos);
            while(total_palitos<30){
                printf("El valor ingresado es incorrecto, ingrese un numero entero mayor o igual a 30:");
                scanf("%d",&total_palitos);
            }
            break;
         case 3:
            printf("CAMBIAR CANTIDAD DE PALITOS A SACAR POR TURNO\n");
            printf("Ingrese un numero entero mayor o igual a 3 y menor a %d:", (int)((float)total_palitos*0.1));
            scanf("%d",&palitos_por_turno);
            while(palitos_por_turno<3||palitos_por_turno>total_palitos*0.1){
                printf("El valor ingresado es incorrecto, ingrese un numero entero mayor o igual a 3 y menor a %d:", (int)((float)total_palitos*0.1));
                scanf("%d",&palitos_por_turno);
            }
         	break;
      }
   }while(op<4&&op!=0);

   if(p!=NULL)
   {

        vaciarPila(p);
        pilaVacia(p);
   }
   return 0;
}

//**********************************************************************
nodo* ingresarDato(void)
{
   nodo *q;

   q=(nodo*)malloc(sizeof(nodo));

   q->valor='I';
   return q;
}

//**********************************************************************
int pilaVacia(nodo*p)
{
	if(p==NULL)
   {
   	system("cls");
      printf("\nPILA VACIA\n");
      system("pause");

      return 0;
   }
   else
   	return 1;
}

//**********************************************************************
void apilar(nodo**p,nodo*q)
{
   q->siguiente=*p;
	*p=q;
}
//**********************************************************************
nodo desapilar(nodo**p)
{
	nodo dato,*aux;
   aux=*p;
   dato=**p;
   *p=(*p)->siguiente;
   free(aux);
   return dato;
}
//**********************************************************************
void listarPila(nodo*p)
{
	system("cls");
   printf("\nPALITOS RESTANTES\n\n");

   while(p)
   {
   	printf("%c",p->valor);
      p=p->siguiente;
   }
	printf("\n\n");
   system("pause");
}
//**********************************************************************
int contarPila(nodo* p){
    int cant=0;
    while(p)
   {
      p=p->siguiente;
      cant++;
   }
   return cant;
}
//**********************************************************************
void vaciarPila(nodo*p)
{
	nodo *aux;
   while(p)
   {
   	aux=p;
      p=p->siguiente;
      free(aux);
   }
}
//**********************************************************************
int menu(void)
{
	int op;
   do
   {
   	system("cls");
   	printf("MENU DE OPCIONES\n\n");
   	printf("1- Jugar\n");
   	printf("2- Cambiar palitos iniciales (default: 30)\n");
   	printf("3- Cambiar maximo de palitos a sacar por turno (default: 3)\n");
   	printf("0- Salir\n");

      printf("Ingrese Opcion:  ");
      scanf("%d",&op);

   }while(op<0||op>3);
   return op;
}
//**********************************************************************
void jugar(nodo** p,int total,int turno,int contraCPU){
    nodo* q;
    char* perdedor;
    for(int i=0;i<total;i++){
        q=ingresarDato();
        apilar(p,q);
    }
    if(contraCPU)
        perdedor=jugarVSCPU(p, turno);
    else
        perdedor=jugarVSJugador(p, turno);
    printf("%s perdio! Se quedo con el ultimo palito\n",perdedor);
    vaciarPila(*p);
    *p=NULL;
    system("pause");
}
char* jugarVSJugador(nodo** p,int turno){
    int ronda=1;
    while(contarPila(*p)!=1){
        jugarTurno(p,turno);
        ronda++;
    }
    if(ronda%2)
        return "El jugador 1";
    else
        return "El jugador 2";
}
char* jugarVSCPU(nodo** p,int turno){
    int ronda=1;
    while(contarPila(*p)!=1){
        if(ronda){
            jugarTurno(p,turno);
        } else{
            jugarTurnoCPU(p,turno);
        }
        ronda=((ronda+1)%2);
    }
    if(ronda)
        return "El jugador";
    else
        return "LA CPU";
}
void jugarTurno(nodo** p, int turno){
    int cant;
    int total=contarPila(*p);
    int maximoASacar=turno<total?turno:total-1;
    listarPila(*p);
    printf("Indicar la cantidad de palitos a retirar:");
    scanf("%d",&cant);
    while(cant<1||cant>maximoASacar){
        printf("El valor a retirar debe estar entre 1 y %d\n",maximoASacar);
        printf("Indicar la cantidad de palitos a retirar:");
        scanf("%d",&cant);
    }
    for(int i=0;i<cant;i++){
        desapilar(p);
    }
}
void jugarTurnoCPU(nodo** p, int turno){
    int cant;
    int total=contarPila(*p);
    srand(time(NULL));
    cant=1+rand()%((turno<total?turno:total-1)-1+1);
    for(int i=0;i<cant;i++){
        desapilar(p);
    }
}