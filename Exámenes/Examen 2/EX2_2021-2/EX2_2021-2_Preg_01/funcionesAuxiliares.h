/* 
 * Proyecto: EX2_2021-2_Preg_01
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 02:36 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructPedido.h"
#include "StructProductoSolicitado.h"

void crearArchStockDeProductosBin(const char *, const char *);
void imprimirRepStockDeProductos(const char *, const char *);
void crearArchPedidosPorInternetBin(const char *, const char *);
void imprimirRepPedidosPorInternetBin(const char *, const char *);
void completarArchPedidosPorInternetBin(const char *, const char *, const char *);
void asignarDetalleDePedido(int, char *, int, FILE *, FILE *);
int buscarPosPedido(int, FILE *);
void datosDelArchivo(FILE *, int, int *);
int buscarPosProducto(char *, FILE *);
int hayStock(int);
void imprimirReporteDePedidos(const char *, const char *);
void imprimirCabecera(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirPedido(struct Pedido, FILE *);
void separarFecha(int, int *, int *, int *);
void separarHora(int, int *, int *, int *);
void separarHora(int, int *, int *, int *);
void imprimirProductos(struct ProductoSolicitado *, int, FILE *);
void imprimirCabeceraDeProductos(FILE *);

#endif /* FUNCIONESAUXILIARES_H */

