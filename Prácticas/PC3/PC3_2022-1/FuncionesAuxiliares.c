/* 
 * Proyecto: 2022-1_ArregosConCadenas_Practica03
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de junio de 2022, 07:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 120
#define MAX_NOMBRE 60
#define MAX_CURSOS 100
#define NO_SE_ENCONTRO -1

FILE *abrirArchivo(const char *nombreDeArchivo, const char *modoDeApertura){
    FILE *arch=fopen(nombreDeArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDeArchivo);
        exit(1);
    }
    return arch;
}

void leerCursos(char **codCurso, char **nomCurso, double *credCurso, int *i){
    FILE *arch=abrirArchivo("Cursos.txt","r");
    int nc;
    char codigo[10], nombre[60];
    while(1){        
        //Codigo del curso:
        fscanf(arch,"%s",codigo);
        if(feof(arch)) break;
        nc=strlen(codigo);
        codCurso[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(codCurso[*i],codigo);        
        //Nombre del curso:
        leerNombreDelCurso(arch,nombre);
        nc=strlen(nombre);
        nomCurso[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(nomCurso[*i],nombre);        
        //Creditos del curso:
        fscanf(arch,"%lf",&credCurso[*i]);
        (*i)++;
    }    
    fclose(arch);
}

void leerNombreDelCurso(FILE *arch, char *nombre){
    nombre[0]=0;   
    int i;
    char palabra[15];
    while(fgetc(arch)!='{');
    while(1){
        fscanf(arch,"%s",palabra);
        strcat(nombre,palabra);       
        if(verificarFin(palabra)){
            for(i=0; nombre[i]; i++);
            nombre[i-1]=0;
            break;        
        }
        strcat(nombre," ");        
    }
}

int verificarFin(char *palabra){    
    int i;
    for(i=0; palabra[i]; i++);
    if(palabra[i-1]=='}') return 1;
    else return 0;
}

void leerAlumnos(char **codAlumno, char **nomAlumno, int *i){
    FILE *arch=abrirArchivo("Alumnos.txt","r");
    int nc;
    char codigo[10], nombre[MAX_NOMBRE], nombreMod[MAX_NOMBRE];
    while(1){                
        //Codigo de alumno:
        fscanf(arch,"%s",codigo);
        if(feof(arch)) break;
        nc=strlen(codigo);
        codAlumno[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(codAlumno[*i],codigo);
        //Nombre de alumno:
        fscanf(arch,"%s",nombre);        
        modificarNombreDeAlumno(nombre,nombreMod);        
        nc=strlen(nombreMod);
        nomAlumno[*i]=(char*)malloc(sizeof(char)*(nc+1));
        strcpy(nomAlumno[*i],nombreMod);
        //Creditos de alumno
        fscanf(arch,"%*lf %*lf %*lf");        
        (*i)++;
    }
    fclose(arch);
}

void modificarNombreDeAlumno(char *nombre, char *nombreMod){    
    //Vaciamos el nombre
    for(int k=0; k<MAX_NOMBRE; k++) nombreMod[k]=0;      
    //Leemos la cantidad de guiones    
    int cantGuiones=0, i, j, centinela; 
    for(i=0; nombre[i]; i++)
        if(nombre[i]=='_') cantGuiones++;    
    //Saltamos los caracteres hasta el primer apellido
    for(i=0, j=0; i<cantGuiones-1; i++){
        centinela=1;
        while(centinela){
            if(nombre[j]=='_') centinela=0;
            j++;
        }        
    }    
    //Leemos la inicial del primer apellido
    i=0;
    nombreMod[i]=convertirMayusc(nombre[j]);       
    i++;
    j++;    
    //Leemos las letras en minuscula del primer apellido
    while(1){
        if(nombre[j]=='_') break;        
        nombreMod[i]=convertirMinusc(nombre[j]);
        i++;
        j++;
    }
    j++;        
    //Leemos la inicial del segundo apellido
    nombreMod[i]=' ';
    i++;    
    nombreMod[i]=convertirMayusc(nombre[j]);
    i++;
    nombreMod[i]='.';
    i++;
    nombreMod[i]=' ';
    i++;    
    //Leemos el primer nombre
    j=0;
    nombreMod[i]=convertirMayusc(nombre[j]);
    i++;
    j++;    
    while(1){
        if(nombre[j]=='_') break;
        nombreMod[i]=convertirMinusc(nombre[j]);  
        i++;
        j++;
    }    
    j++;    
    //Leemos las iniciales de los nombres
    for(int k=0; k<cantGuiones-2; k++){
        nombreMod[i]=' ';
        i++;    
        nombreMod[i]=convertirMayusc(nombre[j]);
        i++;
        nombreMod[i]='.';
        i++;
        if(cantGuiones>3){
            centinela=1;
            while(centinela){            
                if(nombre[j]=='_') centinela=0;
                j++;
            }
        }
    }
}

char convertirMayusc(char c){
    return c-=(c>='a'&&c<='z'?'a'-'A':0);
}

char convertirMinusc(char c){
    return c+=(c>='A'&&c<='Z'?'a'-'A':0);
}

void imprimirReportedeConsolidado(char **codCurso, char **nomCurso, double *credCurso,
                                  int cantCursos, char **codAlumno, char **nomAlumno, 
                                  int cantAlumnos){    
    FILE *archNotas, *archReporte;
    archNotas=abrirArchivo("Notas.txt","r");
    archReporte=abrirArchivo("ReportedeConsolidadoDeCursos.txt","w");
    imprimirCabeceraDeReporte(archReporte);
    int i=0, pos, cantApro[MAX_CURSOS]={}, cantDesa[MAX_CURSOS]={};
    double promedio[MAX_CURSOS]={};
    char curso[10];
    while(1){
        fscanf(archNotas,"%s",curso);
        if(feof(archNotas)) break;
        pos = buscarPosChar(curso,codCurso,cantCursos);
        if(pos!=NO_SE_ENCONTRO){
            imprimirLinea(archReporte,'=',MAX_LINEA);
            fprintf(archReporte,"%3d) %s %10s %32s\n",i+1,"CODIGO","NOMBRE",
                    "CREDITOS");
            fprintf(archReporte,"%11s %3c %-32s %.2lf\n",codCurso[pos],' ',
                    nomCurso[pos],credCurso[pos]); 
            imprimirLinea(archReporte,'-',MAX_LINEA);
            imprimirAlumnosMatriculados(archNotas,archReporte,codAlumno,
                    nomAlumno,cantAlumnos,&cantApro[pos],&cantDesa[pos],
                    &promedio[pos]);
        }else                    
            while(fgetc(archNotas)!='\n');        
    }
    imprimirResumenDeLosCursosDictados(codCurso,nomCurso,credCurso,
            cantApro,cantDesa,promedio,archReporte,cantCursos);
    fclose(archNotas);
    fclose(archReporte);
}

void imprimirCabeceraDeReporte(FILE *archReporte){
    fprintf(archReporte,"%62s\n","INSTITUCION EDUCATIVA LIMA");
    fprintf(archReporte,"%60s\n","CONSOLIDADO DE CURSOS");    
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

int buscarPosChar(char *cod, char **arrCod, int cantCod){
    for(int i=0; i<cantCod; i++)
        if(strcmp(cod,arrCod[i])==0) return i;
    return NO_SE_ENCONTRO;    
}

void imprimirAlumnosMatriculados(FILE *archNotas, FILE *archReporte,
                                 char **codAlumno, char **nomAlumno,
                                 int cantAlumnos, int *cantApro, int *cantDesa,
                                 double *promedio){
    imprimirCabeceraAlumnos(archReporte);
    int nota, pos, i=0;
    char alumno[10];
    while(1){
        fscanf(archNotas,"%s %d",alumno,&nota);        
        pos=buscarPosChar(alumno,codAlumno,cantAlumnos);
        if(pos!=NO_SE_ENCONTRO){            
            fprintf(archReporte,"%7d) %-12s",i+1,codAlumno[pos]);
            fprintf(archReporte,"%-29s %02d\n",nomAlumno[pos],nota);            
            i++;
            if(nota>=11) (*cantApro)++;
            else (*cantDesa)++;
            (*promedio)+=nota;
        }
        if(fgetc(archNotas)=='\n') break;
    }
}

void imprimirCabeceraAlumnos(FILE *archReporte){    
    fprintf(archReporte,"%25s\n","ALUMNOS MATRICULADOS");
    fprintf(archReporte,"%15s %11s %26s\n","CODIGO","NOMBRE","NOTA");
}

void imprimirResumenDeLosCursosDictados(char **codCurso, char **nomCurso,
            double *credCurso, int *cantApro, int *cantDesa, double *promedio,
            FILE *archReporte, int cantCursos){    
    imprimirCabeceraDeResumen(archReporte);
    for(int i=0; i<cantCursos; i++){        
        if(cantApro[i]!=0||cantDesa[i]!=0) promedio[i]/=cantApro[i]+cantDesa[i];
        else promedio[i]=0.0;
        fprintf(archReporte,"%3d) %-10s",i+1,codCurso[i]);
        fprintf(archReporte,"%-50s %.2lf",nomCurso[i],credCurso[i]);        
        fprintf(archReporte,"%12d %15d %14.2lf\n",cantApro[i],cantDesa[i],
                promedio[i]);
    }
}

void imprimirCabeceraDeResumen(FILE *archReporte){    
    fputc('\n',archReporte);
    imprimirLinea(archReporte,'/',MAX_LINEA);
    fprintf(archReporte,"%70s\n","RESUMEN DE LOS CURSOS DICTADOS ESTE SEMESTRE");
    fprintf(archReporte,"%11s %9s %50s %13s %16s %11s\n","CODIGO","NOMBRE",
            "CREDITOS","APROBADOS","DESAPROBADOS","PROMEDIO");    
}