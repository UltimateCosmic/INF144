/* 
 * Proyecto: PC3_2021-2
 * Archivo:  FuncionesAuxiliares.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 5 de junio de 2022, 03:19 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

FILE *abrirArchivo(const char *, const char *);
void leerVentas(int *, int *, int *);
int buscarRepeticion(int, int *, int);
void ordenarLibros(int *, int *, int);
void cambiarInt(int *, int, int);
void cambiarDouble(double *, int, int);
void leerLibros(int *, char **, double *, int);
int buscarIndice(int, int *, int);
void leerNombreDelLibro(FILE *, char *);
int verificarUltimoNombre(char *);
void modificarPalabra(char *palabra);
char convertirMayuscula(char);
char convertirMinuscula(char);
void calcularMontoTotal(int *, double *, double *, int);
void ordenarPorVentas(int *, char **, int *, double *, int);
void cambiarChar(char **, int, int);
void procesarReporteDeEditorial(int *, int *, int);
void imprimirReporteDeEditorial(FILE *, FILE *, int *, int *, int);
void imprimirCabeceraPrincipal(FILE *);
void imprimirLinea(FILE *, char, int);
void imprimirNombreDelAutor(FILE *, FILE *);
void nombreConMayusculas(char *);
void apellidoConMayusculas(char *);
void imprimirCabeceraDeLibrosVendidos(FILE *);
void imprimirLibrosVendidos(FILE *, FILE *, int *, int *, int);
void asignarPos(int *, int *, int, int *, int);


void imprimirMontoTotalVendido(FILE *, double);

#endif /* FUNCIONESAUXILIARES_H */

