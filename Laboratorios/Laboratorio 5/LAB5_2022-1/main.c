/* 
 * Proyecto: LAB05_ArchivosCSV
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"
#include "StructAutor.h"
#define MAX_AUTORES 100
#define MAX_LIBROS 400

int main(int argc, char** argv) {

    //Archivo: Autores.csv
    int cantAutores=0, vendAutor[MAX_AUTORES]={};
    char *codAutor[MAX_AUTORES], *nombreAutor[MAX_AUTORES];
    double regaliasAutor[MAX_AUTORES]={};
    leerAutores(codAutor,nombreAutor,&cantAutores);
    
    //Archivo: Libros.csv
    int vendLibros[MAX_LIBROS], cantLibros=0;
    char *codLibro[MAX_LIBROS], *nombreLibro[MAX_LIBROS];
    double precioLibro[MAX_LIBROS];
    leerLibros(codLibro,nombreLibro,precioLibro,vendLibros,&cantLibros,codAutor,
            regaliasAutor,vendAutor,cantAutores);
    
    //Ordenación de arreglos
    ordenarAutores(codAutor,nombreAutor,regaliasAutor,vendAutor,cantAutores);
    ordenarLibros(codLibro,nombreLibro,precioLibro,vendLibros,cantLibros);
    
    //Archivo: ReporteDeIngresosYPagos.txt
    imprimirReporteDeIngresosYPagos(codAutor,nombreAutor,regaliasAutor,vendAutor,
            cantAutores,codLibro,nombreLibro,precioLibro,vendLibros,cantLibros);
    
    //Estructura (struct)
    struct Autor autores[MAX_AUTORES];
    copiarDatosAEstructura(autores,codAutor,nombreAutor,vendAutor,regaliasAutor,
            cantAutores);
    
    //Archivo: ReporteAutores
    imprimirReporteAutores(autores,cantAutores);
        
    return (EXIT_SUCCESS);
}

