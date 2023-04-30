/* 
 * Proyecto: PC2_2019-1_2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 20 de abril de 2022, 06:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archConsultasMedicas, *archReporteDeConsultas;
    
    archConsultasMedicas = fopen("L2-ConsultasMedicas.txt","r");
    if(archConsultasMedicas==NULL){
        printf("ERROR: No se pudo abrir el archivo L2-ConsultasMedicas.txt\n");
        exit(1);
    }
    archReporteDeConsultas = fopen("ReporteDeConsultas.txt","w");
    if(archReporteDeConsultas==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeConsultas.txt\n");
        exit(1);
    }
    imprimirReporte(archConsultasMedicas,archReporteDeConsultas);
    cerrarArchivos(archConsultasMedicas,archReporteDeConsultas);

    return (EXIT_SUCCESS);
}

