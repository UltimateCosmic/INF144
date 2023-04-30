/* 
 * Proyecto: LAB1_2020-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de abril de 2022, 11:55 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerArrArchAsistenciaClases(int *, int *,double *, int *, int *, int, int);
void lecturaDeCursos(FILE *, int *, int *, double *, int *,  int *, int, int);
void verificarRepeticionDeCurso(int, int *, int *, double *, int *, int *, int, 
                                double);
void leerArrArchEncuestasAlumnos(int, int, double *, double *, int, int *);
void lecturaDeEncuestas(FILE *, int, int, double *, int, int *);
void verificarDatosEncuesta(FILE *, double *, int, int *);
int buscarIndice(int, int *, int);
void calcularPorcEncuestaAjustada(double *, int, double *, double *);
double calcularFactor(double);
void ordenarArreglos(int *, int *, int *, double *, double *, double *, int);
void cambiarValores(int *, int *, int *, double *, double *, double *, int, int);
void ordenarPorPromedioaDeAsistencia(int *, int *, int *, double *, double *,
                                     double *, int);
void ordenarPorNumHorarios(int *, int *, int *, double *, double *, double *, 
                           int);
void cambiarInt(int *, int *);
void cambiarDouble(double *, double *);
void abrirReporte(int *, int *, int *, double *, double *, double *, int, int,
                  int);
void imprimirReporte(FILE *, int *, int *, int *, double *, double *, double *, 
                     int, int, int);
void imprimirCabecera(FILE *, int, int);
void imprimirArreglos(FILE *, int *, int *, int *, double *, double *, double *, int);
void imprimirLinea(FILE *, char, int);

#endif /* FUNCIONESAUXILIARES_H */