/* 
 * Proyecto: PC2_2020-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 21 de abril de 2022, 05:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 110
#define NO_SE_ENCONTRO -1
#define PRECISION 0.0001

void procesarArchivos(FILE *archAlumnos, FILE *archNotas, FILE *archMatricula,
                      FILE *archResultadosAcademicos){
    
    fprintf(archResultadosAcademicos,"%75s\n",
            "RESULTADOS ACADÉMICOS DE LOS ALUMNOS");
    imprimirLinea(archResultadosAcademicos,'=',MAX_LINEA);
    imprimirResultadosAlumnos(archAlumnos,archNotas,archMatricula,
            archResultadosAcademicos);    
}

void imprimirResultadosAlumnos(FILE *archAlumnos, FILE *archNotas, 
                               FILE *archMatricula, FILE *archReporte){
    
    int codAlumno, anio, codFacultad, i=1, alumnosPromPonderadoAprob=0;
    double credAprobados, credDesaprobados; 
    
    while(1){
        
        fscanf(archAlumnos,"%d",&codAlumno);
        if(feof(archAlumnos)) break;
        fscanf(archAlumnos,"%d %d",&anio,&codFacultad);
        
        fscanf(archAlumnos,"%lf",&credAprobados);
        if(fgetc(archAlumnos)!='\n')
            fscanf(archAlumnos,"%lf",&credDesaprobados);
        else
            credDesaprobados=0;
        
        fprintf(archReporte,"%02d) %9s %04d %16s %04d %12s %07d %17s %5.1lf "
                "%20s %3.1lf\n",i,"Alumno:",codAlumno,"A. de Ingreso:",anio,
                "Facultad:",codFacultad,"Cred.aprobados:",credAprobados,
                "Cred.desaprobados:",credDesaprobados);
        imprimirLinea(archReporte,'-',MAX_LINEA);
        
        imprimirCursos(archReporte,archNotas,archMatricula,codAlumno,
                codFacultad,credAprobados,credDesaprobados,
                &alumnosPromPonderadoAprob);
        imprimirLinea(archReporte,'=',MAX_LINEA);
        i++;
    }
    imprimirDetallesFinales(archReporte,i-1,alumnosPromPonderadoAprob);
}

void imprimirCursos(FILE *archReporte, FILE *archNotas, FILE *archMatricula,
                    int codAlumno, int codFacultad, double credAprobados,
                    double credDesaprobados, int *alumnosPromPonderadoAprob){
    
    fprintf(archReporte,"%28s %44s\n","CURSOS APROBADOS","CURSOS DESAPROBADOS");
    fprintf(archReporte,"%s %7s %9s %7s %27s %9s %7s\n","No.","CODIGO",
            "CREDITOS","NOTA","CODIGO","CREDITOS","NOTA");
    imprimirLinea(archReporte,'-',MAX_LINEA);
    
    int codCurso, i=0, j=0;
    double credAproFacu=0, credDesaproFacu=0, credAproOtraFacu=0, 
            credDesaproOtraFacu=0, promedioPonderado=0;
    fscanf(archMatricula,"%*d");
    
    while(1){        
        fscanf(archMatricula,"%d",&codCurso);
        imprimirDetallesCurso(archReporte,archNotas,codAlumno,codCurso,
                codFacultad,&i,&j,&credAproFacu,&credDesaproFacu,
                &credAproOtraFacu,&credDesaproOtraFacu,&promedioPonderado);
        if(fgetc(archMatricula)=='\n') break;
    }   
    promedioPonderado/=(j+i);
    
    imprimirResumenes(archReporte,credAproFacu,credDesaproFacu,credAproOtraFacu,
            credDesaproOtraFacu,i,j,promedioPonderado,credAprobados,
            credDesaprobados);
    
    if(promedioPonderado>=11.0)
        (*alumnosPromPonderadoAprob)++;
}

void imprimirDetallesCurso(FILE *archReporte, FILE *archNotas,  int codAlumno,
                           int codCurso, int codFacultad, int *i, int *j,
                           double *credAproFacu, double *credDesaproFacu,
                           double *credAproOtraFacu, double *credDesaproOtraFacu,
                           double *promedioPonderado){
    
    rewind(archNotas);
    int codigoCurso, codigoFacultad;
    double numCreditos, nota;
    
    while(1){        
        
        fscanf(archNotas,"%d %d",&codigoCurso,&codigoFacultad);
        if(feof(archNotas)) break;
        
        if(codCurso==codigoCurso){        

            fscanf(archNotas,"%lf",&numCreditos); 
            nota = buscarNotaAlumno(archNotas,codAlumno);        
            (*promedioPonderado)+=nota;
            
            fprintf(archReporte,"%03d",(*i)+(*j)+1);            
            if(nota<11.0)
                    for(int k=0; k<46; k++) fputc(' ',archReporte);
            fprintf(archReporte,"%3c %3d %9.2lf %11.2lf\n",' ',
                        codCurso,numCreditos,nota);
                                
            if(codFacultad==codigoFacultad){                                
                if(nota<11.0)                    
                    (*credDesaproFacu)+=numCreditos;
                else
                    (*credAproFacu)+=numCreditos;
                (*i)++;                
            }else{                
                if(nota<11.0)                    
                    (*credDesaproOtraFacu)+=numCreditos;
                else
                    (*credAproOtraFacu)+=numCreditos;                
                (*j)++;
            }
            while(fgetc(archNotas)!='\n');
            break;
        }
        else
            while(fgetc(archNotas)!='\n');        
    }        
}

double buscarNotaAlumno(FILE *archNotas, int codAlumno){    
    int codigoAlumno;
    double nota;    
    while(1){
        fscanf(archNotas,"%d %lf",&codigoAlumno,&nota);
        if(codAlumno==codigoAlumno)
            return nota;
        if(fgetc(archNotas)=='\n') break;
    }
    return NO_SE_ENCONTRO;
}

void imprimirResumenes(FILE *archReporte, double credAproFacu,
                       double credDesaproFacu, double credAproOtraFacu, 
                       double credDesaproOtraFacu, int i, int j, 
                       double promedioPonderado, double creditosAprobados, 
                       double creditosDesaprobados){

    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"%15s\n","RESUMEN:");    
    
    //EN SU FACULTAD:
    double totalCredFacu = credAproFacu + credDesaproFacu;  
    fprintf(archReporte,"%22s\n","EN SU FACULTAD:");
    imprimirResumen(archReporte,i,totalCredFacu,credAproFacu,
                credDesaproFacu);
    
    //EN OTRA FACULTAD:
    double totalCredOtraFacu = credAproOtraFacu + credDesaproOtraFacu;
    fprintf(archReporte,"%24s\n","EN OTRA FACULTAD:");
    imprimirResumen(archReporte,j,totalCredOtraFacu,credAproOtraFacu,
            credDesaproOtraFacu);
    
    //PROMEDIO PONDERADO - CREDITOS APROBADOS Y DESAPROBADOS ACUMULADOS
    imprimirCreditosAcumuladosYPromedioDeNotas(archReporte,
            promedioPonderado,
            credAproFacu+credAproOtraFacu+creditosAprobados,
            credDesaproFacu+credDesaproOtraFacu+creditosDesaprobados);
}

void imprimirResumen(FILE *archReporte, int cursosMatriculados, double totalCred,
                     double credAprobados, double credDesaprobados){
    
    fprintf(archReporte,"%27s %2d %52s %11.1lf\n","Cursos matriculados:",
            cursosMatriculados,"Total de creditos matriculados:",totalCred);
    fprintf(archReporte,"%26s %7.1lf %39s %6.1lf\n","Creditos aprobados:",
            credAprobados,"Creditos desaprobados:",credDesaprobados);
    fprintf(archReporte,"%39s %7.1lf%%\n","Creditos aprobados/matriculados:",
            calcularPorcentaje(totalCred,credAprobados));
    imprimirLinea(archReporte,'-',MAX_LINEA);    
}

void imprimirCreditosAcumuladosYPromedioDeNotas(FILE *archReporte, 
                                                double promedioPonderado,
                                                double credAproAcumulados,
                                                double credDesaproAcumulados){    
    fprintf(archReporte,"%26s %20.2lf\n","Promedio ponderado:",
            promedioPonderado);
    fprintf(archReporte,"%36s %10.2lf\n","Credito aprobados acumulados:",
            credAproAcumulados);
    fprintf(archReporte,"%41s %6.2lf\n","Créditos desaprobados acumulados:",
            credDesaproAcumulados);    
}

double calcularPorcentaje(double total, double aprobados){
    if(total<PRECISION && aprobados<PRECISION) return 0.0;
    else return aprobados*100/total;
}

void imprimirDetallesFinales(FILE *archReporte, int cantAlumnosMatriculados,
                             int alumnosPromPondAprob){
    
    double porcAlumnosPonderadoAprob = calcularPorcentaje(cantAlumnosMatriculados,
            alumnosPromPondAprob);
    imprimirLinea(archReporte,'*',MAX_LINEA);
    fprintf(archReporte,"%49s %d\n","TOTAL DE ALUMNOS MATRICULADOS EN EL CICLO:",
            cantAlumnosMatriculados);
    fprintf(archReporte,"%61s %8.2lf%%\n","PORCENTAJE DE ALUMNOS CON PROMEDIO "
            "PONDERADO APROBADO:",porcAlumnosPonderadoAprob);
    fprintf(archReporte,"%64s %.2lf%%\n","PORCENTAJE DE ALUMNOS CON PROMEDIO "
            "PONDERADO DESAPROBADO:",100.0-porcAlumnosPonderadoAprob);
    imprimirLinea(archReporte,'*',MAX_LINEA);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void cerrarArchivos(FILE *archAlumnos, FILE *archNotas, FILE *archMatricula,
                    FILE *archResultadosAcademicos){
    fclose(archAlumnos);
    fclose(archNotas);
    fclose(archMatricula);
    fclose(archResultadosAcademicos);
}