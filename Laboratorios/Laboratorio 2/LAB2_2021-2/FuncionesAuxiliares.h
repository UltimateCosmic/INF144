/* 
 * Proyecto: LAB2_2021-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 19 de abril de 2022, 03:16 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirReporteDePagos(FILE *, FILE *, FILE *, FILE *);
void imprimirPacientes(FILE *, FILE *, FILE *, FILE *);
int imprimirNombrePaciente(FILE *, FILE *);
char convertirMinuscula(char);
void imprimirEspacios(FILE *, int);
void imprimirDistrito(FILE *, FILE *);
void imprimirRelacionDeConsultas(FILE *, FILE *, FILE *, int);
void buscarConsultas(FILE *, FILE *, FILE *, int, int, int, int, int, double *);
void calcularDuracion(int, int, int, int, int, int, int *, int *);
int duracionEnSegundos(int, int, int);
void buscarTarifa(FILE *, int, double *);
double calcularMontoPagado(double, int, int);
char convertirMayuscula(char);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

