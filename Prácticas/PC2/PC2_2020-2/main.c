/* 
 * Proyecto: PC2_2020-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 21 de abril de 2022, 05:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archAlumnos, *archNotas, *archMatricula, *archResultadosAcademicos;
    
    archAlumnos = fopen("Alumnos.txt","r");
    if(archAlumnos==NULL){
        printf("ERROR: No se pudo abrir el archivo Alumnos.txt\n");
        exit(1);        
    }
    archNotas = fopen("Notas.txt","r");
    if(archNotas==NULL){
        printf("ERROR: No se pudo abrir el archivo Notas.txt\n");
        exit(1);        
    }
    archMatricula = fopen("Matricula.txt","r");
    if(archMatricula==NULL){
        printf("ERROR: No se pudo abrir el archivo Matricula.txt\n");
        exit(1);        
    }
    archResultadosAcademicos = fopen("ResultadosAcademicos.txt","w");
    if(archResultadosAcademicos==NULL){
        printf("ERROR: No se pudo abrir el archivo ResultadosAcademicos.txt\n");
        exit(1);        
    }
    procesarArchivos(archAlumnos,archNotas,archMatricula,archResultadosAcademicos);
    cerrarArchivos(archAlumnos,archNotas,archMatricula,archResultadosAcademicos);
        
    return (EXIT_SUCCESS);
}

