/* 
 * Proyecto: EX2_2021-1_Preg_01
 * Archivo:  StructPrestamo.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 07:20 AM
 */

#ifndef STRUCTPRESTAMO_H
#define STRUCTPRESTAMO_H
#include "StructLibroPrestado.h"

struct Prestamo{
    int codigo;
    char nombre[60];
    struct LibroPrestado libro[7];
    int cantidadDeLibros;    
};

#endif /* STRUCTPRESTAMO_H */

