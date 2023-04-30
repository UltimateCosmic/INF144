/* 
 * Proyecto: Pr02_2022-1_Poligonal
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 2 de mayo de 2022, 07:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FuncionesAuxiliares.h"
#define MAX_VERTICES 100
#define MAX_LINEA 50

void leerArrPoligonal(double *arrPoligonalX, double *arrPoligonalY,
                      int *cantVertices){
    //Apertura de archivo Poligonal.txt
    FILE *archPoligonal;
    archPoligonal = fopen("Poligonal.txt","r");
    if(archPoligonal==NULL){
        printf("ERROR: No se pudo abrir el archivo Poligonal.txt\n");
        exit(1);
    }
    asignarDatosArrPoligonal(archPoligonal,arrPoligonalX,arrPoligonalY,
            cantVertices);
    fclose(archPoligonal);
}

void asignarDatosArrPoligonal(FILE *archPoligonal, double *arrPoligonalX,
                              double *arrPoligonalY, int *cantVertices){
    //Lectura de datos y asignación a los arreglos.
    while(1){
        fscanf(archPoligonal,"%lf %lf",&arrPoligonalX[*cantVertices],
                &arrPoligonalY[*cantVertices]); 
        if(feof(archPoligonal)) break;
        (*cantVertices)++;      //La cantidad de vertices que hay en el archivo.
    }
}

void emitirReporteDeTareas(double *arrPoligonalX, double *arrPoligonalY,
                           int cantVertices){
    //Apertura de archivo de Reporte.txt
    FILE *archReporteDeTareas;
    archReporteDeTareas = fopen("ReporteDeTareas.txt","w");
    if(archReporteDeTareas==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeTareas.txt\n");
        exit(1);
    }
    realizarTareas(archReporteDeTareas,arrPoligonalX,arrPoligonalY,
            cantVertices);       
}

void realizarTareas(FILE *archReporteDeTareas, double *arrPoligonalX, 
                    double *arrPoligonalY, int cantVertices){       
    //Tarea a)
    double longPoligonal = calcularLongPoligonal(arrPoligonalX,arrPoligonalY,
            cantVertices);    
    //Tarea b)
    double areaBajoPoligonal = calcularAreaBajoPoligonal(arrPoligonalX,
            arrPoligonalY,cantVertices);    
    //Tarea c)
    int cantPicos=0, cantValles=0;
    double arrPicosX[MAX_VERTICES], arrVallesX[MAX_VERTICES];
    double arrPicosY[MAX_VERTICES], arrVallesY[MAX_VERTICES];
    determinarPicosYValles(arrPoligonalX,arrPoligonalY,cantVertices,
            arrPicosX,arrPicosY,arrVallesX,arrVallesY,&cantPicos,&cantValles);        
    //Tarea d)
    int iPicoMasBajo, iValleMasAlto;
    determinarPicoMasBajo(arrPicosY,&iPicoMasBajo,cantPicos); 
    determinarValleMasAlto(arrVallesY,&iValleMasAlto,cantValles);    
    //Reporte
    imprimirReporteDeTareas(archReporteDeTareas,longPoligonal,areaBajoPoligonal,
            arrPicosX,arrPicosY,arrVallesX,arrVallesY,cantPicos,cantValles,
            iPicoMasBajo,iValleMasAlto);    
    //Tarea e)      Conlleva a la parte de coordenadas completas del reporte
    abrirArchPuntosACompletar(arrPoligonalX,arrPoligonalY,cantVertices,
            archReporteDeTareas);
}

double calcularLongPoligonal(double *arrPoligonalX, double *arrPoligonalY,
                             int cantVertices){    
    /* Calculo de la longitud poligonal (sumamos las diferentes longitudes que 
     * existen entre dos puntos)*/
    double longitudPoligonal=0, x2, x1, y2, y1;
    for(int i=0; i<cantVertices-1; i++){       
        x1 = arrPoligonalX[i];
        x2 = arrPoligonalX[i+1];
        y1 = arrPoligonalY[i];
        y2 = arrPoligonalY[i+1];
        longitudPoligonal += calcularDistancia(x2,x1,y2,y1);
    }
    return longitudPoligonal;
}

double calcularAreaBajoPoligonal(double *arrPoligonalX, double *arrPoligonalY,
                             int cantVertices){
    //Suma de las áreas bajo la poligonal.
    double area=0, x2, x1, y2, y1;
    for(int i=0; i<cantVertices-1; i++){       
        x1 = arrPoligonalX[i];          
        x2 = arrPoligonalX[i+1];        //         Ejemplo de recta
        y1 = arrPoligonalY[i];          // (x1,y1)---------L--------(x2,y2);
        y2 = arrPoligonalY[i+1];
        area += (calcularDistancia(x2,x2,y2,0)+calcularDistancia(x1,x1,y1,0))*
                calcularDistancia(x2,x1,0,0)/2;
    }
    return area;
}

double calcularDistancia(double x2, double x1, double y2, double y1){
    //Calculo de la distancia entre dos puntos.
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

void determinarPicosYValles(double *arrPoligonalX, double *arrPoligonalY,
                            int cantVertices, double *arrPicosX, 
                            double *arrPicosY, double *arrVallesX, 
                            double *arrVallesY, int *cantPicos, int *cantValles){    
    /* Calculamos los picos y valles (los picos tienen que estar arriba de las
     * coordenadas y que se encuentran entre ese punto y los valles tienen
     * que estar debajo)*/
    double y, y1, y2, x, x1, x2;    
    for(int i=0; i<cantVertices; i++){       
        x1 = arrPoligonalX[i];
        x2 = arrPoligonalX[i+2];
        y1 = arrPoligonalY[i];
        y2 = arrPoligonalY[i+2];
        x = arrPoligonalX[i+1];
        y = arrPoligonalY[i+1];        
        if(y>y1 && y>y2){
            arrPicosX[*cantPicos]=x;
            arrPicosY[*cantPicos]=y;
            (*cantPicos)++;
        }
        if(y<y1 && y<y2){
            arrVallesX[*cantPicos]=x;
            arrVallesY[*cantPicos]=y;
            (*cantValles)++;
        }
    }    
}

void determinarPicoMasBajo(double *arrPicosY, int *iPicoMasBajo, int cantPicos){    
    //Retornamos el indice del pico mas alto
    double masBajo=9999;    
    for(int i=0; i<cantPicos; i++)    
        if(arrPicosY[i]<masBajo){
            masBajo = arrPicosY[i];
            *iPicoMasBajo = i;
        }        
}

void determinarValleMasAlto(double *arrVallesY, int *iValleMasAlto, int cantValles){
    //Retornamos el indice del pico bajo alto
    double masAlto=0;    
    for(int i=0; i<cantValles; i++)    
        if(arrVallesY[i]>masAlto){
            masAlto = arrVallesY[i];
            *iValleMasAlto = i;
        }         
}

void imprimirReporteDeTareas(FILE *archReporteDeTareas, double longPoligonal,
                             double areaBajoPoligonal, double *arrPicosX,
                             double *arrPicosY, double *arrVallesX,
                             double *arrVallesY, int cantPicos, int cantValles,
                             int iPicoMasBajo, int iValleMasAlto){    
    imprimirCabecera(archReporteDeTareas);
    fprintf(archReporteDeTareas,"%20s %10.2lf\n","a) Longitud de la poligonal:",
            longPoligonal);
    imprimirLinea(archReporteDeTareas,'=',MAX_LINEA);
    fprintf(archReporteDeTareas,"%23s %10.2lf\n","b) Área bajo la poligonal:",
            areaBajoPoligonal);
    imprimirLinea(archReporteDeTareas,'=',MAX_LINEA);
    fprintf(archReporteDeTareas,"%23s\n","b) Picos y valles de la poligonal:");
    imprimirPicosYValles(arrPicosX,arrPicosY,arrVallesX,arrVallesY,cantPicos,
            cantValles,archReporteDeTareas);
    imprimirLinea(archReporteDeTareas,'=',MAX_LINEA);
    imprimirPicoMasBajoYValleMasAlto(arrPicosX,arrPicosY,arrVallesX,arrVallesY,
            iPicoMasBajo,iValleMasAlto,archReporteDeTareas);
}

void imprimirCabecera(FILE *archReporteDeTareas){    
    fprintf(archReporteDeTareas,"%50s\n","REPORTE DE TAREAS POLIGONALES");
    imprimirLinea(archReporteDeTareas,'=',MAX_LINEA);
}

void imprimirPicosYValles(double *arrPicosX, double *arrPicosY, 
                          double *arrVallesX, double *arrVallesY, int cantPicos,
                          int cantValles, FILE *archReporteDeTareas){
    imprimirLinea(archReporteDeTareas,'-',MAX_LINEA);
    fprintf(archReporteDeTareas,"%16s\n","PICOS (x,y):");
    imprimirLinea(archReporteDeTareas,'-',MAX_LINEA);
    for(int i=0; i<cantPicos; i++)
        fprintf(archReporteDeTareas,"%5d) %11.2lf %10.2lf\n",i+1,
                arrPicosX[i],arrPicosY[i]);
    imprimirLinea(archReporteDeTareas,'-',MAX_LINEA);
    fprintf(archReporteDeTareas,"%17s\n","VALLES (x,y):");
    imprimirLinea(archReporteDeTareas,'-',MAX_LINEA);
    for(int i=0; i<cantValles; i++)
        fprintf(archReporteDeTareas,"%5d) %11.2lf %10.2lf\n",i+1,
                arrVallesX[i],arrVallesY[i]);    
}

void imprimirPicoMasBajoYValleMasAlto(double *arrPicosX, double *arrPicosY,
                                      double *arrVallesX, double *arrVallesY,
                                      int iPicoMasBajo, int iValleMasAlto,
                                      FILE *archReporteDeTareas){
    fprintf(archReporteDeTareas,"%22s %10.2lf %8.2lf\n","d) Pico más bajo (x,y):",
            arrPicosX[iPicoMasBajo],arrPicosY[iPicoMasBajo]);    
    imprimirLinea(archReporteDeTareas,'-',MAX_LINEA);
    fprintf(archReporteDeTareas,"%23s %9.2lf %8.2lf\n","d) Valle más alto (x,y):",
            arrVallesX[iValleMasAlto],arrVallesY[iValleMasAlto]);    
    imprimirLinea(archReporteDeTareas,'=',MAX_LINEA);
}

void imprimirLinea(FILE *arch, int c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void abrirArchPuntosACompletar(double *arrPoligonalX, double *arrPoligonalY,
                               int cantVertices, FILE *archReporteDeTareas){    
    FILE *archPuntosACompletar;
    archPuntosACompletar = fopen("A_Completar.txt","r");
    if(archPuntosACompletar==NULL){
        printf("ERROR: No se pudo abrir el archivo A_Completar.txt\n");
        exit(1);
    }
    leerPuntosFlotantes(archPuntosACompletar,archReporteDeTareas,arrPoligonalX,
            arrPoligonalY,cantVertices);      
}

void leerPuntosFlotantes(FILE *archPuntosACompletar, FILE *archReporteDeTareas,
                         double *arrPoligonalX, double *arrPoligonalY,
                         int cantVertices){    
    double arrCoordenadasX[MAX_VERTICES], arrCoordenadasY[MAX_VERTICES];
    int cantCoordenadasX=0;
    leerDatosArrCoordenadasX(archPuntosACompletar,arrCoordenadasX,
            &cantCoordenadasX);    
    calcularCoordenadasY(arrPoligonalX,arrPoligonalY,cantVertices,
            arrCoordenadasX,arrCoordenadasY,cantCoordenadasX);
    aniadirCoordenadasCompletasReporte(arrCoordenadasX,arrCoordenadasY,
            cantCoordenadasX,archReporteDeTareas);
}

void leerDatosArrCoordenadasX(FILE *archPuntosACompletar, double *arrCoordenadasX,
                              int *cantCoordenadasX){   
    //Lectura del archivo A_Completar.txt
    while(1){
        fscanf(archPuntosACompletar,"%lf",&arrCoordenadasX[*cantCoordenadasX]);
        if(feof(archPuntosACompletar)) break;
        (*cantCoordenadasX)++;       
    }
    fclose(archPuntosACompletar);  
}

void calcularCoordenadasY(double *arrPoligonalX, double *arrPoligonalY,
                          int cantVertices, double *arrCoordenadasX,
                          double *arrCoordenadasY, int cantCoordenadasX){    
    //Calculo de la coordenada Y
    double x, y, x1, x2, y1, y2;
    for(int i=0; i<cantCoordenadasX; i++){        
        double maxInf=-9999, maxSup=9999;    
        x = arrCoordenadasX[i];        
        //Buscamos los puntos más cercanos
        for(int j=0; j<cantVertices; j++){            
            if(arrPoligonalX[j]>maxInf && arrPoligonalX[j]<x){
                maxInf = arrPoligonalX[j];  
                y1 = arrPoligonalY[j];
            }if(arrPoligonalX[j]<maxSup && arrPoligonalX[j]>x){
                maxSup = arrPoligonalX[j]; 
                y2 = arrPoligonalY[j];
            }
        }        
        x1 = maxInf;
        x2 = maxSup;
        y = (y2-y1)*(x-x1)/(x2-x1)+y1;
        arrCoordenadasY[i] = y;        
    }
}

void aniadirCoordenadasCompletasReporte(double *arrCoordenadasX,
                                        double *arrCoordenadasY,
                                        int cantCoordenadas,
                                        FILE *archReporteDeTareas){    
    //Añadimos las coordenadas completas y cerramos el reporte
    fprintf(archReporteDeTareas,"\n%32s\n","COORDENADAS COMPLETAS");
    fprintf(archReporteDeTareas,"%13c %15c\n",'X','Y');    
    for(int i=0; i<cantCoordenadas; i++)
        fprintf(archReporteDeTareas,"%15.2lf %15.2lf\n",arrCoordenadasX[i],
                arrCoordenadasY[i]);    
    fclose(archReporteDeTareas);
}