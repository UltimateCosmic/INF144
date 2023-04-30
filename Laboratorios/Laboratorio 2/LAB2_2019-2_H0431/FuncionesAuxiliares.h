/* 
 * Proyecto: LAB2_2019-2_H0431
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 03:32 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirListado(FILE *, FILE *);
void imprimirAlumnos(FILE *, FILE *, int *);
int imprimirNombre(FILE *, FILE *);
void convertirLetraAMinuscula(char *);
void convertirLetraAMayuscula(char *);
void imprimirEspacios(FILE *, int);
int imprimirFecha(int, int, int, FILE *);
int convertirFecha(int, int, int);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

