/* 
 * Proyecto: PC2_2021-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 21 de abril de 2022, 10:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 120
#define MAX_ESPACIOS 60

void procesarArchivos(FILE *archAtencionesMedicas, FILE *archMedicos,
                      FILE *archReporteDeIngresos){
    
    fprintf(archReporteDeIngresos,"%70s\n","EMPRESA PRESTADORA DE SALUD");
    fprintf(archReporteDeIngresos,"%88s\n","LISTADO DE INGRESOS DE LOS MEDICOS"
            " E IMPUESTOS QUE DEBEN PAGAR");    
    imprimirMedicos(archAtencionesMedicas,archMedicos,archReporteDeIngresos);
}

void imprimirMedicos(FILE *archAtencionesMedicas, FILE *archMedicos,
                     FILE *archReporteDeIngresos){
    
    int codigo, cantLetras;
    double ingresosTotalDeTodosLosMedicos=0, totalDeImpuestosPagados=0, tarifa,
            remuneracionTotal, impuestoAPagar;    
    
    while(1){        
        
        fscanf(archMedicos,"%d",&codigo);
        if(feof(archMedicos)) break;        
        imprimirLinea(archReporteDeIngresos,'=',MAX_LINEA);
        fprintf(archReporteDeIngresos,"%14s %6c","Nombre:",' ');
        cantLetras = imprimirNombre(archMedicos,archReporteDeIngresos);
        imprimirEspacios(archReporteDeIngresos,cantLetras+9);
        
        fscanf(archMedicos,"%lf",&tarifa);        
        fprintf(archReporteDeIngresos,"%s %05d\n","Codigo:",codigo);
        
        fprintf(archReporteDeIngresos,"%20s ","Especialidad:");        
        cantLetras = imprimirEspecialidad(archReporteDeIngresos,archMedicos);
        imprimirEspacios(archReporteDeIngresos,cantLetras+13);
        
        fprintf(archReporteDeIngresos,"%15s %4.2lf %s\n","Tarifa: S/.",tarifa,
                "por minuto o fraccion");
        imprimirLinea(archReporteDeIngresos,'-',MAX_LINEA);
        
        remuneracionTotal=impuestoAPagar=0;
        imprimirRelacionDeConsultasRealizadas(archReporteDeIngresos,
                archAtencionesMedicas,&remuneracionTotal,codigo,tarifa);
        
        impuestoAPagar = calcularImpuestoAPagar(remuneracionTotal);
        ingresosTotalDeTodosLosMedicos += remuneracionTotal;           
        totalDeImpuestosPagados += impuestoAPagar;        
        imprimirRemuneracion(archReporteDeIngresos,remuneracionTotal,
                impuestoAPagar);
    }
    imprimirLinea(archReporteDeIngresos,'=',MAX_LINEA);
    imprimirDetallesFinales(archReporteDeIngresos,ingresosTotalDeTodosLosMedicos,
            totalDeImpuestosPagados);        
}

int imprimirNombre(FILE *archMedicos, FILE *archReporte){
    
    char letra, cantLetras=0, cantEspacios=0;
    while((letra=fgetc(archMedicos))==' ');
    fputc(letra,archReporte);
    
    while(1){             
        letra = fgetc(archMedicos);
        if(letra=='_'){
            fputc(' ',archReporte);
            letra = fgetc(archMedicos);
            fputc(letra,archReporte);   
            cantEspacios++;
        }else if(letra==' '){
            while((letra=fgetc(archMedicos))==' ');
            ungetc(letra,archMedicos);
            break;
        }else{
            letra = convertirMinuscula(letra);
            fputc(letra,archReporte);
        }    
        cantLetras++;
    }   
    return cantLetras+cantEspacios;
}

char convertirMinuscula(char letra){
    if(letra>='A'&&letra<='Z') return letra+=32;
    else return letra;
}

void imprimirEspacios(FILE *archReporteDeIngresos, int cantLetras){
    for(int i=0; i<MAX_ESPACIOS-cantLetras; i++)
        fputc(' ',archReporteDeIngresos);    
}

int imprimirEspecialidad(FILE *archReporteDeIngresos, FILE *archMedicos){    
    char letra, cantLetras=0;
    while((letra=fgetc(archMedicos))==' ');
    fputc(letra,archReporteDeIngresos);
    while((letra=fgetc(archMedicos))!='\n'){
        fputc(letra,archReporteDeIngresos);
        cantLetras++;
    }    
    return cantLetras;
}

void imprimirRelacionDeConsultasRealizadas(FILE *archReporteDeIngresos,
                                           FILE *archAtencionesMedicas,
                                           double *remuneracionTotal,
                                           int codigo, double tarifa){
    
    (*remuneracionTotal)=0;    
    int codigoMedico, dd, mm, aaaa;
    double montoPagado;
    fprintf(archReporteDeIngresos,"%73s\n","RELACION DE CONSULTAS REALIZADAS");
    fprintf(archReporteDeIngresos,"%13s %15s %12s %16s %15s %17s\n","FECHA",
            "INGRESO","SALIDA","DURACION","PACIENTE","MONTO PAGADO");
    imprimirLinea(archReporteDeIngresos,'-',MAX_LINEA);
    
    while(1){
        
        fscanf(archAtencionesMedicas,"%d",&codigoMedico);
        if(feof(archAtencionesMedicas)) break;
        
        if(codigo==codigoMedico){  
            montoPagado=0;
            fscanf(archAtencionesMedicas,"%d/%d/%d",&dd,&mm,&aaaa);
            imprimirConsultasPorFecha(archReporteDeIngresos,archAtencionesMedicas,
                    dd,mm,aaaa,tarifa,&montoPagado);            
            (*remuneracionTotal)+=montoPagado;
        }else
            while(fgetc(archAtencionesMedicas)!='\n');
    }
    rewind(archAtencionesMedicas);
}

void imprimirConsultasPorFecha(FILE *archReporteDeIngresos,
                               FILE *archAtencionesMedicas, int dd, int mm,
                               int aaaa, double tarifa, double *montoPagado){

    int dni, hIni, mIni, sIni, hFin, mFin, sFin;    
    while(1){
        fscanf(archAtencionesMedicas,"%d",&dni);
        leerHoras(archAtencionesMedicas,&hIni,&mIni,&sIni,&hFin,&mFin,&sFin);     
        imprimirDatos(archReporteDeIngresos,dd,mm,aaaa,hIni,mIni,sIni,hFin,mFin,
                sFin,dni,tarifa,montoPagado);
        if(fgetc(archAtencionesMedicas)=='\n') break;
    }
}

void leerHoras(FILE *archAtencionesMedicas, int *hIni, int *mIni, int *sIni,
               int *hFin, int *mFin, int *sFin){    
    leerHora(archAtencionesMedicas,hIni,mIni,sIni);
    leerHora(archAtencionesMedicas,hFin,mFin,sFin);        
}

void leerHora(FILE *archAtencionesMedicas, int *hora, int *minuto, int *segundo){
    int datosLeidos = fscanf(archAtencionesMedicas,"%d:%d:%d",hora,minuto,segundo);
    if(datosLeidos==2)
        *segundo=0;
    else if(datosLeidos==1){
        *segundo=0;
        *minuto=0;
    }
}

void imprimirDatos(FILE *archReporte, int dd, int mm, int aaaa, int hIni, 
                   int mIni, int sIni, int hFin, int mFin, int sFin, int dni, 
                   double tarifa, double *montoPagado){
    
    int mDuracion, sDuracion;
    calcularDuracion(hIni,mIni,sIni,hFin,mFin,sFin,&mDuracion,&sDuracion);
    double monto = calcularMontoPagado(tarifa,mDuracion,sDuracion);
    (*montoPagado) += monto;
        
    fprintf(archReporte,"%5c %02d/%02d/%04d %4c %02d:%02d:%02d %3c %02d:%02d:%02d",
            ' ',dd,mm,aaaa,' ',hIni,mIni,sIni,' ',hFin,mFin,sFin);
    fprintf(archReporte,"%9c %02d:%02d %7c %08d",' ',mDuracion,sDuracion,' ',dni); 
    fprintf(archReporte,"%15.2lf\n",monto);
}

int calcularDuracion(int hIni, int mIni, int sIni, int hFin, int mFin, int sFin, 
                     int *mDuracion, int *sDuracion){
    
    int duracion = duracionSeg(hFin,mFin,sFin)-duracionSeg(hIni,mIni,sIni);
    (*mDuracion) = duracion/60;
    (*sDuracion) = duracion-(*mDuracion)*60;
}

int duracionSeg(int hora, int minuto, int segundo){
    return hora*60*60 + minuto*60 + segundo;
}

double calcularMontoPagado(double tarifa, int mDuracion, int sDuracion){
    if(sDuracion>0.0) return tarifa*(mDuracion+1);
    else return tarifa*mDuracion;
}

double calcularImpuestoAPagar(double remuneracionTotal){ 
    
    if(remuneracionTotal<=5575.25)
        return calcularPorcentaje(remuneracionTotal,15.5);       
    else if(remuneracionTotal<=15685.83)
        return calcularPorcentaje(5575.25,15.5)+
                calcularPorcentaje(remuneracionTotal-5575.25,23.2);       
    else if(remuneracionTotal>15685.83)
        return calcularPorcentaje(5575.25,15.5)+
                calcularPorcentaje(15685.83,23.2)+
                calcularPorcentaje(remuneracionTotal-5575.25-15685.83,35.7);
}

double calcularPorcentaje(double remuneracionTotal, double porcentaje){
    return remuneracionTotal*porcentaje/100;
}

double imprimirRemuneracion(FILE *archReporteDeIngresos, double remuneracionTotal,
                            double impuestoAPagar){    
    imprimirLinea(archReporteDeIngresos,'-',MAX_LINEA);
    fprintf(archReporteDeIngresos,"REMUNERACION TOTAL RECIBIDA: %6s %7.2lf\n",
            "S/.",remuneracionTotal);
    fprintf(archReporteDeIngresos,"IMPUESTO A PAGAR: %17s %7.2lf\n",
            "S/.",impuestoAPagar);    
}

void imprimirDetallesFinales(FILE *archReporteDeIngresos, 
                             double ingresosTotalDeTodosLosMedicos,
                             double totalDeImpuestosPagados){
    
    fprintf(archReporteDeIngresos,"INGRESOS TOTAL DE TODOS LOS MEDICOS:  S/. "
            "%9.2lf\n",ingresosTotalDeTodosLosMedicos);
    fprintf(archReporteDeIngresos,"TOTAL DE IMPUESTOS PAGADOS: %9c S/. %9.2lf\n",
            ' ',totalDeImpuestosPagados);    
    imprimirLinea(archReporteDeIngresos,'=',MAX_LINEA);
}

void imprimirLinea(FILE *archReporte, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,archReporte);   
    fputc('\n',archReporte);
}

void cerrarArchivos(FILE *archAtencionesMedicas, FILE *archMedicos,
                    FILE *archReporteDeIngresos){
    fclose(archAtencionesMedicas);
    fclose(archMedicos);
    fclose(archReporteDeIngresos);    
}