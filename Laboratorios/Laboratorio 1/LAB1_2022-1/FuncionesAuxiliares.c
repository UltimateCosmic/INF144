/* 
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    20203350, Johan Amador
 * Fecha y hora: 5 de abril de 2022, 08:08 AM
 * 
 */

#include <stdio.h>
void imprimirResultado(double real, double imaginario){
    if(imaginario<0)
        printf("\nResultado: %0.2lf - %0.2lfi\n", real, imaginario*(-1));
    else
        printf("\nResultado: %0.2lf + %0.2lfi\n", real, imaginario);
}