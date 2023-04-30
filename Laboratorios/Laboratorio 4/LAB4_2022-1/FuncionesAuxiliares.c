/* 
 * Proyecto: Consolidado_de_cursos_LAB04
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 31 de mayo de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 140
#define MAX_NOMBRE 30
#define MAX_PALABRA 20
#define MAX_ESP 50
#define PRECISION 0.001
#define NO_SE_ENCONTRO -1

FILE *abrirArchivo(char *nombreDelArchivo, char *modoDeApertura){
    FILE *arch = fopen(nombreDelArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDelArchivo);
        exit(1);
    }
}

void leerCursos(int *arrCurso, double *arrCredCurso, int *i){
    FILE *archCursos = abrirArchivo("Cursos.txt","r");
    while(1){
        fscanf(archCursos,"%d",&arrCurso[*i]);
        if(feof(archCursos)) break;
        while(fgetc(archCursos)!='}');
        fscanf(archCursos,"%lf",&arrCredCurso[*i]);
        (*i)++;
    }    
    fclose(archCursos);
}

void leerAlumnos(int *arrAlumno, double *arrCredApro, double *arrCredDesa, 
                 double *arrCredFalt, int *i){
    FILE *archAlumnos = abrirArchivo("Alumnos.txt","r");
    while(1){
        fscanf(archAlumnos,"%d",&arrAlumno[*i]);
        if(feof(archAlumnos)) break;
        while(fgetc(archAlumnos)==' ');
        while(fgetc(archAlumnos)!=' ');
        fscanf(archAlumnos,"%lf %lf %lf",&arrCredApro[*i],&arrCredDesa[*i],
                &arrCredFalt[*i]);
        (*i)++;
    }    
    fclose(archAlumnos);
}

void leerNotas(int *arrAlumno, double *arrCredApro, double *arrCredDesa,
               double *arrCredFalt, int *arrCursosApro, int *arrCursosDesa,
               double *arrPromPond, int cantAlumnos, int *arrCurso,
               double *arrCredCurso, int *arrCantAproDeCurso, 
               int *arrCantDesaDeCurso, int cantCursos){    
    FILE *archNotas = abrirArchivo("Notas.txt","r");
    ordenarCursosPorCodigo(arrCurso,arrCredCurso,cantCursos);
    int curso, pos;    
    while(1){
        fscanf(archNotas,"%d",&curso);        
        if(feof(archNotas)) break;
        pos = buscarPos(curso,arrCurso,cantCursos);
        if(pos!=NO_SE_ENCONTRO)
            leerNotasDeCurso(arrAlumno,arrCredApro,arrCredDesa,arrCredFalt,
                    arrCursosApro,arrCursosDesa,arrPromPond,cantAlumnos,
                    arrCredCurso[pos],&arrCantAproDeCurso[pos],
                    &arrCantDesaDeCurso[pos],archNotas);
        else
            while(fgetc(archNotas)!='\n');
    }
    calcularPromPond(arrPromPond,arrCursosApro,arrCursosDesa,cantAlumnos);
    fclose(archNotas);
}

void ordenarCursosPorCodigo(int *arrCurso, double *arrCredCurso, int cantCursos){    
    for(int i=0; i<cantCursos-1; i++)
        for(int j=i+1; j<cantCursos; j++)
            if(arrCurso[j]<arrCurso[i]){
                cambiarInt(arrCurso,i,j);
                cambiarDouble(arrCredCurso,i,j);                
            }    
}

void cambiarInt(int *arr, int i, int j){
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;    
}

void cambiarDouble(double *arr, int i, int j){
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;    
}

int buscarPos(int codigo, int *arrCodigo, int cantMax){    
    int limSup=cantMax-1, limInf=0, pm;    
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm = (limSup+limInf)/2;
        if(codigo==arrCodigo[pm]) return pm;
        else if(codigo>arrCodigo[pm]) limInf=pm+1;
        else limSup=pm-1;
    }
}

void leerNotasDeCurso(int *arrAlumno, double *arrCredApro, double *arrCredDesa,
                      double *arrCredFalt, int *arrCursosApro, int *arrCursosDesa,
                      double *arrPromPond, int cantAlumnos, double credCurso,
                      int *cantAproDeCurso, int *cantDesaDeCurso, FILE *archNotas){    
    int alumno, nota, pos;
    while(1){
        fscanf(archNotas,"%d %d",&alumno,&nota);
        pos = buscarPos(alumno,arrAlumno,cantAlumnos);
        if(pos!=NO_SE_ENCONTRO){
            if(nota>=11){
                arrCredApro[pos]+=credCurso;
                arrCursosApro[pos]++;
                arrCredFalt[pos]-=credCurso;
                (*cantAproDeCurso)++;
            }else{
                arrCredDesa[pos]+=credCurso;
                arrCursosDesa[pos]++;    
                (*cantDesaDeCurso)++;
            }
            arrPromPond[pos]+=nota;           
        }
        if(fgetc(archNotas)=='\n') break;
    }
}

void calcularPromPond(double *arrPromPond, int *arrCursosApro, int *arrCursosDesa,
                      int cantAlumnos){    
    for(int i=0; i<cantAlumnos; i++)
        if(arrPromPond[i]>PRECISION)
            arrPromPond[i]/=(arrCursosApro[i]+arrCursosDesa[i]);
}

void imprimirReporteDeConsolidado(int *arrCurso, double *arrCredCurso,
                                  int *arrCantAproDeCurso, int *arrCantDesaDeCurso,
                                  int cantCursos, int *arrAlumno, double *arrCredApro,
                                  double *arrCredDesa, double *arrCredFalt,
                                  int *arrCursosApro, int *arrCursosDesa,
                                  double *arrPromPond, int cantAlumnos){
    
    FILE *archCursos, *archAlumnos, *archReporteDeConsolidado;
    archCursos = abrirArchivo("Cursos.txt","r");
    archAlumnos = abrirArchivo("Alumnos.txt","r");
    archReporteDeConsolidado = abrirArchivo("ReporteDeConsolidado.txt","w");
    imprimirConsolidadoDeAlumnos(arrAlumno,arrCredApro,arrCredDesa,arrCredFalt,
            arrCursosApro,arrCursosDesa,arrPromPond,cantAlumnos,archAlumnos,
            archReporteDeConsolidado);
    imprimirResultadosPorCurso(arrCurso,arrCantAproDeCurso,arrCantDesaDeCurso,
            cantCursos,archCursos,archReporteDeConsolidado);
    fclose(archCursos);
    fclose(archCursos);
    fclose(archReporteDeConsolidado);
}

void imprimirConsolidadoDeAlumnos(int *arrAlumno, double *arrCredApro,
                                  double *arrCredDesa, double *arrCredFalt,
                                  int *arrCursosApro, int *arrCursosDesa,
                                  double *arrPromPond, int cantAlumnos,
                                  FILE *archAlumnos, FILE *archReporte){        
    imprimirCabeceraDeAlumnos(archReporte);
    ordenarAlumnosPorCantCursosApro(arrAlumno,arrCredApro,arrCredDesa,
            arrCredFalt,arrCursosApro,arrCursosDesa,arrPromPond,cantAlumnos);
    int cantAlumnosPasan=0, cantAlumnosNoPasan=0;
    char nombre[60];    
    for(int i=0; i<cantAlumnos; i++){           
        leerNombreDeAlumno(archAlumnos,arrAlumno[i],nombre);                
        fprintf(archReporte,"%2d) %-11d",i+1,arrAlumno[i]);
        fprintf(archReporte,"%s",nombre);
        fprintf(archReporte,"%d %10d",arrCursosApro[i],arrCursosDesa[i]);        
        if(arrPromPond[i]<PRECISION)
            fprintf(archReporte,"%15s","--.--");
        else
            fprintf(archReporte,"%15.2lf",arrPromPond[i]);        
        fprintf(archReporte,"%15.2lf %15.2lf",arrCredApro[i],arrCredDesa[i]);
        if(arrCredFalt[i]<PRECISION){
            fprintf(archReporte,"%10s\n","SI");
            cantAlumnosPasan++;
        }else{
            fprintf(archReporte,"%18s %.2lf %s\n","No, faltan",
                    arrCredFalt[i],"creditos");   
            cantAlumnosNoPasan++;
        }
    }
    imprimirResumenFinal(archReporte,cantAlumnosPasan,cantAlumnosNoPasan);
}

void imprimirCabeceraDeAlumnos(FILE *archReporte){    
    fprintf(archReporte,"%75s\n","INSTITUCION EDUCATIVA LIMA");
    fprintf(archReporte,"%73s\n","CONSOLIDADO DE ALUMNOS");
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"%10s %10s %25s %10s %15s %12s %12s %20s\n","CODIGO",
            "NOMBRE","CURSOS","CURSOS","PROMEDIO","CREDITOS","CREDITOS",
            "PASA A FACULTAD");
    fprintf(archReporte,"%50s %13s %10s %12s %15s\n","APROBADOS","DESAPROBADOS",
            "PONDERADO","APROBADOS","DESAPROBADOS");
    imprimirLinea(archReporte,'-',MAX_LINEA);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void ordenarAlumnosPorCantCursosApro(int *arrAlumno, double *arrCredApro,
                                     double *arrCredDesa, double *arrCredFalt,
                                     int *arrCursosApro, int *arrCursosDesa,
                                     double *arrPromPond, int cantAlumnos){    
    for(int i=0; i<cantAlumnos-1; i++)
        for(int j=i+1; j<cantAlumnos; j++)
            if(arrCursosApro[j]>arrCursosApro[i]){
                cambiarInt(arrAlumno,i,j);
                cambiarDouble(arrCredApro,i,j);
                cambiarDouble(arrCredDesa,i,j);
                cambiarDouble(arrCredFalt,i,j);
                cambiarInt(arrCursosApro,i,j);
                cambiarInt(arrCursosDesa,i,j);
                cambiarDouble(arrPromPond,i,j);
            }
}

void leerNombreDeAlumno(FILE *archAlumnos, int codigoAlumno, char *nombreMod){    
    rewind(archAlumnos);
    int alumno;
    char nombre[MAX_NOMBRE];
    while(1){        
        fscanf(archAlumnos,"%d",&alumno);
        if(feof(archAlumnos)) break;
        if(alumno==codigoAlumno){
            fscanf(archAlumnos,"%s",nombre);
            break;
        }else
            while(fgetc(archAlumnos)!='\n');
    }
    modificarNombreDeAlumno(nombre,nombreMod);
}

void modificarNombreDeAlumno(char *nombre, char *nombreMod){        
    //Llenamos de espacios en blanco
    int cantGuiones=0, i, j, centinela;
    for(i=0; i<MAX_NOMBRE; i++)
        nombreMod[i]=' ';
    nombreMod[i]=0;    
    //Leemos la cantidad de guiones    
    for(i=0; nombre[i]; i++)
        if(nombre[i]=='_') cantGuiones++;    
    //Saltamos los carácteres hasta el primer apellido
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
    //Llenamos con espacios en blanco
    for(i; i<MAX_NOMBRE; i++)
        nombreMod[i]=' ';      
}

char convertirMayusc(char c){
    return c-=(c>='a'&&c<='z'?'a'-'A':0);
}

char convertirMinusc(char c){
    return c+=(c>='A'&&c<='Z'?'a'-'A':0);
}

void imprimirResumenFinal(FILE *archReporte, int cantAlumnosPasan, int cantAlumnosNoPasan){
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"Cantidad de alumnos que pasaran a Facultad: %6d\n",
            cantAlumnosPasan);
    fprintf(archReporte,"Cantidad de alumnos que no pasaran a Facultad: %3d\n",
            cantAlumnosNoPasan);
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"TOTAL DE ALUMNOS MATRICULADOS EN EL CICLO: %7d\n",
            cantAlumnosNoPasan+cantAlumnosPasan);
    imprimirLinea(archReporte,'=',MAX_LINEA);    
}

void imprimirResultadosPorCurso(int *arrCurso, int *arrCantAproDeCurso,
                                int *arrCantDesaDeCurso, int cantCursos,
                                FILE *archCursos, FILE *archReporte){    
    imprimirCabeceraDeResultadosPorCurso(archReporte);
    for(int i=0; i<cantCursos; i++){        
        fprintf(archReporte,"%3d) %-7d",i+1,arrCurso[i]);
        imprimirNombreDelCurso(arrCurso[i],archCursos,archReporte);
        fprintf(archReporte,"%3d %15d\n",arrCantAproDeCurso[i],
                arrCantDesaDeCurso[i]);
    }
}

void imprimirCabeceraDeResultadosPorCurso(FILE *archReporte){
    fputc('\n',archReporte);
    fprintf(archReporte,"%52s\n","RESULTADOS POR CURSO");
    fprintf(archReporte,"%11s %7s %47s %16s\n","CODIGO","NOMBRE","APROBADOS",
            "DESAPROBADOS");    
}

void imprimirNombreDelCurso(int codCurso, FILE *archCursos, FILE *archReporte){    
    rewind(archCursos);
    int codigo;
    while(1){
        fscanf(archCursos,"%d",&codigo);
        if(feof(archCursos)) break;
        if(codigo==codCurso){
            leerNombreDelCurso(archCursos,archReporte);
            break;
        }else
            while(fgetc(archCursos)!='\n');
    }   
}

void leerNombreDelCurso(FILE *archCursos, FILE *archReporte){
    int i=0, j, cantChar=0, centinela=1;
    char palabra[MAX_PALABRA];    
    while(centinela){
        fscanf(archCursos,"%s",palabra);
        if(i==0) palabra[0]=' ';        
        for(j=0; palabra[j]; j++) cantChar++;       
        for(j=0; j<MAX_PALABRA; j++) 
            if(palabra[j]=='}'){
                palabra[j]=0;
                centinela=0;
            }
        fprintf(archReporte,"%s ",palabra);        
        i++;
    }        
    //Imprimimos espacios
    cantChar+=i;
    for(j=0; j<MAX_ESP-cantChar; j++) fputc(' ',archReporte);
}