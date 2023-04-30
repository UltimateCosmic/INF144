/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <math.h>
#include "NumerosComplejos.h"

void suma(double *a, double *b, double c, double d){
    *a = *a + c;
    *b = *b + d;    
}

void resta(double *a, double *b, double c, double d){
    *a = *a - c;
    *b = *b - d;    
}

void multiplicacion(double *a, double *b, double c, double d){
    double auxiliar = *a;
    *a = (*a)*c + (*b)*d;
    *b = (*b)*c - (auxiliar)*d;
}

void division(double *a, double *b, double c, double d){
    double auxiliar = *a;
    *a = ((*a)*c + (*b)*d)/(pow(c,2)+pow(d,2));
    *b = ((*b)*c - (auxiliar)*d)/(pow(c,2)+pow(d,2));    
}

void potencia(double *a, double *b, int n){    
    double aAuxiliar = *a, bAuxiliar = *b;    
    for(int i=1; i<n; i++) multiplicacion(&aAuxiliar,&bAuxiliar,*a,*b); 
    *a = aAuxiliar;
    *b = bAuxiliar;
}