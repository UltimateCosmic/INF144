/* 
 * Proyecto: LAB3_2020-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 9 de mayo de 2022, 01:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX 100
#define MAX_LINEA 85
#define MAX_LINEA_2 53
#define NO_SE_ENCONTRO -1

void procesarAtencionDePacientes(int *codigoMed, double *factorAtenc,
                                 double *codigoRes, int *pacAtend, int *pacRes,
                                 int *cantMed){
    FILE *arch;
    arch=fopen("AtencionDePacientes.txt","r");
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo AtenciónDePacientes.txt\n");
        exit(1);
    }
    leerAtencionDePacientes(codigoMed,factorAtenc,codigoRes,pacAtend,pacRes,
            cantMed,arch);
    fclose(arch);
}

void leerAtencionDePacientes(int *codigoMed, double *factorAtenc, double *codigoRes, 
                             int *pacAtend, int *pacRes, int *cantMed, FILE *arch){    
    *cantMed=0;
    while(1){        
        fscanf(arch,"%*d/%*d/%*d");
        if(feof(arch)) break;
        leerDatosDePacientes(codigoMed,factorAtenc,codigoRes,pacAtend,pacRes,
            cantMed,arch);
    }    
}

void leerDatosDePacientes(int *codigoMed, double *factorAtenc, double *codigoRes, 
                          int *pacAtend, int *pacRes, int *cantMed, FILE *arch){
    int codigoMedico;
    char estado;
    double factor;
    while(1){
        fscanf(arch," %c",&estado);
        saltarNombre(arch);
        fscanf(arch,"%lf %d",&factor,&codigoMedico);           
        if(factor>1.0) factor=1.0;  /* No tiene sentido que los factores sean
                                     * mayores a 1, hay un error en el .txt*/        
        asignatDatosDePacientes(codigoMed,factorAtenc,codigoRes,pacAtend,pacRes,
            cantMed,estado,factor,codigoMedico); 
        if(fgetc(arch)=='\n') break;
    }    
}

void saltarNombre(FILE *arch){
    while(fgetc(arch)==' ');
    while(fgetc(arch)!=' ');    
}

void asignatDatosDePacientes(int *codigoMed, double *factorAtenc, 
                             double *factorRes, int *pacAtend, int *pacRes, 
                             int *cantMed, char estado, double factor,
                             int codigoMedico){
    for(int i=0; i<MAX; i++){        
        if(codigoMed[i]==0||codigoMed[i]==codigoMedico){            
            if(codigoMed[i]==0)
                (*cantMed)++;
            codigoMed[i]=codigoMedico;
            if(estado=='A'){
                factorAtenc[i]+=factor;
                pacAtend[i]++;
            }
            else if(estado=='R'){
                factorRes[i]+=factor;
                pacRes[i]++;
            }            
            break;
        }
    }
}

void procesarReporteDeAtenciones(int *codigoMed, double *factorAtenc,
                                 double *factorRes, int *pacAtend,
                                 int *pacRes, int cantMed){
    FILE *arch;
    arch=fopen("ReporteDeAtenciones.txt","w");
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeAtenciones.txt\n");
        exit(1);
    }
    imprimirReporteDeAtenciones(codigoMed,factorAtenc,factorRes,pacAtend,pacRes,
            cantMed,arch);
    fclose(arch);
}

void imprimirReporteDeAtenciones(int *codigoMed, double *factorAtenc,
                                 double *factorRes, int *pacAtend,
                                 int *pacRes, int cantMed, FILE *arch){    
    imprimirCabeceraReporteDeAtenciones(arch);
    for(int i=0; i<cantMed; i++){        
        fprintf(arch,"%5c %06d",' ',codigoMed[i]);
        fprintf(arch,"%15.2lf %15.2lf",factorAtenc[i],factorRes[i]);
        fprintf(arch,"%14d %17d\n",pacAtend[i],pacRes[i]);        
    }
    imprimirLinea(arch,'=',MAX_LINEA);    
}

void imprimirCabeceraReporteDeAtenciones(FILE *arch){    
    fprintf(arch,"%54s\n","REPORTE DE ATENCIONES");
    imprimirLinea(arch,'=',MAX_LINEA);    
    fprintf(arch,"%15s %17s %15s %17s %15s\n","Cod.Médico","Fact.Atención",
            "Fact.Reserva","Num.Atenciones","Num.Reservas");
    imprimirLinea(arch,'-',MAX_LINEA);    
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);    
}

void procesarReporteDeMedicos(int *codigoMed, double *factorAtenc,
                              double *factorRes, int *pacAtend,
                              int *pacRes, int cantMed){
    FILE *archReporte, *archMedicos;
    archReporte=fopen("ReporteDeMedicos.txt","w");
    if(archReporte==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeMedicos.txt\n");
        exit(1);
    }
    archMedicos=fopen("Medicos.txt","r");
    if(archMedicos==NULL){
        printf("ERROR: No se pudo abrir el archivo Medicos.txt\n");
        exit(1);
    }
    imprimirReporteDeMedicos(codigoMed,factorAtenc,factorRes,pacAtend,pacRes,
            cantMed,archReporte,archMedicos);
    fclose(archReporte);
    fclose(archMedicos);   
}

void imprimirReporteDeMedicos(int *codigoMed, double *factorAtenc,
                              double *factorRes, int *pacAtend,
                              int *pacRes, int cantMed, FILE *archReporte,
                              FILE *archMedicos){
    int codigo;
    double tarifa;
    while(1){        
        fscanf(archMedicos,"%d",&codigo);
        if(feof(archMedicos)) break;
        imprimirDatosDelMedico(archMedicos,archReporte,codigo,&tarifa);
        imprimirArreglos(codigo,tarifa,codigoMed,factorAtenc,factorRes,pacAtend,
                pacRes,cantMed,archReporte);        
    }
}

void imprimirDatosDelMedico(FILE *archMedicos, FILE *archReporte, int codigo, 
                            double *tarifa){    
    fprintf(archReporte,"Médico: ");
    imprimirNombreDelMedico(archMedicos,archReporte);
    fprintf(archReporte,"Código: %06d\n",codigo);
    fprintf(archReporte,"Especialidad: ");
    imprimirEspecialidadDelMedico(archMedicos,archReporte);
    fscanf(archMedicos,"%lf",tarifa);
    fprintf(archReporte,"Honorarios por cita: %.2lf\n",*tarifa);
}

void imprimirNombreDelMedico(FILE *archMedicos, FILE *archReporte){    
    char c;
    while((c=fgetc(archMedicos))==' ');
    ungetc(c,archMedicos);
    while(1){
        c=fgetc(archMedicos);
        if(c==' ') break;
        else if(c=='/'||c=='-') fputc(' ',archReporte);
        else fputc(convertirMayusc(c),archReporte);        
    }    
    fputc('\n',archReporte);
}

char convertirMayusc(char c){
    if(c>='a'&&c<='z') return c-=32;
    else return c;
}

void imprimirEspecialidadDelMedico(FILE *archMedicos, FILE *archReporte){    
    char c;
    while((c=fgetc(archMedicos))==' ');
    while(c!=' '){
        fputc(c,archReporte);
        c=fgetc(archMedicos);        
    }
    fputc('\n',archReporte);
}

void imprimirArreglos(int codigo, double tarifa,int *codigoMed, 
                      double *factorAtenc, double *factorRes, int *pacAtend,
                      int *pacRes, int cantMed, FILE *archReporte){    
    
    /* Posiblemente los cálculos de los montos sean erroneos, 
     * (no hay mucha) aclaración en el problema*/
    imprimirLinea(archReporte,'-',MAX_LINEA_2);    
    int i=buscarIndice(codigo,codigoMed,cantMed);    
    if(i==NO_SE_ENCONTRO) return;
    
    double montoPacAt, montoSegAt;     
    montoPacAt = tarifa*factorAtenc[i];
    montoSegAt = montoPacAt*pacAtend[i]-montoPacAt;
    fprintf(archReporte,"Pacientes atendidos: %d\n",pacAtend[i]);
    imprimirMontos(archReporte,montoPacAt,montoSegAt); 
        
    double montoPacRe, montoSegRe;
    montoPacRe = tarifa*factorRes[i];
    montoSegRe = montoPacRe*pacRes[i]-montoPacRe;
    fprintf(archReporte,"Pacientes por atender: %d\n",pacRes[i]); 
    imprimirMontos(archReporte,montoPacRe,montoSegRe); 
    
    double totalIngresos = montoPacAt+montoSegAt+montoPacRe+montoSegRe;
    fprintf(archReporte,"Total de ingresos: %10.2lf\n",totalIngresos);
    imprimirLinea(archReporte,'=',MAX_LINEA_2);
}

int buscarIndice(int codigo, int *codigoMed, int cantMed){
    for(int i=0; i<cantMed; i++)
        if(codigo==codigoMed[i]) return i;
    return NO_SE_ENCONTRO;
}

void imprimirMontos(FILE *archReporte, double montoPac, 
                    double montoSeg){    
    imprimirLinea(archReporte,'-',MAX_LINEA_2);        
    fprintf(archReporte,"Monto total recibido por pacientes: %9.2lf\n",montoPac);
    fprintf(archReporte,"Monto a solicitar al seguro: %16.2lf\n",montoSeg);
    imprimirLinea(archReporte,'-',MAX_LINEA_2);    
}