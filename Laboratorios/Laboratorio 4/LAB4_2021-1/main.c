/* 
 * Proyecto: LAB4_2021-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de mayo de 2022, 12:04 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_PRODUCTOS 300
#define MAX_PLATOS 100

int main(int argc, char** argv) {

    //Archivo: productosAlmacenados.txt
    int arrCodProd[MAX_PRODUCTOS], cantProd=0;
    double arrCantProd[MAX_PRODUCTOS];
    leerProductosAlmacenados(arrCodProd,arrCantProd,&cantProd);
    ordenarProductos(arrCodProd,arrCantProd,cantProd);
        
    //Archivo: platosAPreparar.txt
    int arrPlato[MAX_PLATOS], arrCantPlato[MAX_PLATOS], cantPlatos=0;
    leerPlatosAPreparar(arrPlato,arrCantPlato,&cantPlatos);
    ordenarPlatos(arrPlato,arrCantPlato,cantPlatos);
    
    //Archivo: ListaDePrecios.txt
    double arrPrecioProd[MAX_PRODUCTOS]={};
    leerListaDePrecios(arrCodProd,arrPrecioProd,cantProd);   
    
    //Archivo: Platos.txt
    double arrPrecioPlato[MAX_PLATOS]={};
    procesarPerdidas(arrCodProd,arrCantProd,cantProd,arrPlato,arrCantPlato,
            cantPlatos,arrPrecioPlato,arrPrecioProd);
    
    //Calculo de sub-totales
    double arrSubtotalProd[MAX_PRODUCTOS], arrSubtotalPlatos[MAX_PLATOS];
    calcularSubtotalProd(arrSubtotalProd,arrCantProd,arrPrecioProd,cantProd);
    calcularSubtotalPlatos(arrSubtotalPlatos,arrCantPlato,arrPrecioPlato,cantPlatos);
      
    //Archivo: ReporteDePerdidas.txt
    imprimirReporteDePerdidas(arrCodProd,arrCantProd,arrPrecioProd,cantProd,
            arrPlato,arrCantPlato,arrPrecioPlato,cantPlatos,arrSubtotalProd,
            arrSubtotalPlatos);

    return (EXIT_SUCCESS);
}

