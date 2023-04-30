/* 
 * Proyecto: LAB4_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de mayo de 2022, 07:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_CLIENTES 100
#define MAX_PRODUCTOS 100
#define MAX_PEDIDOS 50
#define MAX_DETALLES 500

int main(int argc, char** argv) {

    //Archivo: Pedidos.txt
    int arrPedido[MAX_PEDIDOS], arrFecha[MAX_PEDIDOS], arrHora[MAX_PEDIDOS],
            arrDni[MAX_PEDIDOS], cantPedidos=0;
    leerPedidos(arrPedido,arrFecha,arrHora,arrDni,&cantPedidos);
    ordenarPedidos(arrPedido,arrFecha,arrHora,arrDni,cantPedidos);
    
    //Archivo: StockDeProductosAlmacenados.txt
    int arrProducto[MAX_PRODUCTOS], arrStock[MAX_PRODUCTOS], cantProductos=0;
    double arrPrecio[MAX_PRODUCTOS];
    leerStockDeProductos(arrProducto,arrStock,arrPrecio,&cantProductos);
    ordenarStockDeProductos(arrProducto,arrStock,arrPrecio,cantProductos);
    
    //Archivo: DetalleDeLosPedidos.txt
    int arrDetPed[MAX_DETALLES], arrDetProd[MAX_DETALLES], arrDetCant[MAX_DETALLES],
            cantDetalles=0;
    leerDetalleDeLosPedidos(arrDetPed,arrDetProd,arrDetCant,&cantDetalles);
    
    //Archivo: ReporteDePedidos.txt
    imprimirReporteDePedidos(arrPedido,arrFecha,arrHora,arrDni,cantPedidos,
            arrProducto,arrStock,arrPrecio,cantProductos,arrDetPed,arrDetProd,
            arrDetCant,cantDetalles);
    
    return (EXIT_SUCCESS);
}

