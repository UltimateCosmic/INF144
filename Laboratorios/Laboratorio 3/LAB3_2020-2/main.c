/* 
 * Proyecto: LAB3_2020-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 9 de mayo de 2022, 01:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX 100

int main(int argc, char** argv) {

    //Archivo AtenciónDePacientes.txt
    int codigoMed[MAX]={}, pacAtend[MAX]={}, pacRes[MAX]={}, cantMed;
    double factorAtenc[MAX]={}, factorRes[MAX]={};    
    procesarAtencionDePacientes(codigoMed,factorAtenc,factorRes,pacAtend,
            pacRes,&cantMed);
    
    //Archivo ReporteDeAtenciones.txt   (Tarea No.1)
    procesarReporteDeAtenciones(codigoMed,factorAtenc,factorRes,pacAtend,
            pacRes,cantMed);
    
    //Archivo Medicos.txt
    procesarReporteDeMedicos(codigoMed,factorAtenc,factorRes,pacAtend,
            pacRes,cantMed);

    return (EXIT_SUCCESS);
}

