/* 
 * Proyecto: LAB4_2019-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 10 de mayo de 2022, 06:21 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_EMPL 50
#define MAX_UTIL 20
#define MAX_PLAN 500

int main(int argc, char** argv) {

    //Archivo Utilidades.txt
    int arrAnioUtilidad[MAX_UTIL], numUtilidades=0;
    double arrUtilidad[MAX_UTIL], arrPorc[MAX_UTIL];
    procesarUtilidades(arrAnioUtilidad,arrUtilidad,arrPorc,&numUtilidades);
    ordenarUtilidadesPorAnio(arrAnioUtilidad,arrUtilidad,arrPorc,numUtilidades);
    
    //Archivo Empleados.txt
    int arrCodEmpleado[MAX_EMPL], numEmpleados=0;
    double arrSueldoEmpleado[MAX_EMPL];
    procesarEmpleados(arrCodEmpleado,arrSueldoEmpleado,&numEmpleados);
    
    //Archivo Plantillas.txt
    int codPlant[MAX_PLAN], anioPlant[MAX_PLAN], numPlantillas=0,
            mesPlant[MAX_PLAN], diasLaboro[MAX_PLAN];
    double abonoEmpleado[MAX_PLAN];
    procesarPlantillas(codPlant,anioPlant,mesPlant,diasLaboro,abonoEmpleado,
            &numPlantillas);
    abonarEmpleados(abonoEmpleado,diasLaboro,numPlantillas,arrCodEmpleado,
            arrSueldoEmpleado,numEmpleados,codPlant);
    ordenarPlantillas(codPlant,anioPlant,mesPlant,diasLaboro,abonoEmpleado,
            numPlantillas);
    
    //Archivo ReporteDeUtilidades.txt
    procesarReporteDeUtilidades(arrCodEmpleado,arrSueldoEmpleado,numEmpleados,
            codPlant,anioPlant,mesPlant,diasLaboro,abonoEmpleado,numPlantillas);

    return (EXIT_SUCCESS);
}