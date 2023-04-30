/* 
 * Proyecto: Taller_1_2019-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 3 de abril de 2022, 09:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 67

void imprimirReporte(FILE *archConsultas, FILE *archReporte){
    
    fprintf(archReporte,"Reporte de consultas:\n");
        
    int dni, i=0;
    double montoPorMinuto;
    
    while(1){
        
        fscanf(archConsultas,"%d %lf",&dni,&montoPorMinuto);                
        if(feof(archConsultas)) break;
        
        fprintf(archReporte,"DNI del medico: %d\n",dni);       
        fprintf(archReporte,"Costo por consulta por minuto: %.2lf\n",montoPorMinuto);       
        imprimirLinea(archReporte,'=',MAX_LINEA);
        fprintf(archReporte,"%s %17s %18s %19s\n","Fecha","N° Consultas",
                "Tiempo efectivo","Monto recaudado");
        
        int dia, mes, anio, diaConsulta, mesConsulta, anioConsulta, 
                diaTiempo, mesTiempo, anioTiempo, horaTiempo, 
                minTiempo, segundoTiempo, tiempoMayor=0, maxConsultas=0;
        
        double montoSeguro=0, promedioConsultasDiario=0;
        
        while(1){
            
            fscanf(archConsultas,"%d/%d/%d",&dia,&mes,&anio);                        
            if(dia==0) break;            
            
            int horaIni, minIni, segundoIni, horaFin, minFin, segundoFin, 
                    numConsultas=0, horaEfect=0, minutoEfect=0, segundoEfect=0, 
                    tiempoEfectivo=0, tiempoEnSegundos;
            double porcentajePago, montoRecaudado=0;
            
            while(1){
                
                fscanf(archConsultas,"%d:%d:%d",&horaIni,&minIni,&segundoIni);
                fscanf(archConsultas,"%d:%d:%d",&horaFin,&minFin,&segundoFin);
                fscanf(archConsultas,"%lf",&porcentajePago);
                
                numConsultas++;     
                tiempoEnSegundos = calcularTiempoEnSegundos(horaIni,horaFin,
                        minIni,minFin,segundoIni,segundoFin);                
                tiempoEfectivo += tiempoEnSegundos;
                                
                montoRecaudado += calcularMonto(montoPorMinuto,porcentajePago,
                        tiempoEnSegundos);
                
                if(fgetc(archConsultas)=='\n')
                    break;
            }            
            montoSeguro += montoRecaudado;
            promedioConsultasDiario += numConsultas;
            i++;
            
            calcularTiempoEfect(&horaEfect,&minutoEfect,&segundoEfect,
                    tiempoEfectivo);            
            fprintf(archReporte,"%2d/%2d/%4d %9d %9dh %2dm %2ds %16.2lf\n",dia,
                    mes,anio,numConsultas,horaEfect,minutoEfect,segundoEfect,
                    montoRecaudado);
            
            tiempoEnSegundos = horaEfect*60*60 + minutoEfect*60 + segundoEfect;
            
            if(numConsultas>maxConsultas){
                maxConsultas = numConsultas;
                diaConsulta = dia;
                mesConsulta = mes;
                anioConsulta = anio;
            }                            
            if(tiempoEnSegundos>tiempoMayor){
                tiempoMayor = tiempoEnSegundos;
                calcularTiempoEfect(&horaTiempo,&minTiempo,&segundoTiempo,
                        tiempoEnSegundos);
                diaTiempo = dia;
                mesTiempo = mes;
                anioTiempo = anio;
            }    
        }        
        
        // Monto que debe pagarle el seguro y promedio de consultas diario:
        imprimirLinea(archReporte,'=',MAX_LINEA);
        fprintf(archReporte,"Monto que debe pagarte el seguro: S/. %10.2lf\n",
                montoSeguro);
        fprintf(archReporte,"Promedio de consultas diario: %14.2lf\n", 
                promedioConsultasDiario/i); 
        
        // Máximos obtenidos:
        imprimirLinea(archReporte,'=',MAX_LINEA);                   
        fprintf(archReporte,"Maximos obtenidos:\n");
        fprintf(archReporte," Consultas:\n");
        fprintf(archReporte," Fecha: %2d/%2d/%4d  Total: %11d\n",diaConsulta,
                mesConsulta,anioConsulta,maxConsultas);
        fprintf(archReporte," Tiempo:\n");
        fprintf(archReporte," Fecha: %2d/%2d/%4d  Total: %2dh %2dm %2ds\n",
                diaTiempo,mesTiempo,anioTiempo,horaTiempo,mesTiempo,
                segundoTiempo);
        imprimirLinea(archReporte,'=',MAX_LINEA);
    }
}

double calcularMonto(double montoPorMinuto, double porcentajePago, 
        int tiempoEnSegundos){    
    int tiempoEnMinutos = convertirSegundosAMinutos(tiempoEnSegundos);
    return (porcentajePago*montoPorMinuto/100)*tiempoEnMinutos; 
}

int convertirSegundosAMinutos(int tiempoEnSegundos){
    return tiempoEnSegundos/60;        
}

void calcularTiempoEfect(int *horaEfect, int *minutoEfect, int *segundoEfect, 
                         int tiempo){
    *horaEfect = tiempo/60/60;
    tiempo -= (*horaEfect)*60*60;
    *minutoEfect = tiempo/60;
    tiempo -= (*minutoEfect)*60;
    *segundoEfect = tiempo;
}

int calcularTiempoEnSegundos(int horaIni, int horaFin, int minIni, int minFin, 
                             int segundoIni, int segundoFin){    
    int tiempoIni, tiempoFin;
    tiempoIni = (horaIni*60*60) + (minIni*60) + segundoIni;
    tiempoFin = (horaFin*60*60) + (minFin*60) + segundoFin;   
    return tiempoFin - tiempoIni;    
}

void imprimirLinea(FILE *archReporte, char caracter, int cantVeces){   
    for(int i=0; i<cantVeces; i++) fputc(caracter,archReporte);
    fputc('\n',archReporte);
}

void cerrarArchivos(FILE *archConsultasMedicas, FILE *archReporteDeConsultas){ 
    fclose(archConsultasMedicas);
    fclose(archReporteDeConsultas);
}