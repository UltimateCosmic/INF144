/* 
 * Proyecto: 2022_1_ArchivosBinarios_Laboratorio6
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"

int main(int argc, char** argv) {

    //1.
    crearArchAutoresBin("autores.csv","autores.bin");
    verificarArchAutoresBin("ReporteDeVerificacionAutores.txt","autores.bin");
    
    //2.
    crearArchLibrosBin("libros.csv","libros.bin");
    verificarArchLibrosBin("ReporteDeVerificacionLibros.txt","libros.bin");
    
    //3.
    actualizarInfoArchBin("autores.bin","libros.bin");
       
    //5.
    imprimirReporteRecaudacion("reporteRecaudacion.txt");
    
    
    return (EXIT_SUCCESS);
}

