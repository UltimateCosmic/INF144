/* 
 * Proyecto: PC1_2019-2
 * Archivo:  FuncionesAdicionales.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de marzo de 2022, 04:23 PM
 */

#ifndef FUNCIONESADICIONALES_H
#define FUNCIONESADICIONALES_H

int verificarFinDePrograma(int, int, int);
void primerContadorEstadistico(int *, double);
void segundoContadorEstadistico(int *, int, int);
int calcularTiempo(int, int, int, int, int, int);
void tercerDatoEstadistico(int *, double *, double, double);
void cuartoDatoEstadistico(double *, int *, int, double);
void quintoDatoEstadistico(int *, int *, int *, double *, double, int);
void convertirTiempo(int *, int *, int *, int);
void imprimirEstadisticas(int, int, double, int, int, int);

#endif /* FUNCIONESADICIONALES_H */