/* 
 * Proyecto: LAB2_2019-2_H0431_2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 04:46 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archUltimosSismos, *archReporteDeLosSismos;
    
    archUltimosSismos = fopen("UltimosSismos.txt","r");
    if(archUltimosSismos==NULL){
        printf("ERROR: No se pudo abrir el archivo UltimosSismos.txt\n");
        exit(1);        
    }
    archReporteDeLosSismos = fopen("ReporteUltimosSismos.txt","w");
    if(archReporteDeLosSismos==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteUltimosSismos.txt\n");
        exit(1);        
    }
    procesarArchivos(archUltimosSismos,archReporteDeLosSismos);
    cerrarArchivos(archUltimosSismos,archReporteDeLosSismos);
        
    return (EXIT_SUCCESS);
}

