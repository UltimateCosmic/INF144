/* 
 * Proyecto: LAB2_2021-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 25 de abril de 2022, 03:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 106
#define MAX_ESPACIOS 50

void procesarArchivos(FILE *archAlumnosNotas, FILE *archCursos, 
                      FILE *archReporteDeCursos){
    
    imprimirCabecera(archReporteDeCursos);
    int codEspecialidad, codCurso, totalCursosRegistrados=0, mayorAproCod, 
            mayorAproEsp;
    double mayorAproPorc=0;
    
    while(1){
        fscanf(archCursos,"%3d",&codEspecialidad);
        if(feof(archCursos)) break;
        fscanf(archCursos,"%3d",&codCurso);
        imprimirLinea(archReporteDeCursos,'=',MAX_LINEA);
        fprintf(archReporteDeCursos,"%02d) %9s ",
                totalCursosRegistrados+1,"Curso:");
        imprimirDetallesCurso(archCursos,archAlumnosNotas,archReporteDeCursos,
                codEspecialidad,codCurso,&mayorAproCod,
                &mayorAproEsp,&mayorAproPorc);
        totalCursosRegistrados++;
    }
    imprimirDatosFinales(archCursos,archReporteDeCursos,totalCursosRegistrados,
            mayorAproCod,mayorAproEsp,mayorAproPorc);
}

void imprimirCabecera(FILE *archReporte){    
    fprintf(archReporte,"%59s\n","INFORMACION ACADEMICA");
    fprintf(archReporte,"%73s\n","RELACION DE ALUMNOS QUE SE "
            "MATRICULARON POR CURSO");
}

void imprimirDetallesCurso(FILE *archCursos, FILE *archAlumnosNotas, 
                           FILE *archReporteDeCursos, int codEspecialidad, 
                           int codCurso, int *mayorAproCod, int *mayorAproEsp, 
                           double *mayorAproPorc){
    
    double creditos;
    fscanf(archCursos,"%lf",&creditos);
    imprimirNombreDelCurso(archCursos,archReporteDeCursos);
    fprintf(archReporteDeCursos,"%20s %03d %12s %4d %16s %.2lf\n",
            "Especialidad:",codEspecialidad,"Codigo:",codCurso,
            "Creditos:",creditos);
    imprimirLinea(archReporteDeCursos,'-',MAX_LINEA);
    imprimirRelacionDeAlumnos(archAlumnosNotas,archReporteDeCursos,codCurso,
            codEspecialidad,mayorAproCod,mayorAproEsp,mayorAproPorc);
}

void imprimirRelacionDeAlumnos(FILE *archAlumnosNotas, FILE *archReporteDeCursos,
                               int codCurso, int codEspecialidad, 
                               int *mayorAproCod, int *mayorAproEsp, 
                               double *mayorAproPorc){
    
    rewind(archAlumnosNotas);    
    fprintf(archReporteDeCursos,"%27s\n","RELACION DE ALUMNOS:");
    fprintf(archReporteDeCursos,"%10s %18s %9s %14s\n","No.","CODIGO DEL ALUMNO",
            "NOTA","FECHA");
    for(int j=0; j<7; j++) fputc(' ',archReporteDeCursos);
    imprimirLinea(archReporteDeCursos,'-',52);
    
    int anioIngreso, codigoEspecialidad, codAlumno, k=0, alumnosAprobados=0,
            notaMin=20, notaMax=0;
    while(1){        
        fscanf(archAlumnosNotas,"%3d",&anioIngreso);
        if(feof(archAlumnosNotas)) break;
        fscanf(archAlumnosNotas,"%3d%d",&codigoEspecialidad,&codAlumno);
        while(fgetc(archAlumnosNotas)!='\n');
        imprimirAlumnos(archAlumnosNotas,archReporteDeCursos,
                codEspecialidad,codCurso,anioIngreso,codigoEspecialidad,
                codAlumno,&k,&alumnosAprobados,&notaMax,&notaMin);   
    }    
    imprimirResumen(archReporteDeCursos,k,alumnosAprobados,k-alumnosAprobados,
            notaMax,notaMin,mayorAproCod,mayorAproEsp,mayorAproPorc,codCurso,
            codEspecialidad);
}

void imprimirAlumnos(FILE *archAlumnosNotas, FILE *archReporteDeCursos,
                     int codEspecialidad, int codCurso, int codAlumnoAnio, 
                     int codAlumnoEspecialidad, int codAlumno, int *k, 
                     int *alumnosAprobados, int *notaMax, int *notaMin){
    
    int codigoEspecialidad, codigoCurso, nota, dd, mm, aaaa;

    while(1){
        fscanf(archAlumnosNotas,"%3d",&codigoEspecialidad);
        if(codigoEspecialidad==0) break;
        fscanf(archAlumnosNotas,"%3d",&codigoCurso);
        
        if(codigoEspecialidad==codEspecialidad && codCurso==codigoCurso){            
            
            fscanf(archAlumnosNotas,"%d %d/%d/%d",&nota,&dd,&mm,&aaaa);           
            fprintf(archReporteDeCursos,"%6c %03d %8d%d%d",' ',*k+1,
                    codAlumnoAnio,codAlumnoEspecialidad,codAlumno);            
            imprimirEspacios(archReporteDeCursos,codAlumno);
            fprintf(archReporteDeCursos,"%02d %6c %04d/%02d/%02d\n",nota,
                    ' ',aaaa,mm,dd);
            
            if(nota>=11) (*alumnosAprobados)++;
            if(nota>*notaMax) *notaMax=nota;
            if(nota<*notaMin) *notaMin=nota;
            
            (*k)++;
        }else
            while(fgetc(archAlumnosNotas)!='\n');
    }
}

void imprimirEspacios(FILE *archReporteDeCursos, int codAlumno){    
    int cantDig = calcularCantDig(codAlumno);
    for(int i=0; i<MAX_ESPACIOS-cantDig-35; i++) fputc(' ',archReporteDeCursos);
}

int calcularCantDig(int codAlumno){    
    int cantDig = 0;    
    while(codAlumno!=0){        
        codAlumno/=10;
        cantDig++;        
    }
    return cantDig;
}

void imprimirResumen(FILE *archReporteDeCursos, int k, int alumnosAprobados,
                     int alumnosDesaprobados, int notaMax, int notaMin, 
                     int *mayorAproCod, int *mayorAproEsp, 
                     double *mayorAproPorc, int codigo, int especialidad){    
    
    double relacionAprobadosDesaprobados, porcApro, porcDesapro;    
    relacionAprobadosDesaprobados = calcularRelacion(alumnosAprobados,
            alumnosDesaprobados);
    porcApro = calcularPorcentaje(k,alumnosAprobados);
    porcDesapro = 100-porcApro;
    
    if(porcApro>=*mayorAproPorc){        
        *mayorAproPorc = porcApro;
        *mayorAproCod = codigo;
        *mayorAproEsp = especialidad;
    }    
    imprimirLinea(archReporteDeCursos,'=',MAX_LINEA);
    fprintf(archReporteDeCursos,"%15s\n","RESUMEN:");
    fprintf(archReporteDeCursos,"%46s %10d\n","Alumno matriculados de la "
            "especialidad:",k);
    fprintf(archReporteDeCursos,"%17s %39d %17.2lf%%\n","Aprobados:",
            alumnosAprobados,porcApro);
    fprintf(archReporteDeCursos,"%20s %36d %17.2lf%%\n","Desaprobados:",
            alumnosDesaprobados,porcDesapro);    
    fprintf(archReporteDeCursos,"%40s %37.4lf\n","Relación aprobados/"
            "desaprobados:",relacionAprobadosDesaprobados);
    fprintf(archReporteDeCursos,"%19s %34c %02d\n","Nota maxima:",' ',notaMax);
    fprintf(archReporteDeCursos,"%19s %34c %02d\n","Nota minima:",' ',notaMin);    
}

double calcularPorcentaje(int k, int alumnosAprobados){
    return (double)alumnosAprobados*100/k;    
}

double calcularRelacion(int aprobados, int desaprobados){
    if((aprobados==aprobados+desaprobados)||(desaprobados==aprobados+desaprobados))
        return 0.00;
    if(aprobados>=desaprobados) return (double)aprobados/desaprobados;
    else return (double)desaprobados/aprobados;
}

void imprimirNombreDelCurso(FILE *archCursos, FILE *archReporteDeCursos){    
    char c, cantEspacios=0;    
    while((c=fgetc(archCursos))==' ');
    fputc(c,archReporteDeCursos);
    while((c=fgetc(archCursos))!='\n'){
        fputc(c,archReporteDeCursos);
        cantEspacios++;
    }
    for(int i=0; i<MAX_ESPACIOS-cantEspacios-30; i++)
        fputc(' ',archReporteDeCursos);
}

void imprimirDatosFinales(FILE *archCursos,FILE *archReporteDeCursos, 
                          int totalCursos, int codCurso, int codEsp, 
                          double porcAprobados){    
    imprimirLinea(archReporteDeCursos,'=',MAX_LINEA);    
    imprimirLinea(archReporteDeCursos,'*',MAX_LINEA);    
    fprintf(archReporteDeCursos,"%34s %d\n","TOTAL DE Cursos REGISTRADOS:",
            totalCursos);
    fprintf(archReporteDeCursos,"%46s\n %3c","CURSO CON MAYOR PORCENTAJE "
            "DE APROBADOS:",' ');
    imprimirNombreCurso(archCursos,archReporteDeCursos,codCurso,codEsp);
    fprintf(archReporteDeCursos,"%24s %d %11s %d %18s %.2lf%%\n","Especialidad:",
            codEsp,"Codigo:",codCurso,"Aprobados:",porcAprobados);
    imprimirLinea(archReporteDeCursos,'*',MAX_LINEA);    
}

void imprimirNombreCurso(FILE *archCursos, FILE *archReporteDeCursos, 
                         int codCurso, int codEsp){
    rewind(archCursos);
    int curso, especialidad, c;
    while(1){
        fscanf(archCursos,"%3d",&especialidad);
        if(feof(archCursos)) break;
        fscanf(archCursos,"%3d",&curso);        
        if(codCurso==curso && codEsp==especialidad){
            fscanf(archCursos,"%*lf");
            while((c=fgetc(archCursos))!='\n')
                fputc(c,archReporteDeCursos);        
            break;
        }else
            while(fgetc(archCursos)!='\n');        
    }    
}

void imprimirLinea(FILE *archReporte, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,archReporte);
    fputc('\n',archReporte);
}

void cerrarArchivos(FILE *archAlumnosNotas, FILE *archCursos, 
                    FILE *archReporteDeCursos){
    fclose(archAlumnosNotas);
    fclose(archCursos);
    fclose(archReporteDeCursos);
}