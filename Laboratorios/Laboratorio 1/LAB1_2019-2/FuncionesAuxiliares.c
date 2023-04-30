/* 
 * Proyecto: PC1_2019-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 04:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int validarRango(int a, int b){
    return b>a? 1:0;
}

void imprimirPrimos(int a, int b, int *ptr_cantPrimos){    
    while(a<=b){
        if(esPrimo(a) && a!=0){
            printf("%d\n",a);
            (*ptr_cantPrimos)++;
        }
        a++;
    }
}

int esPrimo(int num){    
    
    // Método vintage (clásico)
    /*int cantDivisores=0;
    for(int i=1; i<=num; i++)    
        if(num%i==0) cantDivisores++;
    return cantDivisores==2;*/
    
    for(int i=1; i<num; i++){
        unsigned long long coeficiente = calcularCoeficiente(num,i);        
        if(coeficiente%num!=0) return 0;     
    }
    return 1;
}

unsigned long long calcularCoeficiente(int n, int r){    
    return factorial(n)/(factorial(r)*factorial(n-r));
}

unsigned long long factorial(int num){  
    unsigned long long producto=1;
    for(int i=1; i<=num; i++)
        producto*=i;
    return producto;
}

void imprimirLinea(char simbolo, int cantVeces){    
    for(int i=1; i<cantVeces; i++) printf("%c",simbolo);
    printf("\n");    
}