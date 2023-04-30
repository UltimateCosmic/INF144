/* 
 * Proyecto: EX2_2021-2_Preg_01
 * Archivo:  StructProductoSolicitado.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 03:04 AM
 */

#ifndef STRUCTPRODUCTOSOLICITADO_H
#define STRUCTPRODUCTOSOLICITADO_H

struct ProductoSolicitado{
    char codigo[7];
    char descripcion[60];
    int cantidad;
    double precioUnitario;
    double subtotal;
};


#endif /* STRUCTPRODUCTOSOLICITADO_H */

