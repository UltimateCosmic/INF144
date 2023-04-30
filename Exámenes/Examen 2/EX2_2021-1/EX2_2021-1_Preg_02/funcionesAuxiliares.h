/* 
 * Proyecto: EX2_2021-1_Preg_02
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 08:00 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructLibros.h"
#include "StructRegPrestamos.h"
#include "StructLibroPrestado.h"

void leerLibros(struct Libros *, int *);
void imprimirRepLibros(struct Libros *, int);
void leerRegPrestamos(struct RegPrestamos *, int *);
void llenarLibros(char **, struct LibroPrestado *, int);
int juntarFecha(int, int, int);
void imprimirRepRegPrestamos(struct RegPrestamos *, int);
void actualizarEstructuras(struct Libros *, int, struct RegPrestamos *, int *);
void imprimirCabeceraRepRegPrestamos(FILE *, int, int, int);
void asignarSolicitudDePrestamos(int, char *, struct Libros *, int, 
                                 struct RegPrestamos *, int *, int, int,
                                 FILE *, char *);
int buscarPosLib(char *, struct Libros *, int);
int buscarPosReg(int, struct RegPrestamos *, int *);
int verificarFechaLimite(struct RegPrestamos *, int);

#endif /* FUNCIONESAUXILIARES_H */

