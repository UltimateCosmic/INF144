/* 
 * Proyecto: PC2_2019-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 19 de abril de 2022, 12:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 200

void imprimirControlDeEscritura(FILE *archCuentos, FILE *archControlDeEscritura){ 
        
    fprintf(archControlDeEscritura,"CONTROL DE ESCRITURA DE CUENTOS\n\n\n");    
    int alumno, fin=0;    
    while(1){
        fscanf(archCuentos,"%d",&alumno);
        fprintf(archControlDeEscritura,"Alumno: %04d",alumno);
        fin=imprimirCuento(archCuentos,archControlDeEscritura);
        if(fin) break;
        fputc('\n',archControlDeEscritura);
    }    
}

int imprimirCuento(FILE *archCuentos, FILE *archReporte){
    
    int palabras=0, oraciones=0, parrafos=0, fin=0, letra, cantLetras=0;
    double promedioPalabras=0, promedioOraciones=0;
    
    imprimirTitulo(archCuentos,archReporte);
    while(1){        
        
        letra=fgetc(archCuentos);
        
        if(feof(archCuentos)){
            fin=1;
            break;
        }            
        else if(letra>='1'&&letra<='9'){
            ungetc(letra,archCuentos);
            break;
        }
        else if(letra==' '){            
            if(cantLetras>2)
                palabras++;                
            cantLetras=0;
            fputc(letra,archReporte);
            while((letra=fgetc(archCuentos))==' ');
            ungetc(letra,archCuentos);
        }
        else if(letra=='.'){            
            if(cantLetras>2)
                palabras++;
            cantLetras=0;
            fputc(letra,archReporte);
            fputc('\n',archReporte);    
            while((letra=fgetc(archCuentos))==' ');
            ungetc(letra,archCuentos);
            oraciones++;
        }
        else if(letra=='\n'){
            if(cantLetras>2)
                palabras++;
            cantLetras=0;
            fputc(letra,archReporte);
            while((letra=fgetc(archCuentos))==' ');
            ungetc(letra,archCuentos);
            parrafos++;
        }
        else{
            cantLetras++;
            fputc(letra,archReporte);
        }
            
        //No debe considerar las palabras que están formadas por una o dos letras.
    }
    promedioPalabras=(double)palabras/oraciones;
    promedioOraciones=(double)oraciones/parrafos;
    
    imprimirEstadisticasDelCuento(archReporte,palabras,oraciones,parrafos,
            promedioPalabras,promedioOraciones);
    return fin;
}

void imprimirTitulo(FILE *archCuentos, FILE *archReporte){    
    char letra;
    fgetc(archCuentos);
    fprintf(archReporte,"%20s","TITULO: ");        
    while((letra=fgetc(archCuentos))!='\n'){
        letra=convertirMayuscula(letra);
        fputc(letra,archReporte);
    }
    fputc('\n',archReporte);
    fputc('\n',archReporte);
}

char convertirMayuscula(char letra){
    if(letra>='a'&&letra<='z') return letra-=32;
    else return letra;
}

void imprimirEstadisticasDelCuento(FILE *archReporte, int palabras, int oraciones, int parrafos,
                                   double promedioPalabras,
                                   double promedioOraciones){    
    
    fprintf(archReporte,"\nESTADISTICAS DEL CUENTO\n");
    fprintf(archReporte,"\n%s %11s %10s %16s %16s\n","PALABRAS","ORACIONES",
            "PARRAFOS","PROM. PALABRAS","PROM.ORACIONES");
    imprimirLinea(archReporte,'_',MAX_LINEA);
    fprintf(archReporte,"%4d %9d %11d %14.2lf %14.2lf\n\n",palabras,oraciones,
            parrafos,promedioPalabras,promedioOraciones);
}

void imprimirLinea(FILE *arch, char caracter, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(caracter,arch);
    fputc('\n',arch);    
}

void cerrarArchivos(FILE *archCuentos, FILE *archControlDeEscritura){
    fclose(archControlDeEscritura);
    fclose(archCuentos);
}  