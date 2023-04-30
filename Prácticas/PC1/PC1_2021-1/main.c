/* 
 * Proyecto: PC1_2021-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 15 de abril de 2022, 08:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    printf("%70s\n","INFORMACION ACADEMICA DE LOS ESTUDIANTES");
    int totalDeAlumnosRegistrados=0;
    imprimirInformacionAcademica(&totalDeAlumnosRegistrados);
    printf("TOTAL DE ALUMNOS REGISTRADOS: %d\n",totalDeAlumnosRegistrados);

    return (EXIT_SUCCESS);
}

