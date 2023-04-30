/* 
 * Proyecto: PC4_2021-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 01:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#include "StructBus.h"
#include "StructPasajero.h"
#define MAX_BUSES 30
#define MAX_LISTA 300

int main(int argc, char** argv) {
    
    //Archivo: Buses.csv
    int cantBuses=0;
    struct Bus arrBus[MAX_BUSES];
    leerBuses(arrBus,&cantBuses);
    ordenarBuses(arrBus,cantBuses);
    
    //Archivo: Pasajeros.csv
    int cantLista=0;
    struct Pasajero listaDeEspera[MAX_LISTA]; 
    leerPasajeros(arrBus,cantBuses,listaDeEspera,&cantLista);   
    
    //Archivo: ReporteDePasajeros.txt
    imprimirReporteDePasajeros(arrBus,cantBuses,listaDeEspera,cantLista);
    
    return (EXIT_SUCCESS);
}

