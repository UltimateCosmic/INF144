/* 
 * Proyecto: LAB4_2021-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de mayo de 2022, 12:10 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 100
#define NO_SE_ENCONTRO -1
#define PRECISION 0.0001

FILE *abrirArchivo(char *nombreDeArchivo, char *modoDeApertura){
    FILE *arch = fopen(nombreDeArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDeArchivo);
        exit(1);
    }    
}

void leerProductosAlmacenados(int *arrCodProd, double *arrCantProd, int *i){
    FILE *archProductosAlmacenados = abrirArchivo("productosAlmacenados.txt","r");
    while(1){
        fscanf(archProductosAlmacenados,"%d",&arrCodProd[*i]);
        if(feof(archProductosAlmacenados)) break;
        fscanf(archProductosAlmacenados,"%lf",&arrCantProd[*i]);
        (*i)++;
    }
    fclose(archProductosAlmacenados);
}

void ordenarProductos(int *arrCodProd, double *arrCantProd, int cantProd){    
    for(int i=0; i<cantProd-1; i++)
        for(int j=i+1; j<cantProd; j++)
            if(arrCodProd[j]<arrCodProd[i]){
                cambiarInt(arrCodProd,i,j);
                cambiarDouble(arrCantProd,i,j);                
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

void leerPlatosAPreparar(int *arrPlato, int *arrCantPlato, int *i){
    FILE *archPlatosAPreparar = abrirArchivo("platosAPreparar.txt","r");
    while(1){
        fscanf(archPlatosAPreparar,"%d",&arrPlato[*i]);
        if(feof(archPlatosAPreparar)) break;
        fscanf(archPlatosAPreparar,"%d",&arrCantPlato[*i]);
        (*i)++;        
    }
    fclose(archPlatosAPreparar);
}

void ordenarPlatos(int *arrPlato, int *arrCantPlato, int cantPlatos){
    for(int i=0; i<cantPlatos-1; i++)
        for(int j=i+1; j<cantPlatos; j++)
            if(arrPlato[j]<arrPlato[i]){
                cambiarInt(arrPlato,i,j);
                cambiarInt(arrCantPlato,i,j);                
            }    
}

void leerListaDePrecios(int *arrCodProd, double *arrPrecioProd, int cantProd){
    FILE *archListaDePrecios = abrirArchivo("ListaDePrecios.txt","r");
    while(fgetc(archListaDePrecios)!='\n');
    int producto, pos;
    while(1){
        fscanf(archListaDePrecios,"%d",&producto);
        if(feof(archListaDePrecios)) break;
        pos = buscarPosicion(producto,arrCodProd,cantProd);
        if(pos!=NO_SE_ENCONTRO){
            while(fgetc(archListaDePrecios)!=']');
            fscanf(archListaDePrecios,"%lf",&arrPrecioProd[pos]);            
        }else
            while(fgetc(archListaDePrecios)!='\n');
    }    
    fclose(archListaDePrecios);
}

int buscarPosicion(int codigo, int *arrCod, int cant){
    int limSup=cant, limInf=0, pm;    
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm = (limSup+limInf)/2;
        if(codigo==arrCod[pm]) return pm;
        else if(codigo>arrCod[pm]) limInf=pm+1;
        else limSup=pm-1;        
    }
}

void procesarPerdidas(int *arrCodProd, double *arrCantProd, int cantProd,
                      int *arrPlato, int *arrCantPlato, int cantPlatos, 
                      double *arrPrecioPlato, double *arrPrecioProd){
    FILE *archPlatos = abrirArchivo("Platos.txt","r");
    int plato, pos;
    while(1){
        fscanf(archPlatos,"%d",&plato);
        if(feof(archPlatos)) break;
        pos = buscarPosicion(plato,arrPlato,cantPlatos);
        if(pos!=NO_SE_ENCONTRO){
            while(fgetc(archPlatos)!=')');
            leerIngredientes(arrCodProd,arrCantProd,cantProd,&arrCantPlato[pos],
                    archPlatos,&arrPrecioPlato[pos],arrPrecioProd);
        }else
            while(fgetc(archPlatos)!='\n');
    }     
    fclose(archPlatos);
}

void leerIngredientes(int *arrCodProd, double *arrCantProd, int cantProd,
                      int *arrCantPlato, FILE *archPlatos, double *precioPlato,
                      double *arrPrecioProd){    
    int codProd, pos, maxPlatosFalt=0, resto;
    double cantReq;
    while(1){
        fscanf(archPlatos,"%d %lf",&codProd,&cantReq);
        pos = buscarPosicion(codProd,arrCodProd,cantProd);
        if(pos!=NO_SE_ENCONTRO){
            //      Stock      Cantidad total de ingred. 
            if(arrCantProd[pos]<cantReq*(*arrCantPlato)){                
                resto = cantReq*(*arrCantPlato)-arrCantProd[pos];
                if(resto>=maxPlatosFalt) maxPlatosFalt=resto;              
            };            
            arrCantProd[pos]-=cantReq*(*arrCantPlato);
            (*precioPlato)+=arrPrecioProd[pos]*cantReq;
        }
        if(fgetc(archPlatos)=='\n') break;
    }    
    *arrCantPlato = maxPlatosFalt;
}

void calcularSubtotalProd(double *arrSubtotalProd, double *arrCantProd,
                          double *arrPrecioProd, int cantProd){    
    for(int i=0; i<cantProd; i++)
        arrSubtotalProd[i]=arrCantProd[i]*arrPrecioProd[i]*(-1);
}

void calcularSubtotalPlatos(double *arrSubtotalPlato, int *arrCantPlato,
                            double *arrPrecioPlato, int cantPlato){    
    for(int i=0; i<cantPlato; i++)
        arrSubtotalPlato[i]=arrCantPlato[i]*arrPrecioPlato[i];
}

void imprimirReporteDePerdidas(int *arrCodProd, double *arrCantProd, 
                               double *arrPrecioProd, int cantProd, int *arrPlato,
                               int *arrCantPlato, double *arrPrecioPlato,
                               int cantPlatos, double *arrSubtotalProd,
                               double *arrSubtotalPlatos){
    FILE *archReporteDePerdidas = abrirArchivo("ReporteDePerdidas.txt","w");
    imprimirProductosDescompuestos(arrCodProd,arrCantProd,arrPrecioProd,cantProd,
            archReporteDePerdidas,arrSubtotalProd);
    imprimirPlatosQueNoSePodranPreparar(arrPlato,arrCantPlato,arrPrecioPlato,
            cantPlatos,archReporteDePerdidas,arrSubtotalPlatos);    
    fclose(archReporteDePerdidas);
}

void imprimirProductosDescompuestos(int *arrCodProd, double *arrCantProd,
                                    double *arrPrecioProd, int cantProd, 
                                    FILE *archReporte, double *arrSubtotalProd){    
    imprimirCabeceraProductos(archReporte);
    ordenarProductosPorSubtotal(arrCodProd,arrCantProd,arrPrecioProd,
            arrSubtotalProd,cantProd);
    double costoTotal=0.0;
    for(int i=0; i<cantProd; i++){
        if(arrCantProd[i]<PRECISION && arrPrecioProd[i]>PRECISION){
            fprintf(archReporte,"%3d) %05d %9.2lf %17.2lf %23.2lf\n",i+1,
                    arrCodProd[i],arrCantProd[i]*(-1),arrPrecioProd[i],
                    arrSubtotalProd[i]);
            costoTotal+=arrSubtotalProd[i];
        }
    }
    imprimirCostoTotalProductos(archReporte,costoTotal);
}

void imprimirCabeceraProductos(FILE *archReporte){
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"PRODUCTOS DESCOMPUESTOS\n");
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"%s %12s %25s %18s\n","Producto","Cantidad",
            "Precio Unitario (S/.)","Sub-total (S/.)");    
}

void ordenarProductosPorSubtotal(int *arrCodProd, double *arrCantProd,
            double *arrPrecioProd, double *arrSubtotalProd, int cantProd){    
    for(int i=0; i<cantProd-1; i++)
        for(int j=i+1; j<cantProd; j++)
            if(arrSubtotalProd[j]>arrSubtotalProd[i]){
                cambiarInt(arrCodProd,i,j);
                cambiarDouble(arrCantProd,i,j);
                cambiarDouble(arrPrecioProd,i,j);
                cambiarDouble(arrSubtotalProd,i,j);
            }
}

void imprimirCostoTotalProductos(FILE *archReporte, double costoTotal){
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"Costo total de productos descompuestos: S/. %.2lf\n",
            costoTotal);
    imprimirLinea(archReporte,'=',MAX_LINEA);
}

void imprimirPlatosQueNoSePodranPreparar(int *arrPlato, int *arrCantPlato,
            double *arrPrecioPlato, int cantPlatos, FILE *archReporte,
            double *arrSubtotalPlatos){
    imprimirCabeceraPlatos(archReporte);
    ordenarPlatosPorSubtotal(arrPlato,arrCantPlato,arrPrecioPlato,cantPlatos,
            arrSubtotalPlatos);
    double costoTotal=0.0;
    for(int i=0; i<cantPlatos; i++){            
        fprintf(archReporte,"%2d) %06d %5d %19.2lf %22.2lf\n",i+1,
                arrPlato[i],arrCantPlato[i],arrPrecioPlato[i],
                arrSubtotalPlatos[i]);
        costoTotal+=arrSubtotalPlatos[i];
    }
    imprimirCostoTotalPlatos(archReporte,costoTotal);
}

void imprimirCabeceraPlatos(FILE *archReporte){
    fputc('\n',archReporte);
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"PLATOS QUE NO SE PODRÁN PREPARAR\n");
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"%s %12s %28s %17s\n","Plato","Cantidad",
            "Precio Ingrediente (S/.)","Sub-total (S/.)");    
}

void ordenarPlatosPorSubtotal(int *arrPlato, int *arrCantPlato, 
                              double *arrPrecioPlato, int cantPlatos,
                              double *arrSubtotalProd){
    for(int i=0; i<cantPlatos; i++)
        for(int j=i+1; j<cantPlatos; j++)
            if(arrCantPlato[j]*(-1)>arrCantPlato[i]*(-1) ||
              (arrCantPlato[j]==arrCantPlato[i] && 
               arrSubtotalProd[j]>arrSubtotalProd[i])){
                cambiarInt(arrPlato,i,j);
                cambiarInt(arrCantPlato,i,j);
                cambiarDouble(arrPrecioPlato,i,j);
                cambiarDouble(arrSubtotalProd,i,j);                
            }    
}

void imprimirCostoTotalPlatos(FILE *archReporte, double costoTotal){    
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"Suma de precios de los ingredientes de los platos que"
            "no se podrán preparar: S/. %.2lf\n",costoTotal);
    imprimirLinea(archReporte,'=',MAX_LINEA);    
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}













