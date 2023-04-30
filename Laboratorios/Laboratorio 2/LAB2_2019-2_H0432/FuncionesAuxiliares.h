/* 
 * Proyecto: LAB2_2019-2_H0432
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 04:55 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirListado(FILE *, FILE *);
int imprimirAlumnos(FILE *, FILE *);
int imprimirNombreAlumno(FILE *, FILE *);

void imprimirEspacios(FILE *, int);
int imprimirFechaDeNacimiento(FILE *, int, int, int);
int calcularFecha(int, int, int);
void convertirLetraMayuscula(char *);
void convertirLetraMinuscula(char *);
void imprimirLinea(FILE *, char, int);
void cerrarListado(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

