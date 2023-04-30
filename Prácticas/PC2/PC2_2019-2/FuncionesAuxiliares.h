/* 
 * Proyecto: PC2_2019-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 13 de abril de 2022, 04:28 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *, FILE *, FILE *, FILE *);
void imprimirRecetasAtendidas(FILE *, FILE *, FILE *, FILE *, FILE *, double *,
                              double *, int *, int *, char *);
void imprimirRecetas(FILE *, FILE *, FILE *, FILE *, int, int *, double *, 
                     char*, double *, int *, int *, double *, char *, int);
int determinarFechaCronologicamente(FILE *, FILE *, int, int *, int *, int *, 
                                    int *, int *, int *, double *);
int convertirFecha(int, int, int);
double calcularFacturacion(FILE *, FILE *);
double buscarPrecio(int, FILE *);
void determinarMedicoMayorFacturacion(int *, int *, double *, char *, double *,
                                      int , int , char *);
void determinarRankingDelMedico(FILE *, double *, char *, double *);
void imprimirDatosFinalesMedico(FILE *, int, double, char, double);
void imprimirDetallesFinales(FILE *, double, double, int, int, char);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *, FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */