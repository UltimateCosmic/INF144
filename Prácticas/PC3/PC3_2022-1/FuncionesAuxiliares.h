/* 
 * Proyecto: 2022-1_ArregosConCadenas_Practica03
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de junio de 2022, 07:02 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(const char *, const char *);
void leerCursos(char **, char **, double *, int *);
void leerNombreDelCurso(FILE *, char *);
int verificarFin(char *);
void leerAlumnos(char **, char **, int *);
void modificarNombreDeAlumno(char *, char *);
char convertirMayusc(char);
char convertirMinusc(char);
void imprimirReportedeConsolidado(char **, char **, double *,int, char **,
                                  char **, int);
void imprimirCabeceraDeReporte(FILE *);
void imprimirLinea(FILE *, char, int);
int buscarPosChar(char *, char **, int);
void imprimirAlumnosMatriculados(FILE *, FILE *, char **, char **, int, int *,
                                 int *, double *);
void imprimirCabeceraAlumnos(FILE *);
void imprimirResumenDeLosCursosDictados(char **, char **, double *, int *, int *,
                                        double *, FILE *, int);
void imprimirCabeceraDeResumen(FILE *);

#endif /* FUNCIONESAUXILIARES_H */

