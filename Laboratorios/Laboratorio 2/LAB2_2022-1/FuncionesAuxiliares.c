/* 
 * Proyecto: Laboratorio02-2022-1-Archivos
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de abril de 2022, 08:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 140
#define MAX_ESPACIOS 45

void procesarArchivos(FILE *archClientes, FILE *archProductos, FILE *archPedidos,
                      FILE *archCategorias, FILE *archImpuestos,
                      FILE *archReportePorProducto){    
    imprimirCabecera(archReportePorProducto);    
    int codProducto;
    double totalPorProducto, totalDePedidos=0;        
    while(1){
        fscanf(archProductos,"%d",&codProducto);
        if(feof(archProductos)) break;
        imprimirLinea(archReportePorProducto,'=',MAX_LINEA);
        totalPorProducto = imprimirProducto(archClientes,archProductos,
                archPedidos,archCategorias,archImpuestos,archReportePorProducto,
                codProducto);
        totalDePedidos+=totalPorProducto;
    }
    imprimirTotalDePedidos(archReportePorProducto,totalDePedidos);
}

void imprimirCabecera(FILE *archReportePorProducto){    
    fprintf(archReportePorProducto,"%90s\n","EMPRESA COMERCIALIZADORA ABC S.A.");
    fprintf(archReportePorProducto,"%80s\n","PEDIDOS POR PRODUCTO");        
}

double imprimirProducto(FILE *archClientes, FILE *archProductos,
                        FILE *archPedidos, FILE *archCategorias, 
                        FILE *archImpuestos, FILE *archReportePorProducto,
                        int codProducto){
    
    double totalPorProducto=0, precioUnitario, descuento;
    fprintf(archReportePorProducto,"%15s %04d - ","Producto:",codProducto);  
    imprimirNombreDelProducto(archProductos,archReportePorProducto);
    fscanf(archProductos,"%lf %lf",&precioUnitario,&descuento);
    descuento*=100;
    fprintf(archReportePorProducto,"%s %6.2lf %20s %.2lf%%\n","Precio Unitario:",
            precioUnitario,"Descuento:",descuento); 
    imprimirLinea(archReportePorProducto,'-',MAX_LINEA);
    imprimirListadoDePedidos(archClientes,archPedidos,archCategorias,
            archImpuestos,archReportePorProducto,codProducto,precioUnitario,
            descuento,&totalPorProducto);
    return totalPorProducto;
}

void imprimirListadoDePedidos(FILE *archClientes, FILE *archPedidos,
                              FILE *archCategorias, FILE *archImpuestos,
                              FILE *archReportePorProducto, int codProducto,
                              double precioUnitario, double descuento,
                              double *totalPorProducto){   
    rewind(archPedidos);
    imprimirCabeceraListado(archReportePorProducto);
    int codPedido, dniCliente;
    double total;    
    while(1){        
        fscanf(archPedidos,"%d",&codPedido);
        if(feof(archPedidos)) break;
        fscanf(archPedidos,"%d",&dniCliente);
        //Busqueda de impresión de los pedidos del producto.
        total = buscarDetallesDeProductos(archClientes,archPedidos,
                archCategorias,archImpuestos,archReportePorProducto,codProducto,
                precioUnitario,descuento,codPedido,dniCliente);
        *totalPorProducto += total;
    }
    imprimirLinea(archReportePorProducto,'-',MAX_LINEA);
    fprintf(archReportePorProducto,"Total por producto: %10.2lf\n",*totalPorProducto);
}

void imprimirCabeceraListado(FILE *archReportePorProducto){
    fprintf(archReportePorProducto,"%24s\n","LISTADO DE PEDIDOS");
    fprintf(archReportePorProducto,"%11s %18s %39s %14s %11s %17s %13s %8s\n",
            "Codigo","Cliente","Categoria","%Descuento","Pais","%Impuesto",
            "Cantidad","Total");
    imprimirLinea(archReportePorProducto,'-',MAX_LINEA);
}

double buscarDetallesDeProductos(FILE *archClientes, FILE *archPedidos,
                                 FILE *archCategorias, FILE *archImpuestos,
                                 FILE *archReportePorProducto, int codProducto,
                                 double precioUnitario, double descuento,
                                 int codPedido, int dniCliente){
    int codigoProducto;
    double cantidad, total, nuevoTotal;
    
    while(1){
        fscanf(archPedidos,"%d %lf",&codigoProducto,&cantidad);
        if(codigoProducto==codProducto){
            //Impresión del pedido en caso se encuentre el código del producto.
            imprimirPedido(archClientes,archCategorias,archImpuestos,
                    archReportePorProducto,precioUnitario,descuento,
                    codPedido,dniCliente,cantidad,&total);
            nuevoTotal += total;
        }
        if(fgetc(archPedidos)=='\n') break;
    }    
    return nuevoTotal;
}

void imprimirPedido(FILE *archClientes, FILE *archCategorias, FILE *archImpuestos,
                    FILE *archReportePorProducto, double precioUnitario,
                    double descuento, int codPedido, int dniCliente, 
                    double cantidad, double *total){    
    *total=0;
    int ciudad, pais, telefono;
    char categoria;
    double descuentoCategoria, impuestoPais;
    fprintf(archReportePorProducto,"%10d %3c %08d-",codPedido,' ',dniCliente);
    buscarCliente(archClientes,archReportePorProducto,dniCliente,&ciudad,
            &pais,&telefono,&categoria);
    descuentoCategoria = buscarDescuentoCategoria(archCategorias,categoria);    
    fprintf(archReportePorProducto,"%c %15.2lf %10d-",categoria,
            descuentoCategoria,pais);
    impuestoPais = buscarImpuestoPais(archImpuestos,archReportePorProducto,pais);
    *total = calcularTotal(cantidad,precioUnitario,descuento,descuentoCategoria,
            impuestoPais);
    fprintf(archReportePorProducto,"%9.2lf %11.2lf %11.2lf\n",impuestoPais,
            cantidad,*total);  
}

double buscarDescuentoCategoria(FILE *archCategorias, char categoria){    
    rewind(archCategorias);
    char c;
    double descuento;
    while(1){
        c=fgetc(archCategorias);     
        if(feof(archCategorias))
            break;
        else if(c==categoria){
            //Omisión de la descripción de la categoria.
            while(fgetc(archCategorias)==' ');
            while(fgetc(archCategorias)!=' '); 
            fscanf(archCategorias,"%lf",&descuento);
            break;
        }else
            while(fgetc(archCategorias)!='\n');
    }
    return descuento*100;   
}

double buscarImpuestoPais(FILE *archImpuestos, FILE *archReportePorProducto,
                          int pais){
    rewind(archImpuestos);    
    double descuento;
    int codPais;
    while(1){
        fscanf(archImpuestos,"%d",&codPais);
        if(feof(archImpuestos)) break;
        if(codPais==pais){
            //Impresión del nombre del pais en caso se encuentre el código.
            imprimirPais(archImpuestos,archReportePorProducto);
            fscanf(archImpuestos,"%lf",&descuento);
            break;
        }else
            while(fgetc(archImpuestos)!='\n');
    }
    return descuento*100;
}

void imprimirPais(FILE *archImpuestos, FILE *archReportePorProducto){    
    char c;
    int cantEspacios=0;
    while((c=fgetc(archImpuestos))==' '); 
    fputc(c,archReportePorProducto);    
    while(1){        
        c=fgetc(archImpuestos);        
        if(c==' ') break;
        else fputc(c,archReportePorProducto);        
        cantEspacios++;
    }
    //Impresión de espacios para alineación.
    for(int i=0; i<MAX_ESPACIOS-cantEspacios-35; i++)
        fputc(' ',archReportePorProducto);
}

double calcularTotal(double cantidad, double precioUnitario, double descuento,
                      double descuentoCategoria, double impuestoPais){    
    double precio = precioUnitario-calcularPorcentaje(precioUnitario,
            descuento+descuentoCategoria);
    precio += calcularPorcentaje(precio,impuestoPais);
    return precio*cantidad;    
}

double calcularPorcentaje(double precioUnitario, double descuento){
    //Calculo del porcentaje.
    return precioUnitario*descuento/100;
}

void buscarCliente(FILE *archClientes, FILE *archReportePorProducto,
                   int dniCliente, int *ccc, int *pp, int *n, char *categoria){    
    rewind(archClientes);
    int dni;    
    while(1){
        fscanf(archClientes,"%d",&dni);
        if(feof(archClientes)) break;
        if(dni==dniCliente){
            //Impresión del nombre del cliente en caso se encuentre el DNI.
            imprimirNombreCliente(archClientes,archReportePorProducto);
            fscanf(archClientes,"%3d%2d%d",ccc,pp,n);
            fscanf(archClientes,"%*d/%*d/%*d");     //Omisión de lectura de fecha.       
            while(((*categoria)=fgetc(archClientes))==' ');            
            break;
        }else
            while(fgetc(archClientes)!='\n');
    }    
}

void imprimirNombreCliente(FILE *archClientes, FILE *archReportePorProducto){    
    //Impresión del nombre del cliente.
    char c, cantEspacios=0;
    while((c=fgetc(archClientes))==' '); 
    fputc(c,archReportePorProducto);    
    while(1){        
        c=fgetc(archClientes);
        if(c==' ') 
            break;
        else if(c=='_')
            fputc(' ',archReportePorProducto);
        else
            fputc(c,archReportePorProducto);
        cantEspacios++;
    }
    //Impresión de espacios para alineación.
    for(int i=0; i<MAX_ESPACIOS-cantEspacios-5; i++)
        fputc(' ',archReportePorProducto);
}

void imprimirNombreDelProducto(FILE *archProductos, FILE *archReportePorProducto){        
    //Impresión del nombre del producto.
    char c, cantEspacios=0;
    while((c=fgetc(archProductos))!='"');
    while(1){        
        c=fgetc(archProductos);
        c=convertirMayuscula(c);
        if(c=='"') break;
        fputc(c,archReportePorProducto);
        cantEspacios++;        
    }
    for(int i=0; i<MAX_ESPACIOS-cantEspacios; i++)
        fputc(' ',archReportePorProducto);
}

char convertirMayuscula(char c){
    //Conversión de caracter a mayúscula en caso de ser minúscula.
    if(c>='a'&&c<='z') return c-=32;
    else return c;
}

void imprimirTotalDePedidos(FILE *archReportePorProducto, double totalDePedidos){    
    //Impresión del total de pedidos al final del archivo.
    imprimirLinea(archReportePorProducto,'=',MAX_LINEA);
    fprintf(archReportePorProducto,"TOTAL DE PEDIDOS: %10.2lf\n",totalDePedidos);
    imprimirLinea(archReportePorProducto,'=',MAX_LINEA);    
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    //Impresión de fila de caracteres.
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void cerrarArchivos(FILE *archClientes, FILE *archProductos, FILE *archPedidos,
                    FILE *archCategorias, FILE *archImpuestos,
                    FILE *archReportePorProducto){
    //Cierre de los archivos.
    fclose(archClientes);
    fclose(archProductos);
    fclose(archPedidos);
    fclose(archCategorias);
    fclose(archImpuestos);
    fclose(archReportePorProducto);
}