/* 
 * Proyecto: EX2_2021-2_Preg_01
 * Archivo:  StructProducto.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 03:07 AM
 */

#ifndef STRUCTPRODUCTO_H
#define STRUCTPRODUCTO_H

struct Producto{
    char codigo[7];
    char descripcion[60];
    int stock;
    double precio;
};

#endif /* STRUCTPRODUCTO_H */

