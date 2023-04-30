/* 
 * Proyecto: PC1_2021-2
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 05:09 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"
double calculaFuncion(double c_4, double c_3, double c_2,
                        double c_1, double c_0, double xx) {
    double fxx;
    fxx = c_4*potencia(xx,4) + c_3*potencia(xx,3) + c_2*potencia(xx,2) +
          c_1*xx + c_0;
    return fxx;    
}
double potencia(double x, int n) {
    double p = 1.0;
    for(int i=0; i<n; i++)
        p *= x;
    return p;    
}