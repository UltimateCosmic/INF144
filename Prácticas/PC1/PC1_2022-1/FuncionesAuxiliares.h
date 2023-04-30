/* 
 * Proyecto: Practica01-2022-1_Archivos
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 07:08 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *archVentas, FILE *archReporteCompras);
void imprimirClientes(FILE *, FILE *, int, int, double, double, double, double, 
                      double, int);
void imprimirProductosAdquiridos(FILE *, FILE *, int, int, double, double, 
                                 double, double, double, int, char, int, int);
double imprimirPrimerDesc(FILE *, char, double, double, double);
double imprimirSegundoDesc(FILE *, int, int, double);
double imprimirTercerDesc(FILE *, int, int);
double imprimirImpuesto(FILE *, int, double, int);
double calcularPorcentaje(double, double);
void imprimirPais(FILE *, int);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *archVentas, FILE *archReporteCompras);

#endif /* FUNCIONESAUXILIARES_H */