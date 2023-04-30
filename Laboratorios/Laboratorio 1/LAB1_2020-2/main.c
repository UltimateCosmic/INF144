/* 
 * Proyecto: LAB1_2020-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 5 de abril de 2022, 07:23 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funciones.h"

int main(int argc, char** argv) {
    const int CUENTAMAXIMA = 100;
    int cuenta, darsePorVencido, datosBuenos, raizEncontrada;
    double c2, c1, c0; //coeificientes de la ecuación
    double x1, x2, x3, epsilon;
    /*x1 y x2 intervalo que contiene la raiz,x3 nuevo punto*/
    double fx1, fx2, fx3;
    /*primero encontraremos un intervalo que contenga la raiz */
    datosBuenos = 0;
    darsePorVencido = 0;
    
    while(!datosBuenos && !darsePorVencido) {
        printf("Ingresar los dos puntos de inicio: \n");
        scanf("%lf %lf",&x1,&x2);
        printf("Ingresar los coeficientes: c2,c1,c0 \n");
        scanf("%lf %lf %lf",&c2,&c1,&c0);
        fx1 = solucionDeEcuacion(c2,c1,c0,x1);
        fx2 = solucionDeEcuacion(c2,c1,c0,x2);
        if((x1 == 0.0) Y (x2 == 0.0)) {
            darsePorVencido = 1;
        }
        else {
            if(((fx1<=0.0) && (fx2>=0.0)) || ((fx1>=0.0) && (fx2<=0.0))) {
                datosBuenos = 1;
            }
            else {
                printf("Lo siento, los puntos dados no estan opuestos\n");
                printf("Ingresar 0,0 para terminar (puntos de inicio)\n");
            }
        }
    }
    if(darsePorVencido) {
        printf("Lo siento, el programa se concluye por una falla\n");
        printf("para encontrar un intervalo inicial valido\n");            
    }
    else {  //solución del problema
        printf("Ingresar la exactitud deseada: \n");
        scanf("%lf",&epsilon);
        raizEncontrada = 0;
        cuenta = 0;

        while (!raizEncontrada && cuenta<=CUENTAMAXIMA) {
            x3 = (x2*fx1-x1*fx2)/(fx1-fx2);
            fx3 = solucionDeEcuaciones(c2,c1,c0,x3);
             if (fx3 == 0.0) //hemos encontrado la raiz exacta
                raizEncontrada = 1;
            if (((fx1<=0.0) && (fx3<=0.0)) || ((fx1>=0.0) && (fx3>=0.0)))
                x1 = x3;
            else
                x2 = x3;
            cuenta = cuenta + 1;
            if(fabs(fx3)<epsilon)
                raizEncontrada = 1;
        }
        if(raizEncontrada)
            printf("\nLa raiz es=%lf, con una exactitud de %lf", x3, epsilon);
        else
            printf("\nLo sentimos, no pudimos encontrar la raiz de %d iteraciones",
                    CUENTAMAXIMA);
    }
    return (EXIT_SUCCESS);
}

