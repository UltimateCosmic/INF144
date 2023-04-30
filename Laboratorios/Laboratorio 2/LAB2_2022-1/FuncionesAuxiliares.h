/* 
 * Proyecto: Laboratorio02-2022-1-Archivos
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de abril de 2022, 08:06 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarArchivos(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
void imprimirCabecera(FILE *);
double imprimirProducto(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, int);
void imprimirNombreDelProducto(FILE *, FILE *);
char convertirMayuscula(char);
void imprimirListadoDePedidos(FILE *, FILE *, FILE *, FILE *, FILE *, int,
                              double, double, double *);
void imprimirCabeceraListado(FILE *);
double buscarDetallesDeProductos(FILE *, FILE *, FILE *, FILE *, FILE *, int,
                                 double, double, int, int);
void imprimirPedido(FILE *, FILE *, FILE *, FILE *, double, double, int, int, 
                    double, double *);
void buscarCliente(FILE *, FILE *, int, int *, int *, int *, char *);
void imprimirNombreCliente(FILE *, FILE *);
double buscarDescuentoCategoria(FILE *, char);
double buscarImpuestoPais(FILE *, FILE *, int);
void imprimirPais(FILE *, FILE *);
double calcularTotal(double, double, double, double, double);
double calcularPorcentaje(double, double);
void imprimirTotalDePedidos(FILE *, double);
void imprimirLinea(FILE *, char, int);
void cerrarArchivos(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);

#endif /* FUNCIONESAUXILIARES_H */