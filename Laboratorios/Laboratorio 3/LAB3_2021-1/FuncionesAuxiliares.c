/* 
 * Proyecto: LAB3_2021-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 9 de mayo de 2022, 06:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 120
#define NO_SE_ENCONTRO -1
#define MAX_PROD 50

void procesarProductos(int *arrCodProd, double *arrPrecioProd, int *cantProd){
    FILE *archProductos;
    archProductos=fopen("productos.txt","r");
    if(archProductos==NULL){
        printf("ERROR: No se pudo abrir el archivo productos.txt\n");
        exit(1);
    }
    leerArrProductos(archProductos,arrCodProd,arrPrecioProd,cantProd);
    fclose(archProductos);
}

void leerArrProductos(FILE *archProductos, int *arrCodProd, 
                      double *arrPrecioProd, int *cantProd){    
    while(1){
        fscanf(archProductos,"%d",&arrCodProd[*cantProd]);
        if(feof(archProductos)) break;
        saltarNombre(archProductos);
        fscanf(archProductos,"%lf",&arrPrecioProd[*cantProd]);
        (*cantProd)++;
    }
}

void saltarNombre(FILE *arch){
    while(fgetc(arch)==' ');
    while(fgetc(arch)!=' ');    
}

void procesarTiendas(int *arrCodTienda, int *arrCodPostal, int *cantTiendas){
    FILE *archTiendas;
    archTiendas=fopen("tiendas.txt","r");
    if(archTiendas==NULL){
        printf("ERROR: No se pudo abrir el archivo tiendas.txt\n");
        exit(1);
    }
    leerArrTiendas(archTiendas,arrCodTienda,arrCodPostal,cantTiendas);
    fclose(archTiendas);    
}

void leerArrTiendas(FILE *archTiendas, int *arrCodTienda, int *arrCodPostal, 
                    int *cantTienda){    
    while(1){        
        fscanf(archTiendas,"%d",&arrCodTienda[*cantTienda]);
        if(feof(archTiendas)) break;
        saltarNombre(archTiendas);
        fscanf(archTiendas,"%d",&arrCodPostal[*cantTienda]);
        (*cantTienda)++;        
    }
}

void ordenarTiendas(int *arrCodTienda, int *arrCodPostal, int cantTiendas){
    for(int i=0; i<cantTiendas-1; i++)
        for(int j=i+1; j<cantTiendas; j++)
            if(arrCodPostal[i]>arrCodPostal[j]){
                cambiarInt(arrCodTienda,i,j);
                cambiarInt(arrCodPostal,i,j);
            }    
}

void cambiarInt(int *arr, int i, int k){
    int aux=arr[i];
    arr[i]=arr[k];
    arr[k]=aux;    
}

void procesarReporte(int *arrCodProd, double *arrPrecioProd, int cantProd,
                     int *arrCodTienda, int *arrCodPostal, int cantTiendas){
    FILE *archCompras, *archReporteDeEntregas;
    archCompras=fopen("compras.txt","r");
    if(archCompras==NULL){
        printf("ERROR: No se pudo abrir el archivo compras.txt\n");
        exit(1);
    }
    archReporteDeEntregas=fopen("Reporte.txt","w");
    if(archReporteDeEntregas==NULL){
        printf("ERROR: No se pudo abrir el archivo Reporte.txt\n");
        exit(1);
    }
    imprimirReporte(archCompras,archReporteDeEntregas,arrCodProd,arrPrecioProd,
            cantProd,arrCodTienda,arrCodPostal,cantTiendas);    
    fclose(archCompras);
    fclose(archReporteDeEntregas);
}

void imprimirReporte(FILE *archCompras, FILE *archReporteDeEntregas, 
                     int *arrCodProd, double *arrPrecioProd, int cantProd,
                     int *arrCodTienda, int *arrCodPostal, int cantTiendas){    
    int arrProdCant[MAX_PROD]={};
    double arrProdVenta[MAX_PROD]={};
    fprintf(archReporteDeEntregas,"%67s\n","ENTREGA DE PRODUCTOS");
    for(int i=0; i<cantTiendas; i++)
        if(comprobarVentas(arrCodTienda[i],archCompras,arrCodProd,cantProd)){            
            imprimirTienda(archReporteDeEntregas,arrCodTienda[i],arrCodPostal[i]);
            imprimirEntregaDeProductos(archReporteDeEntregas,archCompras,
                    arrCodTienda[i],arrCodProd,arrPrecioProd,cantProd,
                    arrProdCant,arrProdVenta);
        }    
    imprimirResumenTotal(archReporteDeEntregas,arrProdCant,arrProdVenta,
            arrCodProd,cantProd);
}   

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

int comprobarVentas(int codTienda, FILE *archCompras, int *arrCodProd,
                    int cantProd){
    rewind(archCompras);    
    int codigo;
    char c;
    while(1){
        c=fgetc(archCompras);
        if(feof(archCompras)) break;
        if(c=='T'){
            fscanf(archCompras,"-%d",&codigo);           
            if(codTienda==codigo && comprobarProducto(archCompras,arrCodProd,
                    cantProd))
                return 1;
        }
    }
    return 0;
}

int comprobarProducto(FILE *archCompras, int *arrCodProd, int cantProd){
    int cod;
    while(1){
        fscanf(archCompras,"%d/%*d",&cod);
        for(int i=0; i<cantProd; i++)
            if(arrCodProd[i]==cod) return 1;
        if(fgetc(archCompras)=='\n') break;         
    }
    return 0;
}

void imprimirTienda(FILE *archReporteDeEntregas, int codTienda, int codPostal){    
    imprimirLinea(archReporteDeEntregas,'=',MAX_LINEA);
    fprintf(archReporteDeEntregas,"%22s %02d %29s %05d\n","Destino: Tienda",
            codTienda,"Codigo Postal:",codPostal);
    imprimirLinea(archReporteDeEntregas,'-',MAX_LINEA);
}

void imprimirEntregaDeProductos(FILE *archReporteDeEntregas, FILE *archCompras,
                                int codTienda, int *arrCodProd, 
                                double *arrPrecioProd, int cantProd, 
                                int *arrProdCant, double *arrProdVenta){    
    rewind(archCompras);
    imprimirCabeceraEntregas(archReporteDeEntregas);
    int dni,centinela=0, cantProdAEntregar=0, cantidad;
    char lugarEntrega, tienda;    
    double montoProdAEntregar=0.0;
    while(1){
        fscanf(archCompras,"%*d-%*d %d",&dni);
        if(feof(archCompras)) break;
        fscanf(archCompras," %c",&lugarEntrega);
        if(lugarEntrega=='T'){
            fscanf(archCompras,"-%d",&tienda);          
            if(tienda==codTienda){
                imprimirEntregaIndividual(archReporteDeEntregas,archCompras,
                        arrCodProd,arrPrecioProd,cantProd,dni,&centinela,
                        &cantidad,&montoProdAEntregar,arrProdCant,
                        arrProdVenta);
                cantProdAEntregar+=cantidad;
            }
            else
                while(fgetc(archCompras)!='\n');                
        }else if(lugarEntrega=='D')
            while(fgetc(archCompras)!='\n');
    }    
    if(centinela)
        imprimirResumenPorTienda(archReporteDeEntregas,cantProdAEntregar,
                montoProdAEntregar);
}

void imprimirCabeceraEntregas(FILE *archReporteDeEntregas){
    fprintf(archReporteDeEntregas,"%13s %16s %15s %23s %13s %14s\n","FECHA",
            "PRODUCTO","CANTIDAD","PRECIO UNITARIO","SUBTOTAL","CLIENTE");
    imprimirLinea(archReporteDeEntregas,'-',MAX_LINEA);
}

void imprimirEntregaIndividual(FILE *archReporteDeEntregas, FILE *archCompras,
                               int *arrCodProd, double *arrPrecioProd, 
                               int cantProd, int dni, int *centinela,
                               int *cantProdAEntregar, 
                               double *montoProdAEntregar, int *arrProdCant, 
                               double *arrProdVenta){
    (*cantProdAEntregar)=0;
    int dd, mm, aaaa, codProd, cantidad, i;
    double precio, subtotal;
    fscanf(archCompras,"%d/%d/%d",&dd,&mm,&aaaa);   
    while(1){        
        fscanf(archCompras,"%d/%d",&codProd,&cantidad);
        precio=buscarPrecio(codProd,arrCodProd,arrPrecioProd,cantProd,&i);
        if(precio>0){
            subtotal=precio*cantidad;
            fprintf(archReporteDeEntregas,"%5c %02d/%02d/%4d",' ',dd,mm,aaaa);
            fprintf(archReporteDeEntregas,"%6c %05d %13d",' ',codProd,cantidad);
            fprintf(archReporteDeEntregas,"%23.1lf %17.1lf",precio,subtotal);
            fprintf(archReporteDeEntregas,"%8c %08d\n",' ',dni); 
            (*cantProdAEntregar)+=cantidad;
            (*montoProdAEntregar)+=subtotal;
            arrProdVenta[i]+=subtotal;
            arrProdCant[i]+=cantidad;
            (*centinela)=1;
        }
        if(fgetc(archCompras)=='\n') break;     
    }
}

double buscarPrecio(int codProd, int *arrCodProd, double *arrPrecioProd,
                    int cantProd, int *indice){
    for(int i=0; i<cantProd; i++)
        if(codProd==arrCodProd[i]){
            *indice = i;
            return arrPrecioProd[i];
        }
    return NO_SE_ENCONTRO;
}

void imprimirResumenPorTienda(FILE *archReporteDeEntregas , int cantProdAEntregar,
                              double montoProdAEntregar){    
    imprimirLinea(archReporteDeEntregas,'-',MAX_LINEA);
    fprintf(archReporteDeEntregas,"\nRESUMEN POR TIENDA\n");
    fprintf(archReporteDeEntregas,"CANTIDAD DE PRODUCTOS A ENTREGAR: %6d\n",
            cantProdAEntregar);
    fprintf(archReporteDeEntregas,"MONTO DE PRODUCTOS A ENTREGAR: S/. %9.2lf\n",
            montoProdAEntregar);    
}

void imprimirResumenTotal(FILE *archReporteDeEntregas, int *arrProdCant,    
                          double *arrProdVenta, int *arrCodProd, int cantProd){
    int iMasEntregas, iMenosEntregas, masEntregas=0, menosEntregas=999;
    double totalVentas=0.0;
    for(int i=0; i<cantProd; i++){
        if(arrProdCant[i]>masEntregas){
            masEntregas=arrProdCant[i];
            iMasEntregas=i;
        }
        if(arrProdCant[i]<menosEntregas){
            menosEntregas=arrProdCant[i];
            iMenosEntregas=i;
        }        
        totalVentas+=arrProdVenta[i];
    }
    imprimirProductosDeResumen(archReporteDeEntregas,arrProdCant,arrProdVenta,
            arrCodProd,iMasEntregas,iMenosEntregas,totalVentas);
}

void imprimirProductosDeResumen(FILE *archReporteDeEntregas, int *arrProdCant,    
                                double *arrProdVenta, int *arrCodProd, 
                                int iMasEntregas, int iMenosEntregas,
                                double totalVentas){
    fprintf(archReporteDeEntregas,"\n\n");
    imprimirLinea(archReporteDeEntregas,'=',MAX_LINEA);
    fprintf(archReporteDeEntregas,"RESUMEN TOTAL\n");
    fprintf(archReporteDeEntregas,"%s %2c %05d %20s %3d %20s %8.2lf\n",
            "Producto con más entregas:",' ',arrCodProd[iMasEntregas],
            "Cantidad:",arrProdCant[iMasEntregas],"Total Venta: S/.",
            arrProdVenta[iMasEntregas]);
    fprintf(archReporteDeEntregas,"%s  %05d %20s %3d %20s %8.2lf\n",
            "Producto con menos entregas:",arrCodProd[iMenosEntregas],
            "Cantidad:",arrProdCant[iMenosEntregas],"Total Venta: S/.",
            arrProdVenta[iMenosEntregas]);
    fprintf(archReporteDeEntregas,"%s %9.2lf\n","Total Ventas entregadas en "
            "tiendas:  S/.",totalVentas);
    imprimirLinea(archReporteDeEntregas,'=',MAX_LINEA);
}