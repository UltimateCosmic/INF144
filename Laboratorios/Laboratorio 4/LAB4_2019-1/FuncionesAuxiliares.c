/* 
 * Proyecto: LAB4_2019-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 10 de mayo de 2022, 06:24 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 120
#define NO_SE_ENCONTRO 0

void procesarUtilidades(int *arrAnio, double *arrUtilidad, double *arrPorc,
                        int *numUtilidades){    
    FILE *arch;
    arch=fopen("L4-Utilidades.txt","r");
    if(arch==NULL){
        printf("EROR: No se pudo abrir el archivo LAB4-Utilidades.txt\n");
        exit(1);
    }
    leerUtilidades(arch,arrAnio,arrUtilidad,arrPorc,numUtilidades);
    fclose(arch);
}

void leerUtilidades(FILE *arch, int *arrAnio, double *arrUtilidad, 
                    double *arrPorc, int *numUtilidades){    
    while(1){
        fscanf(arch,"%d",&arrAnio[*numUtilidades]);
        if(feof(arch)) break;        
        fscanf(arch,"%lf %lf",&arrUtilidad[*numUtilidades],
                &arrPorc[*numUtilidades]);
        (*numUtilidades)++;
    }
}

void ordenarUtilidadesPorAnio(int *arrAnioUtilidad, double *arrUtilidad,
                              double *arrPorc, int numUtilidades){    
    for(int i=0; i<numUtilidades-1; i++)
        for(int j=i+1; j<numUtilidades; j++)
            if(arrAnioUtilidad[j]>arrAnioUtilidad[i]){
                cambiarInt(arrAnioUtilidad,i,j);
                cambiarDouble(arrUtilidad,i,j);
                cambiarDouble(arrPorc,i,j);                
            }    
}

void procesarEmpleados(int *arrCodEmpleado, double *arrSueldoEmpleado,
                       int *numEmpleados){
    FILE *arch;
    arch=fopen("L4-Empleados.txt","r");
    if(arch==NULL){
        printf("EROR: No se pudo abrir el archivo LAB4-Empleados.txt\n");
        exit(1);
    }
    leerEmpleados(arch,arrCodEmpleado,arrSueldoEmpleado,numEmpleados);
    fclose(arch);
}

void leerEmpleados(FILE *arch, int *arrCodEmpleado, double *arrSueldoEmpleado,
                   int *numEmpleados){    
    while(1){
        fscanf(arch,"%d",&arrCodEmpleado[*numEmpleados]);
        if(feof(arch)) break;        
        fscanf(arch,"%lf",&arrSueldoEmpleado[*numEmpleados]);
        (*numEmpleados)++;
    }   
}

void procesarPlantillas(int *codPlant, int *anioPlant, int *mesPlant, 
                        int *diasLaboro, double *abonoEmpleado, 
                        int *numPlantillas){
    FILE *arch;
    arch=fopen("L4-Planilla.txt","r");
    if(arch==NULL){
        printf("EROR: No se pudo abrir el archivo LAB4-Plantilla.txt\n");
        exit(1);
    }
    leerPlantillas(arch,codPlant,anioPlant,mesPlant,diasLaboro,abonoEmpleado,
            numPlantillas);
    fclose(arch);    
}

void leerPlantillas(FILE *arch, int *codPlant, int *anioPlant, int *mesPlant, 
                    int *diasLaboro, double *abonoEmpleado, int *numPlantillas){
    while(1){
        fscanf(arch,"%d",&codPlant[*numPlantillas]);
        if(feof(arch)) break;        
        fscanf(arch,"%d %d",&anioPlant[*numPlantillas],&mesPlant[*numPlantillas]);
        fscanf(arch,"%lf %d",&abonoEmpleado[*numPlantillas],
                &diasLaboro[*numPlantillas]);
        (*numPlantillas)++;
    }
}

void abonarEmpleados(double *abonoEmpleado, int *diasLaboro, int numPlantillas,
                     int *arrCodEmpleado, double *arrSueldoEmpleado,
                     int numEmpleados, int *codPlant){    
    for(int i=0; i<numPlantillas; i++)
        abonoEmpleado[i]=calcularAbono(diasLaboro[i],arrCodEmpleado,
                arrSueldoEmpleado,numEmpleados,codPlant[i],abonoEmpleado[i]);
}

double calcularAbono(int diasLaboro, int *arrCodEmpleado, double *arrSueldoEmpleado, 
                     int numEmpleados, int codPlant, double diasLaborables){    
    for(int i=0; i<numEmpleados; i++)
        if(codPlant==arrCodEmpleado[i])
            return fraccion(arrSueldoEmpleado[i],diasLaboro,diasLaborables);
    return NO_SE_ENCONTRO;
}

double fraccion(double sueldoTotal, int diasLaboro, double diasLaborables){
    return sueldoTotal*diasLaboro/diasLaborables;
}

void ordenarPlantillas(int *codPlant, int *anioPlant, int *mesPlant, 
                       int *diasLaboro, double *abonoEmpleado, int numPlantillas){    
    for(int i=0; i<numPlantillas-1; i++)
        for(int k=i+1; k<numPlantillas; k++)
            if(anioPlant[i]>anioPlant[k] ||
               anioPlant[i]==anioPlant[k] && codPlant[i]>codPlant[k] ||
               anioPlant[i]==anioPlant[k] && codPlant[i]==codPlant[k] && 
               mesPlant[i]>mesPlant[k])
                cambiarArrPlant(codPlant,anioPlant,mesPlant,diasLaboro,
                        abonoEmpleado,i,k);
}

void cambiarArrPlant(int *codPlant, int *anioPlant, int *mesPlant, 
                     int *diasLaboro, double *abonoEmpleado, int i, int k){    
    cambiarInt(codPlant,i,k);
    cambiarInt(anioPlant,i,k);
    cambiarInt(mesPlant,i,k);
    cambiarInt(diasLaboro,i,k);
    cambiarDouble(abonoEmpleado,i,k);    
}

void cambiarInt(int *arrInt, int i, int k){
    int aux=arrInt[i];
    arrInt[i]=arrInt[k];
    arrInt[k]=aux;
}

void cambiarDouble(double *arrDouble, int i, int k){
    double aux=arrDouble[i];
    arrDouble[i]=arrDouble[k];
    arrDouble[k]=aux;
}

void procesarReporteDeUtilidades(int *arrCodEmpleado, double *arrSueldoEmpleado,
            int numEmpleados, int *codPlant, int *anioPlant, int *mesPlant,
            int *diasLaboro, double *abonoEmpleado, int numPlantillas){    
    FILE *archReporte = fopen("ReporteDeUtilidades.txt","w");
    if(archReporte==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeUtilidades.txt\n");
        exit(1);
    }
    imprimirEmpleados(archReporte,arrCodEmpleado,arrSueldoEmpleado,numEmpleados);
    //COMPLETAR    
    fclose(archReporte);
}

void imprimirEmpleados(FILE *archReporte, int *arrCodEmpleado, double *arrSueldoEmpleado,
            int numEmpleados){    
    imprimirCabeceraDeEmpleados(archReporte);
    for(int i=0; i<numEmpleados; i++)
        fprintf(archReporte,"%3d   %06d %13.2lf\n",i+1,arrCodEmpleado[i],
                arrSueldoEmpleado[i]);    
}

void imprimirCabeceraDeEmpleados(FILE *archReporte){    
    fprintf(archReporte,"%54s\n","EMPRESA DE TELECOMUNICACIONES S.A.");
    fprintf(archReporte,"%51s\n","CONSULTA DEL PAGO DE UTILIDADES");
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"Empleados:\n");
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"%s %8s %12s\n","No.","CODIGO","SUELDO");
    imprimirLinea(archReporte,'-',MAX_LINEA);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}