/* 
 * Proyecto: Taller_1_2019-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 3 de abril de 2022, 09:07 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirReporte(FILE *, FILE *);
double calcularMonto(double, double, int);
int convertirSegundosAMinutos(int);
void calcularTiempoEfect(int *, int *, int *, int);
int calcularTiempoEnSegundos(int, int, int, int, int, int);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

