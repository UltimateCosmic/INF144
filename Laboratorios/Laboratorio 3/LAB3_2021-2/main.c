/* 
 * Proyecto: LAB3_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 2 de mayo de 2022, 05:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX 100
#define FECHA_HOY 20220508

int main(int argc, char** argv) {

    //Pacientes.txt
    int arrCodPaciente[MAX], arrCodPostal[MAX], cantPacientes=0;
    leerArrPacientes(arrCodPaciente,arrCodPostal,&cantPacientes);
    
    //Medicos.txt
    int arrCodMed[MAX], cantMedicos=0;
    double arrTarifaMed[MAX];
    leerArrMedicos(arrCodMed,arrTarifaMed,&cantMedicos);
    
    //Distritos.txt
    int arrCodDistrito[MAX], cantDistritos=0;
    leerArrDistritos(arrCodDistrito,&cantDistritos);
    
    //AtencinesMedicas.txt
    int arrFechaIni[MAX], arrFechaFin[MAX]={}, arrDuracion[MAX]={}, arrCitas[MAX]={};
    double arrMontoPagado[MAX]={};    
    for(int i=0; i<cantPacientes; i++)
        arrFechaIni[i]=FECHA_HOY;       
    leerArrAtencinesMedicas(arrCodPaciente,arrFechaIni,arrFechaFin,arrDuracion,
            arrCitas,arrMontoPagado,cantPacientes,arrCodMed,arrTarifaMed,
            cantMedicos);
    
    //Calcular la cantidad de citas por distrito.
    int arrCitasDistrito[MAX]={};
    double arrPagoDistrito[MAX]={};
    calcularTotalesPorDistrito(arrCitasDistrito,arrCodDistrito,cantDistritos,
            arrCitas,arrCodPostal,cantPacientes,arrPagoDistrito,arrMontoPagado);
    
    //Ordenar los distritos por la cantidad de citas y pagos totales:
    ordenarDistritosPorTotales(arrCodDistrito,cantDistritos,arrCitasDistrito,
            arrPagoDistrito);
        
    //ReporteDeAtencionesPorDistrito.txt
    imprimirReporte(arrCodPaciente,arrCodPostal,cantPacientes,arrCodDistrito,
            cantDistritos,arrFechaIni,arrFechaFin,arrDuracion,arrCitas,
            arrMontoPagado,arrCitasDistrito,arrPagoDistrito);
    
    return (EXIT_SUCCESS);
}

