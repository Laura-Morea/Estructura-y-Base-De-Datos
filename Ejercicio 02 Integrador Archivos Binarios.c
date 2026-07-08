#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 5
#define MAX_ARTICULOS 6
#define CANT_CHAR_LINEA 50

typedef struct {
    int codigo;
    char nombre[20];
    float saldo;
} Cliente;

typedef struct {
    int codigo;
    char nombre[20];
    float precio;
    int stock;
    float facturado;
} Articulo;

// Prototipos
void tecla();
void linea(int n);
void inicializarDatos(FILE *archClientes, FILE *archArticulos);
void mensajeError();
void mostrarDatos(FILE *archClientes, FILE *archArticulos);
void ingresarVentas(FILE *archClientes, FILE *archArticulos);
Cliente buscarCliente(int codCli,FILE *archClientes);
Articulo buscarArticulo(int codArt,FILE *archArticulos);
void sobreescribirArticulo(Articulo art,FILE *archArticulos);
void sobreescribirCliente(Cliente cli,FILE *archClientes);

int main(int argc, char const *argv[])
{
    char *nomArchCliente="regCliente.dat";
    char *nomArchArticulo="regArticulo.dat";
    FILE *archCli, *archArt;
    archCli=fopen(nomArchCliente,"wb+");
    archArt=fopen(nomArchArticulo,"wb+");
    if((archArt!=NULL)&&(archCli!=NULL)){
        inicializarDatos(archCli,archArt);
        fclose(archCli);
        fclose(archArt);
        archCli=fopen(nomArchCliente,"rb+");
        archArt=fopen(nomArchArticulo,"rb+");
        if((archArt!=NULL)&&(archCli!=NULL)){
            ingresarVentas(archCli,archArt);
            fclose(archArt);
            fclose(archCli);
        } else {
            mensajeError();
        }
    } else {
        mensajeError();
    }
    return 0;
}

void tecla(){
    printf("\nPresione una tecla para continuar...\n");
    fflush(stdin);
    getch();
}

void linea(int n){
    for(int i=0;i<n;i++){
        printf("*");
    }
    printf("\n");
}

void inicializarDatos(FILE *archClientes, FILE *archArticulos) {
    Cliente clientes[MAX_CLIENTES] = {
        {1, "Lopez", 0},
        {2, "Rodriguez", 0},
        {3, "Garcia", 0},
        {4, "Martinez", 0},
        {5, "Perez", 0}
    };
    for(int i=0;i<MAX_CLIENTES;i++){
        fwrite(&(clientes[i]),sizeof(Cliente),1,archClientes);
    }

    Articulo articulos[MAX_ARTICULOS] = {
        {100, "Coca Cola", 2000, 10, 0},
        {101, "Agua Tonica", 3500, 20, 0},
        {102, "Naranja Fanta", 3600, 15, 0},
        {103, "Sprite", 2800, 8, 0},
        {104, "Pomelo", 2500, 12, 0},
        {105, "Mandarina", 1500, 25, 0}
    };
    for(int i=0;i<MAX_ARTICULOS;i++){
        fwrite(&(articulos[i]),sizeof(Articulo),1,archArticulos);
    }
    printf("Datos ingresados correctamente\n");
    tecla();
}

void mensajeError(){
    printf("Hubo un error al intentar abrir alguno de los archivos\n");
    tecla();
}

void mostrarDatos(FILE *archClientes, FILE *archArticulos){
    system("cls");
    fseek(archClientes,0,SEEK_SET);
    Cliente cli;
    linea(CANT_CHAR_LINEA);
    printf("\n\n\t\tDATOS CLIENTES\n\n");
    linea(CANT_CHAR_LINEA);
    printf("CODIGO\t\tNOMBRE\t\tSALDO\n");
    fread(&cli,sizeof(Cliente),1,archClientes);
    while(!(feof(archClientes))){
        printf("%d\t\t%-16s$%.2f\n",cli.codigo,cli.nombre,cli.saldo);
        fread(&cli,sizeof(Cliente),1,archClientes);
    }
    fseek(archArticulos,0,SEEK_SET);
    Articulo art;
    printf("\n");
    linea(CANT_CHAR_LINEA);
    printf("\n\n\t\tDATOS ARTICULOS\n\n");
    linea(CANT_CHAR_LINEA);
    printf("CODIGO\t\tNOMBRE ARTICULO\t\tPRECIO\t\tSTOCK\tFACTURADO\n");
    fread(&art,sizeof(Articulo),1,archArticulos);
    while(!(feof(archArticulos))){
        printf("%d\t\t%-16s\t$%.2f\t%d\t%.2f\n",art.codigo,art.nombre,art.precio,art.stock,art.facturado);
        fread(&art,sizeof(Articulo),1,archArticulos);
    }
}

void ingresarVentas(FILE *archClientes, FILE *archArticulos){
    mostrarDatos(archClientes,archArticulos);
    int num,codCli,codArt, cant;
    Cliente cli;
    Articulo art;
    printf("Ingrese el numero de factura (0 para terminar):");
    scanf("%d",&num);
    while(num!=0){
        printf("Ingrese el codigo de cliente:");
        scanf("%d",&codCli);
        cli=buscarCliente(codCli,archClientes);
        if(cli.codigo!=0){
            printf("Cliente seleccionado: %s\n", cli.nombre);
            printf("Ingrese el codigo del articulo a comprar (0 para terminar):");
            scanf("%d",&codArt);
            while(codArt!=0){
                art=buscarArticulo(codArt,archArticulos);
                if(art.codigo!=0){
                    printf("Articulo seleccionado: %s\tPrecio: $%.2f\tStock disponible: %d\n",art.nombre,art.precio,art.stock);
                    printf("Ingrese la cantidad que desea adquirir:");
                    scanf("%d",&cant);
                    if(cant>0&&cant<=art.stock){
                        cli.saldo+=cant*art.precio;
                        art.facturado+=cant*art.precio;
                        art.stock-=cant;
                        sobreescribirArticulo(art,archArticulos);
                    } else {
                        printf("No es una cantidad valida para hacer la compra\n");
                    }
                } else{
                    printf("No existe el articulo solicitado\n");
                }
                printf("Ingrese el codigo del articulo a comprar (0 para terminar):");
                scanf("%d",&codArt);
            }
            sobreescribirCliente(cli,archClientes);
        } else {
            printf("No existe un cliente con ese codigo\n");
            tecla();
        }
        mostrarDatos(archClientes,archArticulos);
        printf("Ingrese el numero de factura (0 para terminar):");
        scanf("%d",&num);
    }
    tecla();
}

Cliente buscarCliente(int codCli,FILE *archClientes){
    fseek(archClientes,0,SEEK_SET);
    Cliente cli,retorno;
    retorno.codigo=0;
    fread(&cli,sizeof(Cliente),1,archClientes);
    while(!(feof(archClientes))&&retorno.codigo==0){
        if(cli.codigo==codCli){
            retorno=cli;
        }
        fread(&cli,sizeof(Cliente),1,archClientes);
    }
    return retorno;
}

Articulo buscarArticulo(int codArt,FILE *archArticulos){
    fseek(archArticulos,0,SEEK_SET);
    Articulo art,retorno;
    retorno.codigo=0;
    fread(&art,sizeof(Articulo),1,archArticulos);
    while(!(feof(archArticulos))&&retorno.codigo==0){
        if(art.codigo==codArt){
            retorno=art;
        }
        fread(&art,sizeof(Articulo),1,archArticulos);
    }
    return retorno;
}

void sobreescribirArticulo(Articulo art,FILE *archArticulos){
    fseek(archArticulos,-2*sizeof(Articulo),SEEK_CUR);
    fwrite(&art,sizeof(Articulo),1,archArticulos);
}

void sobreescribirCliente(Cliente cli,FILE *archClientes){
    fseek(archClientes,-2*sizeof(Cliente),SEEK_CUR);
    fwrite(&cli,sizeof(Cliente),1,archClientes);
}