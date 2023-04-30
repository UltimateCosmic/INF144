/* 
 * Proyecto: LAB2_2020-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 22 de abril de 2022, 10:19 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void imprimirInformacionAcademicaDeLosEstudiantes();
void imprimirListadoDeCursos(int, int);
void imprimirObservacion(int, int, int, int, int, double, int *, int *, int *,
                         int *);
void actualizarDatosDelResumen(double, int, int, int, int *, int *, int *, int *, 
                               double *, double *, double *, double *, double *,
                               double *, double *, double *, int, int);
void imprimirResumen(int, int, int, int, double, double, double, double, double, 
                     double, double, double);
void imprimirResumenIndividual(int, int, double, double, double, double);
double calcularPromedio(double, double);
void imprimirErrores(int, int, int);
void imprimirEspacios();
void imprimirTotalDeAlumnosRegistrados(int);
void imprimirLinea(char, int);

#endif /* FUNCIONESAUXILIARES_H */

