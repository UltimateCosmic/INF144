/* 
 * Proyecto: LAB2_2021-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 19 de abril de 2022, 03:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 130
#define MAX_ESPACIO 40

void imprimirReporteDePagos(FILE *archMedicos, FILE *archPacientes, 
                            FILE *archAtencionesMedicas, 
                            FILE *archReporteDePagos){
    
    fprintf(archReporteDePagos,"%72s\n","EMPRESA PRESTADORA DE SALUD");
    fprintf(archReporteDePagos,"%75s\n","LISTADOS DE PAGOS DE LOS PACIENTES");    
    imprimirPacientes(archMedicos,archPacientes,archAtencionesMedicas,
            archReporteDePagos);
}

void imprimirPacientes(FILE *archMedicos, FILE *archPacientes, 
                       FILE *archAtencionesMedicas, FILE *archReporteDePagos){
    
    int codigoPaciente, cantLetras;    
    
    while(1){        
        fscanf(archPacientes,"%d",&codigoPaciente);
        if(feof(archPacientes)) break;
        imprimirLinea(archReporteDePagos,'=',MAX_LINEA);       
        cantLetras = imprimirNombrePaciente(archPacientes,archReporteDePagos);
        imprimirEspacios(archReporteDePagos,MAX_ESPACIO-cantLetras);        
        fprintf(archReporteDePagos,"Codigo: %08d\n",codigoPaciente);        
        imprimirDistrito(archPacientes,archReporteDePagos); 
        imprimirRelacionDeConsultas(archMedicos,archAtencionesMedicas,
                archReporteDePagos,codigoPaciente);
    }
}

int imprimirNombrePaciente(FILE *archPacientes, FILE *archReporte){
    
    int cantCaracteres=0, cantEspacios=0;
    fprintf(archReporte,"%14s %7c","Nombre:",' ');
    
    //Colocamos la primera letra
    while(fgetc(archPacientes)!='[');
    char letra = fgetc(archPacientes);
    fputc(letra,archReporte);
    
    while(1){        
        letra = fgetc(archPacientes);        
        if(letra==']')
            break;
        else if(letra==' '){            
            fputc(letra,archReporte);
            letra = fgetc(archPacientes);
            fputc(letra,archReporte);  //Letra mayuscula
            cantCaracteres++;
            cantEspacios++;
        }else{
            letra = convertirMinuscula(letra);
            fputc(letra,archReporte);
            cantCaracteres++;
        }
    }
    if(cantEspacios==2) cantCaracteres--;    
    return cantCaracteres;
}

char convertirMinuscula(char letra){
    if(letra>='A'&&letra<='Z') return letra+=32;
    else return letra;    
}

void imprimirEspacios(FILE *arch, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(' ',arch);
}

void imprimirDistrito(FILE *archPacientes, FILE *archReporte){
    
    fprintf(archReporte,"%16s %5c","Distrito:",' ');    
    char letra;
    while((letra=fgetc(archPacientes))==' ');
    fputc(letra,archReporte);
    
    while(1){        
        letra = fgetc(archPacientes);        
        if(letra=='\n')
            break;
        else if(letra==' ')
            fputc('_',archReporte);
        else{
            letra = convertirMayuscula(letra);
            fputc(letra,archReporte);
        }
    }
    fputc('\n',archReporte);
}

void imprimirRelacionDeConsultas(FILE *archMedicos, FILE *archAtencionesMedicas,
                                 FILE *archReporte, int codigoPaciente){
    
    rewind(archAtencionesMedicas);    
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"%74s\n","RELACION DE CONSULTAS REALIZADAS");
    fprintf(archReporte,"%13s %16s %13s %16s %13s %12s %19s\n","FECHA",
            "INGRESO","SALIDA","DURACION","MEDICO","TARIFA","MONTO PAGADO");
    imprimirLinea(archReporte,'-',MAX_LINEA);
    
    int codMedico, dd, mm, aaaa;
    double pagoTotalRealizado=0, montoPagado=0;
    
    while(1){        
        fscanf(archAtencionesMedicas,"%d",&codMedico);
        if(feof(archAtencionesMedicas)) break;
        fscanf(archAtencionesMedicas,"%d/%d/%d",&dd,&mm,&aaaa);
        buscarConsultas(archAtencionesMedicas,archMedicos,archReporte,dd,mm,
                aaaa,codMedico,codigoPaciente,&montoPagado);
        pagoTotalRealizado+=montoPagado;
    }
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"PAGO TOTAL REALIZADO: %3c S/. %.2lf\n",
            ' ',pagoTotalRealizado);
}

void buscarConsultas(FILE *archAtencionesMedicas, FILE *archMedicos,
                     FILE *archReporte, int dd, int mm, int aaaa, int codMedico,
                     int codPaciente, double *montoPagado){
    
    (*montoPagado)=0;
    
    int dniPaciente, horaIni, minIni, segundoIni, horaFin, minFin, 
            segundoFin, datos, duracionMin=0, duracionSegundos=0;
    double tarifa, monto;
    
    while(1){
        
        fscanf(archAtencionesMedicas,"%d",&dniPaciente);        
        datos = fscanf(archAtencionesMedicas,"%d:%d:%d",
                &horaIni,&minIni,&segundoIni);
        if(datos==2){
            segundoIni=0;
        }else if(datos==1){
            minIni=0;            
            segundoIni=0;
        }   
        datos = fscanf(archAtencionesMedicas,"%d:%d:%d",
                &horaFin,&minFin,&segundoFin);     
        if(datos==2){
            segundoFin=0;
        }else if(datos==1){
            minFin=0;            
            segundoFin=0;
        }       
        if(dniPaciente==codPaciente){
            calcularDuracion(horaIni,minIni,segundoIni,horaFin,minFin,
                    segundoFin,&duracionMin,&duracionSegundos);     
            buscarTarifa(archMedicos,codMedico,&tarifa);
            monto = calcularMontoPagado(tarifa,duracionMin,duracionSegundos);
            fprintf(archReporte,"%5c %02d/%02d/%4d",' ',dd,mm,aaaa);
            fprintf(archReporte,"%5c %02d:%02d:%02d",' ',horaIni,minIni,segundoIni);
            fprintf(archReporte,"%6c %02d:%02d:%02d",' ',horaFin,minFin,segundoFin);
            fprintf(archReporte,"%9c %02d:%02d",' ',duracionMin,duracionSegundos);
            fprintf(archReporte,"%8c %05d %13.2lf %16.2lf\n",' ',
                    codMedico,tarifa,monto);       
            (*montoPagado)+=monto;
        }  
        if(fgetc(archAtencionesMedicas)=='\n') break;
    }    
}

void calcularDuracion(int horaIni, int minIni, int segundoIni, int horaFin, 
                      int minFin, int segundoFin, int *duracionMin, 
                      int *duracionSegundos){
    
    int duracionIniSegundos, duracionFinSegundos, duracion;
    duracionIniSegundos = duracionEnSegundos(horaIni,minIni,segundoIni);
    duracionFinSegundos = duracionEnSegundos(horaFin,minFin,segundoFin);
    duracion = duracionFinSegundos-duracionIniSegundos;   
    
    (*duracionMin) = duracion/60;
    duracion -= (*duracionMin)*60;
    (*duracionSegundos) =duracion;    
}

int duracionEnSegundos(int hora, int min, int segundo){
    return hora*60*60+min*60+segundo;
}

void buscarTarifa(FILE *archMedicos, int codMedico, double *tarifa){
    
    rewind(archMedicos);
    int codigoMedico;
    
    while(1){
        fscanf(archMedicos,"%d",&codigoMedico);
        if(feof(archMedicos)) break;
        if(codMedico==codigoMedico){
            while(fgetc(archMedicos)==' ');
            while(fgetc(archMedicos)!=' ');
            fscanf(archMedicos,"%lf",tarifa);            
            break;
        }else
            while(fgetc(archMedicos)!='\n');
    }
}

double calcularMontoPagado(double tarifa, int durMin, int durSegundos){
    if(durSegundos>0)
        durMin++;
    return tarifa*durMin;
}

char convertirMayuscula(char letra){
    if(letra>='a'&&letra<='z') return letra-=32;
    else return letra;    
}

void imprimirLinea(FILE *arch, char caracter, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(caracter,arch);
    fputc('\n',arch);    
}

void cerrarArchivos(FILE *archMedicos, FILE *archPacientes, 
                    FILE *archAtencionesMedicas, FILE *archReporteDePagos){    
    fclose(archMedicos);
    fclose(archPacientes);
    fclose(archAtencionesMedicas);
    fclose(archReporteDePagos);
}