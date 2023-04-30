/* 
 * Proyecto: EX2_2021-1_Preg_01
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 06:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#include "StructLibro.h"
#include "StructPrestamo.h"
#define NO_SE_ENCONTRO -1

void crearArchLibrosBin(const char *nomArchBin, const char *nomArchCsv){    
    FILE *archBin, *archCsv;
    archBin = abrirArchivo(nomArchBin,"wb");
    archCsv = abrirArchivo(nomArchCsv,"r");
    int numPal;
    char cadena[200], *pal[6];
    struct Libro libro;
    while(1){
        leerCadena(cadena,200,archCsv); 
        if(feof(archCsv)) break;         
        sacaPalabras(cadena,pal,&numPal,',');
        strcpy(libro.codigo,pal[0]);
        strcpy(libro.titulo,pal[1]);
        strcpy(libro.autor,pal[2]);
        libro.aPublicacion = atoi(pal[3]);
        libro.cantidad = atoi(pal[4]);
        libro.prestamos = atoi(pal[5]);
        fwrite(&libro,sizeof(struct Libro),1,archBin);
        for(int i=0; i<numPal; i++) free(pal[i]);
    }
    fclose(archBin);
    fclose(archCsv);
}

void imprimirRepLibros(const char *nomArchBin, const char *nomArchTxt){
    FILE *archBin, *archTxt;
    archBin = abrirArchivo(nomArchBin,"rb");
    archTxt = abrirArchivo(nomArchTxt,"w");    
    struct Libro libro;
    while(1){
        fread(&libro,sizeof(struct Libro),1,archBin);
        if(feof(archBin)) break;
        fprintf(archTxt,"%-10s %-40s %-35s %10d %5d %5d\n",libro.codigo,
                libro.titulo,libro.autor,libro.aPublicacion,libro.cantidad,
                libro.prestamos);        
    }    
    fclose(archBin);
    fclose(archTxt);
}

void crearArchRegistroDePrestamosBin(const char *nomArchBin, const char *nomArchCsv){
    FILE *archBin, *archCsv;
    archBin = abrirArchivo(nomArchBin,"wb");
    archCsv = abrirArchivo(nomArchCsv,"r");
    int numPal, nP;
    char cadena[200], *pal[16], *f[3];
    struct Prestamo prestamo;
    while(1){        
        leerCadena(cadena,200,archCsv); 
        if(feof(archCsv)) break;         
        sacaPalabras(cadena,pal,&numPal,',');        
        prestamo.codigo=atoi(pal[0]);
        strcpy(prestamo.nombre,pal[1]);        
        for(int j=2, k=0; j<numPal; j+=2, k++){
            strcpy(prestamo.libro[k].codigo,pal[j]);
            sacaPalabras(pal[j+1],f,&nP,'/');
            prestamo.libro[k].fecha = juntarFecha(atoi(f[0]),atoi(f[1]),atoi(f[2]));
            for(int k=0; k<nP; k++) free(f[k]);
        }  
        prestamo.cantidadDeLibros=(numPal-2)/2;
        fwrite(&prestamo,sizeof(struct Prestamo),1,archBin); 
        for(int i=0; i<numPal; i++) free(pal[i]);
    }
    fclose(archBin);
    fclose(archCsv);
}

int juntarFecha(int dd, int mm, int aa){
    return aa*10000+mm*100+dd;    
}

void imprimirRepRegPrestamos(const char *nomArchBin, const char *nomArchTxt){    
    FILE *archBin, *archTxt;
    archBin = abrirArchivo(nomArchBin,"rb");
    archTxt = abrirArchivo(nomArchTxt,"w");
    struct Prestamo prestamo;
    while(1){
        fread(&prestamo,sizeof(struct Prestamo),1,archBin);
        if(feof(archBin)) break;
        fprintf(archTxt,"%-10d %-40s %2d\n",prestamo.codigo,prestamo.nombre,
                prestamo.cantidadDeLibros);
        for(int i=0; i<prestamo.cantidadDeLibros; i++)
            fprintf(archTxt,"%12d) %8s %14d\n",i+1,prestamo.libro[i].codigo,
                    prestamo.libro[i].fecha);
        fputc('\n',archTxt);
    }    
    fclose(archBin);
    fclose(archTxt);
}

void completarArchivosBin(const char *nomArchLibrosBin, const char *nomArchRegistroBin,
                          const char *nomArchReporteDePrestamosTxt, 
                          const char *nomArchSolicitudesDePrestamosCsv){    
    //Se nos pide realizarlo en simultaneo
    FILE *archLibros, *archRegPrestamos, *archSolPrestamos, *archRepPrestamos;
    archLibros = abrirArchivo(nomArchLibrosBin,"rb+");
    archRegPrestamos = abrirArchivo(nomArchRegistroBin,"rb+");
    archSolPrestamos = abrirArchivo(nomArchSolicitudesDePrestamosCsv,"r");
    archRepPrestamos = abrirArchivo(nomArchReporteDePrestamosTxt,"w");    
    int numPal, codUsuario, dd, mm, aa, d, m, a, fechaPres;
    char cadena[200], *pal[3];        
    fscanf(archSolPrestamos,"%d/%d/%d %d/%d/%d",&d,&m,&a,&dd,&mm,&aa);   
    imprimirCabeceraDeReporte(archRepPrestamos,d,m,a);
    fechaPres = a*10000+m*100+d;    
    while(1){        
        leerCadena(cadena,200,archSolPrestamos); 
        if(feof(archSolPrestamos)) break;        
        sacaPalabras(cadena,pal,&numPal,',');
        codUsuario = atoi(pal[0]);
        asignarSolicitud(dd,mm,aa,codUsuario,pal[1],pal[2],archLibros,
                archRegPrestamos,fechaPres,archRepPrestamos);       
        for(int i=0; i<numPal; i++) free(pal[i]);
    }    
    
    fclose(archLibros);
    fclose(archRegPrestamos);
    fclose(archSolPrestamos);
    fclose(archRepPrestamos);
}

void asignarSolicitud(int dd, int mm, int aa, int codUsuario, char *nomUsuario,
                      char *codLibro, FILE *archLibros, FILE *archRegPrestamos,
                      int fechaPres, FILE *archRepPrestamos){
    int posL, posU, esNuevo, fecha, cl;
    posL = buscarPosLibro(codLibro,archLibros);
    posU = buscarPosUsuario(codUsuario,archRegPrestamos,&esNuevo);
    struct Libro libro;
    struct Prestamo prestamo;    
    if(posL!=NO_SE_ENCONTRO && posU!=NO_SE_ENCONTRO){
        fprintf(archRepPrestamos,"%-10d %-40s %-18s",codUsuario,
                nomUsuario,codLibro);
        fseek(archLibros,sizeof(struct Libro)*posL,SEEK_SET);
        fread(&libro,sizeof(struct Libro),1,archLibros);
        fseek(archRegPrestamos,sizeof(struct Prestamo)*posU,SEEK_SET);
        fread(&prestamo,sizeof(struct Prestamo),1,archRegPrestamos);        
        fecha = aa*10000+mm*100+dd;        
        if(esNuevo){
            prestamo.codigo=codUsuario;
            strcpy(prestamo.nombre,nomUsuario);            
            prestamo.cantidadDeLibros=0;
        }
        if(cumpleRequisitos(libro.codigo,codLibro,libro.cantidad,libro.prestamos,
                prestamo.cantidadDeLibros,prestamo.libro,esNuevo,fecha,
                archRepPrestamos,libro.titulo)){            
            cl=prestamo.cantidadDeLibros;            
            libro.prestamos++;            
            strcpy(prestamo.libro[cl].codigo,codLibro);
            prestamo.libro[cl].fecha=fechaPres;       
            prestamo.cantidadDeLibros++;
        }        
        fseek(archLibros,sizeof(struct Libro)*posL,SEEK_SET);
        fwrite(&libro,sizeof(struct Libro),1,archLibros);
        fseek(archRegPrestamos,sizeof(struct Prestamo)*posU,SEEK_SET);                
        fwrite(&prestamo,sizeof(struct Prestamo),1,archRegPrestamos);     
        fflush(archLibros);
        fflush(archRegPrestamos);
        
    }    
}

int buscarPosLibro(char *codLibro, FILE *archLibros){    
    struct Libro libro;
    int tamReg, numReg;
    tamReg = sizeof(struct Libro);
    datosDelArchivo(archLibros,tamReg,&numReg);
    for(int i=0; i<numReg; i++){
        fread(&libro,tamReg,1,archLibros);
        if(strcmp(libro.codigo,codLibro)==0) return i;        
    }
    return NO_SE_ENCONTRO;
}

void datosDelArchivo(FILE *archBin, int tamReg, int *numReg){    
    fseek(archBin,0,SEEK_END);
    int tamArch = ftell(archBin);
    fseek(archBin,0,SEEK_SET);
    *numReg = tamArch/tamReg;
}

int buscarPosUsuario(int codUsuario, FILE *archRegPrestamos, int *nuevo){    
    struct Prestamo prestamo;
    int tamReg, numReg, i;
    tamReg = sizeof(struct Prestamo);
    datosDelArchivo(archRegPrestamos,tamReg,&numReg);    
    for(i=0; i<numReg; i++){
        fread(&prestamo,tamReg,1,archRegPrestamos);
        if(codUsuario==prestamo.codigo){   
            *nuevo=0;
            return i;        
        }
    }
    *nuevo=1;
    return i;
}

int cumpleRequisitos(char *libroCodigo, char *codLibro, int libroCantidad,
                     int libroPrestamos, int prestamoCantLibros, 
                     struct LibroPrestado *libro, int esNuevo, int fecha,
                     FILE *archRep, char *titulo){
    
    if(strcmp(libroCodigo,codLibro)!=0){
        fprintf(archRep,"%-20s","NN");
        fprintf(archRep,"%s\n","No existe el libro");
        return 0;
    }
    fprintf(archRep,"%-36s",titulo);
    if((libroPrestamos>0 && libroPrestamos<libroCantidad)==0){
            fprintf(archRep,"%s\n","No hay libro disponible");
        return 0;
    }
    if(prestamoCantLibros>=7){
        fprintf(archRep,"%s\n","Supero el limite de prestamos");
        return 0;
    }    
    if(verificarFechas(libro,prestamoCantLibros,esNuevo,fecha)==0){    
        fprintf(archRep,"%s\n","Supero fecha limite");
        return 0;
    }
    fprintf(archRep,"%s\n","Se le entrego el libro");
    return 1;
}

int verificarFechas(struct LibroPrestado *libro, int cantLibros, int esNuevo, 
                    int fechaLimite){    
    if(esNuevo) return 1;
    else{
        for(int i=0; i<cantLibros; i++) 
            if(libro[i].fecha<fechaLimite) 
                return 0;       
        return 1;
    }
}

void imprimirCabeceraDeReporte(FILE *archRep, int d, int m, int a){
    fprintf(archRep,"%47s %40s %02d/%02d/%04d\n","BIBLIOTECA CENTRAL",
            "Fecha:",d,m,a);
    fprintf(archRep,"%s %10s %47s %10s %40s\n","CODIGO","NOMBRE",
            "COD. DE LIBRO","TITULO","OBSERVACION");
}