/* 
 * Proyecto: EX2_2021-1_Preg_02
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 07:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"
#include "StructLibros.h"
#include "StructRegPrestamos.h"

int main(int argc, char** argv) {

    //a)
    int numLibros=0;
    struct Libros *libros;
    libros = (struct Libros *)malloc(sizeof(struct Libros)*100);
    leerLibros(libros,&numLibros);
    imprimirRepLibros(libros,numLibros);
    
    //b)
    int numRegPres=0;
    struct RegPrestamos *prestamos;
    prestamos= (struct RegPrestamos *)malloc(sizeof(struct Libros)*100);
    leerRegPrestamos(prestamos,&numRegPres);
    imprimirRepRegPrestamos(prestamos,numRegPres);
    
    //c)
    actualizarEstructuras(libros,numLibros,prestamos,&numRegPres);
    
    
    return (EXIT_SUCCESS);
}

