/* 
 * Proyecto: LAB2_2021-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 25 de abril de 2022, 03:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archAlumnosNotas, *archCursos, *archReporteDeCursos;
    
    archAlumnosNotas = fopen("Alumnos-Notas.txt","r");
    if(archAlumnosNotas==NULL){
        printf("ERROR: No se pudo abrir el archivo Alumnos-Notas.txt\n");
        exit(1);
    }
    archCursos = fopen("Cursos.txt","r");
    if(archCursos==NULL){
        printf("ERROR: No se pudo abrir el archivo Cursos.txt\n");
        exit(1);
    }
    archReporteDeCursos = fopen("ReporteDeCursos.txt","w");
    if(archReporteDeCursos==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeCursos.txt\n");
        exit(1);
    }
    procesarArchivos(archAlumnosNotas,archCursos,archReporteDeCursos);
    cerrarArchivos(archAlumnosNotas,archCursos,archReporteDeCursos);

    return (EXIT_SUCCESS);
}