/* 
 * Proyecto: LAB4_2021-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de mayo de 2022, 07:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 95
#define NO_SE_ENCONTRO -1

FILE *abrirArchivo(char *nombreDelArchivo, char *modoDeApertura){
    FILE *arch = fopen(nombreDelArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDelArchivo);
        exit(1);
    }
    return arch;
}

void leerPedidos(int *arrPedido, int *arrFecha, int *arrHora, int *arrDni, int *i){    
    FILE *archPedidos = abrirArchivo("Pedidos.txt","r");
    int dd, mm, aaaa, h, m, s;
    while(1){
        fscanf(archPedidos,"%d",&arrPedido[*i]);
        if(feof(archPedidos)) break;
        fscanf(archPedidos,"%d/%d/%d %d:%d:%d",&dd,&mm,&aaaa,&h,&m,&s);
        fscanf(archPedidos,"%d",&arrDni[*i]);
        arrFecha[*i]=aaaa*10000+mm*100+dd;
        arrHora[*i]=h*60*60+m*60+s;
        (*i)++;        
    }    
    fclose(archPedidos);
}

void ordenarPedidos(int *arrPedido, int *arrFecha, int *arrHora, int *arrDni, 
                    int cantPedidos){    
    for(int i=0; i<cantPedidos-1; i++)
        for(int j=i+1; j<cantPedidos; j++)
            if(arrFecha[i]>arrFecha[j] || 
              (arrFecha[i]==arrFecha[j] && arrHora[i]>arrHora[j]) ||
              (arrFecha[i]==arrFecha[j] && arrHora[i]==arrHora[j] && 
               arrPedido[i]>arrPedido[j])){
                cambiarInt(arrPedido,i,j);
                cambiarInt(arrFecha,i,j);
                cambiarInt(arrHora,i,j);
                cambiarInt(arrDni,i,j);
            }    
}

void cambiarInt(int *arr, int i, int j){
    int aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}

void leerStockDeProductos(int *arrProducto, int *arrStock, double *arrPrecio, int *i){
    FILE *archStock = abrirArchivo("StockDeProductosAlmacenados.txt","r");
    while(1){
        fscanf(archStock,"%d",&arrProducto[*i]);
        if(feof(archStock)) break;
        fscanf(archStock,"%d %lf",&arrStock[*i],&arrPrecio[*i]);
        (*i)++;
    }
    fclose(archStock);
}

void ordenarStockDeProductos(int *arrProducto, int *arrStock, double *arrPrecio,
                             int cantProductos){    
    for(int i=0; i<cantProductos-1; i++)
        for(int j=i+1; j<cantProductos; j++)
            if(arrProducto[i]>arrProducto[j]){
                cambiarInt(arrProducto,i,j);
                cambiarInt(arrStock,i,j);
                cambiarDouble(arrPrecio,i,j);
            }
}

void cambiarDouble(double *arr, int i, int j){
    double aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}

void leerDetalleDeLosPedidos(int *arrDetPed, int *arrDetProd, int *arrDetCant, int *i){    
    FILE *archDetalle = abrirArchivo("DetalleDeLosPedidos.txt","r");
    while(1){
        fscanf(archDetalle,"%d",&arrDetPed[*i]);
        if(feof(archDetalle)) break;
        fscanf(archDetalle,"%d %d",&arrDetProd[*i],&arrDetCant[*i]);
        (*i)++;
    }
    fclose(archDetalle);
}

void imprimirReporteDePedidos(int *arrPedido, int *arrFecha, int *arrHora, 
                              int *arrDni, int cantPedidos, int *arrProducto, 
                              int *arrStock, double *arrPrecio, int cantProductos,
                              int *arrDetPed, int *arrDetProd, int *arrDetCant,
                              int cantDetalles){    
    FILE *archReporte, *archClientes;
    archClientes = abrirArchivo("ClientesRegistrados.txt","r");
    archReporte = abrirArchivo("ReporteDePedidos.txt","w");
    imprimirCabeceraPrincipal(archReporte);
    for(int i=0; i<cantPedidos; i++){
        imprimirCabeceraDePedido(arrPedido[i],arrDni[i],archClientes,
                arrFecha[i],arrHora[i],archReporte);
        imprimirProductosSolicitados(arrPedido[i],arrProducto,arrStock,arrPrecio,
                cantProductos,arrDetPed,arrDetProd,arrDetCant,cantDetalles,
                archReporte);
    }   
    fclose(archClientes);
    fclose(archReporte);
}

void imprimirCabeceraPrincipal(FILE *archReporte){
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"%63s\n","TIENDA VIRTUAL LA MAGNIFICA");
    fprintf(archReporte,"%65s\n","REPORTE DE ATENCIÓN DE PEDIDOS");
    imprimirLinea(archReporte,'-',MAX_LINEA);    
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);    
}

void imprimirCabeceraDePedido(int pedido, int dniCliente, FILE *archClientes,
                              int fecha, int hora, FILE *archReporte){
    rewind(archClientes);
    int dni, dd, mm, aaaa, h, s, m;
    char nombre[60], nombreModificado[50];
    while(1){
        fscanf(archClientes,"%s %d",nombre,&dni);
        if(feof(archClientes)) break;
        if(dni==dniCliente){
            separarFecha(fecha,&dd,&mm,&aaaa); 
            separarHora(hora,&s,&m,&h);
            modificarNombre(nombre,nombreModificado);                       
            fprintf(archReporte,"%14s %10s %18s %22s %15s\n","No. de pedido",
                    "DNI","Nombre","Fecha","Hora");
            fprintf(archReporte,"%10d %7c %08d %5c %-25s %02d/%02d/%-10d "
                    "%02d:%02d:%02d\n",
                    pedido,' ',dniCliente,' ',nombreModificado,dd,mm,aaaa,h,m,s);            
            break;
        }
    }
}

void separarFecha(int fecha, int *dd, int *mm, int *aaaa){    
    *aaaa = fecha/10000;
    fecha -= (*aaaa)*10000;
    *mm = fecha/100;
    fecha -= (*mm)*100;
    *dd = fecha;    
}

void separarHora(int tiempo, int *s, int *m, int *h){    
    *h = tiempo/60/60;
    tiempo -= (*h)*60*60;
    *m = tiempo/60;
    tiempo -= (*m)*60;
    *s = tiempo;
}

void modificarNombre(char *cad1, char *cad2){    
    //Saltamos el nombre
    int i, j;
    for(i=0; cad1[i]!='/'; i++);   
    //Primera letra en mayúscula del apellido
    i++;
    cad2[0]=cad1[i];    
    i++;    
    //Letras de apellido (minuscula)    
    for(j=1; cad1[i]!='/'; i++, j++)
        cad2[j]=convertirMinuscula(cad1[i]);    
    //Espacio entre apellido paterno y nombre
    cad2[j]=' ';        
    j++;    
    //Primera letra en mayúscula del nombre
    cad2[j]=cad1[0];
    j++;    
    //Letras de nombre (minuscula)   
    for(i=1; cad1[i]!='-'&&cad1[i]!='/'; i++, j++)
        cad2[j]=convertirMinuscula(cad1[i]);    
    //Finalizamos la cadena
    cad2[j]=0;
}

char convertirMinuscula(char c){
    return c+=(c>='A'&&c<='Z'?'a'-'A':0);   
}

void imprimirProductosSolicitados(int pedido, int *arrProducto, int *arrStock,
                double *arrPrecio, int cantProductos, int *arrDetPed,
                int *arrDetProd, int *arrDetCant, int cantDetalles,
                FILE *archReporte){    
    imprimirCabeceraDeProductos(archReporte);
    double totalACobrar=0.0, subTotal;
    int i=0, pos, cantAtendida;        
    for(int j=0; j<cantDetalles; j++)        
        if(pedido==arrDetPed[j]){
            pos = buscarPos(arrDetProd[j],arrProducto,cantProductos);
            if(pos!=NO_SE_ENCONTRO){                
                if(arrStock[pos]>=arrDetCant[j]){
                    cantAtendida = arrDetCant[j];
                    arrStock[pos]-=arrDetCant[j];
                }else{                    
                    if(arrStock[pos]>0)
                        cantAtendida = arrStock[pos];                        
                    else
                        cantAtendida = 0;
                    arrStock[pos]=0; 
                }            
                subTotal = cantAtendida*arrPrecio[pos];
                fprintf(archReporte,"%3d) %05d %18d %24d %21.2lf %10.2lf\n",
                        i+1,arrDetProd[j],arrDetCant[j],cantAtendida,
                        arrPrecio[pos],subTotal);
                totalACobrar+=subTotal;
                i++;            
            }
        }
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"Total a cobrar: %15.2lf\n",totalACobrar);
    imprimirLinea(archReporte,'=',MAX_LINEA);
}

void imprimirCabeceraDeProductos(FILE *archReporte){
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"%13s %24s %23s %13s %12s\n","Producto",
            "CANTIDAD SOLICITADA","CANTIDAD ATENDIDA","Precio","SubTotal");    
}

int buscarPos(int producto, int *arrProducto, int cantProductos){    
    int limSup=cantProductos-1, limInf=0, pm;
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm = (limInf+limSup)/2;
        if(producto==arrProducto[pm]) return pm;
        else if(producto>arrProducto[pm]) limInf=pm+1;
        else limSup=pm-1;
    }
}