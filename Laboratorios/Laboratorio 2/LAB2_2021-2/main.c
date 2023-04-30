/* 
 * Proyecto: LAB2_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 19 de abril de 2022, 03:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archMedicos, *archPacientes, *archAtencionesMedicas, *archReporteDePagos;
    
    archMedicos=fopen("Medicos.txt","r");
    if(archMedicos==NULL){
        printf("ERROR: No se pudo abrir el archivo Medicos.txt\n");
        exit(1);
    }
    archPacientes=fopen("Pacientes.txt","r");
    if(archPacientes==NULL){
        printf("ERROR: No se pudo abrir el archivo Pacientes.txt\n");
        exit(1);
    }
    archAtencionesMedicas=fopen("AtencionesMedicas.txt","r");
    if(archAtencionesMedicas==NULL){
        printf("ERROR: No se pudo abrir el archivo AtencionesMedicas.txt\n");
        exit(1);
    }
    archReporteDePagos=fopen("ReporteDePagos.txt","w");
    if(archReporteDePagos==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDePagos.txt\n");
        exit(1);
    }
    imprimirReporteDePagos(archMedicos,archPacientes,archAtencionesMedicas,
            archReporteDePagos);
    cerrarArchivos(archMedicos,archPacientes,archAtencionesMedicas,
            archReporteDePagos); 

    return (EXIT_SUCCESS);
}

