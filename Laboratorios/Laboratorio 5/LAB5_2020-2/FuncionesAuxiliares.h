/* 
 * Proyecto: LAB5_2020-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de junio de 2022, 04:55 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(const char *, const char *);
void leerAlumnos(int *, char **, int *);
void ordenarAlumnos(int *, char **, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void cambiarChar(char **, int, int);
void ordenarCursos(char **, double *, char **, char **, int);
void leerNombre(FILE *, char *);
void leerCursos(char **, double *, char **, char **, int *);
void leerNotas(int *, int, char **, int, double *, double *, double *, double *,
               int *, int *, int *, int *, double *);
int buscarIndInt(int, int *, int);
int buscarIndChar(char *, char **, int);
void calcularPromedios(double *, double *, int *, int *, int);
void imprimirReporte(int *, char **, double *, double *, double *, double *,
                     int, char **, char **, double *, char **, int *, int *);

#endif /* FUNCIONESAUXILIARES_H */

