/* 
 * Proyecto: EX2_2021-2_Preg_02
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 04:57 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#include "StructStockProd.h"
#include "StructPedidos.h"
#define NO_SE_ENCONTRO -1
#define MAX_LINEA 100

void leerStockDeProductos(struct StockProd *productos, int *numProd){    
    FILE *archProd = abrirArchivo("StockDeProductos.csv","r");
    int numPal;
    char linea[100], *pal[4];
    while(1){
        leerCadena(linea,100,archProd);
        if(feof(archProd)) break;
        sacaPalabras(linea,pal,&numPal,',');        
        productos[*numProd].codigo = pal[0];
        productos[*numProd].descripcion = pal[1];
        productos[*numProd].stock = atoi(pal[2]);
        productos[*numProd].precio = atof(pal[3]);
        free(pal[2]);
        free(pal[3]);
        (*numProd)++;
    }   
    fclose(archProd);
}

void imprimirRepStockDeProductos(struct StockProd *prod, int numProd){
    FILE *archRepProd = abrirArchivo("RepStockDeProductos.txt","w");
    for(int i=0; i<numProd; i++)        
        fprintf(archRepProd,"%-10s %-45s %2d %10.2lf\n",prod[i].codigo,
                prod[i].descripcion,prod[i].stock,prod[i].precio);
    fclose(archRepProd);
}

void leerPedidos(struct stPedidos *pedidos, int *numPed){    
    FILE *archPed = abrirArchivo("Pedidos.txt","r");
    int dd, mm, aa, h, m, s;
    while(1){
        fscanf(archPed,"%d",&dd);
        if(feof(archPed)) break;
        fscanf(archPed,"/%d/%d %d:%d:%d",&mm,&aa,&h,&m,&s);
        fscanf(archPed,"%d %d",&pedidos[*numPed].numero,&pedidos[*numPed].cliente);
        pedidos[*numPed].fecha=aa*10000+mm*100+dd;
        pedidos[*numPed].hora=h*3600+m*60+s;        
        pedidos[*numPed].productosEntregados=
                (struct Entregado *)malloc(sizeof(struct Entregado)*20);
        pedidos[*numPed].productosNoEntregados=
                (struct NoEntregado *)malloc(sizeof(struct NoEntregado)*20);
        pedidos[*numPed].cantProdEnt=0;
        pedidos[*numPed].cantProdNoEnt=0;        
        (*numPed)++;
    }   
    fclose(archPed);    
}

void imprimirRepPedidos(struct stPedidos *ped, int numPed){
    FILE *archRepPed = abrirArchivo("RepPedidos.txt","w");
    for(int i=0; i<numPed; i++){        
        fprintf(archRepPed,"%-12d %06d %12d %12d\n",ped[i].fecha,ped[i].hora,
                ped[i].numero,ped[i].cliente);
    }
    fclose(archRepPed);
}

void completarPedidos(struct stPedidos *pedidos, int numPed, 
                      struct StockProd *productos, int numProd){    
    FILE *archDetPed = abrirArchivo("DetalleDeLosPedidos.txt","r");    
    int codPed, cantPed;
    char codProd[7];    
    while(1){
        fscanf(archDetPed,"%d",&codPed);
        if(feof(archDetPed)) break;
        fscanf(archDetPed,"%s %d",codProd,&cantPed);
        asignarProducto(codPed,codProd,cantPed,pedidos,numPed,productos,numProd);
    }
    fclose(archDetPed);
}    

void asignarProducto(int codPed, char *codProd, int cantPed, 
                     struct stPedidos *pedidos, int numPed, 
                     struct StockProd *productos, int numProd){    
    int posProd, posPed, cp;
    posProd = buscarPosProd(codProd,productos,numProd);
    posPed = buscarPosPed(codPed,pedidos,numPed);    
    if(posProd!=NO_SE_ENCONTRO && posPed!=NO_SE_ENCONTRO){        
        if(hayStock(productos[posProd].stock)){            
            cp=pedidos[posPed].cantProdEnt;             
            if(productos[posProd].stock>=cantPed){                
                pedidos[posPed].productosEntregados[cp].cantEntregada=cantPed;                
                pedidos[posPed].productosEntregados[cp].precioUnitario=
                        productos[posProd].precio;
                pedidos[posPed].productosEntregados[cp].subtotal=
                        cantPed*productos[posProd].precio;                
                productos[posProd].stock-=cantPed;                 
            }else{
                pedidos[posPed].productosEntregados[cp].cantEntregada=
                        cantPed-productos[posProd].stock;
                pedidos[posPed].productosNoEntregados[cp].cantNoEntregada=cantPed;
                pedidos[posPed].productosNoEntregados[cp].codigo=
                        productos[posProd].codigo;
                pedidos[posPed].productosNoEntregados[cp].descripcion=
                        productos[posProd].descripcion;                
                pedidos[posPed].productosEntregados[cp].precioUnitario=
                        productos[posProd].precio;
                pedidos[posPed].productosEntregados[cp].subtotal=
                        productos[posProd].stock*productos[posProd].precio;               
                pedidos[posPed].cantProdNoEnt++;               
                productos[posProd].stock=0;
            }
            pedidos[posPed].productosEntregados[cp].codigo=
                    productos[posProd].codigo;
            pedidos[posPed].productosEntregados[cp].descripcion=
                    productos[posProd].descripcion;
            pedidos[posPed].cantProdEnt++;            
        }else{
            cp=pedidos[posPed].cantProdNoEnt;
            pedidos[posPed].productosNoEntregados[cp].cantNoEntregada=cantPed;
            pedidos[posPed].productosNoEntregados[cp].codigo=
                    productos[posProd].codigo;
            pedidos[posPed].productosNoEntregados[cp].descripcion=
                    productos[posProd].descripcion;
            pedidos[posPed].cantProdNoEnt++;
        }
    }
}

int buscarPosProd(char *codProd, struct StockProd *productos, int numProd){    
    for(int i=0; i<numProd; i++) 
        if(strcmp(codProd,productos[i].codigo)==0) return i;
    return NO_SE_ENCONTRO;    
}

int buscarPosPed(int codPed, struct stPedidos *pedidos, int numPed){    
    for(int i=0; i<numPed; i++) 
        if(codPed==pedidos[i].numero) return i;
    return NO_SE_ENCONTRO;
}

int hayStock(int stock){
    if(stock>0) return 1;
    else return 0;    
}

void imprimirReporteDePedidos(struct stPedidos *pedidos, int numPed){    
    FILE *archReporteDePedidos = abrirArchivo("ReporteDePedidos.txt","w");
    imprimirCabeceraPrincipal(archReporteDePedidos);
    for(int i=0; i<numPed; i++){
        imprimirLinea(archReporteDePedidos,'=',MAX_LINEA);
        imprimirDetallesDePedidos(&pedidos[i],archReporteDePedidos);
        imprimirProductosEntregados(&pedidos[i],archReporteDePedidos);
        if(pedidos[i].cantProdNoEnt>0)
            imprimirProductosNoEntregados(&pedidos[i],archReporteDePedidos);        
    }
    fclose(archReporteDePedidos);    
}

void imprimirCabeceraPrincipal(FILE *arch){
    imprimirLinea(arch,'=',MAX_LINEA);    
    fprintf(arch,"%65s\n","TIENDA VIRTUAL LA MAGNIFICA");    
    fprintf(arch,"%62s\n","ATENCIÓN DE PEDIDOS");    
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirDetallesDePedidos(struct stPedidos *ped, FILE *arch){
    int dd, mm, aa, h, m, s;
    separarFecha(ped->fecha,&dd,&mm,&aa);
    separarHora(ped->hora,&h,&m,&s);
    fprintf(arch,"%s %-18d %-11s %02d/%02d/%-19d %-13s %02d:%02d:%02d\n",
            "Pedido No.",ped->numero,"Fecha:",dd,mm,aa,"Hora:",h,m,s);
    fprintf(arch,"%s\n%-6s %08d\n","Cliente:","DNI",ped->cliente);    
}

void imprimirCabeceraDeDetalles(FILE *arch){
    fprintf(arch,"%s %17s %36s %20s %11s\n","Codigo","Descripcion","Cantidad",
            "Precio Unitario","Subtotal");
}

void separarFecha(int fecha, int *dd, int *mm, int *aa){    
    *aa = fecha/10000;
    fecha -= (*aa)*10000;
    *mm = fecha/100;
    *dd = fecha-(*mm)*100;    
}

void separarHora(int hora, int *h, int *m, int *s){    
    *h = hora/3600;
    hora -= (*h)*3600;
    *m = hora/60;
    *s = hora-(*m)*60;
}

void imprimirProductosEntregados(struct stPedidos *pedidos, FILE *arch){
    fprintf(arch,"%s\n","Productos Entregados:");
    imprimirCabeceraDeDetalles(arch);        
    for(int i=0; i<pedidos->cantProdEnt; i++)
        fprintf(arch,"%-12s %-40s %2d %20.2lf %15.2lf\n",
                pedidos->productosEntregados[i].codigo,
                pedidos->productosEntregados[i].descripcion,
                pedidos->productosEntregados[i].cantEntregada,
                pedidos->productosEntregados[i].precioUnitario,
                pedidos->productosEntregados[i].subtotal);
}

void imprimirProductosNoEntregados(struct stPedidos *pedidos, FILE *arch){    
    fprintf(arch,"%s\n","Productos no entregados:");
    imprimirCabeceraDeDetalles(arch);        
    for(int i=0; i<pedidos->cantProdNoEnt; i++)
        fprintf(arch,"%-12s %-40s %2d\n",
                pedidos->productosNoEntregados[i].codigo,
                pedidos->productosNoEntregados[i].descripcion,
                pedidos->productosNoEntregados[i].cantNoEntregada);
}