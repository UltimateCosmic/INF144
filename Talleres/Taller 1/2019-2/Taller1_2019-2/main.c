/* 
 * Proyecto: Taller_1_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 3 de abril de 2022, 09:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archConsultasMedicas, *archReporteDeConsultas;
    
    archConsultasMedicas = fopen("ConsultasMedicas.txt","r");    
    if(archConsultasMedicas==NULL){
        printf("ERROR: No se pudo abrir el archivo ConsultasMedicas.txt\n");
        exit(1);
    }    
    archReporteDeConsultas = fopen("ReporteDeConsultas.txt","w");    
    if(archConsultasMedicas==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeConsultas.txt\n");
        exit(1);
    }
    imprimirReporte(archConsultasMedicas,archReporteDeConsultas);
    cerrarArchivos(archConsultasMedicas,archReporteDeConsultas);
    return (EXIT_SUCCESS);
}

