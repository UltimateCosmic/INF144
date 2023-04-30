/* 
 * Proyecto: PC2_2019-1_2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 20 de abril de 2022, 06:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 67

void imprimirReporte(FILE *archConsultasMedicas, FILE *archReporteDeConsultas){
    
    int dni;
    double monto;
    fprintf(archReporteDeConsultas,"Reporte de consultas:\n");
    
    while(1){
        fscanf(archConsultasMedicas,"%d",&dni);
        if(feof(archConsultasMedicas)) break;
        fscanf(archConsultasMedicas,"%lf",&monto);
        fprintf(archReporteDeConsultas,"DNI del Médico:  %08d\n",dni);
        fprintf(archReporteDeConsultas,"Costo por consulta por minuto: %6.2lf\n",monto);
        imprimirLinea(archReporteDeConsultas,'=',MAX_LINEA);
        imprimirConsultas(archConsultasMedicas,archReporteDeConsultas,monto);
    }
}

void imprimirConsultas(FILE *archConsultasMedicas, FILE *archReporte, double monto){
    
    fprintf(archReporte,"%s %26s %17s %17s\n","Fecha","Número de consultas",
            "Tiempo efectivo","Monto recaudado");
    
    int dd, mm, aaaa, promedioTiempoEfectivo=0, contador=0, maxConsultaFecha, 
            maxConsultaTotal=0, maxTiempoFecha, maxTiempoTotal=0;
    double promedioConsultasDiario=0, montoPagoAlSeguro=0;
    
    while(1){        
        fscanf(archConsultasMedicas,"%d/%d/%d",&dd,&mm,&aaaa);
        if(dd==0) break;
        imprimirConsultaPorFecha(archConsultasMedicas,archReporte,dd,mm,aaaa,
                monto,&montoPagoAlSeguro,&promedioConsultasDiario,
                &promedioTiempoEfectivo,&maxConsultaFecha,&maxConsultaTotal,
                &maxTiempoFecha,&maxTiempoTotal);
        contador++;
    }
    imprimirLinea(archReporte,'=',MAX_LINEA);
    promedioConsultasDiario /= contador;
    promedioTiempoEfectivo /= contador;
    imprimirEstadisticas(archReporte,montoPagoAlSeguro,promedioConsultasDiario,
            promedioTiempoEfectivo);
    imprimirMaximosObtenidos(archReporte,maxConsultaFecha,maxConsultaTotal,
            maxTiempoFecha,maxTiempoTotal);
}

void imprimirConsultaPorFecha(FILE *archConsultasMedicas, FILE *archReporte,
                              int dd, int mm, int aaaa, double monto,
                              double *montoPagoAlSeguro, 
                              double *promedioConsultasDiario,
                              int *promedioTiempoEfectivo, 
                              int *maxConsultaFecha, int *maxConsultaTotal,
                              int *maxTiempoFecha, int *maxTiempoTotal){
    
    int hIni, mIni, sIni, hFin, mFin, sFin, numConsultas=1, 
            hEfectivo, mEfectivo, sEfectivo, duracionTotalSegundos=0, 
            duracionConsulta;
    double montoRecaudado=0, porcentajePago;
    
    while(1){
        
        fscanf(archConsultasMedicas,"%d:%d:%d",&hIni,&mIni,&sIni);
        fscanf(archConsultasMedicas,"%d:%d:%d",&hFin,&mFin,&sFin);
        fscanf(archConsultasMedicas,"%lf",&porcentajePago);
        if(fgetc(archConsultasMedicas)=='\n') break; 
        duracionConsulta = duracion(hFin,mFin,sFin)-duracion(hIni,mIni,sIni);
        duracionTotalSegundos += duracionConsulta;
        montoRecaudado += calcularMonto(duracionConsulta,monto,porcentajePago);
        numConsultas++;       
    }    
    calcularTiempoEfectivo(duracionTotalSegundos,&hEfectivo,&mEfectivo,&sEfectivo);    
    fprintf(archReporte,"%02d/%02d/%04d %9d %13c %2dh %2dm %2ds %14.2lf\n",
            dd,mm,aaaa,numConsultas,' ',hEfectivo,mEfectivo,sEfectivo,
            montoRecaudado);
        
    (*montoPagoAlSeguro) += montoRecaudado; 
    (*promedioConsultasDiario) += numConsultas;
    (*promedioTiempoEfectivo) += duracionTotalSegundos;
    
    if(duracionTotalSegundos>=(*maxTiempoTotal)){
        (*maxTiempoTotal) = duracionTotalSegundos;
        (*maxTiempoFecha) = juntarFecha(dd,mm,aaaa);            
    }    
    if(numConsultas>=(*maxConsultaTotal)){
        (*maxConsultaTotal) = numConsultas;
        (*maxConsultaFecha) = juntarFecha(dd,mm,aaaa);
    }    
}

int duracion(int hora, int minuto, int segundo){
    return hora*60*60 + minuto*60 + segundo;
}

double calcularMonto(int duracionConsulta, double monto, double porcentajePago){    
    int hora, minuto, segundo;
    calcularTiempoEfectivo(duracionConsulta,&hora,&minuto,&segundo);
    double pago = monto*(hora*60+minuto);
    return calcularPorcentaje(pago,porcentajePago);
}

int juntarFecha(int dd, int mm, int aaaa){
    return aaaa*10000+mm*100+dd;        
}

double calcularPorcentaje(double pago, double porcentajePago){
    return pago*porcentajePago/100;    
}

void calcularTiempoEfectivo(int duracionSegundos, int *hEfectivo,
                            int *mEfectivo, int *sEfectivo){    
    (*hEfectivo) = duracionSegundos/60/60;
    duracionSegundos -= (*hEfectivo)*60*60;
    (*mEfectivo) = duracionSegundos/60;
    duracionSegundos -= (*mEfectivo)*60;
    (*sEfectivo) = duracionSegundos;
}

void imprimirEstadisticas(FILE *archReporte, double montoPagoAlSeguro,
                          double promedioConsultasDiario, 
                          int promedioTiempoEfectivo){
    
    int hPromedioEfectivo, mPromedioEfectivo, sPromedioEfectivo;
    calcularTiempoEfectivo(promedioTiempoEfectivo,&hPromedioEfectivo,
            &mPromedioEfectivo,&sPromedioEfectivo);
    
    fprintf(archReporte,"Monto que debe pagarle el seguro: S/. %.2lf\n",
            montoPagoAlSeguro);
    fprintf(archReporte,"Promedio de consultas diario: %16.3lf\n",
            promedioConsultasDiario);
    fprintf(archReporte,"Promedio de tiempo efectivo: %8dh %2dm %2ds\n",
            hPromedioEfectivo,mPromedioEfectivo,sPromedioEfectivo);
    
    imprimirLinea(archReporte,'=',MAX_LINEA);
}

void imprimirMaximosObtenidos(FILE *archReporte, int maxConsultaFecha, 
                              int maxConsultaTotal, int maxTiempoFecha, 
                              int maxTiempoTotal){
    
    int hTiempoTotal, mTiempoTotal, sTiempoTotal, ddConsultas, mmConsultas, 
            aaaaConsultas, ddTiempo, mmTiempo, aaaaTiempo;
    calcularTiempoEfectivo(maxTiempoTotal,&hTiempoTotal,&mTiempoTotal,&sTiempoTotal);
    separarFecha(maxConsultaFecha,&ddConsultas,&mmConsultas,&aaaaConsultas);
    separarFecha(maxTiempoFecha,&ddTiempo,&mmTiempo,&aaaaTiempo);
    
    fprintf(archReporte,"Máximos obtenidos:\n");
    fprintf(archReporte,"%12s\n","Consultas:");
    fprintf(archReporte,"%8s %02d/%02d/%02d %10s %2d\n","Fecha:",ddConsultas,
            mmConsultas,aaaaConsultas,"Total:",maxConsultaTotal);
    fprintf(archReporte,"%9s\n","Tiempo:");
    fprintf(archReporte,"%8s %02d/%02d/%02d %10s %2dh %2dm %2ds\n","Fecha:",
            ddTiempo,mmTiempo,aaaaTiempo,"Total:",hTiempoTotal,mTiempoTotal,
            sTiempoTotal);
    
    imprimirLinea(archReporte,'=',MAX_LINEA);
}

void separarFecha(int fecha, int *dd, int *mm, int *aaaa){
    (*aaaa) = fecha/10000;
    fecha -= (*aaaa)*10000;
    (*mm) = fecha/100;
    fecha -= (*mm)*100;
    (*dd) = fecha;
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);    
}

void cerrarArchivos(FILE *archConsultasMedicas, FILE *archReporteDeConsultas){
    fclose(archConsultasMedicas);
    fclose(archReporteDeConsultas);    
}