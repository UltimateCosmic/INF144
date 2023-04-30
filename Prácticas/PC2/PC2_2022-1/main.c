/* 
 * Proyecto: Pr02_2022-1_Poligonal
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 2 de mayo de 2022, 07:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_VERTICES 100

int main(int argc, char** argv) {
    int cantVertices=0;
    double arrPoligonalX[MAX_VERTICES], arrPoligonalY[MAX_VERTICES];
    leerArrPoligonal(arrPoligonalX,arrPoligonalY,&cantVertices);    
    emitirReporteDeTareas(arrPoligonalX,arrPoligonalY,cantVertices);
    return (EXIT_SUCCESS);
}

