/* 
 * Proyecto: LAB4_2020-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 31 de mayo de 2022, 03:52 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 120
#define NO_SE_ENCONTRO -1

FILE *abrirArchivo(char *nombreDelArchivo, char *modoDeApertura){
    FILE *arch = fopen(nombreDelArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDelArchivo);
        exit(1);        
    }    
}

void leerSalas(int *arrSala, int *arrButacas, int *i){
    FILE *archSalas = abrirArchivo("salas.txt","r");
    while(1){
        fscanf(archSalas,"%d",&arrSala[*i]);
        if(feof(archSalas)) break;
        fscanf(archSalas,"%d",&arrButacas[*i]);
        while(fgetc(archSalas)!='\n');
        (*i)++;
    }    
    fclose(archSalas);
}

void ordenarSalasOPeliculas(int *arrSala, int *arrButaca, int cantSalas){    
    for(int i=0; i<cantSalas-1; i++)
        for(int j=i+1; j<cantSalas; j++)
            if(arrSala[j]<arrSala[i]){
                cambiarInt(arrSala,i,j);
                cambiarInt(arrButaca,i,j);                
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

void leerPeliculas(int *arrPelicula, int *arrFunciones, int *i){
    FILE *archPeliculas = abrirArchivo("peliculas.txt","r");
    int ddI, mmI, aaI, ddF, mmF, aaF, cantDias;
    while(1){
        fscanf(archPeliculas,"%d",&arrPelicula[*i]);
        if(feof(archPeliculas)) break;
        fscanf(archPeliculas,"%d.%d.%d",&ddI,&mmI,&aaI);
        fscanf(archPeliculas,"%d.%d.%d",&ddF,&mmF,&aaF);
        cantDias = calcularCantDias(ddI,mmI,aaI,ddF,mmF,aaF);
        while(fgetc(archPeliculas)==' ');
        while(fgetc(archPeliculas)!=' ');
        leerFunciones(archPeliculas,&arrFunciones[*i],cantDias);
        (*i)++;
    }
    fclose(archPeliculas);
}

int calcularCantDias(int ddI, int mmI, int aaI, int ddF, int mmF, int aaF){
    int fechaInicial, fechaFinal;
    fechaInicial = juntarFecha(ddI,mmI,aaI);
    fechaFinal = juntarFecha(ddF,mmF,aaF);
    return fechaFinal-fechaInicial;     
}

int juntarFecha(int dd, int mm, int aa){
    return aa*365+mm*30+dd;    
}

void leerFunciones(FILE *archPeliculas, int *arrFunciones, int cantDias){
    int cantDatos, i=0, centinela=1;
    fscanf(archPeliculas,"%*d");
    while(centinela){        
        while(1){
            cantDatos = fscanf(archPeliculas,"%*d:%*d");
            if(cantDatos==1) break;
            i++;
            if(fgetc(archPeliculas)=='\n'){
                centinela=0;
                break;
            }
        }
    }
    *arrFunciones = i*cantDias;
}

void leerVentasYOcupacion(int *arrPelicula, int cantPeliculas, int *arrButVend,
            int *arrButOcup, double *arrRecaudacion, int *arrSala, int cantSalas){
    FILE *archVentasYOcupacion = abrirArchivo("ventas_y_ocupacion.txt","r");
    int pelicula, sala, posP, posS, cantEntradas;
    double monto;
    while(1){
        fscanf(archVentasYOcupacion,"%d %d",&pelicula,&sala);
        if(feof(archVentasYOcupacion)) break;
        posP = buscarPosicion(pelicula,arrPelicula,cantPeliculas);
        posS = buscarPosicion(sala,arrSala,cantSalas);
        if(posP!=NO_SE_ENCONTRO && posS!=NO_SE_ENCONTRO){
            fscanf(archVentasYOcupacion,"%*d/%*d/%*d %*d:%*d");
            fscanf(archVentasYOcupacion,"%lf %d",&monto,&cantEntradas);
            arrButVend[posP]+=cantEntradas; 
            arrRecaudacion[posP]+=monto;
            leerOcupacion(archVentasYOcupacion,&arrButOcup[posP]);            
        }else
            while(fgetc(archVentasYOcupacion)!='\n');
    }        
    fclose(archVentasYOcupacion);
}

int buscarPosicion(int codigo, int *arrCodigo, int cant){    
    int limSup=cant, limInf=0, pm;
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm = (limSup+limInf)/2;
        if(codigo==arrCodigo[pm]) return pm;
        if(codigo>arrCodigo[pm]) limInf=pm+1;
        else limSup=pm-1;
    }
}

void leerOcupacion(FILE *archVentasYOcupacion, int *arrButOcup){    
    while(1){
        fscanf(archVentasYOcupacion," %*c%*d");        
        (*arrButOcup)++;
        if(fgetc(archVentasYOcupacion)=='\n') break;
    }
}

void ordenarPeliculasPorRecaudacion(int *arrPelicula, int *arrFunciones,
            int *arrButVend, int *arrButOcup, double *arrRecaudacion,
            int cantPeliculas){
    for(int i=0; i<cantPeliculas-1; i++)
        for(int j=i+1; j<cantPeliculas; j++)
            if(arrFunciones[j]>arrFunciones[i] || 
              (arrFunciones[j]==arrFunciones[i] && 
               arrRecaudacion[j]<arrRecaudacion[i])){
                cambiarInt(arrPelicula,i,j);
                cambiarInt(arrFunciones,i,j);
                cambiarInt(arrButVend,i,j);
                cambiarInt(arrButOcup,i,j);
                cambiarDouble(arrRecaudacion,i,j);
            }
}

void imprimirReporteDeVentasYOcupaciones(int *arrPelicula, int *arrFunciones,
            int *arrButVend, double *arrRecaudacion, int *arrButOcup,
            int cantPeliculas){    
    FILE *archReporte = abrirArchivo("ReporteDeVentasYOcupaciones","w");
    imprimirCabeceraPrincipal(archReporte);
    int butVend=0, butOcup=0, iMasEsp, iMenosEsp, masEsp=0, menosEsp=9999;
    double ocupacion, recaudacionTotal=0.0;
    for(int i=0; i<cantPeliculas; i++){
        ocupacion=calcularPorcentaje(arrButVend[i],arrButOcup[i]);
        fprintf(archReporte,"%04d %21d %20d %18.2lf",arrPelicula[i],arrFunciones[i],
                arrButVend[i],arrRecaudacion[i]);
        fprintf(archReporte,"%17d %13.2lf%%\n",arrButOcup[i],ocupacion);        
        recaudacionTotal+=arrRecaudacion[i];
        butVend+=arrButVend[i];
        butOcup+=arrButOcup[i];
        if(arrButOcup[i]>masEsp){
            masEsp=arrButOcup[i];
            iMasEsp=i;
        }
        if(arrButOcup[i]<menosEsp){
            menosEsp=arrButOcup[i];
            iMenosEsp=i;
        }        
    }
    ocupacion=calcularPorcentaje(butVend,butOcup);
    imprimirResumen(archReporte,cantPeliculas,recaudacionTotal,ocupacion); 
    imprimirMenosYMasEsp(iMasEsp,iMenosEsp,arrPelicula,arrButVend,arrButOcup,
            arrRecaudacion,archReporte);
    fclose(archReporte);
}

void imprimirCabeceraPrincipal(FILE *archReporte){
    fprintf(archReporte,"%75s\n","REPORTE DE VENTAS Y OCUPACIÓN DE SALAS");
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"%s %24s %12s %22s %12s %14s\n","Cod.Película",
            "Funciones Programadas","But.Vend.","Recaudación (S/.).",
            "But.Ocup.","%Ocupación");
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

double calcularPorcentaje(int butVend, int butOcup){
    return (double)butOcup*100/butVend;
}

void imprimirResumen(FILE *archReporte, int cantPeliculas, double recaudacionTotal,
                     double ocupacion){    
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"RESUMEN:\n");
    fprintf(archReporte,"Cantidad de peliculas: %3d\n",cantPeliculas);
    fprintf(archReporte,"Recaudacion total:   S/. %.1lf\n",recaudacionTotal);
    fprintf(archReporte,"%%Ocupacion total: %11.2lf%%\n",ocupacion);    
}

void imprimirMenosYMasEsp(int iMasEsp, int iMenosEsp, int *arrPelicula,
                          int *arrButVend, int *arrButOcup, double *arrRecaudacion,
                          FILE *archReporte){    
    imprimirLinea(archReporte,'-',MAX_LINEA);
    double ocupacionMenosEsp, ocupacionMasEsp;
    ocupacionMenosEsp = calcularPorcentaje(arrButVend[iMenosEsp],arrButOcup[iMenosEsp]);
    ocupacionMasEsp = calcularPorcentaje(arrButVend[iMasEsp],arrButOcup[iMasEsp]);
    fprintf(archReporte,"%s %4d %23s %6d %15s %.1lf%% %20s %5.1lf\n",
            "Pelicula con menos espectadores:",arrPelicula[iMenosEsp],
            "Butacas Vendidas:",arrButVend[iMenosEsp],"%Ocupacion:",
            ocupacionMenosEsp,"Recaudacion: S/.",arrRecaudacion[iMenosEsp]);
    fprintf(archReporte,"%s %6d %23s %6d %15s %.1lf%% %20s %5.1lf\n",
            "Pelicula con mas espectadores:",arrPelicula[iMasEsp],
            "Butacas Vendidas:",arrButVend[iMasEsp],"%Ocupacion:",
            ocupacionMasEsp,"Recaudacion: S/.",arrRecaudacion[iMasEsp]);
    imprimirLinea(archReporte,'=',MAX_LINEA);
}
