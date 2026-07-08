#ifndef UTILES_H_
#define UTILES_H_
/* ==============================================================
    Las 'guardas de inclusión' (también llamadas 'include guards')
son una técnica en C y C++ que evita que el contenido
de un archivo de encabezado (.h) sea incluido más de una vez
durante la compilación;

"#ifndef UTILES_H_":
pregunta al preprocesador si no se ha definido el identificador UTILES_H_.

"#define UTILES_H_":
si no estaba definido, ahora lo define. Esto marca que ya se incluyó el archivo.

"#endif":
cierra la condición #ifndef.
=================================================================
============================================================== */
#include "funcs.h"

#define CHARS_PER_LINE 160

typedef struct{
    cadena ruta, mode;
    FILE* fp;
}Archivo;

// int = atoi // float = atof // long long = %lld = atoll
// renglon[strcspn(renglon, "\r\n")] = '\0'; // saca el '\n' final del renglon.
// fflush(file_.fp); // para limpiar un archivo existente.
// rewind(file_);
///////////////////////////////////////////////////////////////////////////
////////////////////////////  PROTOTIPOS  /////////////////////////////////
///////////////////////////////////////////////////////////////////////////

Archivo readF();
int openF(Archivo* file_);
bool validateF(Archivo file_);
void closeF(Archivo file_);
void removeF(Archivo file_);

void readFs(Archivo files_[], int size);
int openFs(Archivo files_[], int size);
//se podría hacer que, si se creó un archivo ("w"), se borre si falla la carga)
void closeFs(Archivo files_[], int size);
void removeFs(Archivo files_[], int size);

char* separarExtension(cadena ruta);
void agregarAlgoALaRuta(cadena ruta, cadena paraAgregar);

///////////////////////////////////////////////////////////////////////////
/////////////////////////  IMPLEMENTACIONES  //////////////////////////////
///////////////////////////////////////////////////////////////////////////

Archivo readF(){
    Archivo file_;
    leerCadena("Ingrese ruta: ", file_.ruta);
    leerCadena("Modo: ", file_.mode);
return file_;
}

int openF(Archivo* file_){
    file_->fp = fopen(file_->ruta, file_->mode);
return validateF(*file_);
}

bool validateF(Archivo file_){
    int result = file_.fp != NULL;
    if(!result) printf("Error: No se pudo abrir '%s'\n", file_.ruta);
return result;
}

void closeF(Archivo file_){
    int result = fclose(file_.fp);
    if(result == 0) printf("\n'%s' cerrado correctamente.\n", file_.ruta);
    else printf("\nError: No se pudo abrir '%s'\n", file_.ruta);
}

void removeF(Archivo file_){
    closeF(file_);
    if(remove(file_.ruta) == 0) printf("\n'%s' eliminado correctamente.\n", file_.ruta);
    else printf("\nError: No se pudo eliminar '%s'\n", file_.ruta);
}

void readFs(Archivo files_[], int size){
    for(int i= 0; i < size; i++){
        files_[i] = readF();
    }
}

int openFs(Archivo files_[], int size){
    int i= 0, result;
    do{
        result = openF(&files_[i]);
        i++;
    }while(i < size && result != 0);

    if(result == 0 && i != 1) closeFs(files_, i);
return result;
}

void closeFs(Archivo files_[], int size){
    for(int i= 0; i < size; i++){
        closeF(files_[i]);
    }
}

void removeFs(Archivo files_[], int size){
    for(int i= 0; i < size; i++){
        removeF(files_[i]);
    }
}

char* separarExtension(cadena ruta){
    char* extension = strrchr(ruta, '.');
    char* copia = strdup(extension);    // crea una copia independiente.
    *extension = '\0';
return copia;
}

/* void sacarExtension(cadena ruta){
     char* extension = strrchr(ruta, '.');
     char* punteroAExtension = strstr(ruta, extension);

     int longitud_subcadena = strlen(extension);
     int longitud_restante = strlen(ruta) - (punteroAExtension - ruta) - longitud_subcadena;
     memmove(punteroAExtension, punteroAExtension + longitud_subcadena, longitud_restante + 1);
} */
//versión alterna)

void agregarAlgoALaRuta(cadena ruta, cadena paraAgregar){
    char* extension = separarExtension(ruta);
    strcat(ruta, paraAgregar);
    strcat(ruta, extension);
}


////////////////////////////
#endif      /* UTILES_H_ */
////////////////////////////