/* 
 * Proyecto: 2022_1_ArchivosBinarios_Laboratorio6
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 08:05 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructAutor.h"

void crearArchAutoresBin(const char *, const char *);
void verificarArchAutoresBin(const char *, const char *);
void datosDelArchivo(FILE *, int, int *, int *);
void crearArchLibrosBin(const char *, const char *);
void asignarAutores(struct Autor *, char **, int, int *);
void verificarArchLibrosBin(const char *, const char *);
void actualizarInfoArchBin(const char *, const char *);
void actualizarInfoLibro(struct Autor *, const char *, double);
double calcularPorcentaje(double, double);
void imprimirReporteRecaudacion(const char *);
void imprimirReporteRecaudacion(const char *);
void imprimirLinea(FILE *, char, int);
void imprimirRecaudacionPorLibros(FILE *, const char *);
void imprimirCabeceraLibros(FILE *);
void imprimirAutoresDeLibros(FILE *, struct Autor *, int);
void imprimirCabeceraAutoresDeLibros(FILE *);
void imprimirRecaudacionPorAutores(FILE *, const char *);
void imprimirCabeceraRegaliaPorAutores(FILE *);
void imprimirTotales(int, double, double, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

