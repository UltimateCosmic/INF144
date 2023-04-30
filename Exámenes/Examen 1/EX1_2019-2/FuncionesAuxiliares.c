/* 
 * Proyecto: EX1_2019-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de mayo de 2022, 06:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 100
#define NO_SE_ENCONTRO -1

void procesarArchivos(FILE *archPronosticoVentas, FILE *archCapacidadProduccion,
                      FILE *archProyeccionAlmacen,
                      FILE *archReportePlanProduccion){    
    int anio;
    imprimirCabecera(archReportePlanProduccion);    
    solicitarAnio(&anio);    
    imprimirProductos(archPronosticoVentas,archCapacidadProduccion,
            archProyeccionAlmacen,archReportePlanProduccion,anio);
}

void imprimirCabecera(FILE *archReportePlanProduccion){    
    fprintf(archReportePlanProduccion,"%40s\n","PLAN DE PRODUCCION");
    imprimirLinea(archReportePlanProduccion,'=',MAX_LINEA);
}

void solicitarAnio(int *anio){
    printf("Ingrese el anio del que desea emitir plan de produccion: ");
    scanf("%d",anio);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);    
    fputc('\n',arch);
}

void imprimirProductos(FILE *archPronosticoVentas, FILE *archCapacidadProduccion,
                       FILE *archProyeccionAlmacen, FILE *archReportePlanProduccion,
                       int anio){    
    int anioEstimacion, codProducto;
    while(1){        
        fscanf(archPronosticoVentas,"%d %d",&anioEstimacion,&codProducto);
        if(feof(archPronosticoVentas)) break;
        if(anio==anioEstimacion)
            imprimirPlanDeProduccion(archPronosticoVentas,archCapacidadProduccion,
                    archProyeccionAlmacen,archReportePlanProduccion,anio,
                    codProducto);            
        else
            while(fgetc(archPronosticoVentas)!='\n');
    }   
}

void imprimirPlanDeProduccion(FILE *archPronosticoVentas, 
                              FILE *archCapacidadProduccion,
                              FILE *archProyeccionAlmacen, 
                              FILE *archReportePlanProduccion, int anio, 
                              int codProducto){
    
    fprintf(archReportePlanProduccion,"Producto: %d\n",codProducto);
    imprimirLinea(archReportePlanProduccion,'-',MAX_LINEA);
    fprintf(archReportePlanProduccion,"%s %15s %20s %15s %15s %15s %15s %15s\n",
            "Semana","Stock Inicial","Unidades Producidas","Disp.Ventas",
            "St.Seguridad","St.Disponible","Pend.Prod","Cap.Disp");
    imprimirLinea(archReportePlanProduccion,'-',MAX_LINEA);
    
    int semana, cantVentaEstimada, stockInicial, unidProd, dispVentas, 
            stSeguridad, stDisp, pendProd, capDisp, loteMin, loteMax, 
            stockSegSemanal, stockProyectado, i=1;
    
    buscarCapacidadDeProduccion(anio,codProducto,archCapacidadProduccion,
            &loteMin,&loteMax);
    //Reutilizo la función por la similitud entre los archivos.
    buscarCapacidadDeProduccion(anio-1,codProducto,archProyeccionAlmacen,
            &stockSegSemanal,&stockProyectado);
     
    stockInicial=stockProyectado;
    
    while(1){
        fscanf(archPronosticoVentas,"%d %d",&semana,&cantVentaEstimada);        
        for(i; i<=semana; i++){
            
            
        }
        i=semana;
        if(fgetc(archPronosticoVentas)=='\n') break;
    }
    
}

void buscarCapacidadDeProduccion(int anio, int codProducto, FILE *archCapacidad,
                                 int *loteMin, int *loteMax){
    rewind(archCapacidad);
    int anioCap, codProductoCap;    
    while(1){
        fscanf(archCapacidad,"%d %d",&anioCap,&codProductoCap);
        if(feof(archCapacidad)) break;
        if(anio==anioCap && codProducto==codProductoCap){
            fscanf(archCapacidad,"%d %d",loteMin,loteMax);
            return;
        }else
            while(fgetc(archCapacidad)!='\n');        
    }
    *loteMax = NO_SE_ENCONTRO;
    *loteMin = NO_SE_ENCONTRO;    
}

void cerrarArchivos(FILE *archPronosticoVentas, FILE *archCapacidadProduccion,
                    FILE *archProyeccionAlmacen,
                    FILE *archReportePlanProduccion){
    fclose(archPronosticoVentas);
    fclose(archCapacidadProduccion);    
    fclose(archProyeccionAlmacen);
    fclose(archReportePlanProduccion);
}