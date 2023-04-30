/* 
 * Proyecto: PC2_2019-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 19 de abril de 2022, 12:39 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirControlDeEscritura(FILE *, FILE *);
int imprimirCuento(FILE *, FILE *);
void imprimirTitulo(FILE *, FILE *);
char convertirMayuscula(char);
void imprimirEstadisticasDelCuento(FILE *, int, int, int, double, double);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

