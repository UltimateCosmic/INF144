/* 
 * Proyecto: LAB4_2020-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 31 de mayo de 2022, 03:52 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(char *, char *);
void leerSalas(int *, int *, int *);
void ordenarSalasOPeliculas(int *, int *, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void leerPeliculas(int *, int *, int *);
int calcularCantDias(int, int, int, int, int, int);
int juntarFecha(int, int, int);
void leerFunciones(FILE *, int *, int);
void leerVentasYOcupacion(int *, int, int *, int *, double *, int *, int);
int buscarPosicion(int, int *, int);
void leerOcupacion(FILE *, int *);
void ordenarPeliculasPorRecaudacion(int *, int *, int *, int *, double *, int);
void imprimirReporteDeVentasYOcupaciones(int *, int *, int *, double *, int *,
                                         int);
void imprimirCabeceraPrincipal(FILE *);
void imprimirLinea(FILE *, char, int);
double calcularPorcentaje(int, int);
void imprimirResumen(FILE *, int, double, double);
void imprimirMenosYMasEsp(int, int, int *, int *, int *, double *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

