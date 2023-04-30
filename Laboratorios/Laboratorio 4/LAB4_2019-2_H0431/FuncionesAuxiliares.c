/* 
 * Proyecto: LAB4_2019-2_H0431
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 1 de mayo de 2022, 01:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 57
#define MAX_LINEA_2 122
#define MAX_BARRA 50
#define MAX 20
#define NO_SE_ENCONTRO -1

void leerArrPersonas(int *arrDni, int *arrTelefono, int *arrCargoFam, 
                     int *arrRiesgo, int *cantPersonas){    
    FILE *archPersonas;
    archPersonas = fopen("L4-Personas.txt","r");
    if(archPersonas==NULL){
        printf("ERROR: No se pudo abrir el archivo L4-Personas.txt\n");
        exit(1);        
    }
    asignarDatosPersonas(archPersonas,arrDni,arrTelefono,arrCargoFam,arrRiesgo,
            cantPersonas);
    fclose(archPersonas);    
}

void asignarDatosPersonas(FILE *archPersonas, int *arrDni, int *arrTelefono,
                          int *arrCargoFam, int *arrRiesgo, int *cantPersonas){
    while(1){
        fscanf(archPersonas,"%d %d %d %d",&arrDni[*cantPersonas],
                &arrTelefono[*cantPersonas],&arrCargoFam[*cantPersonas],
                &arrRiesgo[*cantPersonas]);
        if(feof(archPersonas)) break;
        (*cantPersonas)++;
    }
}

void leerArrIngresos(double *arrIngreso, int *arrDni, int cantPersonas,
                     int *fechaMasReciente, int *fechaMasAntigua){
    FILE *archRegistroDeIngresos;
    archRegistroDeIngresos = fopen("L4-RegistroDeIngresos.txt","r");
    if(archRegistroDeIngresos==NULL){
        printf("ERROR: No se pudo abrir el archivo L4-RegistroDeIngresos.txt\n");
        exit(1);        
    }
    asignarDatosIngresos(archRegistroDeIngresos,arrIngreso,arrDni,cantPersonas,
            fechaMasReciente,fechaMasAntigua);
    fclose(archRegistroDeIngresos);
}

void asignarDatosIngresos(FILE *archRegistroDeIngresos, double *arrIngreso,
                          int *arrDni, int cantPersonas, int *fechaMasReciente,
                          int *fechaMasAntigua){        
    int dni, dd, mm, aaaa, fecha;
    double ingreso;
    while(1){
        fscanf(archRegistroDeIngresos,"%d",&dni);
        if(feof(archRegistroDeIngresos)) break;
        fscanf(archRegistroDeIngresos,"%lf %d/%d/%d",&ingreso,&dd,&mm,&aaaa);
        fecha = juntarFecha(dd,mm,aaaa);
        asignarIngresoAPersona(arrIngreso,arrDni,cantPersonas,fechaMasReciente,
                fechaMasAntigua,dni,ingreso,fecha);
    }    
}

int juntarFecha(int dd, int mm, int aaaa){
    return aaaa*10000 + mm*100 + dd;
}

void asignarIngresoAPersona(double *arrIngreso, int *arrDni, int cantPersonas, 
                            int *fechaMasReciente, int *fechaMasAntigua, 
                            int dni, double ingreso, int fecha){    
    int i=buscarIndiceIngresos(arrDni,dni,cantPersonas);
    if(i==NO_SE_ENCONTRO) return;    
    arrIngreso[i] += ingreso;
    cambiarFechas(fecha,fechaMasReciente,fechaMasAntigua);   
}

int buscarIndiceIngresos(int *arrDni, int dni, int cantPersonas){    
    for(int i=0; i<cantPersonas; i++)
        if(dni==arrDni[i]) return i;    
    return NO_SE_ENCONTRO;
}

void cambiarFechas(int fecha, int *fechaMasReciente, int *fechaMasAntigua){
    if(fecha>*fechaMasReciente)
        *fechaMasReciente=fecha;
    if(fecha<*fechaMasAntigua)
        *fechaMasAntigua=fecha;
}

void calcularLineasDeCredito(double *arrLineaBancoA, double *arrLineaBancoB,
                             double *arrIngreso, int *arrCargoFam, int *arrRiesgo,
                             int cantPersonas){
    double f1, f2;    
    for(int i=0; i<cantPersonas; i++){
        f1 = calcularF1BancoA(arrCargoFam[i]);        
        f2 = calcularF2BancoA(arrRiesgo[i]);
        arrLineaBancoA[i] = (150*arrIngreso[i]/12)*(f1/3.5)*f2;
        f1 = calcularF1BancoB(arrCargoFam[i]);        
        f2 = calcularF2BancoB(arrRiesgo[i]);
        arrLineaBancoB[i] = (150*arrIngreso[i]/12)*(f1/3.5)*f2;
    }    
}

double calcularF1BancoA(int cargoFamiliar){
    if(cargoFamiliar==0) return 8.0;
    else if(cargoFamiliar==1) return 6.0;
    else if(cargoFamiliar==2) return 4.0;
    else if(cargoFamiliar==3) return 2.0;
    else if(cargoFamiliar>3) return 0.1;
}

double calcularF2BancoA(int riesgoFinanciero){
    if(riesgoFinanciero>=1 && riesgoFinanciero<=5) return 1.0;
    else if(riesgoFinanciero>=6) return 0.1;
}

double calcularF1BancoB(int cargoFamiliar){
    if(cargoFamiliar==0) return 7.5;
    else return 1.5;
}

double calcularF2BancoB(int riesgoFinanciero){    
    if(riesgoFinanciero>=1 && riesgoFinanciero<2) return 1.0;
    else if(riesgoFinanciero>=2 && riesgoFinanciero<3) return 0.7;
    else if(riesgoFinanciero>=3 && riesgoFinanciero<4) return 0.4;
    else if(riesgoFinanciero>=4 && riesgoFinanciero<5) return 0.1;
    else if(riesgoFinanciero>=5) return 0.05;
}

void imprimirPrimerReporte(int fechaMasAntigua, int fechaMasReciente,
                           int *arrDni, int *arrTelefono, double *arrLineaBancoA,
                           double *arrLineaBancoB, int cantPersonas){    
    FILE *archReporteLineasDeCredito;
    archReporteLineasDeCredito = fopen("LineasDeCredito.txt","w");
    if(archReporteLineasDeCredito==NULL){
        printf("ERROR: No se pudo abrir el archivo LineasDeCredito.txt\n");
        exit(1);        
    }
    imprimirReporteLineasDeCredito(archReporteLineasDeCredito,fechaMasAntigua,
            fechaMasReciente,arrDni,arrTelefono,arrLineaBancoA,arrLineaBancoB,
            cantPersonas);            
    fclose(archReporteLineasDeCredito);
}

void imprimirReporteLineasDeCredito(FILE *archReporteLineasDeCredito, 
                                    int fechaMasAntigua, int fechaMasReciente,
                                    int *arrDni, int *arrTelefono, 
                                    double *arrLineaBancoA, 
                                    double *arrLineaBancoB, int cantPersonas){    
    imprimirCabeceraLineasDeCredito(archReporteLineasDeCredito,fechaMasAntigua,
            fechaMasReciente);
    for(int i=0; i<cantPersonas; i++)        
        fprintf(archReporteLineasDeCredito,"%08d %13d %12.2lf %12.2lf\n",
                arrDni[i],arrTelefono[i],arrLineaBancoA[i],arrLineaBancoB[i]);  
}       

void imprimirCabeceraLineasDeCredito(FILE *archReporteLineasDeCredito,
                                     int fechaMasAntigua, int fechaMasReciente){    
    int ddReciente, mmReciente, aaaaReciente, ddAntigua, mmAntigua, aaaaAntigua;
    separarFecha(fechaMasReciente,&ddReciente,&mmReciente,&aaaaReciente);
    separarFecha(fechaMasAntigua,&ddAntigua,&mmAntigua,&aaaaAntigua);
    fprintf(archReporteLineasDeCredito,"LÍNEAS DE CRÉDITO\n");
    fprintf(archReporteLineasDeCredito,"Fecha más reciente en el registro de"
            "ingresos: %02d/%02d/%4d\n",ddReciente,mmReciente,aaaaReciente);
    fprintf(archReporteLineasDeCredito,"Fecha más antigua en el registro de"
            "ingresos:  %02d/%02d/%4d\n",ddAntigua,mmAntigua,aaaaAntigua);
    imprimirLinea(archReporteLineasDeCredito,'=',MAX_LINEA);
    fprintf(archReporteLineasDeCredito,"%s %19s %12s %11s\n","DNI","Teléfono",
            "Banco A","Banco B");
    imprimirLinea(archReporteLineasDeCredito,'-',MAX_LINEA);
}

void separarFecha(int fecha, int *dd, int *mm, int *aaaa){    
    *aaaa = fecha/10000;
    fecha -= (*aaaa)*10000;
    *mm = fecha/100;
    *dd = fecha-(*mm)*100;
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirSegundoReporte(double *arrLineaBancoA, double *arrLineaBancoB,
                            int cantPersonas){   
    FILE *archReporteDistribucionDeFrecuencias;
    archReporteDistribucionDeFrecuencias = fopen("DistribucionDeFrecuencias.txt","w");
    if(archReporteDistribucionDeFrecuencias==NULL){
        printf("ERROR: No se pudo abrir el archivo DistribucionDeFrecuencias.txt\n");
        exit(1);        
    }
    imprimirReporteDistribucionDeFrec(archReporteDistribucionDeFrecuencias,
            arrLineaBancoA,arrLineaBancoB,cantPersonas);            
    fclose(archReporteDistribucionDeFrecuencias);   
}

void imprimirReporteDistribucionDeFrec(FILE *archReporteDistribucionDeFrecuencias,
                                       double *arrLineaBancoA,
                                       double *arrLineaBancoB, int cantPersonas){
    imprimirCabeceraDistrubicionDeFrec(archReporteDistribucionDeFrecuencias);
    int arrGrafA[MAX]={0}, arrGrafB[MAX]={0};
    calcularArrGraf(arrGrafA,arrGrafB,arrLineaBancoA,arrLineaBancoB,cantPersonas);
    imprimirGraficas(archReporteDistribucionDeFrecuencias,arrGrafA,arrGrafB);
    imprimirLinea(archReporteDistribucionDeFrecuencias,'=',MAX_LINEA_2);
}

void imprimirCabeceraDistrubicionDeFrec(FILE *archReporteDistribucionDeFrecuencias){
    fprintf(archReporteDistribucionDeFrecuencias,"%74s\n","DISTRIBUCION DE "
            "FRECUENCIAS");
    fprintf(archReporteDistribucionDeFrecuencias,"%80s\n","LÍNEAS DE CRÉDITO "
            "SEGÚN LOS BANCOS");
    fprintf(archReporteDistribucionDeFrecuencias,"%51s %20s\n","Banco A",
            "Banco B");
    imprimirLinea(archReporteDistribucionDeFrecuencias,'=',MAX_LINEA_2);
}

void calcularArrGraf(int *arrGrafA, int *arrGrafB, double *arrLineaBancoA, 
                     double *arrLineaBancoB, int cantPersonas){    
    for(int i=0; i<cantPersonas; i++){
        if((int)(arrLineaBancoA[i]/5000)>MAX)
            arrGrafA[MAX-1]++;
        else
            arrGrafA[(int)(arrLineaBancoA[i]/5000)]++;
        if((int)(arrLineaBancoB[i]/5000)>MAX)
            arrGrafB[MAX-1]++;
        else
            arrGrafB[(int)(arrLineaBancoB[i]/5000)]++;
    }
}

void imprimirGraficas(FILE *archReporte, int *arrGrafA, int *arrGrafB){    
    int maxDistribucionA, maxDistribucionB;
    maxDistribucionA = buscarMaxDistribucion(arrGrafA);
    maxDistribucionB = buscarMaxDistribucion(arrGrafB);    
    for(int i=0; i<MAX; i++){        
        fprintf(archReporte,"%6d %9c",(i+1)*5000,'|');
        imprimirChar(archReporte,'#',maxDistribucionA,arrGrafA[i]);
        fprintf(archReporte,"%5s","||");
        imprimirChar(archReporte,'&',maxDistribucionB,arrGrafB[i]);
        fputc('\n',archReporte);
    }
}

int buscarMaxDistribucion(int *arrGraf){
    int max=0;
    for(int i=0; i<MAX; i++)
        if(arrGraf[i]>=max)
            max=arrGraf[i];
    return max;
}

void imprimirChar(FILE *archReporte, char c, int maxDistribucion, int arrGraf){    
    int numChar = arrGraf*MAX_BARRA/maxDistribucion;   
    for(int i=0; i<numChar; i++) fputc(c,archReporte);
    imprimirEspacios(archReporte,numChar);
}

void imprimirEspacios(FILE *archReporte, int numChar){
    for(int i=0; i<MAX_BARRA-numChar; i++) fputc(' ',archReporte);
}