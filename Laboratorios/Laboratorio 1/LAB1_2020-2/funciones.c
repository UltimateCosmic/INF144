/* 
 * Proyecto: LAB1_2020-2
 * Archivo:  funciones.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 5 de abril de 2022, 07:46 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <funciones.h>

double solucionDeEcuacion(double c2, double c1, double c0, double x) {    
    double fxx;
    fxx = c2*x*x + c1*x + c0;
    return fxx;
}