/* 
 * Proyecto: LAB3_2021-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 2 de mayo de 2022, 05:24 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerArrPacientes(int *, int *, int *);
void asignarDatosArrPacientes(FILE *, int *, int *, int *);
void leerArrMedicos(int *, double *, int *);
void asignarDatosArrMedicos(FILE *, int *, double *, int *);
void leerArrDistritos(int *, int *);
void asignarDatosArrDistritos(FILE *, int *, int *);
void leerArrAtencinesMedicas(int *, int *, int *, int *, int *,  double *, int, 
                             int *, double *, int);
void asignarDatosArrAtencinesMedicas(FILE *, int *, int *, int *, int *, int *, 
                             double *, int, int *, double *, int);
void leerRegistros(FILE *, int *, 
                   int *, int *, int *, 
                   int *, double *, int,
                   int, int, int, int, int *,
                   double *, int);
void leerHora(FILE *, int *, int *, int *);
int buscarIndice(int, int *, int);
void asignarArrDeRegistros(int *, int *, int *, int *, double *, int, int, int, 
                           int *, double *, int, int, int, int, int, int, int, 
                           int, int);
void ajustarFechas(int, int, int, int *, int *, int);
int juntarFecha(int, int, int);
int ajustarDuracion(int, int, int, int, int, int, int *, int);
int duracionSeg(int, int, int);
void ajustarMonto(double *, int *, double *, int, int, int, int);
int duracionMin(int);
void imprimirReporte(int *, int *, int, int *, int, int *, int *, int *, int *,
                     double *, int *, double *);
void calcularTotalesPorDistrito(int *, int *, int, int *, int *, int, double *,
                                double *);
void ordenarDistritosPorTotales(int *, int, int *, double *);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void procesarReporte(FILE *, FILE *, int *, int *, int, int *, int, int *, int *, 
                     int *, int *, double *, int *, double *);
void imprimirCabecera(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirDistrito(FILE *, int *, FILE *);
void imprimirNombreDelDistrito(FILE *, FILE *);
char convertirMayuscula(char);
void imprimirRegistro(int *, int *, int, int, int *, int *, int *, int *, 
                      double *, FILE *, int, double);
void imprimirCabeceraRegistro(FILE *);
void separarFecha(int, int *, int *, int *);
void separarHora(int, int *, int *, int *);
void imprimirDistritosConMayorYMenorPagoRealizado(FILE *, int *, double *, int);
int buscarIndiceMayorPago(double *, int);
int buscarIndiceMenorPago(double *, int);

#endif /* FUNCIONESAUXILIARES_H */

