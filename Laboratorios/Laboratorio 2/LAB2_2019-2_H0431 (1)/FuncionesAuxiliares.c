/* 
 * Proyecto: LAB2_2019-2_H0431_2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 04:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 100
#define FECHA_HOY 20220418

void procesarArchivos(FILE *archUltimosSismos, FILE *archReporte){
    
    fprintf(archReporte,"\n%50s\n","REPORTE DE LOS SISMOS A TRAVÉS DE TIEMPO");
    imprimirLinea(archReporte,'=',MAX_LINEA);
    
    int ppp, rr, ccc, i=0;
    double intensidadPromedio=0, duracionPromedio=0;
        
    while(1){        
        fscanf(archUltimosSismos,"%3d%2d%3d",&ppp,&rr,&ccc);
        if(feof(archUltimosSismos)) break;        
        fprintf(archReporte,"%s %03d %10s %03d %15s %02d %20s %03d\n","N° ",i,
                "PAIS:",ppp,"REGION",rr,"CIUDAD:",ccc);
        imprimirLinea(archReporte,'=',MAX_LINEA);        
        imprimirSismos(archUltimosSismos,archReporte,&intensidadPromedio,
                &duracionPromedio);        
        imprimirLinea(archReporte,'-',MAX_LINEA);        
    }
        
}

void imprimirSismos(FILE *archUltimosSismos, FILE *archReporte, 
                    double intensidadPromedio, double duracionPromedio){
        
    /* 
    //Datos para el resumen:
    int cantRegistros=0;
    int duracionAnt, horaQueEmpezoAnt, fechaAnt=FECHA_HOY;
    int duracionRec, horaQueEmpezoRec, fechaRec=0;
    int duracionMay, horaQueEmpezoMay, fechaMay;
    double intensidadAnt, intensidadRec, intensidadMay;*/
    
    fprintf(archReporte,"%s %25s %25s %8s\n","INTENSIDAD","HORA QUE EMPEZÓ",
            "HORA QUE TERMINÓ","FECHA");
    int dd, mm, aaaa, duracion, hora, min, segundo, datosLeidos, i=0, 
            horaFin, minFin, segundoFin;
    double intensidad;
    
    while(1){
        
        fscanf(archUltimosSismos,"%d/%d/%d",&dd,&mm,&aaaa);
        fscanf(archUltimosSismos,"%lf %d",&intensidad,&duracion);        
        datosLeidos = fscanf(archUltimosSismos,"%d:%d:%d",&hora,&min,&segundo);
        
        if(datosLeidos==1){
            min=0;
            segundo=0;
        }else if(datosLeidos==2)
            segundo=0;    
        
        calcularHoraFin(hora,min,segundo,duracion,&horaFin,&minFin,&segundoFin);        
        fprintf(archReporte,"%10.2lf %5c %02d:%02d:%02d %5c %02d:%02d:%02d "
                "%5c %02d/%02d/%02d\n",intensidad,' ',hora,min,segundo,' ',
                horaFin,minFin,segundoFin,' ',dd,mm,aaaa);
        
        (*intensidadPromedio)+=intensidad;
        (*duracionPromedio)+=duracion;
        i++;
        
        if(fgetc(archUltimosSismos)=='\n') break;
    }    
    (*intensidadPromedio)/=i;
    (*duracionPromedio)/=i; 
    
    imprimirLinea(archReporte,'-',MAX_LINEA); 
    fprintf(archReporte,"INTENSIDAD PROMEDIO: %7.2lf\n",intensidadPromedio);
    fprintf(archReporte,"DURACIÓN PROMEDIO: %9.2lf segundos\n",duracionPromedio);
}

void calcularHoraFin(int hora,int min, int segundo, int duracion, int *horaFin, 
                     int *minFin, int *segundoFin){
    
    int inicioEnSegundos = convertirHoraASegundos(hora,min,segundo);
    int finEnSegundos = inicioEnSegundos+duracion;
    
    (*horaFin) = finEnSegundos/60/60;
    finEnSegundos -= (*horaFin)*60*60;
    (*minFin) = finEnSegundos/60;
    finEnSegundos -= (*minFin)*60;
    (*segundoFin) = finEnSegundos;
}

int convertirHoraASegundos(int hora, int min, int segundo){
    return hora*60*60 + min*60 + segundo;
}

void imprimirLinea(FILE *archReporte, char caracter, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(caracter,archReporte);
    fputc('\n',archReporte);        
}

void cerrarArchivos(FILE *archUltimosSismos, FILE *archReporteDeLosSismos){
    fclose(archReporteDeLosSismos);
    fclose(archUltimosSismos);    
}