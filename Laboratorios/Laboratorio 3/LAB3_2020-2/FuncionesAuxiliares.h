/* 
 * Proyecto: LAB3_2020-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 9 de mayo de 2022, 01:47 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarAtencionDePacientes(int *, double *, double *, int *, int *, int *);
void leerAtencionDePacientes(int *, double *, double *, int *, int *, int *, 
                             FILE *);
void leerDatosDePacientes(int *, double *, double *, int *, int *, int *, FILE *);
void saltarNombre(FILE *);
void asignatDatosDePacientes(int *, double *, double *, int *, int *,  int *,
                             char, double, int);
void procesarReporteDeAtenciones(int *, double *, double *, int *, int *, int);
void imprimirReporteDeAtenciones(int *, double *, double *, int *, int *, int, 
                                 FILE *);
void imprimirCabeceraReporteDeAtenciones(FILE *);
void imprimirLinea(FILE *, char, int);
void procesarReporteDeMedicos(int *, double *, double *, int *, int *, int);
void imprimirReporteDeMedicos(int *, double *, double *, int *, int *, int, 
                              FILE *, FILE *);
void imprimirDatosDelMedico(FILE *, FILE *, int, double *);
void imprimirNombreDelMedico(FILE *, FILE *);
char convertirMayusc(char);
void imprimirEspecialidadDelMedico(FILE *, FILE *);
void imprimirArreglos(int, double, int *, double *, double *, int *, int *, 
                      int, FILE *);
int buscarIndice(int, int *, int);
void imprimirMontos(FILE *, double, double);

#endif /* FUNCIONESAUXILIARES_H */