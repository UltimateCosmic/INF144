/* 
 * Proyecto: EX2_2021-1_Preg_02
 * Archivo:  StructRegPrestamos.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 08:12 PM
 */

#ifndef STRUCTREGPRESTAMOS_H
#define STRUCTREGPRESTAMOS_H
#include "StructLibroPrestado.h"

struct RegPrestamos{
    int codigo;
    char *nombre;
    struct LibroPrestado *libro;
    int cantidadDeLibros;    
};

#endif /* STRUCTREGPRESTAMOS_H */

