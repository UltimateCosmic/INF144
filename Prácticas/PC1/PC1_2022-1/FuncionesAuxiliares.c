/* 
 * Proyecto: Practica01-2022-1_Archivos
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 07:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 115

void procesarArchivos(FILE *archVentas, FILE *archReporteCompras){
    
    int dd, mm, aaaa, tipoProducto, codigoPais;
    double descuentoCatA, descuentoCatB, descuentoCatC, 
            descuentoAdicionalProd, porcentajeImpuesto; 
    
    //Lectura de datos iniciales.
    fscanf(archVentas,"%d/%d/%d",&dd,&mm,&aaaa);    
    fprintf(archReporteCompras,"%70s\n","EMPRESA COMERCIALIZADORA ABC S.A.");
    fprintf(archReporteCompras,"%54s %02d/%02d/%04d\n",
            "Fecha de emision:",dd,mm,aaaa);    
    fscanf(archVentas,"%lf%% %lf%% %lf%%",&descuentoCatA,&descuentoCatB,
            &descuentoCatC);
    fscanf(archVentas,"%d %lf%%",&tipoProducto,&descuentoAdicionalProd);
    fscanf(archVentas,"%d %lf%%",&codigoPais,&porcentajeImpuesto);
    
    //Impresión de cabecera
    fprintf(archReporteCompras,"%32s %04d\n","Productos con descuento:",
            tipoProducto);
    fprintf(archReporteCompras,"%40s ","Pais con impuestos a las ventas:");
    imprimirPais(archReporteCompras,codigoPais);        
    imprimirLinea(archReporteCompras,'=',MAX_LINEA);    
    imprimirClientes(archVentas,archReporteCompras,tipoProducto,codigoPais,
            descuentoCatA,descuentoCatB,descuentoCatC,descuentoAdicionalProd,
            porcentajeImpuesto,mm);
}   

void imprimirClientes(FILE *archVentas, FILE *archReporte, int tipoProducto,
                      int codigoPais, double descuentoCatA, double descuentoCatB,
                      double descuentoCatC, double descuentoAdicionalProd,
                      double porcentajeImpuesto, int mm){
    
    int dni, ciudad, pais, numero, ddNac, mmNac, aaaaNac;
    char categoria;
    
    while(1){        
                
        fscanf(archVentas,"%d",&dni);        
        if(feof(archVentas)) break;        //Verificación de fin de archivo
        fscanf(archVentas,"%3d%2d%d",&ciudad,&pais,&numero);        
        while((categoria=fgetc(archVentas))==' ');      //Categoria de cliente
        fscanf(archVentas,"%d/%d/%d",&ddNac,&mmNac,&aaaaNac);
        
        fprintf(archReporte,"%16s %08d %41s ","Cliente:",dni,"Pais:");
        imprimirPais(archReporte,pais);
        fprintf(archReporte,"%69s %d\n","Ciudad:",ciudad);
        fprintf(archReporte,"%71s %d\n","Telefono:",numero);
        fprintf(archReporte,"%28s %02d/%02d/%04d %32s %c\n",
                "Fecha de nacimiento:",ddNac,mmNac,aaaaNac,
                "Categoria:",categoria);
        imprimirLinea(archReporte,'-',MAX_LINEA);
        imprimirProductosAdquiridos(archVentas,archReporte,tipoProducto,
                codigoPais,descuentoCatA,descuentoCatB,descuentoCatC,
                descuentoAdicionalProd,porcentajeImpuesto,pais,
                categoria,mmNac,mm);
    }    
}

void imprimirProductosAdquiridos(FILE *archVentas, FILE *archReporte, 
                                 int tipoProducDesc, int codigoPaisImpuesto, 
                                 double descuentoCatA, double descuentoCatB,
                                 double descuentoCatC, double descAdicionalProd,
                                 double porcentajeImpuesto, 
                                 int pais, char categoria, int mmNac, 
                                 int mmEmision){
    //Cabecera de productos adquiridos
    fprintf(archReporte,"%28s\n","PRODUCTOS ADQUIRIDOS");
    fprintf(archReporte,"%10s %8s %7s %11s %10s %10c %s %15s %15s\n",
            "TIPO","CODIGO","P.U.","Cantidad","Total",'%',"de Descuentos",
            "Impuesto","A Pagar");
    imprimirLinea(archReporte,'-',MAX_LINEA);
    
    int tipoProducto, codigoProducto;
    double totalAPagar=0, precioUnitario, cantidad, total, aPagar;
    double primerDesc, segundoDesc, tercerDesc, impuesto;
    
    while(1){
        
        fscanf(archVentas,"%4d",&tipoProducto);
        if(tipoProducto==0) break;      //Condición de fin.
        fscanf(archVentas,"%d",&codigoProducto);
        fscanf(archVentas,"%lf %lf",&precioUnitario,&cantidad);
        
        //Calculamos el total (sin descuentos ni impuestos)
        total = cantidad*precioUnitario;
        fprintf(archReporte,"%5c %04d %7d %9.2lf %10.2lf %11.2lf",' ',
                tipoProducto,codigoProducto,precioUnitario,cantidad,total);
        
        //Impresion de los descuentos
        primerDesc = imprimirPrimerDesc(archReporte,categoria,
                descuentoCatA,descuentoCatB,descuentoCatC);
        segundoDesc = imprimirSegundoDesc(archReporte,tipoProducDesc,
                tipoProducto,descAdicionalProd);
        tercerDesc = imprimirTercerDesc(archReporte,mmEmision,mmNac);
        impuesto = imprimirImpuesto(archReporte,codigoPaisImpuesto,
                porcentajeImpuesto,pais);
        
        //Calculamos el resultado a pagar aplicando los descuentos e impuestos
        aPagar = total;        
        if(primerDesc>=0)
            aPagar = aPagar-calcularPorcentaje(aPagar,primerDesc);     
        if(segundoDesc>=0)
            aPagar = aPagar-calcularPorcentaje(aPagar,segundoDesc);
        if(tercerDesc>=0)
            aPagar = aPagar-calcularPorcentaje(aPagar,tercerDesc);
        if(impuesto>=0)
            aPagar = aPagar+calcularPorcentaje(aPagar,impuesto);
            
        fprintf(archReporte,"%18.2lf\n",aPagar);
        totalAPagar+=aPagar;
    }
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"%99s %8.2lf\n","Total a pagar:",totalAPagar);
    imprimirLinea(archReporte,'=',MAX_LINEA);
}

double calcularPorcentaje(double precio, double descuento){
    //Calculo del precio descontado.
    return precio*descuento/100;
}

double imprimirPrimerDesc(FILE *archReporte, char categoria, 
                          double descuentoCatA, double descuentoCatB,
                          double descuentoCatC){    
    //Verificamos si existe algún descuento por la categoria del cliente.
    fprintf(archReporte,"%10c",' ');    
    if(categoria=='A'){
        fprintf(archReporte,"%05.2lf|",descuentoCatA);
        return descuentoCatA;
    }else if(categoria=='B'){
        fprintf(archReporte,"%05.2lf|",descuentoCatB);
        return descuentoCatB;
    }else if(categoria=='C'){
        fprintf(archReporte,"%05.2lf|",descuentoCatC);
        return descuentoCatC;
    }else{
        fprintf(archReporte,"--.--|");
        return -1;
    }
}

double imprimirSegundoDesc(FILE *archReporte, int tipoProducDesc, 
                         int tipoProducto, double descAdicionalProd){    
    /* Verificamos si existe un descuento por el tipo de 
     * producto que compra el cliente.*/
    if(tipoProducDesc==tipoProducto){
        fprintf(archReporte,"%05.2lf|",descAdicionalProd);        
        return descAdicionalProd;
    }else{
        fprintf(archReporte,"--.--|");
        return -1;
    }
}

double imprimirTercerDesc(FILE *archReporte, int mmEmision, int mmNac){
    //Verificamos si existe un descuento por el mes de nacimiento del cliente.
    if(mmEmision==mmNac){
        fprintf(archReporte,"%05.2lf",5.00);
        return 5.00;
    }else{
        fprintf(archReporte,"--.--");
        return -1;
    }
}

double imprimirImpuesto(FILE *archReporte, int codigoPaisImpuesto, 
                      double porcentajeImpuesto, int pais){    
    //Verificamos si existe un impuesto que se tiene que pagar por el país.
    if(codigoPaisImpuesto==pais){        
        fprintf(archReporte,"%6c %05.2lf",' ',porcentajeImpuesto); 
        return porcentajeImpuesto;
    }else{
        fprintf(archReporte,"%6c --.--",' ');
        return -1;
    }
}

void imprimirPais(FILE *archReporteCompras, int codigoPais){    
    //Impresión del nombre del país dependiendo el código.
    if(codigoPais==51)
        fprintf(archReporteCompras,"Perú");
    else if(codigoPais==63)
        fprintf(archReporteCompras,"Brasil");
    else if(codigoPais==77)
        fprintf(archReporteCompras,"Colombia");
    else if(codigoPais==98)
        fprintf(archReporteCompras,"Uruguay");
    
    fprintf(archReporteCompras," (%d)\n",codigoPais);
}

void imprimirLinea(FILE *archReporte, char caracter, int cantVeces){
    //Impresión de linea de caracteres.
    for(int i=0; i<cantVeces; i++) fputc(caracter,archReporte);
    fputc('\n',archReporte);    
}

void cerrarArchivos(FILE *archVentas, FILE *archReporteCompras){
    //Cierre de archivos.
    fclose(archReporteCompras);
    fclose(archVentas);    
}