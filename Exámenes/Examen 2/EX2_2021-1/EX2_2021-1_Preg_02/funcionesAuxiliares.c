/* 
 * Proyecto: EX2_2021-1_Preg_02
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 08:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#define NO_SE_ENCONTRO -1

void leerLibros(struct Libros *libros, int *numLibros){    
    FILE *archCsv = abrirArchivo("Libros.csv","r");    
    int numPal;
    char cadena[200], *pal[6];    
    while(1){
        leerCadena(cadena,200,archCsv);
        if(feof(archCsv)) break;
        sacaPalabras(cadena,pal,&numPal,',');        
        libros[*numLibros].codigo = pal[0];
        libros[*numLibros].titulo = pal[1];
        libros[*numLibros].autor = pal[2];
        libros[*numLibros].aPublicacion = atoi(pal[3]);
        libros[*numLibros].cantidad = atoi(pal[4]);
        libros[*numLibros].prestamos = atoi(pal[5]);
        for(int i=4; i<numPal; i++) free(pal[i]);
        (*numLibros)++;
    }    
    fclose(archCsv);
}

void imprimirRepLibros(struct Libros *libros, int numLibros){
    FILE *archRep = abrirArchivo("RepLibros.txt","w");    
    for(int i=0; i<numLibros; i++)
        fprintf(archRep,"%-10s %-35s %-30s %10d %10d %10d\n",libros[i].codigo,
                libros[i].titulo,libros[i].autor,libros[i].aPublicacion,
                libros[i].cantidad,libros[i].prestamos);
    fclose(archRep);
}

void leerRegPrestamos(struct RegPrestamos *prestamos, int *numRegPres){    
    FILE *archCsv = abrirArchivo("RegistroDePrestamos.csv","r");    
    int numPal;
    char cadena[200], *pal[16], *f[3];    
    while(1){
        leerCadena(cadena,200,archCsv);
        if(feof(archCsv)) break;
        sacaPalabras(cadena,pal,&numPal,',');        
        prestamos[*numRegPres].codigo = atoi(pal[0]);
        prestamos[*numRegPres].nombre = pal[1];
        prestamos[*numRegPres].cantidadDeLibros = (numPal-2)/2;        
        prestamos[*numRegPres].libro = (struct LibroPrestado *)
                malloc(sizeof(struct LibroPrestado)*7);        
        llenarLibros(pal,prestamos[*numRegPres].libro,
                prestamos[*numRegPres].cantidadDeLibros);
        (*numRegPres)++;
    }    
    fclose(archCsv);
}

void llenarLibros(char **pal, struct LibroPrestado *libro, int cantLibros){    
    int numPal;
    char *f[3];    
    for(int i=0, j=2; i<cantLibros; i++, j+=2){
        libro[i].codigo = pal[j];        
        sacaPalabras(pal[j+1],f,&numPal,'/');              
        libro[i].fecha = juntarFecha(atoi(f[0]),atoi(f[1]),atoi(f[2]));    
        for(int k=0; k<3; k++) free(f[k]);
        free(pal[j+1]);
    }
}

int juntarFecha(int dd, int mm, int aa){
    return aa*10000+mm*100+dd;
}

void imprimirRepRegPrestamos(struct RegPrestamos *prestamos, int numRegPres){
    FILE *archRep = abrirArchivo("RepRegPrestamos.txt","w");    
    for(int i=0; i<numRegPres; i++){
        fprintf(archRep,"%-10d %-35s %10d\n",prestamos[i].codigo,
                prestamos[i].nombre,prestamos[i].cantidadDeLibros);
        for(int j=0; j<prestamos[i].cantidadDeLibros; j++){
            fprintf(archRep,"%15d) %-10s",j+1,prestamos[i].libro[j].codigo);
            fprintf(archRep,"%10d\n",prestamos[i].libro[j].fecha);
        }
    }
    fclose(archRep);
}

void actualizarEstructuras(struct Libros *libros, int numLibros, 
                           struct RegPrestamos *prestamos, int *numRegPres){    
    FILE *archSolPres, *archRepPres;
    archSolPres = abrirArchivo("SolicitudesDePrestamos.csv","r");
    archRepPres = abrirArchivo("ReporteDePrestamos.txt","w");    
    int ddP, mmP, aaP, ddL, mmL, aaL, fechaPed, fechaLim, numPal;   
    fscanf(archSolPres,"%d/%d/%d %d/%d/%d\n",&ddP,&mmP,&aaP,&ddL,&mmL,&aaL);   
    imprimirCabeceraRepRegPrestamos(archRepPres,ddL,mmL,aaL);
    fechaPed = juntarFecha(ddP,mmP,aaP);
    fechaLim = juntarFecha(ddL,mmL,aaL);            
    char cadena[300], *pal[3];    
    while(1){
        leerCadena(cadena,300,archSolPres);        
        if(feof(archSolPres)) break;        
        sacaPalabras(cadena,pal,&numPal,',');
        asignarSolicitudDePrestamos(atoi(pal[0]),pal[2],libros,numLibros,
                prestamos,numRegPres,fechaPed,fechaLim,archRepPres,pal[1]);
        free(pal[0]);
    }    
    fclose(archSolPres);
    fclose(archRepPres);    
}

void imprimirCabeceraRepRegPrestamos(FILE *archRep, int dd, int mm, int aa){
    fprintf(archRep,"%60s %15s %02d/%02d/%04d\n","BIBLIOTECA CENTRAL",
            "Fecha:",dd,mm,aa);
    fprintf(archRep,"%s %10s %41s %8s %44s\n","CODIGO","NOMBRE","COD. DE LIBRO",
            "TITULO","OBSERVACION");    
}

void asignarSolicitudDePrestamos(int codUsuario, char *codLibro, 
                                 struct Libros *libros, int numLibros,
                                 struct RegPrestamos *prestamos, int *numRegPres,
                                 int fechaPed, int fechaLim, FILE *archRepPres,
                                 char *nomUsuario){  
    fprintf(archRepPres,"%-10d %-40s %-10s",codUsuario,nomUsuario,codLibro);    
    int pReg, pLib, cl;
    pLib = buscarPosLib(codLibro,libros,numLibros);
    pReg = buscarPosReg(codUsuario,prestamos,numRegPres);              
    if(pLib==NO_SE_ENCONTRO){
        fprintf(archRepPres,"%-40s","NN");
        fprintf(archRepPres,"%-30s\n","No existe el libro");
        return;
    }
    fprintf(archRepPres,"%-40s",libros[pLib].titulo);
    if(libros[pLib].prestamos<=0){
        fprintf(archRepPres,"%-30s\n","No hay libro disponible");
        return;
    }    
    if(pReg!=NO_SE_ENCONTRO && prestamos[pReg].cantidadDeLibros>=7){
        fprintf(archRepPres,"%-30s\n","Supero el limite de prestamos");
        return;
    }
    if(pReg!=NO_SE_ENCONTRO && verificarFechaLimite(&prestamos[pReg],fechaLim)==0){
        fprintf(archRepPres,"%-30s\n","Supero fecha limite");
        return;
    }
    if(pReg==NO_SE_ENCONTRO){        
        pReg = *numRegPres;        
        prestamos[pReg].codigo = codUsuario;
        prestamos[pReg].nombre = nomUsuario;
        prestamos[pReg].cantidadDeLibros = 0;        
        prestamos[pReg].libro = (struct LibroPrestado *)
                malloc(sizeof(struct LibroPrestado)*7);        
        (*numRegPres)++;
    }
    cl = prestamos[pReg].cantidadDeLibros;
    prestamos[pReg].libro[cl].codigo = codLibro;
    prestamos[pReg].libro[cl].fecha = fechaPed;    
    prestamos[pReg].cantidadDeLibros++;
    libros[pLib].prestamos--;
    fprintf(archRepPres,"%-30s\n","Se le entrego el libro");
}

int buscarPosLib(char *codLibro, struct Libros *libros, int numLibros){        
    for(int i=0; i<numLibros; i++)     
        if(strcmp(libros[i].codigo,codLibro)==0) return i;    
    return NO_SE_ENCONTRO;
}

int buscarPosReg(int codUsuario, struct RegPrestamos *prestamos, int *numRegPres){
    for(int i=0; i<(*numRegPres); i++)
        if(codUsuario==prestamos[i].codigo) return i;    
    return NO_SE_ENCONTRO;
}

int verificarFechaLimite(struct RegPrestamos *prestamos, int fechaLim){    
    for(int i=0; i<prestamos->cantidadDeLibros; i++)
        if(prestamos->libro[i].fecha>fechaLim) return 0;
    return 1;
}