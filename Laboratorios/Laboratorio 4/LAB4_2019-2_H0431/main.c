/* 
 * Proyecto: LAB4_2019-2_H0431
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 1 de mayo de 2022, 01:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX 500
#define FECHA_HOY 20220501

int main(int argc, char** argv) {

    //Archivo Personas.txt
    int arrDni[MAX], arrTelefono[MAX], arrCargoFam[MAX], 
            arrRiesgo[MAX], cantPersonas=0;
    leerArrPersonas(arrDni,arrTelefono,arrCargoFam,arrRiesgo,&cantPersonas);
    
    //Archivo RegistroDeIngresos.txt
    int fechaMasReciente=0, fechaMasAntigua=FECHA_HOY;
    double arrIngreso[MAX]={0};
    leerArrIngresos(arrIngreso,arrDni,cantPersonas,&fechaMasReciente,
            &fechaMasAntigua);
    
    //Lineas de credito
    double arrLineaBancoA[MAX]={0}, arrLineaBancoB[MAX]={0};
    calcularLineasDeCredito(arrLineaBancoA,arrLineaBancoB,arrIngreso,
            arrCargoFam,arrRiesgo,cantPersonas);
    
    //Reporte 1:
    imprimirPrimerReporte(fechaMasAntigua,fechaMasReciente,arrDni,arrTelefono,
            arrLineaBancoA,arrLineaBancoB,cantPersonas);
    
    //Reporte 2:
    imprimirSegundoReporte(arrLineaBancoA,arrLineaBancoB,cantPersonas);
    
    return (EXIT_SUCCESS);
}

