/* 
 * Proyecto: Pr02_2022-1_Poligonal
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 2 de mayo de 2022, 07:07 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerArrPoligonal(double *, double *, int *);
void asignarDatosArrPoligonal(FILE *, double *, double *, int *);
void emitirReporteDeTareas(double *, double *, int);
void realizarTareas(FILE *, double *, double *, int);
double calcularLongPoligonal(double *, double *, int);
double calcularAreaBajoPoligonal(double *, double *, int);
double calcularDistancia(double, double, double, double);
void determinarPicosYValles(double *, double *, int, double *, double *, 
                            double *, double *, int *, int *);
void determinarPicoMasBajo(double *, int *, int);
void determinarValleMasAlto(double *, int *, int);
void imprimirReporteDeTareas(FILE *, double, double, double *, double *, 
                             double *, double *, int, int, int, int);
void imprimirCabecera(FILE *);
void imprimirPicosYValles(double *, double *, double *, double *, int, int, 
                          FILE *);
void imprimirPicoMasBajoYValleMasAlto(double *, double *, double *, double *,
                                      int, int, FILE *);
void imprimirLinea(FILE *, int, int);
void abrirArchPuntosACompletar(double *, double *, int, FILE *);
void leerPuntosFlotantes(FILE *, FILE *, double *, double *, int);
void leerDatosArrCoordenadasX(FILE *, double *, int *);
void leerDatosArrCoordenadasX(FILE *, double *, int *);
void calcularCoordenadasY(double *, double *, int, double *, double *, int);
void aniadirCoordenadasCompletasReporte(double *, double *, int, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

