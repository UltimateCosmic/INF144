/* 
 * Proyecto: LAB4_2019-2_H0431
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 1 de mayo de 2022, 01:07 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerArrPersonas(int *, int *, int *, int *, int *);
void asignarDatosPersonas(FILE *, int *, int *, int *, int *, int *);
void leerArrIngresos(double *, int *, int, int *, int *);
void asignarDatosIngresos(FILE *, double *, int *, int, int *, int *);
int juntarFecha(int, int, int);
void asignarIngresoAPersona(double *, int *, int, 
                            int *, int *, 
                            int, double, int);
int buscarIndiceIngresos(int *, int, int);
void cambiarFechas(int, int *, int *);
void calcularLineasDeCredito(double *, double *, double *, int *, int *, int);
double calcularF1BancoA(int);
double calcularF2BancoA(int);
double calcularF1BancoB(int);
double calcularF2BancoB(int);
void imprimirPrimerReporte(int, int, int *, int *, double *, double *, int);
void imprimirReporteLineasDeCredito(FILE *, int, int, int *, int *, double *, 
                                    double *, int);
void imprimirCabeceraLineasDeCredito(FILE *, int, int);
void separarFecha(int, int *, int *, int *);
void imprimirLinea(FILE *, char, int);
void imprimirSegundoReporte(double *, double *, int);
void imprimirReporteDistribucionDeFrec(FILE *, double *, double *, int);
void imprimirCabeceraDistrubicionDeFrec(FILE *);
void calcularArrGraf(int *, int *, double *, double *, int);
void imprimirGraficas(FILE *, int *, int *);
int buscarMaxDistribucion(int *);
void imprimirChar(FILE *, char, int, int);
void imprimirEspacios(FILE *, int);

#endif /* FUNCIONESAUXILIARES_H */

