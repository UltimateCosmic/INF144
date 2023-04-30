/* 
 * Proyecto: EX2_2021-2_Preg_02
 * Archivo:  StructPedidos.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 05:18 AM
 */

#ifndef STRUCTPEDIDOS_H
#define STRUCTPEDIDOS_H
#include "StructEntregado.h"
#include "StructNoEntregado.h"

struct stPedidos{
    int numero;
    int fecha;
    int hora;
    int cliente;
    struct Entregado *productosEntregados;
    int cantProdEnt;
    struct NoEntregado *productosNoEntregados;
    int cantProdNoEnt;
};

#endif /* STRUCTPEDIDOS_H */

