/* 
 * Proyecto: PC4_2021-1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 01:34 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructBus.h"

void leerBuses(struct Bus *, int *);
void modificarNombreDelChofer(char *, char *);
void corregirPalabra(char *);
char convertirMinusc(char);
void ordenarBuses(struct Bus *, int);
void cambiarStructBus(struct Bus *, int, int);
void leerPasajeros(struct Bus *, int, struct Pasajero *, int *);
void modificarNombrePasajero(char *);
int buscarIndice(char *, struct Bus *, int);
void imprimirReporte(struct Bus *, int);
void imprimirReporteDePasajeros(struct Bus *, int, struct Pasajero *, int);
void imprimirCabeceraPrincipal(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirRuta(FILE *, struct Bus);
void imprimirPasajeros(FILE *, struct Bus);
void imprimirCabeceraDePasajeros(FILE *, char *);
void imprimirPasajerosEnListaDeEspera(FILE *, struct Pasajero *, int);
void imprimirCabeceraDeListaDeEspera(FILE *);

#endif /* FUNCIONESAUXILIARES_H */

