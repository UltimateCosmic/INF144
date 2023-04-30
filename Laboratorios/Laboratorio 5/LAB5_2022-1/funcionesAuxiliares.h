/* 
 * Proyecto: LAB05_ArchivosCSV
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 08:06 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructAutor.h"

void leerAutores(char **, char **, int *);
void leerLibros(char **, char **, double *, int *, int *, char **, double *,
                int *, int);
void calcularRegaliasYVentas(char **, int, double *, char **, int, double, 
                             int *, int);
int buscarIndice(char *, char **, int);
double calcularPorcentaje(double, double);
void ordenarAutores(char **, char **, double *, int *, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void cambiarChar(char **, int, int);
void ordenarLibros(char **, char **, double *, int *, int);
void imprimirReporteDeIngresosYPagos(char **, char **, double *, int *, int,
                                     char **, char **, double *, int *, int);
void imprimirPagoALosAutores(FILE *, char **, char **, double *, int *, int);
void imprimirCabeceraDeAutores(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirRecaudacionPorLibrosVendidos(FILE *, char **, char **, double *,
                                          int *, int);
void imprimirCabeceraDeLibros(FILE *);
void copiarDatosAEstructura(struct Autor *, char **,  char **, int *, double *,
                            int);
void imprimirReporteAutores(struct Autor *, int);

#endif /* FUNCIONESAUXILIARES_H */

