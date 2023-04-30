/* 
 * Proyecto: PC1.2_2018-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 12:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAdicionales.h"

int main(int argc, char** argv) {  
    
    int x,y,xAux=0,yAux=0,s1=0,s2=0,lados=0;
    double area;
    printf("Ingrese las coordenadas del poligono:\n");    
    
    while(1){
        scanf("%d %d",&x,&y);
        if(verificarFin(x,y)) break;  
        actualizarSumatorias(&s1,&s2,x,y,xAux,yAux);        
        coordenadasAuxiliares(&xAux,&yAux,x,y);
        lados++;
    }
    area = (double)(s1-s2)/2;
    imprimirResultados(lados,area);
    
    return (EXIT_SUCCESS);
}