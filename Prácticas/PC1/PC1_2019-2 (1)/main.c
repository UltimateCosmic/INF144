/* 
 * Proyecto: PC1_2019-2_1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 11 de abril de 2022, 05:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 50

int main(int argc, char** argv) {    
    
    int limInf, limSup;    
    while(1){
        
        printf("Ingrese un rango de valores mayores a 1000:\n");
        scanf("%d %d",&limInf,&limSup);
        
        if(limInf==0 && limSup==0) break;        
        else if(validarRango(limInf,limSup))
            imprimirCifrasNoRepetidas(limInf,limSup);
        
        imprimirLinea('-',MAX_LINEA);
    }
    printf("Fin del programa\n");
    
    return (EXIT_SUCCESS);
}