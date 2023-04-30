/* 
 * Proyecto: EX1_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de mayo de 2022, 06:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archPronosticoVentas, *archCapacidadProduccion, 
            *archProyeccionAlmacen, *archReportePlanProduccion;
    
    archPronosticoVentas = fopen("pronostico_ventas.txt","r");
    if(archPronosticoVentas==NULL){
        printf("ERROR: No se pudo abrir el archivo pronostico_ventas.txt\n");
        exit(1);        
    }
    archCapacidadProduccion = fopen("capacidad_produccion.txt","r");
    if(archCapacidadProduccion==NULL){
        printf("ERROR: No se pudo abrir el archivo capacidad_produccion.txt\n");
        exit(1);        
    }
    archProyeccionAlmacen = fopen("proyeccion_almacen.txt","r");
    if(archProyeccionAlmacen==NULL){
        printf("ERROR: No se pudo abrir el archivo proyeccion_almacen.txt\n");
        exit(1);        
    }
    archReportePlanProduccion = fopen("plan_produccion.txt","w");
    if(archReportePlanProduccion==NULL){
        printf("ERROR: No se pudo abrir el archivo plan_produccion.txt\n");
        exit(1);        
    }    
    procesarArchivos(archPronosticoVentas,archCapacidadProduccion,
            archProyeccionAlmacen,archReportePlanProduccion);
    cerrarArchivos(archPronosticoVentas,archCapacidadProduccion,
            archProyeccionAlmacen,archReportePlanProduccion);  
    
    return (EXIT_SUCCESS);
}

