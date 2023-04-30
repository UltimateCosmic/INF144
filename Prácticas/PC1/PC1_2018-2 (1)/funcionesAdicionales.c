/* 
 * Proyecto: PC1.2_2018-2
 * Archivo:  funcionesAdicionales.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 12:25 PM
 */

#include <stdio.h>
#include <stdlib.h>

int verificarFin(int x, int y){
    return x==0 && y==0? 1:0;   
}

void imprimirResultados(int lados, double area){
    printf("\nResultados:\n");
    printf("El poligono tiene %d lados\n",lados);
    printf("Su area es: %.2lf\n",area);    
}

void coordenadasAuxiliares(int *xAux, int *yAux, int x, int y){
    *xAux = x;
    *yAux = y;    
}

void actualizarSumatorias(int *s1, int *s2, int x, int y, int xAux, int yAux){
    *s1 += x*yAux;
    *s2 += y*xAux;
}