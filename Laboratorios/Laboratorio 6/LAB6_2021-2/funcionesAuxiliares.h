/* 
 * Proyecto: LAB6_2021-2
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 04:45 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructCursoMatriculado.h"

void crearArchCursosBin(const char *, const char *);
void crearArchEscalasBin(const char *, const char *);
void crearArchAlumnosBin(const char *, const char *);
void leerArchNotasCsv(const char *, const char *);
void completarDatosDeAlumnos(char **, FILE *);
void datosDelArchivo(FILE *, int, int *, int *);
void extraerFecha(char *, int *, int *, int *);
int juntarFecha(int, int, int);
void calcularDatosArchAlumnosBin(const char *);
double buscarCreditos(struct CursoMatriculado, char const *);
double calcularPago(struct CursoMatriculado, char *, char const *);
void separarFecha(int, int *, int *, int *);
void separarSemestre(int, int *, int *);
int verificarCiclo(int, int, int, int);
void imprimirReporteDeCuentas(char const *,char const *);
void imprimirLinea(FILE *, char, int);
void imprimirCabecera(FILE *);
void imprimirTotalRecaudado(FILE *, double);

#endif /* FUNCIONESAUXILIARES_H */

