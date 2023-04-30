/* 
 * Proyecto: 2022_1_ArchivosBinarios_Laboratorio6
 * Archivo:  StructLibro.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 08:11 AM
 */

#ifndef STRUCTLIBRO_H
#define STRUCTLIBRO_H
#include "StructAutor.h"

struct Libro{
    char codigo[9];
    char nombre[200];
    double precio;
    struct Autor autor[10];
    int cantAutores;
    int cantVend;
    double montoRecaudado;    
};

#endif /* STRUCTLIBRO_H */

