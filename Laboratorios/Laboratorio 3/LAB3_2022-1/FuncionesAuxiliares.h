/* 
 * Proyecto: ManejoDeArchivos_Lab03_2022_1
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 10 de mayo de 2022, 08:01 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void procesarClientes(int *, int *, int *);
void leerClientes(FILE *, int *, int *, int *);
void saltarNombre(FILE *, char);
void ordenarClientesPorDNI(int *, int *, int);
void cambiarInt(int *, int, int);
void procesarPedidos(int *, double *, double *, double *, int *, int *, double *,
                     int);
void leerPedidos(FILE *, int *, double *, double *, double *, int *, int *, 
                 double *, int );
int buscarIndice(int, int *);
void asignarTotalGastadoCli(int *, int, double *, int, double);
void procesarReporteDeVentas(int *, int *, double *, int, int *, double *,
                             double *, double *, int);
void ordenarArreglosParaReporte(int *, int *, double *, int, int *, double *,
                                double *, double *, int);
void ordenarProductos(int *, double *, double *, double *, int);
void cambiarDouble(double *, int, int);
void ordenarClientes(int *, int *, double *, int);
void imprimirReporteDeVentas(FILE *, int *, int *, double *, int, int *, double *,
                             double *, double *, int);
void imprimirCabeceraPrincipal(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirIngresosPorProducto(FILE *,int *, double *, double *, double *, int);
void imprimirCabeceraIngresosPorProducto(FILE *);
void imprimirTotalRecaudado(FILE *, double);
void imprimirGastosPorCliente(FILE *, int *, int *, double *, int);
void imprimirCabeceraGastosPorCliente(FILE *);
void determinarMayorYMenorGasto(double *, int, double *, double *, int *, int *);
void imprimirCliMayorYMenorGasto(FILE *, int *, double *, int, int);

#endif /* FUNCIONESAUXILIARES_H */

