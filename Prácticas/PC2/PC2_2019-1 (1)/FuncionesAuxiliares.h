/* 
 * Proyecto: PC2_2019-1_2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 20 de abril de 2022, 06:28 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirReporte(FILE *, FILE *);
void imprimirConsultas(FILE *, FILE *, double);
void imprimirConsultaPorFecha(FILE *, FILE *, int, int, int, double, double *, 
                              double *, int *, int *, int *, int *, int *);
int duracion(int, int, int);
double calcularMonto(int, double, double);
int juntarFecha(int, int, int);
double calcularPorcentaje(double, double);
void calcularTiempoEfectivo(int, int *, int *, int *);
void imprimirEstadisticas(FILE *, double, double, int);
void imprimirMaximosObtenidos(FILE *, int, int, int, int);
void separarFecha(int, int *, int *, int *);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

