/* 
 * Proyecto: LAB2_2020-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 22 de abril de 2022, 10:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 110
#define MAX_ESPACIOS 47
#define INVALIDO -1
#define PRECISION 0.0001

void imprimirInformacionAcademicaDeLosEstudiantes(){
    
    int codAlumno, anioIngreso, codFacultad, cantAlumnos=0;
    printf("%69s\n","INFORMACION ACADEMICA DE LOS ESTUDIANTES");
    
    while(1){        
        scanf("%4d",&codAlumno);
        if(feof(stdin)) break;
        scanf("%4d%d",&anioIngreso,&codFacultad);        
        imprimirLinea('=',MAX_LINEA);
        printf("%02d) %10s %04d %28s %4d %16s %07d\n",cantAlumnos+1,"Alumno:",
                codAlumno,"A. de Ingreso:",anioIngreso,"Facultad:",codFacultad);
        imprimirLinea('-',MAX_LINEA);
        imprimirListadoDeCursos(anioIngreso,codFacultad);
        cantAlumnos++;
    }
    imprimirTotalDeAlumnosRegistrados(cantAlumnos);
}

void imprimirListadoDeCursos(int anioIngreso, int codFacultad){
    
    printf("%28s %44s %32s\n","CURSOS APROBADOS","CURSOS DESAPROBADOS",
            "OBSERVACION");
    printf("%s %7s %9s %7s %11s %16s %9s %7s %11s\n","No.","CODIGO",
            "CREDITOS","NOTA","FECHA","CODIGO","CREDITOS","NOTA","FECHA");
    imprimirLinea('-',MAX_LINEA);
    
    int codCurso, codigoFacultad, nota, dd, mm, aaaa, i=1, centinela;
    double numCreditos;
    
    //VARIABLES PARA RESUMEN:
    int cursosMatriFacu, cursosMatriOtraFacu, cursosAproFacu, cursosAproOtraFacu,
            cursosErrorNoConsiderados, cursosErrorFecha, cursosErrorCred;
    double credAproFacu, credAproOtraFacu, credDesaproFacu, credDesaproOtraFacu,
            promGenFacu, promGenOtraFacu, promGenAproFacu, promGenAproOtraFacu;
    
    cursosMatriFacu=cursosMatriOtraFacu=cursosAproFacu=cursosAproOtraFacu=
            credAproFacu=credAproOtraFacu=credDesaproFacu=credDesaproOtraFacu=
            promGenFacu=promGenOtraFacu=promGenAproFacu=promGenAproOtraFacu=
            cursosErrorNoConsiderados=cursosErrorFecha=cursosErrorCred=0.0;    
    
    while(1){        
        scanf("%d-%d %lf %d",&codCurso,&codigoFacultad,&numCreditos,&nota);
        scanf("%d/%d/%d",&dd,&mm,&aaaa);        
        printf("%03d ",i);
        if(nota<11.0) imprimirEspacios();        
        printf("%2c %04d %7.2lf %8d %4c %04d/%02d/%02d",' ',codCurso,
                numCreditos,nota,' ',aaaa,mm,dd);
        imprimirObservacion(codigoFacultad,codFacultad,nota,aaaa,anioIngreso,
                numCreditos,&centinela,&cursosErrorNoConsiderados,
                &cursosErrorFecha,&cursosErrorCred);
        actualizarDatosDelResumen(numCreditos,nota,codigoFacultad,codFacultad,
                &cursosMatriFacu,&cursosMatriOtraFacu,&cursosAproFacu,
                &cursosAproOtraFacu,&credAproFacu,&credAproOtraFacu,
                &credDesaproFacu,&credDesaproOtraFacu,&promGenFacu,
                &promGenOtraFacu,&promGenAproFacu,&promGenAproOtraFacu,
                aaaa,anioIngreso);
        putchar('\n');
        if(getchar()=='\n') break;        
        centinela=0;
        i++;
    }
    imprimirResumen(cursosMatriFacu,cursosMatriOtraFacu,cursosAproFacu,
            cursosAproOtraFacu,credAproFacu,credAproOtraFacu,credDesaproFacu,
            credDesaproOtraFacu,promGenFacu,promGenOtraFacu,promGenAproFacu,
            promGenAproOtraFacu);
    imprimirErrores(cursosErrorNoConsiderados,cursosErrorFecha,cursosErrorCred);
}

void imprimirObservacion(int codigoFacultad, int codFacultad, int nota, int aaaa, 
                         int anioIngreso, double creditos, int *centinela,
                         int *cursosErrorNoConsiderados, int *cursosErrorFecha,
                         int *cursosErrorCred){
    
    int cursosConError=0, segundoCentinela=0;
    
    if(codigoFacultad!=codFacultad){
        if(nota>=11){
            imprimirEspacios();  
            (*centinela)=1;
        }
        segundoCentinela=1;
    }
    if((aaaa<anioIngreso)||(creditos<0.0)){
        if(nota>=11.0 && centinela==0) imprimirEspacios();
        printf("%18s","ERROR EN DATOS");
        if(aaaa<anioIngreso)
            (*cursosErrorFecha)++;
        if(creditos<0.0)
            (*cursosErrorCred)++;
        cursosConError=1;
    }else if(segundoCentinela)
        printf("%17s","OTRA FACULTAD");    
    if(cursosConError)
        (*cursosErrorNoConsiderados)++;
}

void actualizarDatosDelResumen(double numCreditos, int nota, int codigoFacultad,
                               int codFacultad, int *cursosMatriFacu, 
                               int *cursosMatriOtraFacu, int *cursosAproFacu,
                               int *cursosAproOtraFacu, double *credAproFacu,
                               double *credAproOtraFacu, double *credDesaproFacu,
                               double *credDesaproOtraFacu, double *promGenFacu,
                               double *promGenOtraFacu, double *promGenAproFacu,
                               double *promGenAproOtraFacu, int aaaa, int anio){    

    if(numCreditos<0.0||aaaa<anio) return;

    if(codigoFacultad==codFacultad){        //EN SU FACULTAD        
        if(nota>=11.0){
            (*credAproFacu)+=numCreditos;   
            (*cursosAproFacu)++;
            (*promGenAproFacu)+=nota;
        }else
            (*credDesaproFacu)+=numCreditos;            
        
        (*cursosMatriFacu)++;       
        (*promGenFacu)+=nota;
    }
    else{                                   //EN OTRA FACULTAD        
        if(nota>=11.0){
            (*credAproOtraFacu)+=numCreditos;   
            (*cursosAproOtraFacu)++;
            (*promGenAproOtraFacu)+=nota;
        }else
            (*credDesaproOtraFacu)+=numCreditos;            
        
        (*cursosMatriOtraFacu)++;       
        (*promGenOtraFacu)+=nota;
    }
}

void imprimirResumen(int cursosMatriFacu, int cursosMatriOtraFacu, 
                     int cursosAproFacu, int cursosAproOtraFacu, 
                     double credAproFacu, double credAproOtraFacu, 
                     double credDesaproFacu, double credDesaproOtraFacu, 
                     double promGenFacu, double promGenOtraFacu, 
                     double promGenAproFacu, double promGenAproOtraFacu){
    
    imprimirLinea('=',MAX_LINEA);
    printf("%15s\n","RESUMEN:");
    
    printf("%22s\n","EN SU FACULTAD:");    
    imprimirResumenIndividual(cursosMatriFacu,cursosAproFacu,credAproFacu,
            credDesaproFacu,promGenFacu,promGenAproFacu);    
    
    printf("%24s\n","EN OTRA FACULTAD:");    
    imprimirResumenIndividual(cursosMatriOtraFacu,cursosAproOtraFacu,
            credAproOtraFacu,credDesaproOtraFacu,promGenOtraFacu,
            promGenAproOtraFacu);    
}

void imprimirResumenIndividual(int cursosMatri, int cursosApro, double credApro,
                               double credDesapro, double promGen,
                               double promGenApro){
    
    int centinela=0;
    double credAproMatriculado, totalDeCreditos, promedioGen, promedioGenApro;
    totalDeCreditos = credApro+credDesapro;
    credAproMatriculado = calcularPromedio(totalDeCreditos,credApro);
    promedioGen = promGen/cursosMatri;
    promedioGenApro = promGenApro/cursosApro;
    
    if(credAproMatriculado<0.0)
        centinela=1;
    
    printf("%27s %2d","Cursos matriculados:",cursosMatri);    
    printf("%40s %12.2lf\n","Total de creditos:",totalDeCreditos);
    printf("%26s %6.2lf","Creditos aprobados:",credApro);    
    printf("%41s %8.2lf\n","Creditos desaprobados:",credDesapro);
    
    if(centinela)        
        printf("%39s %5s\n","Creditos aprobados/matriculados:","NA%");  
    else
        printf("%39s %5.2lf%%\n","Creditos aprobados/matriculados:",
                credAproMatriculado);    
    imprimirLinea('-',MAX_LINEA);
    
    if(centinela){
        printf("%24s %17s\n","Promedio general:","NA");
        printf("%37s %4s\n","Promedio general de aprobados:","NA");
    }else{
        printf("%24s %20.2lf\n","Promedio general:",promedioGen);
        printf("%37s %7.2lf\n","Promedio general de aprobados:",
                promedioGenApro);
    }
    imprimirLinea('-',MAX_LINEA);
}

double calcularPromedio(double totalDeCreditos, double credApro){
    if(totalDeCreditos<=PRECISION) return INVALIDO;
    else return 100.0*credApro/totalDeCreditos;
}

void imprimirErrores(int cursosErrorNoConsiderados, int cursosErrorFecha,
                     int cursosErrorCred){
    
    printf("%50s: %02d\n","Cursos con error que no fueron considerados",
            cursosErrorNoConsiderados);
    printf("%35s: %14c %02d\n","Cursos con error en la fecha",' ',
            cursosErrorFecha);
    printf("%40s: %10c %02d\n","Cursos con error en los créditos",' ',
            cursosErrorCred);
    imprimirLinea('=',MAX_LINEA);
}

void imprimirEspacios(){
    for(int i=0; i<MAX_ESPACIOS; i++) putchar(' ');    
}

void imprimirTotalDeAlumnosRegistrados(int cantAlumnos){    
    imprimirLinea('*',MAX_LINEA);
    printf("%35s %3d\n","TOTAL DE ALUMNOS REGISTRADOS:",cantAlumnos);
    imprimirLinea('*',MAX_LINEA);    
}

void imprimirLinea(char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) putchar(c);    
    putchar('\n');
}