/* 
 * Archivo:  main.c
 * Autor:    20203350, Johan Amador
 * Fecha y hora: 5 de abril de 2022, 08:03 AM
 * 
 * ********************************************************************
 * Programa que permite realizar operaciones aritméticas empleando
 * números complejos de la forma "a + bi".
 * ********************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include "NumerosComplejos.h"
#include "FuncionesAuxiliares.h"


int main(int argc, char** argv) {
    /*declaración de variables*/
    char opcion, operador;
    double a, b, c, d, real, imaginario;
    double numReal, numImag;
    int n = 0;
    
    printf("\nIngrese un numero complejo: ");
    char i;
    scanf("%lf %lf%c", &a, &b, &i);    
    
    while(1){
        printf("\nIngrese la operacion y el siguiente numero complejo: ");
        scanf("\n%c", &opcion);
        if((opcion == 'F') || (opcion == 'f')) break;
        if((opcion == 'P') || (opcion =='p')){
            scanf("%d", &n);
            potenciar(a, b, n, &real, &imaginario);
        }
        else{
            scanf("%lf %lf%c", &c, &d, &i);
            if((opcion == 'S') || (opcion =='s'))
                sumar(a, b, c, d, &real, &imaginario);
            else if((opcion == 'R') || (opcion =='r'))
                restar(a, b, c, d, &real, &imaginario);
            else if((opcion == 'M') || (opcion =='m'))
                multiplicar(a, b, c, d, &real, &imaginario);
            else if((opcion == 'D') || (opcion =='d')){
                dividir(a, b, c, d, &real, &imaginario);
            }
        }
        a = real ; b = imaginario;
        imprimirResultado(real, imaginario);
        i2++;
    }        
    return (EXIT_SUCCESS);
}