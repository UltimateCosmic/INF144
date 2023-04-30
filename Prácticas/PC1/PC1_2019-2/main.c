/* 
 * Proyecto: PC1_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 7 de abril de 2022, 09:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    int resultado1, resultado4_1, resultado4_2, resultado5;
    double resultado2, resultado3;    
    
    resultado1=resultado4_1=resultado4_2=resultado5=0;
    resultado2=resultado3=0.0;
    resultado2=1;
    
    leerDatos(&resultado1, &resultado2, &resultado3, &resultado4_1, 
            &resultado4_2, &resultado5);
    imprimirResultados(resultado1, resultado2, resultado3, resultado4_1, 
            resultado4_2, resultado5);

    return (EXIT_SUCCESS);
}