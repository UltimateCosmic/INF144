/* 
 * Proyecto: ManejoDeArchivos_Lab03_2022_1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 10 de mayo de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_CLIENTES 50
#define MAX_PEDIDOS 200

int main(int argc, char** argv) {

    //Archivo Clientes.txt
    int arrDNI_Cli[MAX_CLIENTES], arrTelefonoCli[MAX_CLIENTES], numClientes=0;
    procesarClientes(arrDNI_Cli,arrTelefonoCli,&numClientes);
    ordenarClientesPorDNI(arrDNI_Cli,arrTelefonoCli,numClientes);
        
    //Archivo Pedidos.txt
    int arrCodigoProd[MAX_PEDIDOS]={}, numProd=0;
    double arrPrecioProd[MAX_PEDIDOS], arrCantidadProd[MAX_PEDIDOS]={},
            arrTotalProd[MAX_PEDIDOS]={}, arrTotalGastadoCli[MAX_CLIENTES]={};
    procesarPedidos(arrCodigoProd,arrPrecioProd,arrCantidadProd,arrTotalProd,
            &numProd,arrDNI_Cli,arrTotalGastadoCli,numClientes);
        
    //Archivo ReporteDeVentas.txt
    procesarReporteDeVentas(arrDNI_Cli,arrTelefonoCli,arrTotalGastadoCli,
            numClientes,arrCodigoProd,arrPrecioProd,arrCantidadProd,arrTotalProd,
            numProd);
    
    return (EXIT_SUCCESS);
}