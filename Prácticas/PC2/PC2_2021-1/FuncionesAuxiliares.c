/* 
 * Proyecto: PC2_2021-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de abril de 2022, 04:18 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 114
#define MAX_PRODUCTOS 50
#define NO_SE_ENCONTRO 0
#define FIN 1

void leerProductos(int *codProducto, int *cantProductos, double *precioProducto){
    FILE *archProductos;    
    archProductos = fopen("productos.txt","r");
    if(archProductos==NULL){
        printf("ERROR: No se pudo abrir el archivo productos.txt\n");
        exit(1);        
    }   
    //Leemos el código y precio de los productos y dejamos de lado el nombre
    while(1){
        fscanf(archProductos,"%d",&codProducto[*cantProductos]);
        if(feof(archProductos)) break;
        while(fgetc(archProductos)==' ');   //Saltamos el nombre
        while(fgetc(archProductos)!=' ');
        fscanf(archProductos,"%lf",&precioProducto[*cantProductos]);        
        (*cantProductos)++;
    }        
    fclose(archProductos);
}

void imprimirReporte(int *codProducto, int cantProductos, double *precioProducto){    
    FILE *archReporte, *archTiendas;    
    archReporte = fopen("Reporte.txt","w");
    if(archReporte==NULL){
        printf("ERROR: No se pudo abrir el archivo Reporte.txt\n");
        exit(1);        
    }  
    archTiendas = fopen("tiendas.txt","r");
    if(archTiendas==NULL){
        printf("ERROR: No se pudo abrir el archivo tiendas.txt\n");
        exit(1);        
    }    
    fprintf(archReporte,"%67s\n","ENTREGA DE PRODUCTOS");
    imprimirEntregaDeProductos(archReporte,archTiendas,codProducto,
            cantProductos,precioProducto);
    fclose(archReporte);    
    fclose(archTiendas);
}

void imprimirEntregaDeProductos(FILE *archReporte, FILE *archTiendas,
                                int *codProducto, int cantProductos,
                                double *precioProducto){    
    FILE *archCompras;
    archCompras = fopen("compras.txt","r");
    if(archCompras==NULL){
        printf("ERROR: No se pudo abrir el archivo compras.txt\n");
        exit(1);        
    }
    int codTienda, verificarFin;    
    //Variables para el Resultado Total.    
    int cantVendidaProd[MAX_PRODUCTOS]={0};
    double totalVentaProd[MAX_PRODUCTOS]={0.0};    
    while(1){
        fscanf(archTiendas,"%d",&codTienda);        
        if(feof(archTiendas)) break;
        verificarFin = imprimirDestino(archReporte,archTiendas,codTienda,
                archCompras);
        if(verificarFin==0)
            imprimirEntregasPorFecha(archReporte,archCompras,codTienda,codProducto,
                cantProductos,precioProducto,cantVendidaProd,totalVentaProd);
    }
    imprimirResumenTotal(archReporte,cantVendidaProd,totalVentaProd,cantProductos,
            codProducto);
    fclose(archCompras);
}

int imprimirDestino(FILE *archReporte, FILE *archTiendas, int codTienda,
                     FILE *archCompras){
    if(comprobarNoHayVentas(codTienda,archCompras)) return 1;
    int codPostal;
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"%22s %d - ","Destino: Tienda",codTienda);
    imprimirNombreDeLaTienda(archReporte,archTiendas);
    fscanf(archTiendas,"%d",&codPostal);
    fprintf(archReporte," - Codigo Postal: %05d\n",codPostal);
    imprimirLinea(archReporte,'-',MAX_LINEA);
    return 0;
}

int comprobarNoHayVentas(int codTienda, FILE *archCompras){    
    /* Algoritmo que recorre todo el archivo compras.txt para verificar si
     * existieron compras en una tienda*/
    rewind(archCompras);
    int c, codigo;    
    while(1){
        fscanf(archCompras,"%*d-%*d %*d");
        if(feof(archCompras)) break;
        while(1){
            c=fgetc(archCompras);
            if(c=='T'){
                fscanf(archCompras,"-%d",&codigo);
                if(codTienda==codigo) return 0;
            }else if(c=='\n')
                break;
        }
    }
    return 1;    
}

void imprimirNombreDeLaTienda(FILE *archReporte, FILE *archTiendas){    
    char c=fgetc(archTiendas);
    while(1){
        c = fgetc(archTiendas);
        if(c=='-') fputc(' ',archReporte);
        else if(c==' ') break; 
        else fputc(c,archReporte);
    }   
}

void imprimirEntregasPorFecha(FILE *archReporte, FILE *archCompras, 
                              int codTienda, int *codProducto, int cantProductos,
                              double *precioProducto, int *cantVendidaProd,
                              double *totalVentaProd){    
    rewind(archCompras);
    fprintf(archReporte,"%13s %16s %15s %23s %13s %14s\n","FECHA","PRODUCTO",
            "CANTIDAD","PRECIO UNITARIO","SUBTOTAL","CLIENTE");
    imprimirLinea(archReporte,'-',MAX_LINEA);    
    
    int dniCliente, cantDeProductos=0;
    double montoProductosAEntregar=0;
    
    while(1){
        fscanf(archCompras,"%*d-%*d");
        if(feof(archCompras)) break;
        fscanf(archCompras,"%d",&dniCliente);
        imprimirEntregaCliente(archReporte,archCompras,codTienda,codProducto,
                cantProductos,precioProducto,dniCliente,&cantDeProductos,
                &montoProductosAEntregar,cantVendidaProd,totalVentaProd);
    }
    imprimirResumenPorTienda(archReporte,cantDeProductos,montoProductosAEntregar);
}

void imprimirEntregaCliente(FILE *archReporte, FILE *archCompras, int codTienda,
                            int *codProducto, int cantProductos, 
                            double *precioProducto, int dniCliente,
                            int *cantDeProductos, 
                            double *montoProductosAEntregar, int *cantVendidaProd,
                            double *totalVentaProd){ 
    int tienda, dd, mm, aaaa, verificarFin;    
    while(1){        
        leerTienda(archCompras,&tienda);        
        fscanf(archCompras,"%d/%d/%d",&dd,&mm,&aaaa);
        verificarFin = imprimirListaDeEntregas(archReporte,archCompras,codTienda,
                codProducto,cantProductos,precioProducto,dniCliente,
                cantDeProductos,montoProductosAEntregar,dd,mm,aaaa,tienda,
                cantVendidaProd,totalVentaProd);
        if(verificarFin==FIN)
            break;
    }
}

void leerTienda(FILE *archCompras, int *tienda){
    while(fgetc(archCompras)==' ');
    if(fgetc(archCompras)=='-'){
        fscanf(archCompras,"%d",tienda);
        return;        
    }else
        *tienda = NO_SE_ENCONTRO;
}

int imprimirListaDeEntregas(FILE *archReporte, FILE *archCompras, int codTienda,
                            int *codProducto, int cantProductos,
                            double *precioProducto, int dniCliente,
                            int *cantDeProductos, double *montoProductosAEntregar,
                            int dd, int mm, int aaaa, int tienda, 
                            int *cantVendidaProd, double *totalVentaProd){  
    
    int codigoProducto, cantidadProducto, c;
    double subtotal;
    while(1){        
        fscanf(archCompras,"%d/%d",&codigoProducto,&cantidadProducto);        
        while((c=fgetc(archCompras))==' ');
        if(c=='T'||c=='D'){
            ungetc(c,archCompras);
            break;
        }
        else if(c=='\n') return FIN;
        if(tienda==codTienda){
            imprimirProducto(archReporte,dd,mm,aaaa,codigoProducto,
                    cantidadProducto,precioProducto,&subtotal,dniCliente,
                    codProducto,cantProductos,cantVendidaProd,totalVentaProd);
            *montoProductosAEntregar += subtotal;
            *cantDeProductos += cantidadProducto;
        }
        ungetc(c,archCompras);
    }    
    return 0;
}

void imprimirProducto(FILE *archReporte, int dd, int mm, int aaaa,
                      int codigoProducto, int cantidadProducto, 
                      double *precioProducto, double *subtotal, int dniCliente, 
                      int *codProducto, int cantProductos, int *cantVendidaProd,
                      double *totalVentaProd){   
    int i;
    double precio = buscarPrecioProducto(codigoProducto,codProducto,
            precioProducto,cantProductos, &i);    
    *subtotal = precio*cantidadProducto;    
    cantVendidaProd[i] += cantidadProducto;
    totalVentaProd[i] += *subtotal;    
    fprintf(archReporte,"%5c %02d/%02d/%4d %6c",' ',dd,mm,aaaa,' ');
    fprintf(archReporte,"%05d %13d %21.1lf",codigoProducto,cantidadProducto,precio);
    fprintf(archReporte,"%18.1lf %8c %08d\n",*subtotal,' ',dniCliente);    
}

double buscarPrecioProducto(int codigoProducto, int *codProducto,
                            double *precioProducto, int cantProductos,
                            int *indice){   
    for(int i=0; i<cantProductos; i++)        
        if(codigoProducto==codProducto[i]){
            *indice = i; 
            return precioProducto[i];
        }
}

void imprimirResumenPorTienda(FILE *archReporte, int cantDeProductos,
                              double montoProductosAEntregar){
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"\nRESUMEN POR TIENDA\n");
    fprintf(archReporte,"CANTIDAD DE PRODUCTOS A ENTREGAR: %5d\n",
            cantDeProductos);
    fprintf(archReporte,"MONTO DE PRODUCTOS A ENTREGAR: S/. %8.2lf\n",
            montoProductosAEntregar);
}

void imprimirResumenTotal(FILE *archReporte, int *cantVendidaProd,
                          double *totalVentaProd, int cantProductos,
                          int *codProducto){
    
    int iMasEntregas, iMenosEntregas;
    buscarIndicesVentas(totalVentaProd,cantProductos,
            &iMasEntregas,&iMenosEntregas);
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"RESUMEN TOTAL\n");
    fprintf(archReporte,"%-30s %05d %20s %4d %24s %8.2lf\n",
            "Producto con mas entregas:",codProducto[iMasEntregas],
            "Cantidad:",cantVendidaProd[iMasEntregas],
            "Total Venta: S/.",totalVentaProd[iMasEntregas]);    
    fprintf(archReporte,"%-30s %05d %20s %4d %24s %8.2lf\n",
            "Producto con menos entregas:",codProducto[iMenosEntregas],
            "Cantidad:",cantVendidaProd[iMenosEntregas],
            "Total Venta:  S/.",totalVentaProd[iMenosEntregas]);
    double totalVentas = calcularTotalVentas(totalVentaProd,cantProductos);
    fprintf(archReporte,"Total Ventas entregadas en tiendas: S/. %9.2lf\n",
            totalVentas);
    imprimirLinea(archReporte,'=',MAX_LINEA);
}

void buscarIndicesVentas(double *totalVentaProd, int cantProductos, 
                           int *iMasEntregas, int *iMenosEntregas){
    double mayorVenta=0, menorVenta=999999;
    for(int i=0; i<cantProductos; i++){   
        if(totalVentaProd[i]>=mayorVenta){
            mayorVenta = totalVentaProd[i];
            *iMasEntregas = i;
        }
        if(totalVentaProd[i]<=menorVenta){
            menorVenta = totalVentaProd[i];
            *iMenosEntregas = i;
        }        
    }
}

double calcularTotalVentas(double *totalVentaProd, int cantProductos){    
    double totalVentas=0;    
    for(int i=0; i<cantProductos; i++)
        totalVentas += totalVentaProd[i];
    return totalVentas;
}

void imprimirLinea(FILE *archReporte, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,archReporte);  
    fputc('\n',archReporte);
}