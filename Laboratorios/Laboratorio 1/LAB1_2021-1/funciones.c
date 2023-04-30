/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <math.h>

double evaluarFuncion(double a, double b, double c, double d, double e,
                      double f, double x){
    double resultado;
    resultado = a*pow(x,5) + b*pow(x,4) + c*pow(x,3) +
                d*pow(x,2) + e*pow(x,1) + f*pow(x,0);
    return resultado;  
}