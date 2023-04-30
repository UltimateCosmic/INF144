/* 
 * Proyecto: LAB2_2019-2_H0432
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 04:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archAlumnos, *archListado;
    
    archAlumnos = fopen("alumnos.txt","r");
    if(archAlumnos==NULL){
        printf("ERROR: No se pudo abrir el archivo alumnos.txt\n");
        exit(1);
    }
    
    archListado = fopen("listado.txt","w");
    if(archListado==NULL){
        printf("ERROR: No se pudo abrir el archivo listado.txt\n");
        exit(1);
    }
    imprimirListado(archAlumnos,archListado);
    cerrarListado(archAlumnos,archListado);    

    return (EXIT_SUCCESS);
}

