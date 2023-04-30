/* 
 * Proyecto: LAB2_2019-2_H0431_2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 04:49 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *);
void imprimirSismos(FILE *, FILE *, double *, double *);
void calcularHoraFin(int,int, int, int, int *, int *, int *);
int convertirHoraASegundos(int, int, int);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

