/* 
 * Proyecto: LAB4_2021-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de mayo de 2022, 12:10 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(char *, char *);
void leerProductosAlmacenados(int *, double *, int *);
void ordenarProductos(int *, double *, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void leerPlatosAPreparar(int *, int *, int *);
void ordenarPlatos(int *, int *, int);
void leerListaDePrecios(int *, double *, int);
int buscarPosicion(int, int *, int);
void procesarPerdidas(int *, double *, int, int *, int *, int, double *, 
                      double *);
void leerIngredientes(int *, double *, int, int *, FILE *, double *, double *);
void calcularSubtotalProd(double *, double *, double *, int);
void calcularSubtotalPlatos(double *, int *, double *, int);
void imprimirReporteDePerdidas(int *, double *, double *, int, int *, int *, 
                               double *, int, double *, double *);
void imprimirProductosDescompuestos(int *, double *, double *, int, FILE *, 
                                    double *);
void imprimirCabeceraProductos(FILE *);
void ordenarProductosPorSubtotal(int *, double *, double *, double *, int);
void imprimirCostoTotalProductos(FILE *, double);
void imprimirPlatosQueNoSePodranPreparar(int *, int *, double *, int, FILE *,
                                         double *);
void imprimirCabeceraPlatos(FILE *);
void ordenarPlatosPorSubtotal(int *, int *, double *, int, double *);
void imprimirCostoTotalPlatos(FILE *, double);
void imprimirLinea(FILE *, char, int);

#endif /* FUNCIONESAUXILIARES_H */

