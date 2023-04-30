/* 
 * Proyecto: LAB3_2021-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 9 de mayo de 2022, 06:20 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarProductos(int *, double *, int *);
void leerArrProductos(FILE *, int *, double *, int *);
void saltarNombre(FILE *);
void procesarTiendas(int *, int *, int *);
void leerArrTiendas(FILE *, int *, int *, int *);
void ordenarTiendas(int *, int *, int);
void cambiarInt(int *, int, int);
void procesarReporte(int *, double *, int, int *, int *, int);
void imprimirReporte(FILE *, FILE *, int *, double *, int, int *, int *, int);
void imprimirLinea(FILE *, char, int);
int comprobarVentas(int, FILE *, int *, int);
int comprobarProducto(FILE *, int *, int);
void imprimirTienda(FILE *, int, int);
void imprimirEntregaDeProductos(FILE *, FILE *, int, int *, double *, int, 
                                int *, double *);
void imprimirCabeceraEntregas(FILE *);
void imprimirEntregaIndividual(FILE *, FILE *, int *, double *, int, int, int *,
                               int *, double *, int *, double *);
double buscarPrecio(int, int *, double *, int, int *);
void imprimirResumenPorTienda(FILE * , int, double);
void imprimirResumenTotal(FILE *, int *, double *, int *, int);
void imprimirProductosDeResumen(FILE *, int *, double *, int *, int, int,
                                double);

#endif /* FUNCIONESAUXILIARES_H */

