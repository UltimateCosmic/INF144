/* 
 * Proyecto: EX2_2021-1_Preg_01
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 06:47 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"

int main(int argc, char** argv) {

    //a)    
    crearArchLibrosBin("Libros.bin","Libros.csv");
    imprimirRepLibros("Libros.bin","RepLibros.txt");
    
    //b)
    crearArchRegistroDePrestamosBin("RegistroDePrestamos.bin","RegistroDePrestamos.csv");
    imprimirRepRegPrestamos("RegistroDePrestamos.bin","RepRegPrestamos.txt");
    
    //c)
    completarArchivosBin("Libros.bin","RegistroDePrestamos.bin",
            "ReporteAtencionDePrestamos.txt","SolicitudesDePrestamos.csv");
    imprimirRepLibros("Libros.bin","RepLibros2.txt");
    imprimirRepRegPrestamos("RegistroDePrestamos.bin","RepRegPrestamos2.txt");
    
    return (EXIT_SUCCESS);
}

