/* 
 * Proyecto: PC1_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 04:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 70

int main(int argc, char** argv) {
    
    while(1){        
        int a, b, cantPrimos=0;
        printf("Ingrese el rango a y b: ");
        scanf("%d %d",&a,&b);

        if(validarRango(a,b)){
            if(b<=64){
                imprimirPrimos(a,b,&cantPrimos);
                printf("Total de valores primos: %d\n",cantPrimos);  
            }else
                printf("EL RANGO DE VALORES NO PUEDE SOBREPASAR EL VALOR 64\n");   
        }else
            printf("EL RANGO DE VALORES NO ES CORRECTO\n");
        
        imprimirLinea('-',MAX_LINEA);
    }
    return (EXIT_SUCCESS);
}

