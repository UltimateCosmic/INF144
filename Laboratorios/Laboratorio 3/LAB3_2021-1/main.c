/* 
 * Proyecto: LAB3_2021-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 9 de mayo de 2022, 06:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_PROD 50
#define MAX_TIEN 20

int main(int argc, char** argv) {

    //Archivo productos.txt
    int arrCodProd[MAX_PROD], cantProd=0;
    double arrPrecioProd[MAX_PROD];
    procesarProductos(arrCodProd,arrPrecioProd,&cantProd);
    
    //Archivo tiendas.txt
    int arrCodTienda[MAX_TIEN], arrCodPostal[MAX_TIEN], cantTiendas=0;
    procesarTiendas(arrCodTienda,arrCodPostal,&cantTiendas);
    ordenarTiendas(arrCodTienda,arrCodPostal,cantTiendas);
    
    //Archivo Reporte.txt
    procesarReporte(arrCodProd,arrPrecioProd,cantProd,arrCodTienda,arrCodPostal,
            cantTiendas);
    
    return (EXIT_SUCCESS);
}

