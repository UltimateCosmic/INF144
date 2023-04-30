/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 23 de marzo de 2022, 10:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "NumerosComplejos.h"

int main(int argc, char** argv) {
    
    int n, cantDatosLeidos;
    double a, b, c, d;
    char operacion;
    
    printf("Ingrese un numero complejo: ");
    scanf("%lf %lfi", &a, &b);
    
    while(1){
        
        printf("Ingrese la operacion y el siguiente numero complejo:\n");
        cantDatosLeidos = scanf(" %c", &operacion, &c, &d);        
        if(cantDatosLeidos==2) n = (int)c;
        
        if(operacion=='F') break;
        else if(operacion=='S'||operacion=='s'){
            scanf("%lf %lfi",&c, &d);
            suma(&a,&b,c,d);
        }
        else if(operacion=='R'||operacion=='r') {
            scanf("%lf %lfi",&c, &d);
            resta(&a,&b,c,d);
        }           
        else if(operacion=='M'||operacion=='m'){
            scanf("%lf %lfi",&c, &d);
            multiplicacion(&a,&b,c,d); 
        }            
        else if(operacion=='D'||operacion=='d'){
            scanf("%lf %lfi",&c, &d);
            division(&a,&b,c,d);
        }            
        else if(operacion=='P'||operacion=='p'){
            scanf("%d",&n);
            potencia(&a,&b,n);
        }            
        
        if(b>=0) printf("Resultado: %.2lf + %.2lfi\n",a,b);
        else printf("Resultado: %.2lf - %.2lfi\n",a,-b);
    }        
    if(b>=0) printf("El resultado final es %.2lf + %.2lfi\n",a,b);
    else printf("El resultado final es %.2lf - %.2lfi\n",a,-b);
    
    return (EXIT_SUCCESS);
}