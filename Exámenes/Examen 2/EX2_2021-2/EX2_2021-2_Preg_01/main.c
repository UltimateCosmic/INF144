/* 
 * Proyecto: EX2_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 02:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"

int main(int argc, char** argv) {

    //a)
    crearArchStockDeProductosBin("StockDeProductos.bin","StockDeProductos.csv");
    imprimirRepStockDeProductos("StockDeProductos.bin","RepStockDeProductos.txt");

    //b)
    crearArchPedidosPorInternetBin("PedidosPorInternet.bin","Pedidos.txt");
    imprimirRepPedidosPorInternetBin("PedidosPorInternet.bin","RepPedidos.txt");
    
    //c)
    completarArchPedidosPorInternetBin("PedidosPorInternet.bin",
            "DetalleDeLosPedidos.txt","StockDeProductos.bin");
    
    //d)
    imprimirReporteDePedidos("PedidosPorInternet.bin","ReporteDePedidos.txt");
    
    return (EXIT_SUCCESS);
}

