/* 
 * Proyecto: Practica01-2022-1_Archivos
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 07:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archVentas, *archReporteCompras;
    
    //Apertura de archivos.
    archVentas = fopen("Ventas.txt","r");
    if(archVentas==NULL){
        printf("ERROR: No se pudo abrir el archivo Ventas.txt\n");
        exit(1);
    }
    archReporteCompras = fopen("IngresosPorVentasMarzo2022.txt","w");
    if(archReporteCompras==NULL){
        printf("ERROR: No se pudo abrir el archivo IngresosPorVentasMarzo2022.txt\n");
        exit(1);
    }
    procesarArchivos(archVentas,archReporteCompras);    
    cerrarArchivos(archVentas,archReporteCompras);    

    return (EXIT_SUCCESS);
}

