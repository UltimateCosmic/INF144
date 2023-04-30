/* 
 * Proyecto: PC3_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 5 de junio de 2022, 03:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LIBROS 1200

int main(int argc, char** argv) {

    //Archivo: Ventas.txt
    int arrLibro[MAX_LIBROS]={}, arrVentas[MAX_LIBROS], cantLibros=0;
    leerVentas(arrLibro,arrVentas,&cantLibros);
    ordenarLibros(arrLibro,arrVentas,cantLibros);
    
    //Archivo: Libros.txt
    char *arrNombreLibro[MAX_LIBROS];
    double arrPrecio[MAX_LIBROS], arrMonto[MAX_LIBROS]={};
    leerLibros(arrLibro,arrNombreLibro,arrPrecio,cantLibros);
    calcularMontoTotal(arrVentas,arrPrecio,arrMonto,cantLibros);
    
    //Arhivo: ReporteDeEditorial.txt
    ordenarPorVentas(arrLibro,arrNombreLibro,arrVentas,arrMonto,cantLibros);
    procesarReporteDeEditorial(arrLibro,arrVentas,cantLibros);

    return (EXIT_SUCCESS);
}

