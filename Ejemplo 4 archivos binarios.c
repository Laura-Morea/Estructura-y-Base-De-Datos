#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct{
    char nombre[25];
    int edad;
} Registro;

void cargaRegistros(FILE *archivo);
void muestraRegistros(FILE *archivo);
void contarRegistros(FILE *archivo);

int main(int argc, char const *argv[])
{
    Registro persona;
    FILE *archivo;
    system("cls");
    system("color 9f");
    archivo=fopen("datos.dat","ab");
    if(archivo!=NULL){
        printf("Carga de Registros (Nombre y edad) en un archivo binario\n");
        cargaRegistros(archivo);
        fclose(archivo);
    } else{
        printf("Error en la apertura del archivo");
    }
    printf("\n");
    archivo=fopen("datos.dat","rb");
    if(archivo!=NULL){
        printf("\nMuestra de registros (Nombre y edad) de un archivo binario \n");
        muestraRegistros(archivo);
        fclose(archivo);
    } else{
        printf("Error en la apertura del archivo");
    }
    printf("\n");
    system("pause");
    archivo=fopen("datos.dat","rb");
    if(archivo!=NULL){
        printf("\nCuenta la cantidad de registros (Nombre y Edad) del archivo binario\n");
        contarRegistros(archivo);
        fclose(archivo);
    } else{
        printf("Error en la apertura del archivo");
    }
    system("pause");
    return 0;
}

void cargaRegistros(FILE *archivo){
    Registro persona;
    char tecla;
    if(archivo!=NULL){
        do{
            fflush(stdin); //se vacia el buffer de teclado
            printf("\nIntroduzca el nombre de la persona:\n");
            scanf("%s",persona.nombre);
            if(strlen(persona.nombre)>0){
                printf("Introduzca la edad:\n");
                scanf("%d",&persona.edad);
                fwrite(&persona, sizeof(Registro),1,archivo);
                printf("\n");
            }
            printf("Desea continuar (s/n): ");
            fflush(stdin);
            tecla = getchar();
        } while(tecla=='s');
    }
}

void muestraRegistros(FILE *archivo){
    Registro persona;
    int i;
    char tecla;
    fread(&persona,sizeof(Registro),1,archivo); //en sizeof es importante que ponga el tipo de la variable
    while(!feof(archivo)){
        printf("Nombre: %s, Edad: %d\n",persona.nombre,persona.edad);
        fread(&persona,sizeof(Registro),1,archivo);
    }
}

void contarRegistros(FILE *archivo){
    int cantReg;
    fseek(archivo,0,SEEK_END);
    cantReg=ftell(archivo)/sizeof(Registro);
    printf("\nCantidad de registros en el archivo: %d\n", cantReg);
}