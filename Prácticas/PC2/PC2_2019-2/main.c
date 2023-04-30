/* 
 * Proyecto: PC2_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 13 de abril de 2022, 04:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archRecetas, *archMedicinas, *archMedicos, 
            *archNiveles, *archReporteDeRecetasAtendidas;
    
    archRecetas = fopen("Recetas.txt","r");
    if(archRecetas==NULL){
        printf("ERROR: No se pudo abrir el archivo Recetas.txt\n");
        exit(1);        
    }
    archMedicinas = fopen("Medicinas.txt","r");
    if(archMedicinas==NULL){
        printf("ERROR: No se pudo abrir el archivo Medicinas.txt\n");
        exit(1);        
    }
    archMedicos = fopen("Medicos.txt","r");
    if(archMedicos==NULL){
        printf("ERROR: No se pudo abrir el archivo Medicos.txt\n");
        exit(1);        
    }
    archNiveles = fopen("niveles.txt","r");
    if(archNiveles==NULL){
        printf("ERROR: No se pudo abrir el archivo niveles.txt\n");
        exit(1);        
    }
    archReporteDeRecetasAtendidas = fopen("ReporteDeRecetasAtendidas.txt","w");
    if(archReporteDeRecetasAtendidas==NULL){
        printf("ERROR: No se pudo abrir el archivo "
                "ReporteDeRecetasAtendidas.txt\n");
        exit(1);        
    }   
    procesarArchivos(archRecetas,archMedicinas,archMedicos,archNiveles,
            archReporteDeRecetasAtendidas);
    cerrarArchivos(archRecetas,archMedicinas,archMedicos,archNiveles,
            archReporteDeRecetasAtendidas);
    
    return (EXIT_SUCCESS);
}

