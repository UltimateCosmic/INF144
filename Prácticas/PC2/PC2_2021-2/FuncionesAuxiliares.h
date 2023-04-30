/* 
 * Proyecto: PC2_2021-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 21 de abril de 2022, 10:22 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *, FILE *);
void imprimirMedicos(FILE *, FILE *, FILE *);
int imprimirNombre(FILE *, FILE *);
char convertirMinuscula(char);
void imprimirEspacios(FILE *, int);
int imprimirEspecialidad(FILE *, FILE *);
void imprimirRelacionDeConsultasRealizadas(FILE *, FILE *, double *, int, double);
void imprimirConsultasPorFecha(FILE *, FILE *, int, int, int, double, double *);
void leerHoras(FILE *, int *, int *, int *, int *, int *, int *);
void leerHora(FILE *, int *, int *, int *);
void imprimirDatos(FILE *, int, int, int, int, int, int, int, int, int, int, 
                   double, double *);
int calcularDuracion(int, int, int, int, int, int, int *, int *);
int duracionSeg(int, int, int);
double calcularMontoPagado(double, int, int);
double calcularImpuestoAPagar(double);
double calcularPorcentaje(double, double);
double imprimirRemuneracion(FILE *, double, double);
void imprimirDetallesFinales(FILE *, double, double);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */