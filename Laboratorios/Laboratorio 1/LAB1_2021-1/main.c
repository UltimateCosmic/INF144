/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 23 de marzo de 2022, 11:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PRECISION 0.01

#include "funciones.h"

int main(int argc, char** argv) {
    
    double a, b, c, d, e, f;
    double limiteInf, limiteSup;
    double h, x1, x2, y1, y2;
    int numIntervalos = 0, i;
    double area = 0.0, areaAnt, longitud =0.0, longitudAnt;
    
    printf("Ingrese los coeficientes a, b, c, d, e, f: ");
    scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);
    
    printf("Ingrese los limites inferior y superior: ");
    scanf("%lf %lf", &limiteInf, &limiteSup);
    
    do{
        areaAnt = area;
        longitudAnt = longitud;
        area = longitud = 0;
        numIntervalos++;
        h = (limiteSup - limiteInf) / numIntervalos;
        x1 = limiteInf;
        
        for(i =1; i<=numIntervalos; i++) {
            x2 = x1 + h;
            y1 = evaluarFuncion(a, b, c, d, e, f, x1);
            y2 = evaluarFuncion(a, b, c, d, e, f, x2);
            area += (y1 + y2)*h/2;
            longitud += sqrt( pow(y2-y1,2) + pow(h,2) );
            x1 = x2;            
        }       
        
    }while(fabs(area-areaAnt)>=PRECISION &&
           fabs(longitud-longitudAnt)>=PRECISION);
    
    
    printf("\n%8s %11s\n", "Area", "Longitud");   
    printf("%8.3lf %11.3lf\n", area, longitud);    
    
    return (EXIT_SUCCESS);
}

