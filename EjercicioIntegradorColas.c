#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#define s scanf


typedef struct {
    int identificador;
    char nombreTrabajo[30];
    int cantPaginas;
    char nombreUsuario[20];
} Trabajo;

typedef struct elemento
{
    Trabajo dato;
    struct elemento *sig;
} nodo;

void acolar(nodo, nodo **, nodo **);
nodo *nuevonodo(nodo);
nodo desacolar(nodo **);
void listar(nodo *);
int contarCola(nodo *);
void recorrer(nodo *);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_dato(void);
void dato_eliminado(nodo);
void buscarTrabajo(nodo *);
Trabajo buscarTrabajoporID(nodo*,int);
void eliminarTrabajosPorUsuario(nodo**);
int menu(void);

int main()
{
    nodo *p = NULL, *q, r;
    int op;
    system("cls");
    system("color 9f");
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
        {
            r = ingresar_dato();
            acolar(r, &p, &q);
            break;
        }
        case 2:
        {
            if (verificar(p) != NULL){
                printf("Imprimiento documento... \n");
                r = desacolar(&p);
            }
            dato_eliminado(r);
            break;
        }
        case 3:
        {
            if (verificar(p) != NULL)
            {
                printf("\nTrabajos pendientes:\n\n");
                listar(p);
                getch();
            }
            break;
        }
        case 4:
        {
            if(verificar(p)!=NULL){
                buscarTrabajo(p);
            } else{
                printf("No hay trabajos en la cola de impresion\n");
            }
            break;
        }
        case 5:
        {
            printf("Cantidad de trabajos pendientes\n\n");
            int c=contarCola(p);
            printf("Hay un total de %d trabajos pendientes\n", c);
            system("pause");
            break;
        }
        case 6:
        {
            if(verificar(p)!=NULL){
                eliminarTrabajosPorUsuario(&p);
            } else{
                printf("No hay archivos en la cola de impresion\n");
            }
            break;
        }
        case 7:
        {
            if (verificar(p) != NULL){
                printf("Vaciando la cola de impresion\n\n");
                vaciar(&p);
                system("pause");
            }
            break;
        }
        }
    } while (op < 8);
    if (verificar(p) != NULL)
        vaciar(&p);
    printf("\nHasta luego!!");
    return 0;
} // CIERRA MAIN
//**********************************************************************
nodo *nuevonodo(nodo r)
{
    nodo *x;
    x = (nodo *)malloc(sizeof(nodo));
    x->dato = r.dato; //*x=r;
    x->sig = NULL;
    return (x);
}
//**********************************************************************
void acolar(nodo r, nodo **p, nodo **q)
{
    nodo *nuevo;
    nuevo = nuevonodo(r);
    if (*p == NULL)
        *p = nuevo;
    else
        (*q)->sig = nuevo;
    *q = nuevo;
} // CIERRA ACOLAR
//**********************************************************************
nodo desacolar(nodo **p)
{
    nodo r, *aux;
    r = **p;
    aux = *p;
    *p = (*p)->sig;
    free(aux);
    return (r);
} // CIERRA DESACOLAR
//**********************************************************************
void listar(nodo *p)
{
    if (p)
    {
        printf("\tID: %d\tArchivo: %s\tAutor: %s\tPaginas: %d\n", p->dato.identificador,p->dato.nombreTrabajo, p->dato.nombreUsuario, p->dato.cantPaginas);
        listar(p->sig);
    }
} // CIERRA LISTAR
//**********************************************************************
int contarCola(nodo *p){
    int c=0;
    while (p)
    {
        c++;
        p=p->sig;
    }
    return c;
} // CIERRA CONTAR
//**********************************************************************
void vaciar(nodo **p)
{
    nodo *aux;
    while (*p != NULL)
    {
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
} // CIERRA VACIAR
//**********************************************************************
nodo *verificar(nodo *p)
{
    if (p == NULL)
    {
        system("cls"); // clrscr();
        printf("\nCola de impresion vacia!");
        printf("\n\n\n\nPulse una tecla para continuar...");
        getch();
    }
    return (p);
} // CIERRA VERIFICAR
//**********************************************************************
nodo ingresar_dato(void)
{
    nodo r;
    Trabajo t;
    system("cls"); // clrscr();
    printf("AGREGANDO TRABAJO A LA COLA DE IMPRESION\n\n");
    printf("\nIngrese el nro de trabajo: ");
    s("%d", &t.identificador);
    printf("\nIndique el nombre del documento: ");
    scanf(" %[^\n]",t.nombreTrabajo);
    do{
        printf("\nIndique la cantidad de paginas del documento: ");
        scanf("%d",&t.cantPaginas);
    } while(t.cantPaginas<0);
    printf("\nProporcione el nombre del creador del documento: ");
    fflush(stdin);
    scanf(" %[^\n]",t.nombreUsuario);
    r.dato=t;
    return (r);
} // CIERRA INGRESAR_DATO
//**********************************************************************
void dato_eliminado(nodo r)
{
    system("cls"); // clrscr();
    printf("Se imprimio exitosamente\n\n\tID: %d\tArchivo: %s\tAutor: %s\tPaginas: %d\n", r.dato.identificador,r.dato.nombreTrabajo, r.dato.nombreUsuario, r.dato.cantPaginas);
    printf("\n\n\nPulse una tecla para continuar...");
    getch();
} // CIERRA DATO_ELIMINADO
//**********************************************************************
void buscarTrabajo(nodo *p){
    int n;
    Trabajo t;
    printf("Buscando trabajo por ID\n\n");
    printf("Ingrese el numero de ID: ");
    fflush(stdin);
    scanf("%d",&n);
    t=buscarTrabajoporID(p,n);
    if(t.identificador!=-1){
        printf("El trabajo seleccionado es:\nID: %d\tnombre del trabajo: %s\tcantidad de paginas: %d\tnombre del creador: %s\n",t.identificador,t.nombreTrabajo,t.cantPaginas,t.nombreUsuario);
    } else{
        printf("No se encontro el trabajo buscado\n");
    }
    system("pause");
} //CIERRA BUSCARTRABAJO
//**********************************************************************
Trabajo buscarTrabajoporID(nodo*p,int n){
    int encontrado=0,i=0;
    Trabajo t;
    t.identificador=-1;
    int c=contarCola(p);
    while(i<c&&!encontrado){
        if (p){
            if(((p->dato).identificador)==n){
                encontrado=1;
                t=p->dato;
            } else{
                p=p->sig;
                i++;
            }
        }
    }
    return t;
} // CIERRA BUSCARTRABAJOPORID
//**********************************************************************
void eliminarTrabajosPorUsuario(nodo** p){
    char nombre[20];
    nodo* anterior=NULL;
    nodo* actual=*p;
    printf("Eliminando trabajos por usuario\n\n");
    printf("Ingrese el nombre del usuario: ");
    fflush(stdin);
    scanf(" %[^\n]",nombre);
    while(actual){
        if(strcmp(actual->dato.nombreUsuario,nombre)==0){
            if(anterior==NULL){
                *p=actual->sig;
                free(actual);
                actual=(*p);
            } else{
                anterior->sig=actual->sig;
                free(actual);
                actual=anterior->sig;
            }
        } else{
            anterior=actual;
            actual=actual->sig;
        }
    }
    listar(*p);
    system("pause");
}// CIERRA ELIMINARTRABAJOSPORUSUARIO
//**********************************************************************
int menu(void)
{
    int op;
    system("cls");
    printf("\n\t\t\t\tMenu principal");
    do
    {
        printf("\n\n\t\t\t\tAgregar un trabajo    - 1");
        printf("\n\n\t\t\t\tImprimir un trabajo - 2");
        printf("\n\n\t\t\t\tMostrar trabajos pendientes    - 3");
        printf("\n\n\t\t\t\tBuscar un trabajo    - 4");
        printf("\n\n\t\t\t\tCantidad de trabajos pendientes     - 5");
        printf("\n\n\t\t\t\tEliminar trabajos del usuario     - 6");
        printf("\n\n\t\t\t\tVaciar la cola de impresion     - 7");
        printf("\n\n\t\t\t\tSalir     - 8");
        printf("\n\n\nOpcion nro.: ");
        fflush(stdin);
        s("%d", &op);
    } while (op < 1 || op > 8);
    return (op);
} // CIERRA MENU