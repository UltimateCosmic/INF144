/* 
 * Proyecto: LAB4_2019-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 10 de mayo de 2022, 06:24 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarUtilidades(int *, double *, double *, int *);
void leerUtilidades(FILE *, int *, double *, double *, int *);
void ordenarUtilidadesPorAnio(int *, double *, double *, int);
void procesarEmpleados(int *, double *, int *);
void leerEmpleados(FILE *, int *, double *, int *);
void procesarPlantillas(int *, int *, int *, int *, double *, int *);
void leerPlantillas(FILE *, int *, int *, int *, int *, double *, int *);
void abonarEmpleados(double *, int *, int, int *, double *, int, int *);
double calcularAbono(int, int *, double *, int, int, double);
double fraccion(double, int, double);
void ordenarPlantillas(int *, int *, int *, int *, double *, int);
void cambiarArrPlant(int *, int *, int *, int *, double *, int, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void procesarReporteDeUtilidades(int *, double *,
            int, int *, int *, int *,
            int *, double *, int);
void imprimirEmpleados(FILE *, int *, double *,
            int);
void imprimirCabeceraDeEmpleados(FILE *);
void imprimirLinea(FILE *, char, int);

#endif /* FUNCIONESAUXILIARES_H */

