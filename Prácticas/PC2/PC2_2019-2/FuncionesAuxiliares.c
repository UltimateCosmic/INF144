/* 
 * Proyecto: PC2_2019-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 13 de abril de 2022, 04:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 94
#define FECHA_INICIO 20160101
#define FECHA_FIN 20170131

void procesarArchivos(FILE *archRecetas, FILE *archMedicinas, FILE *archMedicos,
                      FILE *archNiveles, FILE *archReporte){
        
    fprintf(archReporte,"%61s\n","Reporte de recetas atendidas");
    fprintf(archReporte,"%75s\n","Fechas a considerar: entre el 01/01/2012 y el"
            " 31/01/2012");
    
    double totalFacturacion=0, medicoMasFacturacionMonto=0;
    int medicoMasFacturacionColegiatura, medicoMasFacturacionEspecialidad;
    char medicoMasFacturacionNivel;
    
    imprimirRecetasAtendidas(archRecetas,archMedicinas,archMedicos,archNiveles,
            archReporte,&totalFacturacion,&medicoMasFacturacionMonto,
            &medicoMasFacturacionColegiatura,&medicoMasFacturacionEspecialidad,
            &medicoMasFacturacionNivel);    
    imprimirDetallesFinales(archReporte,totalFacturacion,
            medicoMasFacturacionMonto,medicoMasFacturacionColegiatura,
            medicoMasFacturacionEspecialidad,medicoMasFacturacionNivel);  
}

void imprimirRecetasAtendidas(FILE *archRecetas, FILE *archMedicinas, 
                              FILE *archMedicos, FILE *archNiveles, 
                              FILE *archReporte, double *totalFacturacion,
                              double *medicoMasFacturacionMonto,
                              int *medicoMasFacturacionColegiatura, 
                              int *medicoMasFacturacionEspecialidad,
                              char *medicoMasFacturacionNivel){
    
    int colegiatura,especialidad,numPacientesRecomendados=0;
    double totalFacturadoPorMedico,descuentoPacientes;
    char nivelDeFacturacion;
    
    while(1){
               
        imprimirLinea(archReporte,'=',MAX_LINEA);        
        fscanf(archMedicos,"%d",&colegiatura);
        if(feof(archMedicos)) break;
        fscanf(archMedicos,"%d",&especialidad);        
        fprintf(archReporte,"%s %5d %18s %3d\n",
                "Número de colegiatura del médico:",colegiatura,
                "Especialidad:",especialidad);        
        imprimirLinea(archReporte,'-',MAX_LINEA);        
        
        descuentoPacientes=numPacientesRecomendados=totalFacturadoPorMedico=0;
        imprimirRecetas(archRecetas,archMedicinas,archReporte,archNiveles,
                colegiatura,&numPacientesRecomendados,&totalFacturadoPorMedico,
                &nivelDeFacturacion,&descuentoPacientes,
                medicoMasFacturacionColegiatura,
                medicoMasFacturacionEspecialidad,medicoMasFacturacionMonto,
                medicoMasFacturacionNivel,especialidad);
        imprimirDatosFinalesMedico(archReporte,numPacientesRecomendados,
                totalFacturadoPorMedico,nivelDeFacturacion,descuentoPacientes);
        
        (*totalFacturacion)+=totalFacturadoPorMedico;
    }
}

void imprimirRecetas(FILE *archRecetas, FILE *archMedicinas, FILE *archReporte,
                     FILE *archNiveles, int colegiatura, 
                     int *numPacientesRecomendados, 
                     double *totalFacturadoPorMedico, char *nivelDeFacturacion,
                     double *descuentoPacientes, 
                     int *medicoMasFacturacionColegiatura,
                     int *medicoMasFacturacionEspecialidad,
                     double *medicoMasFacturacionMonto,
                     char *medicoMasFacturacionNivel, int especialidad){
    
    int dd, mm, aaaa, dni;    
    double totalFacturado;
    
    fprintf(archReporte,"%s %18s %30s\n","FECHA","DNI","Total Facturado (S/.)");
    
    int mayorFecha, menorFecha=FECHA_INICIO, seEncontroNuevaReceta;   
    
    while(1){
        
        rewind(archRecetas);
        seEncontroNuevaReceta=totalFacturado=0;
        mayorFecha = FECHA_FIN;
        
        seEncontroNuevaReceta = determinarFechaCronologicamente(archRecetas,
                archMedicinas, colegiatura,&mayorFecha,&menorFecha,&dd,&mm,
                &aaaa,&dni,&totalFacturado);
        
        if(seEncontroNuevaReceta==0) break;      
        fprintf(archReporte,"%02d/%02d/%04d %7c %08d %18.2lf\n",dd,mm,aaaa,' ',
                dni,totalFacturado);      
        
        (*totalFacturadoPorMedico)+=totalFacturado;
        (*numPacientesRecomendados)++;
    }
    
    determinarRankingDelMedico(archNiveles,totalFacturadoPorMedico,
            nivelDeFacturacion,descuentoPacientes);
    
    determinarMedicoMayorFacturacion(medicoMasFacturacionColegiatura,
            medicoMasFacturacionEspecialidad,medicoMasFacturacionMonto,
            medicoMasFacturacionNivel,totalFacturadoPorMedico,colegiatura,
            especialidad,nivelDeFacturacion);
}

int determinarFechaCronologicamente(FILE *archRecetas, FILE *archMedicinas, 
                                    int colegiatura, int *mayorFecha, 
                                    int *menorFecha, int *ddImp, int *mmImp, 
                                    int *aaaaImp, int *dniImp, 
                                    double *totalFacturado){
    
    int seEncontroNuevaReceta = 0;
    int dd, mm, aaaa, dni, numColeg, fecha;
    
    while(1){

        fscanf(archRecetas,"%d",&dd);
        if(feof(archRecetas)) break;
        fscanf(archRecetas,"/%d/%d %d %d",&mm,&aaaa,&dni,&numColeg);

        fecha = convertirFecha(dd,mm,aaaa);

        if(numColeg==colegiatura && fecha<(*mayorFecha) && fecha>(*menorFecha)){            
            *totalFacturado += calcularFacturacion(archRecetas,archMedicinas);            
            *mayorFecha = fecha;
            seEncontroNuevaReceta = 1;
            *ddImp = dd;
            *mmImp = mm;
            *aaaaImp = aaaa;
            *dniImp = dni;                
        }else
            while(fgetc(archRecetas)!='\n');        
    }    
    *menorFecha = *mayorFecha;   
    return seEncontroNuevaReceta;    
}

int convertirFecha(int dd, int mm, int aaaa){
    return aaaa*10000 + mm*100 + dd;
}

double calcularFacturacion(FILE *archRecetas, FILE *archMedicinas){
    
    int codMedicamento, cantidad;
    double facturacion=0, precio;
    
    while(1){        
        fscanf(archRecetas,"%d %d",&codMedicamento,&cantidad);
        precio = buscarPrecio(codMedicamento,archMedicinas);
        facturacion += precio*cantidad;        
        if(fgetc(archRecetas)=='\n') break;
    }
    return facturacion;    
}

double buscarPrecio(int codMedicamento, FILE *archMedicinas){
    
    rewind(archMedicinas);    
    int codigo;
    double precioUnitario=0;
    
    while(1){
        
        fscanf(archMedicinas,"%d",&codigo);
        if(feof(archMedicinas)) break;
        
        if(codigo==codMedicamento){    
            fscanf(archMedicinas,"%lf",&precioUnitario);
            break;
        }else
            while(fgetc(archMedicinas)!='\n');
    }
    return precioUnitario;
}

void determinarMedicoMayorFacturacion(int *medicoMasFacturacionColegiatura,
                                      int *medicoMasFacturacionEspecialidad,
                                      double *medicoMasFacturacionMonto,
                                      char *medicoMasFacturacionNivel,
                                      double *totalFacturadoPorMedico,
                                      int colegiatura, int especialidad,
                                      char *nivelDeFacturacion){
    
    if((*totalFacturadoPorMedico)>(*medicoMasFacturacionMonto)){        
        (*medicoMasFacturacionColegiatura) = colegiatura;
        (*medicoMasFacturacionEspecialidad) = especialidad;
        (*medicoMasFacturacionMonto) = (*totalFacturadoPorMedico);
        (*medicoMasFacturacionNivel) = (*nivelDeFacturacion);
    }   
}

void determinarRankingDelMedico(FILE *archNiveles, double *totalFacturado, 
                                char *nivelDeFacturacion, 
                                double *descuentoPacientes){
    
    rewind(archNiveles);
    int factInicial, factFinal;
    double descuentoFuturo; 
    
    while(1){
        
        fscanf(archNiveles,"%d",&factInicial);
        if(feof(archNiveles)) break;
        fscanf(archNiveles,"%d",&factFinal);
        
        if((*totalFacturado)>factInicial && (*totalFacturado)<factFinal){
            
            while(((*nivelDeFacturacion)=fgetc(archNiveles))==' ');
            fscanf(archNiveles,"%lf",&descuentoFuturo);            
            (*descuentoPacientes) = descuentoFuturo*100;
                    
        }else
            while(fgetc(archNiveles)!='\n');        
    }
    
}

void imprimirDatosFinalesMedico(FILE *archReporte, int numPacientesRecomendados, 
                                double totalFacturadoPorMedico, 
                                char nivelDeFacturacion, 
                                double descuentoPacientes){
    
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"Número de pacientes recomendados: %2d\n",
            numPacientesRecomendados);
    fprintf(archReporte,"Total facturado por el Médico: S/. %4.2lf\n",
            totalFacturadoPorMedico);
    fprintf(archReporte,"Nivel de Facturación: %c - Descuento para sus "
            "pacientes: %.0lf%%\n", nivelDeFacturacion, descuentoPacientes);    
}

void imprimirDetallesFinales(FILE *archReporte, double totalFacturacion,
                             double medicoMasFacturacionMonto, 
                             int medicoMasFacturacionColegiatura,
                             int medicoMasFacturacionEspecialidad,
                             char medicoMasFacturacionNivel){    
    fprintf(archReporte,"Total de facturación en el Periodo: S/. %8.2lf\n",
            totalFacturacion);
    fprintf(archReporte,"1er médico con más facturación: ");
    fprintf(archReporte,"%s %5d %15s %2d\n","Colegiatura:",
            medicoMasFacturacionColegiatura,"Especialidad:",
            medicoMasFacturacionEspecialidad);
    fprintf(archReporte,"%52s %6.2lf %10s %c\n","Monto facturado: S/.",
            medicoMasFacturacionMonto," - Nivel de Facturación:",
            medicoMasFacturacionNivel);    
}

void imprimirLinea(FILE *archReporte, char caracter, int cantVeces){    
    for(int i=0; i<cantVeces; i++) fputc(caracter,archReporte);
    fputc('\n',archReporte);
}

void cerrarArchivos(FILE *archRecetas, FILE *archMedicinas, FILE *archMedicos,
                    FILE *archNiveles, FILE *archReporteDeRecetasAtendidas){    
    fclose(archMedicinas);
    fclose(archMedicos);
    fclose(archNiveles);
    fclose(archRecetas);
    fclose(archReporteDeRecetasAtendidas);
}