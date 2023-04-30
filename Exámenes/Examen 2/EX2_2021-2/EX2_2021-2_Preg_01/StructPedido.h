/* 
 * Proyecto: EX2_2021-2_Preg_01
 * Archivo:  StructPedido.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 02:58 AM
 */

#ifndef STRUCTPEDIDO_H
#define STRUCTPEDIDO_H
#include "StructProductoSolicitado.h"

struct Pedido{
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct ProductoSolicitado productosPedidos[20];
    int cantProdPed;    
};

#endif /* STRUCTPEDIDO_H */

