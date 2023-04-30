/* 
 * Proyecto: Consolidado_de_cursos_LAB04
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 31 de mayo de 2022, 08:02 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(char *, char *);
void leerCursos(int *, double *, int *);
void leerAlumnos(int *, double *, double *, double *, int *);
void leerNotas(int *, double *, double *, double *, int *, int *, double *, 
               int, int *, double *, int *, int *, int);
void ordenarCursosPorCodigo(int *, double *, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
int buscarPos(int, int *, int);
void leerNotasDeCurso(int *, double *, double *, double *, int *, int *, 
                      double *, int, double, int *, int *, FILE *);
void calcularPromPond(double *, int *, int *, int);
void imprimirReporteDeConsolidado(int *, double *,
                                  int *, int *,
                                  int, int *, double *,
                                  double *, double *,
                                  int *, int *,
                                  double *, int);
void imprimirConsolidadoDeAlumnos(int *, double *,
                                  double *, double *,
                                  int *, int *,
                                  double *, int,
                                  FILE *, FILE *);
void imprimirCabeceraDeAlumnos(FILE *);
void imprimirLinea(FILE *, char, int);
void ordenarAlumnosPorCantCursosApro(int *, double *, double *, double *, int *,
                                     int *, double *, int);
void leerNombreDeAlumno(FILE *, int, char *);
void modificarNombreDeAlumno(char *, char *);
char convertirMayusc(char);
char convertirMinusc(char);
void imprimirResumenFinal(FILE *, int, int);
void imprimirResultadosPorCurso(int *, int *, int *, int, FILE *, FILE *);
void imprimirCabeceraDeResultadosPorCurso(FILE *);
void imprimirNombreDelCurso(int, FILE *, FILE *);
void leerNombreDelCurso(FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */

