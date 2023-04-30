/* 
 * Proyecto: PC2_2019-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 19 de abril de 2022, 12:35 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archCuentos, *archControlDeEscritura;
    
    archCuentos = fopen("cuentos.txt","r");
    if(archCuentos==NULL){
        printf("ERROR: No se pudo abrir el archivo cuentos.txt\n");
        exit(1);        
    }
    archControlDeEscritura = fopen("ControlDeEscritura.txt","w");
    if(archControlDeEscritura==NULL){
        printf("ERROR: No se pudo abrir el archivo ControlDeEscritura.txt\n");
        exit(1);        
    }
    imprimirControlDeEscritura(archCuentos,archControlDeEscritura);
    cerrarArchivos(archCuentos,archControlDeEscritura);    

    return (EXIT_SUCCESS);
}

