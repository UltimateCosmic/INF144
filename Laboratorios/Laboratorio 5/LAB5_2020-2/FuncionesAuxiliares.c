/* 
 * Proyecto: LAB5_2020-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de junio de 2022, 04:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncionesAuxiliares.h"
#define NO_SE_ENCONTRO -1

FILE *abrirArchivo(const char *nombreDeArchivo, const char *modoDeApertura){
    FILE *arch=fopen(nombreDeArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDeArchivo);
        exit(1);
    }
    return arch;
}

void leerAlumnos(int *codAlumno, char **nomAlumno, int *i){
    FILE *arch=abrirArchivo("Alumnos.txt","r");
    int nc;
    char nombre[60];
    while(1){
        fscanf(arch,"%d",&codAlumno[*i]);
        if(feof(arch)) break;
        leerNombre(arch,nombre);
        nc=strlen(nombre);
        nomAlumno[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(nomAlumno[*i],nombre);        
        (*i)++;
    }
    fclose(arch);
}

void ordenarAlumnos(int *codAlumno, char **nomAlumno, int cantAlumnos){    
    for(int i=0; i<cantAlumnos-1; i++)
        for(int j=i+1; j<cantAlumnos; j++)
            if(codAlumno[j]<codAlumno[i]){
                cambiarInt(codAlumno,i,j);
                cambiarChar(nomAlumno,i,j);                
            }
}

void cambiarInt(int *arr, int i, int j){
    int aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;    
}

void cambiarDouble(double *arr, int i, int j){
    double aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;    
}

void cambiarChar(char **arr, int i, int j){
    char *aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;    
}

void leerCursos(char **codCurso, double *credCurso, char **codFacu,
                char **nomCurso, int *i){
    FILE *arch=abrirArchivo("Cursos.txt","r");
    int nc;
    char cadena[50];
    while(1){
        
        //Codigo de curso
        fscanf(arch,"%s",cadena);
        if(feof(arch)) break;
        nc=strlen(cadena);
        codCurso[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(codCurso[*i],cadena);
        
        //Creditos de curso y codigo de facultad
        fscanf(arch,"%lf %s",&credCurso[*i],cadena);
        nc=strlen(cadena);
        codFacu[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(codFacu[*i],cadena);
        
        //Nombre del curso
        leerNombre(arch,cadena);
        nc=strlen(cadena);
        nomCurso[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(nomCurso[*i],cadena);
                
        (*i)++;
    }
    fclose(arch);
}

void ordenarCursos(char **codCurso, double *credCurso, char **codFacu,
                   char **nomCurso, int cantCursos){    
    for(int i=0; i<cantCursos-1; i++)
        for(int j=i+1; j<cantCursos; j++)
            if(strcmp(codCurso[j],codCurso[i])<0){
                cambiarChar(codCurso,i,j);
                cambiarDouble(credCurso,i,j);
                cambiarChar(codFacu,i,j);
                cambiarChar(nomCurso,i,j);                
            }    
}

void leerNombre(FILE *arch, char *nombre){
    nombre[0]=0;
    char palabra[20];    
    while(1){
        fscanf(arch,"%s",palabra);
        strcat(nombre,palabra);
        if(fgetc(arch)=='\n') break;     
        strcat(nombre," ");
    }
}

void leerNotas(int *codAlumno, int cantAlumnos, char **codCurso, int cantCursos,
               double *promGen, double *promApro, double *credApro,
               double *credDesa, int *cantApro, int *cantDesa, 
               int *cantCurApro, int *cantCurDesa, double *credCurso){    
    FILE *arch=abrirArchivo("Notas.txt","r");
    int alumno, nota, posA, posC;
    char curso[10];
    while(1){
        fscanf(arch,"%d",&alumno);
        if(feof(arch)) break;
        fscanf(arch,"%s %d",curso,&nota);
        posA=buscarIndInt(alumno,codAlumno,cantAlumnos);
        posC=buscarIndChar(curso,codCurso,cantCursos);
        if(posA!=NO_SE_ENCONTRO && posC!=NO_SE_ENCONTRO){                        
            if(nota>=11){               
                credApro[posA]+=credCurso[posC];
                cantCurApro[posA]++;    
                promApro[posA]+=nota;
                cantApro[posC]++;
            }else{
                credDesa[posA]+=credCurso[posC];
                cantCurDesa[posA]++;
                cantDesa[posC]++;
            }           
            promGen[posA]+=nota;
        }
    }
    fclose(arch);    
}

int buscarIndInt(int cod, int *arrCod, int cantCod){    
    int limSup=cantCod-1, limInf=0, pm;    
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm=(limSup+limInf)/2;
        if(arrCod[pm]==cod) return pm;
        if(arrCod[pm]>cod) limInf=pm+1;
        else limSup=pm-1;
    }
}

int buscarIndChar(char *cod, char **arrCod, int cantCod){    
    int limSup=cantCod-1, limInf=0, pm;    
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm=(limSup+limInf)/2;
        if(strcmp(arrCod[pm],cod)==0) return pm;
        if(strcmp(arrCod[pm],cod)<0) limInf=pm+1;
        else limSup=pm-1;
    }
}

void calcularPromedios(double *promGen, double *promApro, int *cantCurApro,
                       int *cantCurDesa, int cantAlumnos){    
    for(int i=0; i<cantAlumnos; i++){
        promGen[i]/=(cantCurApro[i]+cantCurDesa[i]);                
        promApro[i]/=cantCurApro[i];
    }    
}

void imprimirReporte(int *codAlumno, char **nomAlumno, double *promGen, 
                     double *promApro, double *credApro, double *credDesa,
                     int cantAlumnos, char **codCurso, char **nomCurso,
                     double *credCurso, char **codFacu, int *cantApro,
                     int *cantDesa){
    
    for(int i=0; i<cantAlumnos; i++){
        
        printf("%d %-30s %.2lf %5.2lf",codAlumno[i],nomAlumno[i],promGen[i],
                promApro[i]);
        printf("%5.2lf %5.2lf\n",credApro[i],credDesa[i]);
        
        
    }
    
    
}