/* 
 * Proyecto: EX2_2021-1_Preg_01
 * Archivo:  funcionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 06:49 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "StructLibroPrestado.h"

void crearArchLibrosBin(const char *, const char *);
void imprimirRepLibros(const char *, const char *);
void crearArchRegistroDePrestamosBin(const char *, const char *);
int juntarFecha(int, int, int);
void imprimirRepRegPrestamos(const char *, const char *);
void completarArchivosBin(const char *, const char *, const char *, const char *);
void asignarSolicitud(int, int, int, int, char *, char *, FILE *, FILE *, int, FILE *);
int buscarPosLibro(char *, FILE *);
void datosDelArchivo(FILE *, int, int *);
int buscarPosUsuario(int, FILE *, int *);
int cumpleRequisitos(char *, char *, int, int, int, struct LibroPrestado *, int, 
                     int, FILE *, char *);
int verificarFechas(struct LibroPrestado *, int, int, int);
void imprimirCabeceraDeReporte(FILE *, int, int, int);

#endif /* FUNCIONESAUXILIARES_H */

