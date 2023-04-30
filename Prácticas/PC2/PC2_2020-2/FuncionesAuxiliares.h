/* 
 * Proyecto: PC2_2020-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 21 de abril de 2022, 05:17 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *, FILE *, FILE *);
void imprimirResultadosAlumnos(FILE *, FILE *, FILE *, FILE *);
void imprimirCursos(FILE *, FILE *, FILE *, int, int, double, double, int *);
void imprimirDetallesCurso(FILE *, FILE *,  int, int, int, int *, int *, 
                           double *, double *, double *, double *, double *);
double buscarNotaAlumno(FILE *, int);
void imprimirResumenes(FILE *, double, double, double, double, int, int, 
                       double, double, double);
void imprimirResumen(FILE *, int, double, double, double);
void imprimirCreditosAcumuladosYPromedioDeNotas(FILE *, double, double, double);
double calcularPorcentaje(double, double);
void imprimirDetallesFinales(FILE *, int, int);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

