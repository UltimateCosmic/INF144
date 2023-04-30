/* 
 * Proyecto: EX2_2021-1_Preg_01
 * Archivo:  StructLibro.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 06:53 AM
 */

#ifndef STRUCTLIBRO_H
#define STRUCTLIBRO_H

struct Libro{
    char codigo[8];
    char titulo[60];
    char autor[60];
    int aPublicacion;
    int cantidad;
    int prestamos;
};

#endif /* STRUCTLIBRO_H */

