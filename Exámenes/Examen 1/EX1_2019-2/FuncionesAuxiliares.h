/* 
 * Proyecto: EX1_2019-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de mayo de 2022, 06:25 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *, FILE *, FILE *);
void imprimirCabecera(FILE *);
void solicitarAnio(int *);
void imprimirLinea(FILE *, char, int);
void imprimirProductos(FILE *, FILE *, FILE *, FILE *, int);
void imprimirPlanDeProduccion(FILE *, FILE *, FILE *, FILE *, int, int);
void buscarCapacidadDeProduccion(int, int, FILE *, int *, int *);
void cerrarArchivos(FILE *, FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

