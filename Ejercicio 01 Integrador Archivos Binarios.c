# include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int codigo;
    char nombre[30];
    float tempMin;
    float tempMax;
    float amplitud;
} Registro;

void cargarRegistros(FILE *);
int disponible(int, FILE *);
void mostrarYAmplitudMax(FILE *);
void mostrarCiudadesAmplitudMax(FILE *,float);

int main(int argc, char const *argv[])
{
    FILE *archivo;
    char *nombreArch="temperaturas.dat";
    archivo=fopen(nombreArch,"ab+"); //si usara wb+ piso el archivo existente
    if(archivo==NULL){
        printf("Error. No pudo abrirse el archivo binario");
    } else {
        cargarRegistros(archivo);
        fclose(archivo);
            archivo=fopen(nombreArch,"rb");
        if(archivo==NULL){
            printf("Error. El archivo es inexistente o no puede leerse");
        } else {
            mostrarYAmplitudMax(archivo);
            fclose(archivo);
        }
    }
    return 0;
}

void cargarRegistros(FILE *arch){
    Registro ciudad;
    printf("Ingrese el codigo de ciudad (0 para terminar): ");
    scanf("%d", &(ciudad.codigo));
    while(ciudad.codigo!=0){
        if(disponible(ciudad.codigo, arch)){
            printf("\nIngrese el nombre de la ciudad: ");
            scanf("%s",&(ciudad.nombre));
            do{
                printf("\nIngrese la temperatura minima registrada: ");
                scanf("%f",&(ciudad.tempMin));
                printf("\nIngrese la temperatura maxima registrada: ");
                scanf("%f",&(ciudad.tempMax));
                if((ciudad.tempMin)>(ciudad.tempMax))
                    printf("\nError. No puede registrarse una temperatura maxima menor a la minima. Ingresar los valores nuevamente\n");
            } while((ciudad.tempMin)>(ciudad.tempMax));
            ciudad.amplitud=ciudad.tempMax-ciudad.tempMin;
            fseek(arch,0,SEEK_END);
            fwrite(&ciudad,sizeof(Registro),1,arch);
        } else {
            printf("\nCodigo existente\n");
        }
        printf("\nIngrese el codigo de ciudad (0 para terminar): ");
        scanf("%d", &(ciudad.codigo));
    }
}

int disponible(int cod, FILE *arch){
    Registro aux;
    int disponible=1;
    fseek(arch,0,SEEK_SET);
    fread(&aux,sizeof(Registro),1,arch);
    while(!(feof(arch))&&(disponible!=0)){
        if(cod==(aux.codigo))
            disponible=0;
        fread(&aux,sizeof(Registro),1,arch);
    }
    return disponible;
}

void mostrarYAmplitudMax(FILE *arch){
    Registro ciudad;
    float maxAmpl;
    printf("ESTADISTICA DE TEMPERATURAS DE CUIDADES\n");
    printf("COD\tCIUDAD\t\tMINIMA\tMAXIMA\tAMPLITUD\n\n");
    fseek(arch,0,SEEK_SET);
    fread(&ciudad,sizeof(Registro),1,arch);
    maxAmpl=ciudad.amplitud;
    while(!(feof(arch))){
        printf("%d\t%s", ciudad.codigo, ciudad.nombre);
        if(strlen(ciudad.nombre)<8)
            printf("\t");
        printf("\t%.2f\t%.2f\t%.2f\n", ciudad.tempMin, ciudad.tempMax, ciudad.amplitud);
        if(ciudad.amplitud>maxAmpl)
            maxAmpl=ciudad.amplitud;
        fread(&ciudad,sizeof(Registro),1,arch);
    }
    mostrarCiudadesAmplitudMax(arch,maxAmpl);
}

void mostrarCiudadesAmplitudMax(FILE *arch,float maxAmpl){
    Registro ciudad;
    printf("\nLa amplitud maxima es de %.2f y corresponde a:\n", maxAmpl);
    fseek(arch,0,SEEK_SET);
    fread(&ciudad,sizeof(Registro),1,arch);
    while(!(feof(arch))){
        if(ciudad.amplitud==maxAmpl)
            printf("%s\n",ciudad.nombre);
        fread(&ciudad,sizeof(Registro),1,arch);
    }
}