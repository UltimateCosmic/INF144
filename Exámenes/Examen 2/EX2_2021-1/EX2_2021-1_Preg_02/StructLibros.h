/* 
 * Proyecto: EX2_2021-1_Preg_02
 * Archivo:  StructLibros.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 07:59 PM
 */

#ifndef STRUCTLIBROS_H
#define STRUCTLIBROS_H

struct Libros{
    char *codigo;
    char *titulo;
    char *autor;
    int aPublicacion;
    int cantidad;
    int prestamos;    
};

#endif /* STRUCTLIBROS_H */

