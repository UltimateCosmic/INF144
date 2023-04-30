/* 
 * Proyecto: PC2_2021-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de abril de 2022, 04:18 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerProductos(int *, int *, double *);
void imprimirReporte(int *, int, double *);
void imprimirEntregaDeProductos(FILE *, FILE *, int *, int, double *);
int imprimirDestino(FILE *, FILE *, int, FILE *);
int comprobarNoHayVentas(int, FILE *);
void imprimirNombreDeLaTienda(FILE *, FILE *);
void imprimirEntregasPorFecha(FILE *, FILE *, int, int *, int, double *, int *, 
                              double *);
void imprimirEntregaCliente(FILE *, FILE *, int, int *, int, double *, int, 
                            int *, double *, int *, double *);
int imprimirListaDeEntregas(FILE *, FILE *, int, int *, int, double *, int,
                            int *, double *, int, int, int, int, int *, double *);
void imprimirProducto(FILE *, int, int, int, int, int, double *, double *, int, 
                      int *, int, int *, double *);
double buscarPrecioProducto(int, int *, double *, int, int *);
void imprimirResumenPorTienda(FILE *, int, double);
void imprimirResumenTotal(FILE *, int *, double *, int, int *);
void leerTienda(FILE *, int *);
void buscarIndicesVentas(double *, int, int *, int *);
double calcularTotalVentas(double *, int);

void imprimirLinea(FILE *, char, int);

#endif /* FUNCIONESAUXILIARES_H */

