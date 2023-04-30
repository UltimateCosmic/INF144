/* 
 * Proyecto: PC2_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 21 de abril de 2022, 10:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archAtencionesMedicas, *archMedicos, *archReporteDeIngresos;
    
    archAtencionesMedicas = fopen("AtencinesMedicas.txt","r");
    if(archAtencionesMedicas==NULL){
        printf("ERROR: No se pudo abrir el archivo AtencinesMedicas.txt\n");
        exit(1);
    }
    archMedicos = fopen("Medicos.txt","r");
    if(archMedicos==NULL){
        printf("ERROR: No se pudo abrir el archivo Medicos.txt\n");
        exit(1);
    }
    archReporteDeIngresos = fopen("ReporteDeIngresos.txt","w");
    if(archReporteDeIngresos==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeIngresos.txt\n");
        exit(1);
    }    
    procesarArchivos(archAtencionesMedicas,archMedicos,archReporteDeIngresos);
    cerrarArchivos(archAtencionesMedicas,archMedicos,archReporteDeIngresos);

    return (EXIT_SUCCESS);
}

