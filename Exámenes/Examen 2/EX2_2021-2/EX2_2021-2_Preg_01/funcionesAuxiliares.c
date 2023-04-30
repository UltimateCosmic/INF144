/* 
 * Proyecto: EX2_2021-2_Preg_01
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de julio de 2022, 02:35 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#include "StructProducto.h"
#include "StructPedido.h"
#define NO_SE_ENCONTRO -1
#define MAX_LINEA 100

void crearArchStockDeProductosBin(const char *nomArchBin, const char *nomArchCsv){    
    FILE *archBin, *archCsv;
    archBin = abrirArchivo(nomArchBin,"wb");
    archCsv = abrirArchivo(nomArchCsv,"r");    
    int numPal;
    char cadena[100], *pal[4];    
    struct Producto producto;
    while(1){
        leerCadena(cadena,100,archCsv);
        if(feof(archCsv)) break;
        sacaPalabras(cadena,pal,&numPal,',');                
        strcpy(producto.codigo,pal[0]);
        strcpy(producto.descripcion,pal[1]);
        producto.stock=atoi(pal[2]);
        producto.precio=atof(pal[3]);
        for(int i=0; i<numPal; i++) free(pal[i]);
        fwrite(&producto,sizeof(struct Producto),1,archBin);
    }    
    fclose(archBin);
    fclose(archCsv);    
}

void imprimirRepStockDeProductos(const char *nomArchBin, const char *nomArchTxt){
    FILE *archBin, *archTxt;
    archBin = abrirArchivo(nomArchBin,"rb");
    archTxt = abrirArchivo(nomArchTxt,"w");
    struct Producto prod;
    while(1){        
        fread(&prod,sizeof(struct Producto),1,archBin);
        if(feof(archBin)) break;
        fprintf(archTxt,"%-10s %-50s %5d %10.2lf\n",prod.codigo,prod.descripcion,
                prod.stock,prod.precio);
    }   
    fclose(archBin);
    fclose(archTxt);
}

void crearArchPedidosPorInternetBin(const char *nomArchBin, const char *nomArchTxt){
    FILE *archBin, *archTxt;
    archBin = abrirArchivo(nomArchBin,"wb");
    archTxt = abrirArchivo(nomArchTxt,"r");    
    int dd, mm, aa, h, m, s, numPed, dni;
    struct Pedido pedido;
    while(1){
        fscanf(archTxt,"%d",&dd);
        if(feof(archTxt)) break;
        fscanf(archTxt,"/%d/%d %d:%d:%d",&mm,&aa,&h,&m,&s);
        fscanf(archTxt,"%d %d",&numPed,&dni);
        pedido.fecha=aa*10000+mm*100+dd;
        pedido.hora=h*3600+m*60+s;
        pedido.numero=numPed;
        pedido.cliente=dni;
        pedido.cantProdPed=0;
        fwrite(&pedido,sizeof(struct Pedido),1,archBin);
    }    
    fclose(archBin);
    fclose(archTxt);
}

void imprimirRepPedidosPorInternetBin(const char *nomArchBin, const char *nomArchTxt){
    FILE *archBin, *archTxt;
    archBin = abrirArchivo(nomArchBin,"rb");
    archTxt = abrirArchivo(nomArchTxt,"w");
    struct Pedido ped;
    while(1){
        fread(&ped,sizeof(struct Pedido),1,archBin);
        if(feof(archBin)) break;        
        fprintf(archTxt,"%-12d %06d %10d %10d %4d\n",ped.fecha,ped.hora,
                ped.numero,ped.cliente,ped.cantProdPed);
    }    
    fclose(archBin);
    fclose(archTxt);
}

void completarArchPedidosPorInternetBin(const char *nomArchPedidosBin, 
                                        const char *nomArchDetPedidosTxt,
                                        const char *nomArchStockDeProductosBin){    
    FILE *archPed, *archDetPed, *archProd;
    archPed = abrirArchivo(nomArchPedidosBin,"rb+");
    archDetPed = abrirArchivo(nomArchDetPedidosTxt,"r");
    archProd = abrirArchivo(nomArchStockDeProductosBin,"rb+");    
    int numPed, cant;
    char codProd[7];    
    while(1){
        fscanf(archDetPed,"%d",&numPed);
        if(feof(archDetPed)) break;
        fscanf(archDetPed,"%s %d",codProd,&cant);
        asignarDetalleDePedido(numPed,codProd,cant,archPed,archProd);
    }
    fclose(archPed);
    fclose(archDetPed);
    fclose(archProd);    
}

void asignarDetalleDePedido(int numPed, char *codProd, int cant, FILE *archPed, 
                            FILE *archProd){    
    int posPed, posProd, cp;
    struct Producto prod;
    struct Pedido ped;
    posPed = buscarPosPedido(numPed,archPed);
    posProd = buscarPosProducto(codProd,archProd);    
    if(posPed!=NO_SE_ENCONTRO && posProd!=NO_SE_ENCONTRO){        
        
        fseek(archProd,posProd*sizeof(struct Producto),SEEK_SET);
        fread(&prod,sizeof(struct Producto),1,archProd);
        if(hayStock(prod.stock)){        
            fseek(archPed,posPed*sizeof(struct Pedido),SEEK_SET);
            fread(&ped,sizeof(struct Pedido),1,archPed);            
            cp = ped.cantProdPed;            
            strcpy(ped.productosPedidos[cp].codigo,prod.codigo);
            strcpy(ped.productosPedidos[cp].descripcion,prod.descripcion);             
            if(prod.stock>=cant){
                ped.productosPedidos[cp].cantidad=cant;
                prod.stock-=cant;
            }else{
                ped.productosPedidos[cp].cantidad=prod.stock;
                prod.stock=0;
            }            
            ped.productosPedidos[cp].precioUnitario=prod.precio;
            ped.productosPedidos[cp].subtotal=prod.precio*
                    ped.productosPedidos[cp].cantidad;     
            ped.cantProdPed++;
            fseek(archPed,posPed*sizeof(struct Pedido),SEEK_SET);
            fwrite(&ped,sizeof(struct Pedido),1,archPed);
            fseek(archProd,posProd*sizeof(struct Producto),SEEK_SET);
            fwrite(&prod,sizeof(struct Producto),1,archProd);
            fflush(archPed);
            fflush(archProd);
        }
    }    
}

int buscarPosPedido(int numPed, FILE *archPed){    
    struct Pedido ped;    
    int tamReg, numReg;
    tamReg = sizeof(struct Pedido);
    datosDelArchivo(archPed,tamReg,&numReg);    
    for(int i=0; i<numReg; i++){
        fread(&ped,tamReg,1,archPed);        
        if(numPed==ped.numero) return i;        
    }
    return NO_SE_ENCONTRO;
}

void datosDelArchivo(FILE *archBin, int tamReg, int *numReg){    
    fseek(archBin,0,SEEK_END);
    int tamArch = ftell(archBin);
    fseek(archBin,0,SEEK_SET);
    *numReg = tamArch/tamReg;
}

int buscarPosProducto(char *codProd, FILE *archProd){
    struct Producto prod;    
    int tamReg, numReg;
    tamReg = sizeof(struct Producto);
    datosDelArchivo(archProd,tamReg,&numReg);    
    for(int i=0; i<numReg; i++){
        fread(&prod,tamReg,1,archProd);        
        if(strcmp(codProd,prod.codigo)==0) return i;        
    }
    return NO_SE_ENCONTRO;    
}

int hayStock(int stock){    
    if(stock>0) return 1;
    else return 0;
}

void imprimirReporteDePedidos(const char *nomArchBin, const char *nomArchTxt){    
    FILE *archBin, *archTxt; 
    archBin = abrirArchivo(nomArchBin,"rb");
    archTxt = abrirArchivo(nomArchTxt,"w");    
    imprimirCabecera(archTxt);    
    struct Pedido pedido;
    while(1){
        imprimirLinea(archTxt,'=',MAX_LINEA);  
        fread(&pedido,sizeof(struct Pedido),1,archBin);
        if(feof(archBin)) break;
        imprimirPedido(pedido,archTxt);        
    }
    fclose(archBin);    
    fclose(archTxt);    
}

void imprimirCabecera(FILE *arch){    
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"%65s\n","TIENDA VIRTUAL LA MAGNIFICA");
    fprintf(arch,"%62s\n","ATENCIÓN DE PEDIDOS");  
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirPedido(struct Pedido ped, FILE *arch){
    int dd, mm, aa, h, m, s;
    separarFecha(ped.fecha,&dd,&mm,&aa);
    separarHora(ped.hora,&h,&m,&s);
    fprintf(arch,"%s %-18d %-11s %02d/%02d/%-19d %-13s %02d:%02d:%02d\n",
            "Pedido No.",ped.numero,"Fecha:",dd,mm,aa,"Hora:",h,m,s);
    fprintf(arch,"%s\n%-6s %08d\n","Cliente:","DNI",ped.cliente);
    imprimirProductos(ped.productosPedidos,ped.cantProdPed,arch);
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

void imprimirProductos(struct ProductoSolicitado *prod, int cantProdPed, FILE *arch){
    imprimirCabeceraDeProductos(arch);        
    for(int i=0; i<cantProdPed; i++)
        fprintf(arch,"%-12s %-40s %2d %20.2lf %15.2lf\n",prod[i].codigo,
                prod[i].descripcion,prod[i].cantidad,prod[i].precioUnitario,
                prod[i].subtotal);    
}

void imprimirCabeceraDeProductos(FILE *arch){
    fprintf(arch,"%s\n","Productos:");
    fprintf(arch,"%s %17s %36s %20s %11s\n","Codigo","Descripcion","Cantidad",
            "Precio Unitario","Subtotal");    
}