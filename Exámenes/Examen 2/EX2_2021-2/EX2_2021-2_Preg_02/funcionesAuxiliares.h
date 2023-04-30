/* 
 * Proyecto: EX2_2021-2_Preg_02
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 04:57 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructStockProd.h"
#include "StructPedidos.h"

void leerStockDeProductos(struct StockProd *, int *);
void imprimirRepStockDeProductos(struct StockProd *, int);
void leerPedidos(struct stPedidos *, int *);
void imprimirRepPedidos(struct stPedidos *, int);
void completarPedidos(struct stPedidos *, int, struct StockProd *, int);
void asignarProducto(int, char *, int, 
                     struct stPedidos *, int, 
                     struct StockProd *, int);
int buscarPosProd(char *, struct StockProd *, int);
int buscarPosPed(int, struct stPedidos *, int);
int hayStock(int);
void imprimirReporteDePedidos(struct stPedidos *, int);
void imprimirCabeceraPrincipal(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirDetallesDePedidos(struct stPedidos *, FILE *);
void imprimirCabeceraDeDetalles(FILE *);
void separarFecha(int, int *, int *, int *);
void separarHora(int, int *, int *, int *);
void imprimirProductosEntregados(struct stPedidos *, FILE *);
void imprimirProductosNoEntregados(struct stPedidos *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

