/* 
 * Proyecto: LAB05_ArchivosCSV
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 08:05 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#define MAX_LINEA 120
#define NO_SE_ENCONTRO -1

void leerAutores(char **codAutor, char **nombreAutor, int *i){
    FILE *arch = abrirArchivo("Autores.csv","r");
    int np, nc;         //Número de palabras y número de caracteres
    char cadena[100];
    char *palabras[2];
    while(1){
        //Lectura y separación de la cadena
        leerCadena(cadena,100,arch);
        if(feof(arch)) break;
        sacaPalabras(cadena,palabras,&np,',');
        //Código:
        nc = strlen(palabras[0]);
        codAutor[*i] = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(codAutor[*i],palabras[0]);
        //Nombre:
        nc = strlen(palabras[1]);
        nombreAutor[*i] = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(nombreAutor[*i],palabras[1]);        
        //Free:
        for(int j=0; j<np; j++) free(palabras[j]);
        (*i)++;
    }
    fclose(arch);
}

void leerLibros(char **codLibro, char **nombreLibro, double *precioLibro,
                int *vendLibros, int *cantLibros, char **codAutor,
                double *regaliasAutor, int *vendAutor, int cantAutores){
    FILE *arch = abrirArchivo("Libros.csv","r");
    int np, nc, cL=0;         //Número de palabras, caracteres, y libros
    char cadena[200];
    char *palabras[14];
    while(1){
        //Lectura y separación de la cadena
        leerCadena(cadena,200,arch);
        if(feof(arch)) break;
        sacaPalabras(cadena,palabras,&np,',');        
        //Código:
        nc = strlen(palabras[0]);
        codLibro[cL] = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(codLibro[cL],palabras[0]);
        //Nombre:
        nc = strlen(palabras[1]);
        nombreLibro[cL] = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(nombreLibro[cL],palabras[1]);
        //Precio:
        precioLibro[cL] = atof(palabras[2]);
        //Venta:
        vendLibros[cL] = atoi(palabras[np-1]);
        //Regalías:
        calcularRegaliasYVentas(palabras,np,regaliasAutor,codAutor,cantAutores,
                precioLibro[cL],vendAutor,vendLibros[cL]);
        //Free:
        for(int i=0; i<np; i++) free(palabras[i]);
        cL++;
    }
    *cantLibros = cL;
    fclose(arch);
}

void calcularRegaliasYVentas(char **palabras, int np, double *regaliasAutor,
                             char **codAutor, int cantAutores, double precio, 
                             int *vendAutor, int vendLibros){    
    //Iteramos partir del tercer indice hasta el penúltimo
    int j;
    double porcentaje, regalias;
    for(int i=3; i<np-2; i+=2){
        j=buscarIndice(palabras[i],codAutor,cantAutores);
        if(j!=NO_SE_ENCONTRO){
            porcentaje = atof(palabras[i+1]);
            regalias = calcularPorcentaje(porcentaje,precio);
            regaliasAutor[j]+=regalias;
            vendAutor[j]+=vendLibros;
        }
    }    
}

int buscarIndice(char *codigo, char **codAutor, int cantAutores){    
    for(int i=0; i<cantAutores; i++)
        if(strcmp(codigo,codAutor[i])==0) return i;
    return NO_SE_ENCONTRO;
}

double calcularPorcentaje(double porcentaje, double precio){
    return porcentaje*precio/100;    
}
/*     100 %    ->  precio
    porcentaje  ->    X     */

void ordenarAutores(char **codAutor, char **nombreAutor, double *regaliasAutor,
                    int *vendAutor, int cantAutores){
    for(int i=0; i<cantAutores-1; i++)
        for(int j=i+1; j<cantAutores; j++)
            if(vendAutor[j]>vendAutor[i] || (vendAutor[j]==vendAutor[i] && 
                    strcmp(codAutor[j],codAutor[i])<0)){
                cambiarChar(codAutor,i,j);
                cambiarChar(nombreAutor,i,j);
                cambiarDouble(regaliasAutor,i,j);
                cambiarInt(vendAutor,i,j);
            }
}

void cambiarInt(int *arr, int i, int j){
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;    
}

void cambiarDouble(double *arr, int i, int j){
    double aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;    
}

void cambiarChar(char **arr, int i, int j){
    char *aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;    
}

void ordenarLibros(char **codLibro, char **nombreLibro, double *precioLibro,
                   int *vendLibros, int cantLibros){
    for(int i=0; i<cantLibros-1; i++)
        for(int j=i+1; j<cantLibros; j++)
            if(nombreLibro[j]>nombreLibro[i]){
                cambiarChar(codLibro,i,j);
                cambiarChar(nombreLibro,i,j);
                cambiarDouble(precioLibro,i,j);
                cambiarInt(vendLibros,i,j);
            }
}

void imprimirReporteDeIngresosYPagos(char **codAutor, char **nombreAutor,
                                     double *regaliasAutor, int *vendAutor,
                                     int cantAutores, char **codLibro,
                                     char **nombreLibro, double *precioLibro,
                                     int *vendLibros, int cantLibros){    
    FILE *arch = abrirArchivo("ReporteDeIngresosYPagos.txt","w");
    imprimirPagoALosAutores(arch,codAutor,nombreAutor,regaliasAutor,vendAutor,
            cantAutores);
    imprimirRecaudacionPorLibrosVendidos(arch,codLibro,nombreLibro,precioLibro,
            vendLibros,cantLibros);
    fclose(arch);
}

void imprimirPagoALosAutores(FILE *arch, char **codAutor, char **nombreAutor,
                             double *regaliasAutor, int *vendAutor, int cantAutores){
    imprimirCabeceraDeAutores(arch);    
    double totalRegalias=0.0;
    for(int i=0; i<cantAutores; i++){        
        fprintf(arch,"%-9s %-45s %5d %24.2lf\n",codAutor[i],nombreAutor[i],
                vendAutor[i],regaliasAutor[i]);
        totalRegalias+=regaliasAutor[i];
    }
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"Total a pagar por regalias: %8.2lf\n",totalRegalias);
    imprimirLinea(arch,'=',MAX_LINEA);
}

void imprimirCabeceraDeAutores(FILE *arch){
    fprintf(arch,"%70s\n","Editorial TP");
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"PAGO A LOS AUTORES:\n");
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"%s %9s %52s %18s\n","CODIGO","NOMBRE",
            "TOTAL DE LIBROS VENDIDOS","REGALIAS");
    imprimirLinea(arch,'-',MAX_LINEA);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirRecaudacionPorLibrosVendidos(FILE *arch, char **codLibro,
                                          char **nombreLibro, double *precioLibro,
                                          int *vendLibros, int cantLibros){
    imprimirCabeceraDeLibros(arch);  
    double totalRecaudado=0.0, recaudacion;
    for(int i=0; i<cantLibros; i++){                
        recaudacion = precioLibro[i]*vendLibros[i];
        fprintf(arch,"%-11s %-60s %5d %24.2lf\n",codLibro[i],nombreLibro[i],
                vendLibros[i],recaudacion);                
        totalRecaudado+=recaudacion;
    }
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"Total de recaudado: %8.2lf\n",totalRecaudado);
}

void imprimirCabeceraDeLibros(FILE *arch){
    fprintf(arch,"RECAUDACION POR LIBROS VENDIDOS:\n");
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"%s %11s %65s %22s\n","CODIGO","TITULO","LIBROS VENDIDOS",
            "TOTAL RECAUDADO");     
    imprimirLinea(arch,'-',MAX_LINEA);
}

void copiarDatosAEstructura(struct Autor *autores, char **codAutor, 
                            char **nombreAutor, int *vendAutor,
                            double *regaliasAutor, int cantAutores){    
    int nc;     //Número de caracteres
    for(int i=0; i<cantAutores; i++){
        //Código:
        nc = strlen(codAutor[i]);
        autores[i].codigo = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(autores[i].codigo,codAutor[i]);
        //Nombre:
        nc = strlen(nombreAutor[i]);
        autores[i].nombre = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(autores[i].nombre,nombreAutor[i]);
        //Ventas:
        autores[i].librosVend = vendAutor[i];
        //Regalías:
        autores[i].regalias = regaliasAutor[i];
    }
}

void imprimirReporteAutores(struct Autor *autores, int cantAutores){
    FILE *arch = abrirArchivo("ReporteAutores.txt","w");        
    imprimirCabeceraDeAutores(arch);    
    double totalRegalias=0.0;
    for(int i=0; i<cantAutores; i++){        
        fprintf(arch,"%-9s %-45s %5d %24.2lf\n",autores[i].codigo,
                autores[i].nombre,autores[i].librosVend,autores[i].regalias);
        totalRegalias+=autores[i].regalias;
    }
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"Total a pagar por regalias: %8.2lf\n",totalRegalias);
    imprimirLinea(arch,'=',MAX_LINEA);
    fclose(arch);
}