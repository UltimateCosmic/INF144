/* 
 * Proyecto: 2022_1_ArchivosBinarios_Laboratorio6
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 08:05 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#include "StructAutor.h"
#include "StructLibro.h"
#define MAX_LINEA 120

void crearArchAutoresBin(const char *nomArchCsv, const char *nomArchBin){    
    FILE *archCsv, *archBin;
    archCsv=abrirArchivo(nomArchCsv,"r");
    archBin=abrirArchivo(nomArchBin,"wb");    
    struct Autor autor;    
    int numPal;
    char linea[100], *pal[2];    
    while(1){
        leerCadena(linea,200,archCsv);
        if(feof(archCsv)) break;        
        sacaPalabras(linea,pal,&numPal,',');        
        strcpy(autor.codigo,pal[0]);
        strcpy(autor.nombre,pal[1]);
        autor.librosVend=0;
        autor.montoRegalias=0.0;
        for(int i=0; i<numPal; i++) free(pal[i]);
        fwrite(&autor,sizeof(struct Autor),1,archBin);        
    }    
    fclose(archCsv);    
    fclose(archBin);    
}

void verificarArchAutoresBin(const char *nomArchTxt, const char *nomArchBin){
    FILE *archTxt, *archBin;
    archTxt=abrirArchivo(nomArchTxt,"w");
    archBin=abrirArchivo(nomArchBin,"rb");
    struct Autor autor;
    int tamReg, tamArch, cantReg;
    tamReg=sizeof(struct Autor);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);    
    for(int i=0; i<cantReg; i++){
        fread(&autor,tamReg,1,archBin);                 
        fprintf(archTxt,"%-10s %-40s %10d %12.2lf\n",autor.codigo,autor.nombre,
                autor.librosVend,autor.montoRegalias);   
    }
    fclose(archBin);
    fclose(archTxt);    
}

void datosDelArchivo(FILE *archBin, int tamReg, int *tamArch, int *cantReg){    
    fseek(archBin,0,SEEK_END);  //Cursor al final
    *tamArch = ftell(archBin);
    *cantReg = (*tamArch)/tamReg;
    fseek(archBin,0,SEEK_SET);
}

void crearArchLibrosBin(const char *nomArchCsv, const char *nomArchBin){    
    FILE *archCsv, *archBin;
    archCsv=abrirArchivo(nomArchCsv,"r");
    archBin=abrirArchivo(nomArchBin,"wb");    
    struct Libro libro;
    int numPal;
    char linea[400], *pal[24];    
    while(1){
        leerCadena(linea,400,archCsv);
        if(feof(archCsv)) break;        
        sacaPalabras(linea,pal,&numPal,',');
        strcpy(libro.codigo,pal[0]);
        strcpy(libro.nombre,pal[1]);
        libro.precio = atof(pal[2]);
        libro.cantVend = atoi(pal[numPal-1]);        
        libro.montoRecaudado=0.0;        
        asignarAutores(libro.autor,pal,numPal,&libro.cantAutores);  
        for(int i=0; i<numPal; i++) free(pal[i]);
        fwrite(&libro,sizeof(struct Libro),1,archBin); 
    }    
    fclose(archCsv);    
    fclose(archBin);    
}

void asignarAutores(struct Autor *autor, char **pal, int numPal, int *cantAutores){    
    *cantAutores=0;
    for(int i=3; i<numPal-2; i+=2){        
        strcpy(autor[*cantAutores].codigo,pal[i]);        
        autor[*cantAutores].montoRegalias=atof(pal[i+1]);
        (*cantAutores)++;
    }
}

void verificarArchLibrosBin(const char *nomArchTxt, const char *nomArchBin){
    FILE *archTxt, *archBin;
    archTxt=abrirArchivo(nomArchTxt,"w");
    archBin=abrirArchivo(nomArchBin,"rb");
    struct Libro libro;
    int tamReg, tamArch, cantReg;
    tamReg=sizeof(struct Libro);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);       
    for(int i=0; i<cantReg; i++){
        fread(&libro,tamReg,1,archBin);        
        fprintf(archTxt,"\n%-10s %-30s %10.2lf %10d %10.2lf %10d\n",
                libro.codigo,libro.nombre,libro.precio,libro.cantVend,
                libro.montoRecaudado,libro.cantAutores);
        for(int j=0; j<libro.cantAutores; j++)
            fprintf(archTxt,"%5d) %-10s %10.2lf\n",j+1,libro.autor[j].codigo,
                    libro.autor[j].montoRegalias);
    }
    fclose(archBin);
    fclose(archTxt);    
}

void actualizarInfoArchBin(const char *nomArchAutores, const char *nomArchLibros){
    FILE *archLibros=abrirArchivo(nomArchLibros,"rb+");    
    struct Libro libro;
    int tamReg, tamArch, cantReg;
    tamReg=sizeof(struct Libro);
    datosDelArchivo(archLibros,tamReg,&tamArch,&cantReg);    
    for(int i=0; i<cantReg; i++){
        fread(&libro,tamReg,1,archLibros);
        for(int j=0; j<libro.cantAutores; j++)
            actualizarInfoLibro(&libro.autor[j],nomArchAutores,libro.precio);
        fseek(archLibros,tamReg*i,SEEK_SET);
        fwrite(&libro,tamReg,1,archLibros);
        fflush(archLibros);
    }
    fclose(archLibros);    
}

void actualizarInfoLibro(struct Autor *autorLibro, const char *nomArchAutores,
                         double precio){    
    FILE *archAutores=abrirArchivo(nomArchAutores,"rb+");
    struct Autor autor;
    int tamReg, tamArch, cantReg;
    tamReg=sizeof(struct Autor);
    datosDelArchivo(archAutores,tamReg,&tamArch,&cantReg);    
    for(int i=0; i<cantReg; i++){
        fread(&autor,tamReg,1,archAutores);
        if(strcmp(autorLibro->codigo,autor.codigo)==0){
            autor.librosVend++;
            autor.montoRegalias=calcularPorcentaje(autorLibro->montoRegalias,precio);                        
            strcpy(autorLibro->nombre,autor.nombre);
            autorLibro->librosVend=autor.librosVend;
            autorLibro->montoRegalias=autor.montoRegalias;            
            fseek(archAutores,tamReg*i,SEEK_SET);
            fwrite(&autor,tamReg,1,archAutores);
            fflush(archAutores);
            break;
        }
    }   
    fclose(archAutores);
}

double calcularPorcentaje(double porcentaje, double total){
    return porcentaje*total/100;
}

void imprimirReporteRecaudacion(const char *nombreDelArchivo){    
    FILE *arch = abrirArchivo(nombreDelArchivo,"w");
    imprimirRecaudacionPorLibros(arch,"libros.bin");
    imprimirRecaudacionPorAutores(arch,"autores.bin");    
    fclose(arch);   
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);    
}

void imprimirRecaudacionPorLibros(FILE *arch, const char *nomArchBin){
    FILE *archBin;
    archBin=abrirArchivo(nomArchBin,"rb");
    struct Libro libro;
    int tamReg, tamArch, cantReg, librosVendidos=0;
    double totalRecaudado, totalSinRegalias=0;
    tamReg=sizeof(struct Libro);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);    
    fprintf(arch,"%60s\n","RECAUDACIÓN POR LIBROS VENDIDOS");    
    for(int i=0; i<cantReg; i++){        
        fread(&libro,tamReg,1,archBin);   
        imprimirLinea(arch,'=',MAX_LINEA);
        imprimirCabeceraLibros(arch);
        fprintf(arch,"%-13s %-30s %10d %15.2lf %20.2lf\n",libro.codigo,
                libro.nombre,libro.cantVend,libro.montoRecaudado,libro.precio);   
        imprimirLinea(arch,'-',MAX_LINEA);        
        imprimirAutoresDeLibros(arch,libro.autor,libro.cantAutores);
        librosVendidos+=libro.cantVend;
        totalRecaudado+=libro.montoRecaudado;
    }
    imprimirTotales(librosVendidos,totalRecaudado,totalSinRegalias,arch);    
    fputc('\n',arch);
    fclose(archBin);
}

void imprimirCabeceraLibros(FILE *arch){
    fprintf(arch,"%20s %30s %40s %20s %10s\n","CODIGO","TITULO","LIBROS VENDIDOS",
            "TOTAL RECAUDADO","TOTAL SIN REGALÍAS");
    imprimirLinea(arch,'-',MAX_LINEA);
}

void imprimirAutoresDeLibros(FILE *arch, struct Autor *autor, int cantAutores){    
    imprimirCabeceraAutoresDeLibros(arch);    
    for(int i=0; i<cantAutores; i++){        
        fprintf(arch,"%-10s %-20s %10.2lf\n",autor[i].codigo,autor[i].nombre,
                autor[i].montoRegalias);        
    }
}

void imprimirTotales(int librosVendidos, double totalRecaudado,
                     double totalSinRegalias, FILE *arch){
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"Total de libros vendidos: %10d\n",librosVendidos);
    fprintf(arch,"Total recaudado: S/. %10.2lf\n",totalRecaudado);
    fprintf(arch,"Total sin regalías: S/. %10.2lf\n",totalSinRegalias);
}

void imprimirCabeceraAutoresDeLibros(FILE *arch){
    fprintf(arch,"%10s %20s %30s\n","CODIGO","NOMBRE","REGALÍAS POR EL LIBRO");
    imprimirLinea(arch,'-',MAX_LINEA);
}

void imprimirRecaudacionPorAutores(FILE *arch, const char *nomArchBin){
    FILE *archBin;
    archBin=abrirArchivo(nomArchBin,"rb");
    struct Autor autor;
    int tamReg, tamArch, cantReg;
    double totalAPagar=0.0;
    tamReg=sizeof(struct Autor);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);    
    imprimirCabeceraRegaliaPorAutores(arch);   
    for(int i=0; i<cantReg; i++){        
        fread(&autor,tamReg,1,archBin);        
        fprintf(arch,"%-10s %-40s %10d %20.2lf\n",autor.codigo,autor.nombre,
                autor.librosVend,autor.montoRegalias);
        totalAPagar+=autor.montoRegalias;
    }
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"Total a pagar por regalías: S/. %.2lf\n",totalAPagar);   
    imprimirLinea(arch,'=',MAX_LINEA);
    fclose(archBin);
}

void imprimirCabeceraRegaliaPorAutores(FILE *arch){    
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"%50s\n","REGALIAS POR AUTORES");
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"%10s %20s %30s %20s\n","CODIGO","NOMBRE",
            "TOTAL DE LIBROS VENDIDOS","REGALIAS");
    imprimirLinea(arch,'-',MAX_LINEA);    
}