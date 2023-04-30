/* 
 * Proyecto: PC1_2019-2_1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 11 de abril de 2022, 05:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

void imprimirCifrasNoRepetidas(int limInf, int limSup){
    
    int totalDeValores=0;
    printf("Los con cifras no repetidas son:\n");
    
    while(limInf<limSup){        
        if(numeroNoTieneCifrasRepetidas(limInf)){
            printf("%d\n",limInf);
            totalDeValores++;    
        }
        limInf++;
    }    
    printf("Total de valores: %d\n",totalDeValores);
}

int numeroNoTieneCifrasRepetidas(int num){
    
    int aux1=num, aux2, dig1, dig2;
    
    while(aux1!=0){
        dig1 = aux1%10;
        aux1 /= 10;        
        aux2 = aux1;
        
        while(aux2!=0){            
            dig2 = aux2%10;            
            if(dig1==dig2)
                return 0;            
            aux2 /= 10;            
        }
    }
    return 1;
}

void imprimirLinea(char caracter, int cantVeces){    
    for(int i=0; i<cantVeces; i++) putchar(caracter);
    putchar('\n');
}

int validarRango(int limInf, int limSup){    
    
    if(limInf>1000 && limInf<limSup)  
        return 1;
    else{
        printf("El rango ingresado no es valido\n");
        return 0;        
    }   
}