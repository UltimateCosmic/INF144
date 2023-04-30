/* 
 * Proyecto: LAB4_2021-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de mayo de 2022, 07:36 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(char *, char *);
void leerPedidos(int *, int *, int *, int *, int *);
void ordenarPedidos(int *, int *, int *, int *, int);
void cambiarInt(int *, int, int);
void leerStockDeProductos(int *, int *, double *, int *);
void ordenarStockDeProductos(int *, int *, double *, int);
void cambiarDouble(double *, int, int);
void leerDetalleDeLosPedidos(int *, int *, int *, int *);
void imprimirReporteDePedidos(int *, int *, int *, int *, int, int *, int *, 
                              double *, int, int *, int *, int *, int);
void imprimirCabeceraPrincipal(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirCabeceraDePedido(int, int, FILE *, int, int, FILE *);
void separarFecha(int, int *, int *, int *);
void separarHora(int, int *, int *, int *);
void modificarNombre(char *, char *);
char convertirMinuscula(char);
void imprimirProductosSolicitados(int, int *, int *, double *, int, int *, int *, 
                                  int *, int, FILE *);
void imprimirCabeceraDeProductos(FILE *);
int buscarPos(int, int *, int);

#endif /* FUNCIONESAUXILIARES_H */

