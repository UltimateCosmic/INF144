/* 
 * Proyecto: PC1_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 04:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcionesAuxiliares.h"
int main(int argc, char** argv) {
    const int MAX_CICLOS = 100;
    int veces, muchosCiclos, datosCorrectos, raizEncontrada;
    double c_4, c_3, c_2, c_1, c_0; /*Coeficientes de la ecuacion*/
    double x1, x2, x3, exactitud;
    /*x1 y x2 intervalo que contiene la raiz, x3 es el nuevo punto*/
    double f1x, f2x, f3x;
    /*primero encontraremos un intervalo que contiene la raiz */
    datosCorrectos = 0;
    muchosCiclos = 0;
    while(!datosCorrectos && !muchosCiclos){
        printf("Ingresar dos puntos de inicio: \n");
        scanf("%lf %lf",&x1,&x2);
        printf("Ingresar los coeficientes: c4 al c0 \n");
        scanf("%lf %lf %lf %lf %lf",&c_4,&c_3,&c_2,&c_1,&c_0);
        f1x = calculaFuncion(c_4,c_3,c_2,c_1,c_0,x1);
        f2x = calculaFuncion(c_4,c_3,c_2,c_1,c_0,x2);
        if((fabs(x1)<exactitud) && (fabs(x2)<exactitud) ) {
            muchosCiclos = 1;
        }
        else {
            if(((f1x <= 0.0) && (f2x >= 0.0)) || 
                    ((f1x >= 0.0) && (f2x <= 0.0))) {
                datosCorrectos = 1;
            }
            else {
                printf("Lo siento, los puntos dados no estan opuestos\n");
                printf("Ingresar 0,0 para terminar (puntos de inicio)\n");                
            }
        }
    }
    if (muchosCiclos) {
        printf("Lo siento, el programa se concluye por una falla\n");
        printf("para encontrar un intervalo inicial valido\n");
    }
    else {  //solución del problema
        printf("Ingresar la exactitud deseada: \n");
        scanf("%lf",&exactitud);
        raizEncontrada = 0;
        veces = 0;
        while (!raizEncontrada && (veces<=MAX_CICLOS)) {
            x3 = (x2*f1x - x1 * f2x) / (f1x - f2x);
            f3x = calculaFuncion(c_4,c_3,c_2,c_1,c_0,x3);
             if (fabs(f3x)<exactitud) // hemos encontrado la raiz exacta
                 raizEncontrada = 1;
            if(((f1x <= 0.0) && (f3x <= 0.0)) ||
                    ((f1x >= 0.0) && (f3x >= 0.0))) {
                x1 = x3; f1x = f3x;
            }
            else {
                x2 = x3; f2x = f3x;
            }
            veces += 1;
            if(fabs(f3x)<exactitud)
                raizEncontrada = 1;         
        }
        if(raizEncontrada)
            printf("\nLa raiz es = %lf, con una exactitud de %lf\n",
                    x3, exactitud);
        else
            printf("%s %d %s\n",
                    "\nLo sentimos, no pudimos encontrar la raiz en ",
                    MAX_CICLOS, " iteraciones");
    }
    return (EXIT_SUCCESS);
}

/*
 *                           Cuestionario de Paideia:
 * 
 *                                  <Pregunta 1>
 * - Error 1: Existe una equivocación al emplear las variables 'x_1' y 'x_2'
 *            en la línea 25, el identificador es diferente a como las declaramos.
 * - Error 2: Para emplear la funcion 'fabs' tenemos que incluir en el
 *            preprocesador la libreria '<math.h>'.
 * - Error 3: En la lïnea 34 usamos de manera equivocada el operador, tendríamos
 *            que usar el '>=' en vez del '=>'.
 * 
 *                      <Pregunta 2> Respuesta: 2.240000
 *                      <Pregunta 3> Respuesta: 8.505769
 * 
 *                                  <Pregunta 4>
 * while() - línea 24
 *              f1x                             f2x                                 f3x                              x3 
 * 0)   1.7930159226080222e-307 	8.0085886651527429e-307		8.0099128006799977e-307		1.7931696281391117e-307
 * 1)   -13.050960000000012		5.1038400000000061		8.0099128006799977e-307		1.7931696281391117e-307
 
 * while() - línea 54
 *              f1x                             f2x                                 f3x                              x3 
 * 2)   -34.624997639268202		5.1038400000000061		-34.624997639268202		-1.4590481856038073
 * 3)   -34.624997639268202		0.12858910699199563		0.12858910699199563		-0.79751255566014834
 * 4)   -34.624997639268202		0.0020553027523087727		0.0020553027523087727		-0.79996025340481336
 * 5)   -34.624997639268202		3.237918965321579e-005		3.237918965321579e-005		-0.7999993738359783
 * 
 *              <Pregunta 5> Respuesta: 3 ciclos - Raíz = 15.581064
 */

