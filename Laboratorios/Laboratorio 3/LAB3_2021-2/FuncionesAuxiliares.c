/* 
 * Proyecto: LAB3_2021-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 2 de mayo de 2022, 05:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 112
#define NO_SE_ENCONTRO -1

void leerArrPacientes(int *arrCodPaciente, int *arrCodPostal,
                      int *cantPacientes){    
    FILE *archPacientes;
    archPacientes = fopen("Pacientes.txt","r");
    if(archPacientes==NULL){
        printf("ERROR: No se pudo abrir el archivo Pacientes.txt\n");
        exit(1);
    }
    asignarDatosArrPacientes(archPacientes,arrCodPaciente,arrCodPostal,
            cantPacientes);    
    fclose(archPacientes);
}

void asignarDatosArrPacientes(FILE *archPacientes, int *arrCodPaciente,
                              int *arrCodPostal, int *cantPacientes){
    while(1){
        fscanf(archPacientes,"%d",&arrCodPaciente[*cantPacientes]);
        if(feof(archPacientes)) break;
        while(fgetc(archPacientes)!=']');
        fscanf(archPacientes,"%d",&arrCodPostal[*cantPacientes]);
        (*cantPacientes)++;
    }    
}

void leerArrMedicos(int *arrCodMed, double *arrTarifaMed, int *cantMedicos){
    FILE *archMedicos;
    archMedicos = fopen("Medicos.txt","r");
    if(archMedicos==NULL){
        printf("ERROR: No se pudo abrir el archivo Medicos.txt\n");
        exit(1);
    }
    asignarDatosArrMedicos(archMedicos,arrCodMed,arrTarifaMed,
            cantMedicos);    
    fclose(archMedicos);        
}

void asignarDatosArrMedicos(FILE *archMedicos, int *arrCodMed,
                            double *arrTarifaMed, int *cantMedicos){
    while(1){
        fscanf(archMedicos,"%d",&arrCodMed[*cantMedicos]);
        if(feof(archMedicos)) break;
        while(fgetc(archMedicos)==' ');
        while(fgetc(archMedicos)!=' ');
        fscanf(archMedicos,"%lf",&arrTarifaMed[*cantMedicos]);
        while(fgetc(archMedicos)!='\n');
        (*cantMedicos)++;
    }   
}

void leerArrDistritos(int *arrCodDistrito, int *cantDistritos){
    FILE *archDistritos;
    archDistritos = fopen("Distritos.txt","r");
    if(archDistritos==NULL){
        printf("ERROR: No se pudo abrir el archivo Distritos.txt\n");
        exit(1);
    }
    asignarDatosArrDistritos(archDistritos,arrCodDistrito,cantDistritos);    
    fclose(archDistritos);    
}

void asignarDatosArrDistritos(FILE *archDistritos, int *arrCodDistrito,
                              int *cantDistritos){
    while(1){
        fscanf(archDistritos,"%d",&arrCodDistrito[*cantDistritos]);  
        if(feof(archDistritos)) break;
        while(fgetc(archDistritos)!='\n');
        (*cantDistritos)++;
    }
}

void leerArrAtencinesMedicas(int *arrCodPaciente, int *arrFechaIni, 
                             int *arrFechaFin, int *arrDuracion, int *arrCitas,
                             double *arrMontoPagado, int cantPacientes, 
                             int *arrCodMed, double *arrTarifaMed,
                             int cantMedicos){
    FILE *archAtencinesMedicas;
    archAtencinesMedicas = fopen("AtencinesMedicas.txt","r");
    if(archAtencinesMedicas==NULL){
        printf("ERROR: No se pudo abrir el archivo AtencinesMedicas.txt\n");
        exit(1);
    }
    asignarDatosArrAtencinesMedicas(archAtencinesMedicas,arrCodPaciente,
            arrFechaIni,arrFechaFin,arrDuracion,arrCitas,arrMontoPagado,
            cantPacientes,arrCodMed,arrTarifaMed,cantMedicos);
    fclose(archAtencinesMedicas);        
}

void asignarDatosArrAtencinesMedicas(FILE *archAtencinesMedicas, 
                                     int *arrCodPaciente, int *arrFechaIni, 
                                     int *arrFechaFin, int *arrDuracion, 
                                     int *arrCitas, double *arrMontoPagado,
                                     int cantPacientes, int *arrCodMed, 
                                     double *arrTarifaMed, int cantMedicos){
    int codMedico, dd, mm, aaaa;
    while(1){
        fscanf(archAtencinesMedicas,"%d %d/%d/%d",&codMedico,&dd,&mm,&aaaa);
        if(feof(archAtencinesMedicas)) break;
        leerRegistros(archAtencinesMedicas,arrCodPaciente,arrFechaIni,
                arrFechaFin,arrDuracion,arrCitas,arrMontoPagado,codMedico,
                dd,mm,aaaa,cantPacientes,arrCodMed,arrTarifaMed,cantMedicos);        
    }
}

void leerRegistros(FILE *archAtencinesMedicas, int *arrCodPaciente, 
                   int *arrFechaIni, int *arrFechaFin, int *arrDuracion, 
                   int *arrCitas, double *arrMontoPagado, int codMedico,
                   int dd, int mm, int aaaa, int cantPacientes, int *arrCodMed,
                   double *arrTarifaMed, int cantMedicos){    
    int dni, hIni, mIni, sIni, hFin, mFin, sFin, indice;
    while(1){
        fscanf(archAtencinesMedicas,"%d",&dni);  
        leerHora(archAtencinesMedicas,&hIni,&mIni,&sIni);       
        leerHora(archAtencinesMedicas,&hFin,&mFin,&sFin);
        indice = buscarIndice(dni,arrCodPaciente,cantPacientes); 
        if(indice!=NO_SE_ENCONTRO)
            asignarArrDeRegistros(arrFechaIni,arrFechaFin,arrDuracion,arrCitas,
                    arrMontoPagado,dd,mm,aaaa,arrCodMed,arrTarifaMed,cantMedicos,
                    hIni,mIni,sIni,hFin,mFin,sFin,indice,codMedico);
        if(fgetc(archAtencinesMedicas)=='\n') break;
    }    
}

void leerHora(FILE *archAtencinesMedicas, int *hora, int *minuto, int *segundo){    
    int cantDatos = fscanf(archAtencinesMedicas,"%d:%d:%d",hora,minuto,segundo);
    if(cantDatos==1){
        *minuto=0;
        *segundo=0;
    }else if(cantDatos==2)
        *segundo=0;
}

int buscarIndice(int codPaciente, int *arrCodPaciente, int cantPacientes){    
    for(int i=0; i<cantPacientes; i++)
        if(codPaciente==arrCodPaciente[i]) return i;
    return NO_SE_ENCONTRO;
}

void asignarArrDeRegistros(int *arrFechaIni, int *arrFechaFin, int *arrDuracion,
                           int *arrCitas, double *arrMontoPagado, int dd, int mm,
                           int aaaa, int *arrCodMed, double *arrTarifaMed,
                           int cantMedicos, int hIni, int mIni, int sIni,
                           int hFin, int mFin, int sFin, int i,
                           int codMedico){   
    ajustarFechas(dd,mm,aaaa,arrFechaIni,arrFechaFin,i);
    int duracion = ajustarDuracion(hIni,mIni,sIni,hFin,mFin,sFin,arrDuracion,i);
    ajustarMonto(arrMontoPagado,arrCodMed,arrTarifaMed,cantMedicos,codMedico,i,
            duracion);
    arrCitas[i]++;    
}

void ajustarFechas(int dd, int mm, int aaaa, int *arrFechaIni, 
                   int *arrFechaFin, int i){
    int fecha = juntarFecha(dd,mm,aaaa);    
    if(fecha<arrFechaIni[i])
        arrFechaIni[i]=fecha;
    if(fecha>arrFechaFin[i])
        arrFechaFin[i]=fecha;
}

int juntarFecha(int dd, int mm, int aaaa){
    return aaaa*10000 + mm*100 + dd;
}

int ajustarDuracion(int hIni, int mIni, int sIni, int hFin, int mFin, int sFin,
                     int *arrDuracion, int i){   
    int duracion = duracionSeg(hFin,mFin,sFin)-duracionSeg(hIni,mIni,sIni);    
    arrDuracion[i]+=duracion;
    return duracion;
}

int duracionSeg(int hora, int minuto, int segundo){
    return hora*60*60 + minuto*60 + segundo;    
}

void ajustarMonto(double *arrMontoPagado, int *arrCodMed, double *arrTarifaMed,
                  int cantMedicos, int codMedico, int i, int duracion){    
    int j, min;
    j=buscarIndice(codMedico,arrCodMed,cantMedicos);
    min = duracionMin(duracion);
    arrMontoPagado[i] += arrTarifaMed[j]*min;
}

int duracionMin(int duracion){    
    int min = duracion/60;
    if(duracion-min*60>0) return min+1;
    else return min;
}

void imprimirReporte(int *arrCodPaciente, int *arrCodPostal, int cantPacientes,
                     int *arrCodDistrito, int cantDistritos, int *arrFechaIni,
                     int *arrFechaFin, int *arrDuracion, int *arrCitas,
                     double *arrMontoPagado, int *arrCitasDistrito,
                     double *arrPagoDistrito){
    FILE *archDistritos, *archReporteDeAtencionesPorDistrito;
    archDistritos = fopen("Distritos.txt","r");
    if(archDistritos==NULL){
        printf("ERROR: No se pudo abrir el archivo Distritos.txt\n");
        exit(1);
    } 
    archReporteDeAtencionesPorDistrito = fopen("ReporteDeAtenciones"
            "PorDistrito.txt","w");
    if(archDistritos==NULL){
        printf("ERROR: No se pudo abrir el archivo "
                "ReporteDeAtencionesPorDistrito.txt\n");
        exit(1);
    }    
    procesarReporte(archDistritos,archReporteDeAtencionesPorDistrito,
            arrCodPaciente,arrCodPostal,cantPacientes,arrCodDistrito,
            cantDistritos,arrFechaIni,arrFechaFin,arrDuracion,arrCitas,
            arrMontoPagado,arrCitasDistrito,arrPagoDistrito);
    fclose(archDistritos);    
    fclose(archReporteDeAtencionesPorDistrito);    
}

void calcularTotalesPorDistrito(int *arrCitasDistrito, int *arrCodDistrito,
                                int cantDistritos, int *arrCitas,
                                int *arrCodPostal, int cantPacientes, 
                                double *arrPagoTotal, double *arrMontoPagado){   
    for(int i=0; i<cantPacientes; i++)
        for(int j=0; j<cantDistritos; j++)     
            if(arrCodPostal[i]==arrCodDistrito[j]){
                arrCitasDistrito[j]+=arrCitas[i];      
                arrPagoTotal[j]+=arrMontoPagado[i];          
                break;
            }
}

void ordenarDistritosPorTotales(int *arrCodDistrito, int cantDistritos,
                                int *arrCitasDistrito, double *arrPagoDistrito){    
    for(int i=0; i<cantDistritos-1; i++)
        for(int j=i+1; j<cantDistritos; j++)
            if(arrCitasDistrito[i]>arrCitasDistrito[j] ||
               arrCitasDistrito[i]==arrCitasDistrito[j] && 
                    arrPagoDistrito[i]<arrPagoDistrito[j]){                
                cambiarInt(arrCodDistrito,i,j);
                cambiarInt(arrCitasDistrito,i,j);
                cambiarDouble(arrPagoDistrito,i,j);                
            }
}

void cambiarInt(int *arrInt, int i, int j){
    int aux=arrInt[i];
    arrInt[i]=arrInt[j];
    arrInt[j]=aux;
}

void cambiarDouble(double *arrDouble, int i, int j){
    double aux=arrDouble[i];
    arrDouble[i]=arrDouble[j];
    arrDouble[j]=aux;
}

void procesarReporte(FILE *archDistritos, FILE *archReporteDeAtenciones,
                     int *arrCodPaciente, int *arrCodPostal, int cantPacientes,
                     int *arrCodDistrito, int cantDistritos, int *arrFechaIni,
                     int *arrFechaFin, int *arrDuracion, int *arrCitas,
                     double *arrMontoPagado, int *arrCitasDistrito,
                     double *arrPagoDistrito){    
    imprimirCabecera(archReporteDeAtenciones);    
    for(int i=0; i<cantDistritos; i++){
        if(arrCitasDistrito[i]!=0){
            imprimirLinea(archReporteDeAtenciones,'=',MAX_LINEA);
            imprimirDistrito(archReporteDeAtenciones,&arrCodDistrito[i],
                    archDistritos);
            imprimirRegistro(arrCodPaciente,arrCodPostal,cantPacientes,
                    arrCodDistrito[i],arrFechaIni,arrFechaFin,arrDuracion,
                    arrCitas,arrMontoPagado,archReporteDeAtenciones,
                    arrCitasDistrito[i],arrPagoDistrito[i]);
        }
    }
    imprimirDistritosConMayorYMenorPagoRealizado(archReporteDeAtenciones,
            arrCodDistrito,arrPagoDistrito,cantDistritos);
}

void imprimirCabecera(FILE *archReporteDeAtenciones){    
    fprintf(archReporteDeAtenciones,"%69s\n","EMPRESA PRESTADORA DE SALUD");
    fprintf(archReporteDeAtenciones,"%74s\n","ATENCIÓN DE PACIENTES POR DISTRITO");
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirDistrito(FILE *archReporteDeAtenciones, int *arrCodDistrito,
                      FILE *archDistritos){
    rewind(archDistritos);
    int codDistrito;
    fprintf(archReporteDeAtenciones,"%19s %05d - ","Distrito:",*arrCodDistrito);    
    while(1){
        fscanf(archDistritos,"%d",&codDistrito);
        if(feof(archDistritos)) break;
        if(codDistrito==*arrCodDistrito){
            imprimirNombreDelDistrito(archDistritos,archReporteDeAtenciones);  
            break;
        }else
            while(fgetc(archDistritos)!='\n');
    }   
}

void imprimirNombreDelDistrito(FILE *archDistritos, FILE *archReporteDeAtenciones){    
    char c;
    while((c=fgetc(archDistritos))==' ');
    fputc(c,archReporteDeAtenciones);    
    while(1){               
        c=fgetc(archDistritos);  
        if(c=='\n') break;
        else fputc(convertirMayuscula(c),archReporteDeAtenciones);
    }
    fputc('\n',archReporteDeAtenciones);
    imprimirLinea(archReporteDeAtenciones,'-',MAX_LINEA);
}

char convertirMayuscula(char c){
    if(c>='a'&&c<='z') return c-=32;
    else return c;
}

void imprimirRegistro(int *arrCodPaciente, int *arrCodPostal, int cantPacientes,
                      int arrCodDistrito, int *arrFechaIni, int *arrFechaFin,
                      int *arrDuracion, int *arrCitas, double *arrMontoPagado,
                      FILE *archReporte, int citasDistrito,
                      double pagoDistrito){   
    int ddIni, mmIni, aaaaIni, ddFin, mmFin, aaaaFin, h, m, s;
    double pagoTotal=0;
    imprimirCabeceraRegistro(archReporte);   
    for(int i=0; i<cantPacientes; i++){
        if(arrCodPostal[i]==arrCodDistrito){
            separarFecha(arrFechaIni[i],&ddIni,&mmIni,&aaaaIni);
            separarFecha(arrFechaFin[i],&ddFin,&mmFin,&aaaaFin);
            separarHora(arrDuracion[i],&h,&m,&s);
            fprintf(archReporte,"%c %08d",' ',arrCodPaciente[i]);                        
            fprintf(archReporte,"%7c %02d/%02d/%4d %6c %02d/%02d/%4d",' ',
                    ddIni,mmIni,aaaaIni,' ',ddFin,mmFin,aaaaFin);
            fprintf(archReporte,"%7c %02d:%02d:%02d %15d",' ',h,m,s,arrCitas[i]);
            fprintf(archReporte,"%21.2lf\n",arrMontoPagado[i]);
        }        
    }
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"CANTIDAD TOTAL DE CITAS: %d\n",citasDistrito);
    fprintf(archReporte,"PAGO TOTAL:    S/. %8.2lf\n",pagoDistrito);    
}

void imprimirCabeceraRegistro(FILE *archReporte){    
    fprintf(archReporte,"%10s %15s %15s %21s %19s %17s\n","PACIENTE","INICIO",
            "FIN","DURACION CITAS","CANTIDAD CITAS","MONTO PAGADO");
    imprimirLinea(archReporte,'-',MAX_LINEA);
}

void separarFecha(int fecha, int *dd, int *mm, int *aaaa){    
    *aaaa = fecha/10000;
    fecha -= (*aaaa)*10000;
    *mm = fecha/100;
    *dd = fecha-(*mm)*100;    
}

void separarHora(int duracion, int *h, int *m, int *s){
    *h = duracion/60/60;
    duracion -= (*h)*60*60;
    *m = duracion/60;
    *s = duracion-(*m)*60;
}

void imprimirDistritosConMayorYMenorPagoRealizado(FILE *archReporteDeAtenciones,
                                                  int *arrCodDistrito,
                                                  double *arrPagoDistrito, 
                                                  int cantDistritos){
    imprimirLinea(archReporteDeAtenciones,'=',MAX_LINEA);
    int iMayorPago = buscarIndiceMayorPago(arrPagoDistrito,cantDistritos);
    int iMenorPago = buscarIndiceMenorPago(arrPagoDistrito,cantDistritos);
    fprintf(archReporteDeAtenciones,"%s %05d %s %.2lf\n","DISTRITO CON MAYOR "
            "PAGO REALIZADO:",arrCodDistrito[iMayorPago],"- S/.",
            arrPagoDistrito[iMayorPago]);
    fprintf(archReporteDeAtenciones,"%s %05d %s %.2lf","DISTRITO CON MENOR "
            "PAGO REALIZADO:",arrCodDistrito[iMenorPago],"- S/.",
            arrPagoDistrito[iMenorPago]);
}

int buscarIndiceMayorPago(double *arrPagoDistrito, int cantDistritos){
    int indice, mayorPago=0;    
    for(int i=0; i<cantDistritos; i++)
        if(arrPagoDistrito[i]>mayorPago){
            mayorPago = arrPagoDistrito[i];
            indice = i;
        }       
    return indice;
}

int buscarIndiceMenorPago(double *arrPagoDistrito, int cantDistritos){
    int indice, menorPago=999999;    
    for(int i=0; i<cantDistritos; i++)
        if(arrPagoDistrito[i]<menorPago && arrPagoDistrito[i]>0.001){
            menorPago = arrPagoDistrito[i];
            indice = i;
        }       
    return indice;
}