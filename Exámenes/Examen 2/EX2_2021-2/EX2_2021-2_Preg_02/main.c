/* 
 * Proyecto: EX2_2021-2_Preg_02
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 04:56 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"
#include "StructStockProd.h"
#include "StructPedidos.h"

int main(int argc, char** argv) {

    //a)
    int numProd=0;
    struct StockProd *productos;
    productos = (struct StockProd *)malloc(sizeof(struct StockProd)*50);
    leerStockDeProductos(productos,&numProd);
    imprimirRepStockDeProductos(productos,numProd);
    
    //b)
    int numPed=0;
    struct stPedidos *pedidos;
    pedidos = (struct stPedidos *)malloc(sizeof(struct stPedidos)*50);
    leerPedidos(pedidos,&numPed);
    imprimirRepPedidos(pedidos,numPed);
    
    //c)
    completarPedidos(pedidos,numPed,productos,numProd); 
    
    //d)
    imprimirReporteDePedidos(pedidos,numPed);
    
    return (EXIT_SUCCESS);
}

