/* 
 * Proyecto: PC2_2021-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de abril de 2022, 04:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_PRODUCTOS 50

int main(int argc, char** argv) {
    int codProducto[MAX_PRODUCTOS], cantProductos=0;
    double precioProducto[MAX_PRODUCTOS];
    leerProductos(codProducto,&cantProductos,precioProducto);    
    imprimirReporte(codProducto,cantProductos,precioProducto);    
    return (EXIT_SUCCESS);
}