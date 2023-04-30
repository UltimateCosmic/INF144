/* 
 * Proyecto: LAB2_2021-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 25 de abril de 2022, 03:50 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *, FILE *);
void imprimirCabecera(FILE *);
void imprimirDetallesCurso(FILE *, FILE *, FILE *, int, int, int *, int *, 
                           double *);
void imprimirRelacionDeAlumnos(FILE *, FILE *, int, int, int *, int *, double *);
void imprimirAlumnos(FILE *, FILE *, int, int, int, int, int, int *, int *, 
                     int *, int *);
void imprimirEspacios(FILE *, int);
int calcularCantDig(int);
void imprimirResumen(FILE *, int, int, int, int, int, int *, int *, double *, 
                     int, int);
double calcularPorcentaje(int, int);
double calcularRelacion(int, int);
void imprimirNombreDelCurso(FILE *, FILE *);
void imprimirDatosFinales(FILE *,FILE *, int, int, int, double);
void imprimirNombreCurso(FILE *, FILE *, int, int);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */