
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionescadenas.h"


FILE *abrirArchivo(const char *nombre,const char*modo){
    FILE *arch;
    arch=fopen(nombre,modo);
    if (arch==NULL){
        printf("Error: El archivo %s no se puede abrir\n",nombre);
        exit(1);
    }
    return arch;
}

void leerCadena(char *cadena,int tope, FILE *Archivo){
    int numcar;
    fgets(cadena,tope,Archivo);
    numcar=strlen(cadena);
    if (cadena[numcar-1]=='\n') cadena[numcar-1]=0;
}

char *leeCadenaExacta(FILE *arch){
    char buffer[500];
    char *cadena;
    int longitud;
    leerCadena(buffer,500,arch);
    if (feof(arch)) return NULL;
    longitud=strlen(buffer);
    cadena=(char *)malloc(sizeof(char)*(longitud+1));
    strcpy(cadena,buffer);
    return cadena;
}

void sacaPalabras(char *cadena,char **palabras,int *num_pal,char carSep){
    int i=0;
    char buffer[100];
    int ncar=0;
    char *ptr;
    *num_pal=0;
    while(1){
        while (cadena[i]==carSep)i++;
        if (cadena[i]==0) break;
        ncar=0;
        while(cadena[i]!=carSep && cadena[i]!=0){
            buffer[ncar]=cadena[i];
            ncar++;
            i++;        
        }
        buffer[ncar]=0;
        ptr=(char *)malloc(sizeof(char)*(ncar+1));
        strcpy(ptr,buffer);
        palabras[*num_pal]=ptr;
        (*num_pal)++;
    }
}
