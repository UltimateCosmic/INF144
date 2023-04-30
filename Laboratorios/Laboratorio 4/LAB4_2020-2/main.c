/* 
 * Proyecto: LAB4_2020-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 31 de mayo de 2022, 03:51 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_SALAS 20
#define MAX_PELICULAS 20

int main(int argc, char** argv) {

    //Archivo: salas.txt
    int arrSala[MAX_SALAS], arrButaca[MAX_SALAS], cantSalas=0;
    leerSalas(arrSala,arrButaca,&cantSalas);
    ordenarSalasOPeliculas(arrSala,arrButaca,cantSalas);   
    
    //Archivo: peliculas.txt
    int arrPelicula[MAX_PELICULAS], arrFunciones[MAX_PELICULAS]={}, cantPeliculas=0;
    leerPeliculas(arrPelicula,arrFunciones,&cantPeliculas);
    ordenarSalasOPeliculas(arrPelicula,arrFunciones,cantPeliculas);
    
    //Archivo: ventas_y_ocupacion.txt
    int arrButVend[MAX_PELICULAS]={}, arrButOcup[MAX_PELICULAS]={};
    double arrRecaudacion[MAX_PELICULAS]={};
    leerVentasYOcupacion(arrPelicula,cantPeliculas,arrButVend,arrButOcup,
            arrRecaudacion,arrSala,cantSalas);
    
    //Archivo: ReporteDeVentasYOcupaciones
    ordenarPeliculasPorRecaudacion(arrPelicula,arrFunciones,arrButVend,
            arrButOcup,arrRecaudacion,cantPeliculas);
    imprimirReporteDeVentasYOcupaciones(arrPelicula,arrFunciones,arrButVend,
            arrRecaudacion,arrButOcup,cantPeliculas);

    return (EXIT_SUCCESS);
}
