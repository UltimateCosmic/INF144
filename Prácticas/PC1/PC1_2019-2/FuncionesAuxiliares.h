/* 
 * Proyecto: PC1_2019-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 8 de abril de 2022, 01:21 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerDatos(int *, double *, double *, int *, int *, int *);
void determinarPCN(int, int *, int *, int *);
void actualizarResultado1(int *, int, int);
void actualizarResultado2(double *, int, int, int, int, int, int, double);
void actualizarResultado3(double *, int, int, int, int, double, int *);
void actualizarResultado4(int *, int *, int, double, double *, double *);
void actualizarMayorTarifa(int *, double *, int, double);
void actualizarMenorTarifa(int *, double *, int, double);
void actualizarResultado5(int *, int, int, int, int, int, int *, double *);
double calcularPromedioTarifa(int, int, int, double);
int calcularTiempo(int, int, int);
int verificarFinDeDatos(int, int, int, int, int, int, int, int, int, int, double);
void imprimirResultados(int, double, double, int, int, int);

#endif /* FUNCIONESAUXILIARES_H */

