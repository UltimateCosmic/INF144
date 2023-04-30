/* 
 * Proyecto: PC1_2021-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 15 de abril de 2022, 08:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 150
#define PRECISION 0.0001

void imprimirLinea(char caracter, int cantVeces){    
    for(int i=0; i<cantVeces; i++) putchar(caracter);
    putchar('\n');    
}

void imprimirInformacionAcademica(int *totalDeAlumnosRegistrados){
    
    int codigo, anioDeIngreso;    
    while(1){
        scanf("%d",&codigo);
        if(feof(stdin)) break;
        scanf("-%d",&anioDeIngreso);
        imprimirNombreYCodigo(codigo,anioDeIngreso);
        imprimirCursosYResumen(anioDeIngreso);
        (*totalDeAlumnosRegistrados)++;
    }
    imprimirLinea('=',MAX_LINEA);
}

void imprimirNombreYCodigo(int codigo, int anioDeIngreso){
    imprimirLinea('=',MAX_LINEA);        
    printf("%24s","Alumno: ");
    imprimirNombreDelEstudiante();        
    printf("%24s %04d - %06d\n","Codigo:",anioDeIngreso,codigo);
    imprimirLinea('-',MAX_LINEA);    
}

void imprimirNombreDelEstudiante(){   
    char letra;
    while(1){            
        letra = getchar();            
        if(letra=='\n') break;
        else if(letra=='/'||letra=='-') putchar(' ');
        else if(letra!=' ') putchar(letra);            
    }
}

void imprimirCursosYResumen(int anioDeIngreso){
    
    printf("%32s %61s %34s\n","CURSOS APROBADOS","CURSOS DESAPROBADOS",
            "OBSERVACION");        
    printf("%s %9s %11s %8s %10s %26s %11s %8s %10s\n","No.","CODIGO",
            "CREDITOS","NOTA","FECHA","CODIGO","CREDITOS","NOTA","FECHA");
    imprimirLinea('-',MAX_LINEA);
    
    int cursosMatriculados=0, cursosConErrorNoConsiderados=0;
    double creditosAprobados=0, creditosDesaprobados=0, totalDeCreditos=0, 
            creditosAprobadosMatriculados=0, promedioGeneral=0, 
            promedioGeneralDeAprobados=0;
    
    imprimirCursos(&cursosMatriculados,&creditosAprobados,&creditosDesaprobados,
            &totalDeCreditos,&creditosAprobadosMatriculados,&promedioGeneral,
            &promedioGeneralDeAprobados,&cursosConErrorNoConsiderados,
            anioDeIngreso);
    imprimirResumen(cursosMatriculados,creditosAprobados,creditosDesaprobados,
            totalDeCreditos,creditosAprobadosMatriculados,promedioGeneral,
            promedioGeneralDeAprobados,cursosConErrorNoConsiderados);
}

void imprimirCursos(int *cursosMatriculados, double *creditosAprobados, 
                    double *creditosDesaprobados, double *totalDeCreditos,
                    double *creditosAprobadosMatriculados,
                    double *promedioGeneral, double *promedioGeneralDeAprobados,
                    int *cursosConErrorNoConsiderados, int anioDeIngreso){
    
    double creditos;
    int nota, dd, mm, aaaa, i=1, j=0;
    
    while(1){
        
        scanf("%lf",&creditos);
        if(creditos<PRECISION) break;
        scanf("%d",&nota);
        scanf("%d/%d/%d",&dd,&mm,&aaaa);
                     
        printf("%03d",i);
        if(nota<11){
            printf("%59c",' '); //Curso desapr.
            (*creditosDesaprobados)+=creditos;
        } 
        imprimirCodigoDelCurso();        
        printf("%10.2lf %7c%02d",creditos,' ',nota);        
        printf("%4c %04d/%02d/%02d",' ',aaaa,mm,dd);
        
        if(nota>=11){
            printf("%59c",' ');
            (*creditosAprobados)+=creditos;
            (*promedioGeneralDeAprobados)+=nota;
            j++;
        }
        if(anioDeIngreso<aaaa){
            printf("%22s\n","ERROR FECHA");//Observacion 
            (*cursosConErrorNoConsiderados)++;
        }
        else putchar('\n');
        i++; 
        (*promedioGeneral)+=nota;
    }
    (*totalDeCreditos)=(*creditosAprobados)+(*creditosDesaprobados);
    (*cursosMatriculados)=(i-1)-(*cursosConErrorNoConsiderados);   
    (*creditosAprobadosMatriculados);
    (*promedioGeneral)/=(*cursosMatriculados);
    (*promedioGeneralDeAprobados)/=j;
    (*creditosAprobadosMatriculados) = ((*creditosAprobados)*100)/
            ((*creditosAprobados)+(*creditosDesaprobados));
}

void imprimirCodigoDelCurso(){    
    char letra;    
    while((letra=getchar())!='\n') putchar(letra);   
}

void imprimirResumen(int cursosMatriculados, double creditosAprobados, 
                     double creditosDesaprobados, double totalDeCreditos,
                     double creditosAprobadosMatriculados, 
                     double promedioGeneral, double promedioGeneralDeAprobados,
                     int cursosConErrorNoConsiderados){
    
    imprimirLinea('=',MAX_LINEA);
    printf("RESUMEN:\n");
    printf("%s %02d %53s %10.2lf\n","Cursos matriculados: ",cursosMatriculados,
            "Total de creditos:",totalDeCreditos);
    printf("%s %7.2lf %54s %6.2lf\n","Creditos aprobados:",creditosAprobados,
            "Creditos desaprobados:",creditosDesaprobados);
    printf("Creditos aprobados/matriculados: %3.2lf%%\n",
            creditosAprobadosMatriculados);
    
    imprimirLinea('-',MAX_LINEA);
    printf("Promedio general: %20.2lf\n",promedioGeneral);    
    printf("Promedio general de aprobados: %7.2lf\n",
            promedioGeneralDeAprobados);
    
    imprimirLinea('-',MAX_LINEA);
    printf("Cursos con error no considerados: %02d\n",
            cursosConErrorNoConsiderados);
}