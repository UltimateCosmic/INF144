/* 
 * Proyecto: LAB1_2020-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de abril de 2022, 11:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FuncionesAuxiliares.h"
#define MAX 100
#define MAX_LINEA 83
#define NO_SE_ENCONTRO -1
#define PRECISION 0.1

void leerArrArchAsistenciaClases(int *arrCodCurso, int *arrCantHorarios,
                                 double *arrPromPonderado, int *arrCantAlumnos,
                                 int *cantCursos, int anio, int ciclo){    
    FILE *archAsistenciaClases;
    archAsistenciaClases = fopen("Asistencia_clases.txt","r");
    if(archAsistenciaClases==NULL){
        printf("ERROR: No se pudo abrir el archivo Asistencia_clases.txt\n");
        exit(1);        
    }
    lecturaDeCursos(archAsistenciaClases,arrCodCurso,arrCantHorarios,
            arrPromPonderado,arrCantAlumnos,cantCursos,anio,ciclo);
    fclose(archAsistenciaClases);
}

void lecturaDeCursos(FILE *archAsistenciaClases, int *arrCodCurso, 
                     int *arrCantHorarios, double *arrPromPonderado, 
                     int *arrCantAlumnos, int *cantCursos, int anio, int ciclo){    
    int anioCurso, cicloCurso, codCurso, cantAlumnos;
    double porcAsistencia;    
    while(1){        
        fscanf(archAsistenciaClases,"%d %d",&anioCurso,&cicloCurso);
        if(feof(archAsistenciaClases)) break;        
        if(anioCurso==anio && cicloCurso==ciclo){            
            fscanf(archAsistenciaClases,"%d %*d %d %lf",&codCurso,
                    &cantAlumnos,&porcAsistencia);
            verificarRepeticionDeCurso(codCurso,arrCodCurso,arrCantHorarios,
                    arrPromPonderado,arrCantAlumnos,cantCursos,cantAlumnos,
                    porcAsistencia);            
        }else
            while(fgetc(archAsistenciaClases)!='\n');
    }    
    for(int i=0; i<(*cantCursos); i++)
        arrPromPonderado[i]/=arrCantAlumnos[i];
}

void verificarRepeticionDeCurso(int codCurso, int *arrCodCurso, 
                                int *arrCantHorarios, double *arrPromPonderado, 
                                int *arrCantAlumnos, int *cantCursos, 
                                int cantAlumnos, double porcAsistencia){    
    for(int j=0; j<MAX; j++){        
        if(arrCodCurso[j]==0||arrCodCurso[j]==codCurso){            
            arrCantHorarios[j]++;
            arrCantAlumnos[j]+=cantAlumnos; 
            arrPromPonderado[j]+=porcAsistencia*cantAlumnos;
            if(arrCodCurso[j]==0){
                (*cantCursos)++;
                arrCodCurso[j]=codCurso;
            }
            break;
        }
    }    
}

void leerArrArchEncuestasAlumnos(int anio, int ciclo, double *arrPromEncuesta,
                                 double *arrPorcEncuestaAjust, int cantCursos,
                                 int *arrCodCurso){    
    FILE *archEncuestasAlumnos;
    archEncuestasAlumnos = fopen("Encuestas_Alumnos.txt","r");
    if(archEncuestasAlumnos==NULL){
        printf("ERROR: No se pudo abrir el archivo Encuestas_Alumnos.txt\n");
        exit(1);        
    }
    lecturaDeEncuestas(archEncuestasAlumnos,anio,ciclo,arrPromEncuesta,
                       cantCursos,arrCodCurso);
    fclose(archEncuestasAlumnos);    
}

void lecturaDeEncuestas(FILE *archEncuestasAlumnos, int anio, int ciclo,
                        double *arrPromEncuesta, int cantCursos, 
                        int *arrCodCurso){    
    int anioEncuesta, cicloEncuesta;
    while(1){        
        fscanf(archEncuestasAlumnos,"%d %d",&anioEncuesta,&cicloEncuesta);
        if(feof(archEncuestasAlumnos)) break;
        if(anioEncuesta==anio && cicloEncuesta==ciclo)
            verificarDatosEncuesta(archEncuestasAlumnos,arrPromEncuesta,
                    cantCursos,arrCodCurso);            
        else
            while(fgetc(archEncuestasAlumnos)!='\n');
    }
}

void verificarDatosEncuesta(FILE *archEncuestasAlumnos, double *arrPromEncuesta,
                            int cantCursos, int *arrCodCurso){    
    int codCurso, i, cantValoresEncuesta=0;
    double valorEncuesta;
    fscanf(archEncuestasAlumnos,"%d %*d %*d/%*d/%*d",&codCurso); 
    i=buscarIndice(codCurso,arrCodCurso,cantCursos);
    if(i==NO_SE_ENCONTRO) return;
    while(1){
        fscanf(archEncuestasAlumnos,"%lf",&valorEncuesta);
        if(valorEncuesta<=100.0){
            arrPromEncuesta[i]+=valorEncuesta;
            cantValoresEncuesta++;
        }
        if(fgetc(archEncuestasAlumnos)=='\n') break;            
    }
    arrPromEncuesta[i]/=cantValoresEncuesta;    
}

int buscarIndice(int codCurso, int *arrCodCurso, int cantCursos){
    for(int i=0; i<cantCursos; i++)
        if(codCurso==arrCodCurso[i]) return i;
    return NO_SE_ENCONTRO;
}

void calcularPorcEncuestaAjustada(double *arrPorcEncuestaAjust, int cantCursos,
                                  double *arrPromPonderado, 
                                  double *arrPromEncuesta){    
    for(int i=0; i<cantCursos; i++)
        arrPorcEncuestaAjust[i]=arrPromEncuesta[i]*
                calcularFactor(arrPromPonderado[i]);
}

double calcularFactor(double promPondAsistencia){    
    if(promPondAsistencia>=90) return 1.0;
    else if(promPondAsistencia>=80 && promPondAsistencia<90) return 1.05;
    else if(promPondAsistencia>=70 && promPondAsistencia<80) return 1.08;
    else if(promPondAsistencia>=60 && promPondAsistencia<70) return 1.11;
    else if(promPondAsistencia>=50 && promPondAsistencia<60) return 1.13;
    else if(promPondAsistencia<50) return 0;    
}

void ordenarArreglos(int *arrCodCurso, int *arrCantHorarios, int *arrCantAlumnos,
                     double *arrPromPonderado, double *arrPromEncuesta,
                     double *arrPorcEncuestaAjust, int cantCursos){    
    for(int i=0; i<cantCursos; i++)
        for(int j=0, k=1; k<cantCursos; j++, k++)
            if(arrPorcEncuestaAjust[j]<arrPorcEncuestaAjust[k])
                cambiarValores(arrCodCurso,arrCantHorarios,arrCantAlumnos,
                        arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
                        j,k);      
    ordenarPorPromedioaDeAsistencia(arrCodCurso,arrCantHorarios,arrCantAlumnos,
                        arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
                        cantCursos);
}

void cambiarValores(int *arrCodCurso, int *arrCantHorarios, int *arrCantAlumnos,
                    double *arrPromPonderado, double *arrPromEncuesta,
                    double *arrPorcEncuestaAjust, int j, int k){ 
    //Cambio de datos entre arreglos de tipo int
    cambiarInt(&arrCodCurso[j],&arrCodCurso[k]);
    cambiarInt(&arrCantHorarios[j],&arrCantHorarios[k]);
    cambiarInt(&arrCantAlumnos[j],&arrCantAlumnos[k]);
    //Cambio de datos entre arreglos de tipo double
    cambiarDouble(&arrPromPonderado[j],&arrPromPonderado[k]);
    cambiarDouble(&arrPromEncuesta[j],&arrPromEncuesta[k]);
    cambiarDouble(&arrPorcEncuestaAjust[j],&arrPorcEncuestaAjust[k]);
}

void ordenarPorPromedioaDeAsistencia(int *arrCodCurso, int *arrCantHorarios,
                                     int *arrCantAlumnos, double *arrPromPonderado,
                                     double *arrPromEncuesta,
                                     double *arrPorcEncuestaAjust, 
                                     int cantCursos){    
    for(int i=0; i<cantCursos; i++)
        for(int j=0, k=1; k<cantCursos; j++, k++)
            if(arrPromPonderado[j]<arrPromPonderado[k] && 
                    abs(arrPorcEncuestaAjust[j]-arrPorcEncuestaAjust[k])<PRECISION)
                cambiarValores(arrCodCurso,arrCantHorarios,arrCantAlumnos,
                        arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
                        j,k);    
    ordenarPorNumHorarios(arrCodCurso,arrCantHorarios,arrCantAlumnos,
                        arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
                        cantCursos);
}

void ordenarPorNumHorarios(int *arrCodCurso, int *arrCantHorarios,
                           int *arrCantAlumnos, double *arrPromPonderado,
                           double *arrPromEncuesta, double *arrPorcEncuestaAjust, 
                           int cantCursos){    
    for(int i=0; i<cantCursos; i++)
        for(int j=0, k=1; k<cantCursos; j++, k++)
            if(arrCantHorarios[j]>arrCantHorarios[k] && 
                    abs(arrPromPonderado[j]-arrPromPonderado[k])<PRECISION)
                cambiarValores(arrCodCurso,arrCantHorarios,arrCantAlumnos,
                        arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
                        j,k);
}

void cambiarInt(int *a, int *b){
    int temp = *a;
    *a = *b; *b = temp;    
}

void cambiarDouble(double *a, double *b){
    double temp = *a;
    *a = *b; *b = temp;    
}

void abrirReporte(int *arrCodCurso, int *arrCantHorarios, int *arrCantAlumnos,
                  double *arrPromPonderado, double *arrPromEncuesta,
                  double *arrPorcEncuestaAjust, int cantCursos, int anio,
                  int ciclo){    
    FILE *archReporteResumenAsistencia;
    archReporteResumenAsistencia=fopen("Resumen_Asistencia_Encuesta.txt","w");
    if(archReporteResumenAsistencia==NULL){
        printf("ERROR: No se pudo abrir el archivo Resumen_Asistencia_Encuesta"
                ".txt\n");        
        exit(1);
    }
    imprimirReporte(archReporteResumenAsistencia,arrCodCurso,arrCantHorarios,
            arrCantAlumnos,arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
            cantCursos,anio,ciclo); 
    fclose(archReporteResumenAsistencia);    
}

void imprimirReporte(FILE *archReporteResumenAsistencia, int *arrCodCurso, 
                     int *arrCantHorarios, int *arrCantAlumnos,
                     double *arrPromPonderado, double *arrPromEncuesta,
                     double *arrPorcEncuestaAjust, int cantCursos, int anio,
                     int ciclo){        
    imprimirCabecera(archReporteResumenAsistencia,anio,ciclo);
    imprimirArreglos(archReporteResumenAsistencia,arrCodCurso,arrCantHorarios,
            arrCantAlumnos,arrPromPonderado,arrPromEncuesta,arrPorcEncuestaAjust,
            cantCursos);
    imprimirLinea(archReporteResumenAsistencia,'=',MAX_LINEA);
}

void imprimirCabecera(FILE *archReporteResumenAsistencia, int anio, int ciclo){    
    fprintf(archReporteResumenAsistencia,"RESUMEN DE LA ASISTENCIA Y ENCUESTA "
            "DE ALUMNOS POR CURSO\n");
    fprintf(archReporteResumenAsistencia,"%s %6d %11s %d\n","ANIO:",anio,
            "CICLO:",ciclo);
    imprimirLinea(archReporteResumenAsistencia,'=',MAX_LINEA);
    fprintf(archReporteResumenAsistencia,"%s %8s %9s %15s %18s %23s\n","CURSO",
            "ALUMNOS","HORARIOS","ASISTENCIA (%)","ENCUESTA REAL (%)",
            "ENCUESTA AJUSTADA (%)");
    imprimirLinea(archReporteResumenAsistencia,'=',MAX_LINEA);
}

void imprimirArreglos(FILE *archReporteResumenAsistencia, int *arrCodCurso,
                      int *arrCantHorarios, int *arrCantAlumnos,
                      double *arrPromPonderado, double *arrPromEncuesta,
                      double *arrPorcEncuestaAjust, int cantCursos){    
    for(int i=0; i<cantCursos; i++)
        fprintf(archReporteResumenAsistencia,"%05d %6d %6d %13.1lf%% %16.1lf%% "
                "%18.1lf%%\n",arrCodCurso[i],arrCantAlumnos[i],arrCantHorarios[i],
                arrPromPonderado[i],arrPromEncuesta[i],arrPorcEncuestaAjust[i]);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}