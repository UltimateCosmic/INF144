/* 
 * Proyecto: ManejoDeArchivos_Lab03_2022_1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 10 de mayo de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_PEDIDOS 200
#define MAX_LINEA 88
#define NO_SE_ENCONTRO -1

void procesarClientes(int *arrDni, int *arrTelefono, int *numClientes){
    //Apertura de archivo
    FILE *archClientes;
    archClientes=fopen("Clientes.txt","r");
    if(archClientes==NULL){
        printf("ERROR: No se pudo abrir el archivo Clientes.txt\n");
        exit(1);
    }
    leerClientes(archClientes,arrDni,arrTelefono,numClientes);
    fclose(archClientes);
}

void leerClientes(FILE *archClientes, int *arrDni, int *arrTelefono, 
                  int *numClientes){
    //Lectura de los clientes, la iteración termina al fin de archivo
    while(1){
        fscanf(archClientes,"%d",&arrDni[*numClientes]);
        if(feof(archClientes)) break;
        saltarNombre(archClientes,']');
        fscanf(archClientes,"%d",&arrTelefono[*numClientes]);
        (*numClientes)++;
    }
}

void saltarNombre(FILE *arch, char c){
    //Salto del nombre del cliente o del pedido dependiendo del caracter de fin
    while(fgetc(arch)!=c);    
}

void ordenarClientesPorDNI(int *arrDni, int *arrTelefono, int numClientes){
    //Previo al reporte el problema nos solicita ordenar los clientes por DNI
    for(int i=0; i<numClientes-1; i++)
        for(int k=i+1; k<numClientes; k++)
            if(arrDni[i]>arrDni[k]){
                cambiarInt(arrDni,i,k);
                cambiarInt(arrTelefono,i,k);                
            }
}

void cambiarInt(int *arrInt, int i, int k){
    //Cambio de valor entre dos datos de un mismo arreglo con indice diferente
    int aux=arrInt[i];
    arrInt[i]=arrInt[k];
    arrInt[k]=aux;
}

void procesarPedidos(int *arrCodigoProd, double *arrPrecioProd,
                     double *arrCantidadProd, double *arrTotalProd, int *numProd,
                     int *arrDNI_Cli, double *arrTotalGastadoCli, int numClientes){
    //Apertura de archivo
    FILE *archPedidos;
    archPedidos=fopen("Pedidos.txt","r");
    if(archPedidos==NULL){
        printf("ERROR: No se pudo abrir el archivo Pedidos.txt\n");
        exit(1);
    }
    leerPedidos(archPedidos,arrCodigoProd,arrPrecioProd,arrCantidadProd,
            arrTotalProd,numProd,arrDNI_Cli,arrTotalGastadoCli,numClientes);
    fclose(archPedidos);   
}

void leerPedidos(FILE *archPedidos, int *arrCodigoProd, double *arrPrecioProd,
                 double *arrCantidadProd, double *arrTotalProd, int *numProd,
                 int *arrDNI_Cli, double *arrTotalGastadoCli, int numClientes){    
    int codigo, i, dni;
    double cantidad, precio, subtotal;
    while(1){
        fscanf(archPedidos,"%d",&codigo);
        if(feof(archPedidos)) break;
        saltarNombre(archPedidos,'*');
        saltarNombre(archPedidos,'*');
        i=buscarIndice(codigo,arrCodigoProd);        
        if(i!=NO_SE_ENCONTRO){
            //En caso sea un nuevo producto, la cantidad aumenta
            if(arrCodigoProd[i]==0) (*numProd)++;
            fscanf(archPedidos,"%lf %lf",&cantidad,&precio);       
            fscanf(archPedidos,"%d %*d/%*d/%*d",&dni);
            subtotal=precio*cantidad;
            arrCodigoProd[i]=codigo;
            arrPrecioProd[i]=precio;
            arrCantidadProd[i]+=cantidad;
            arrTotalProd[i]+=subtotal;;
            asignarTotalGastadoCli(arrDNI_Cli,dni,arrTotalGastadoCli,
                    numClientes,subtotal);
        }//Saltamos la linea en caso no se encuentre el producto
        else
            while(fgetc(archPedidos)!='\n');
    }
}

int buscarIndice(int codigo, int *arrCodigoProd){    
    //Buscamos el indice del producto comparando los códigos
    for(int i=0; i<MAX_PEDIDOS; i++)
        if(codigo==arrCodigoProd[i]||arrCodigoProd[i]==0) return i;
    return NO_SE_ENCONTRO;
}

void asignarTotalGastadoCli(int *arrDNI_Cli, int dni, double *arrTotalGastadoCli,
                            int numClientes, double subtotal){    
    //Asignamos el total gastado al cliente
    for(int i=0; i<numClientes; i++)
        if(arrDNI_Cli[i]==dni)
            arrTotalGastadoCli[i]+=subtotal;
}

void procesarReporteDeVentas(int *arrDNI_Cli, int *arrTelefonoCli,
                             double *arrTotalGastadoCli, int numClientes,
                             int *arrCodigoProd, double *arrPrecioProd,
                             double *arrCantidadProd, double *arrTotalProd,
                             int numProd){
    //Apertura de archivo
    FILE *archReporteDeVentas;
    archReporteDeVentas=fopen("ReporteDeVentas.txt","w");
    if(archReporteDeVentas==NULL){
        printf("ERROR: No se pudo abrir el archivo ReporteDeVentas.txt\n");
        exit(1);
    }
    imprimirReporteDeVentas(archReporteDeVentas,arrDNI_Cli,arrTelefonoCli,
            arrTotalGastadoCli,numClientes,arrCodigoProd,arrPrecioProd,
            arrCantidadProd,arrTotalProd,numProd);
    fclose(archReporteDeVentas);   
}

void imprimirReporteDeVentas(FILE *archReporteDeVentas, int *arrDNI_Cli, 
                             int *arrTelefonoCli, double *arrTotalGastadoCli, 
                             int numClientes, int *arrCodigoProd, 
                             double *arrPrecioProd, double *arrCantidadProd, 
                             double *arrTotalProd, int numProd){
    ordenarArreglosParaReporte(arrDNI_Cli,arrTelefonoCli,arrTotalGastadoCli,
            numClientes,arrCodigoProd,arrPrecioProd,arrCantidadProd,arrTotalProd,
            numProd);
    imprimirCabeceraPrincipal(archReporteDeVentas);
    imprimirIngresosPorProducto(archReporteDeVentas,arrCodigoProd,arrPrecioProd,
            arrCantidadProd,arrTotalProd,numProd);
    imprimirGastosPorCliente(archReporteDeVentas,arrDNI_Cli,arrTelefonoCli,
            arrTotalGastadoCli,numClientes);
}

void ordenarArreglosParaReporte(int *arrDNI_Cli, int *arrTelefonoCli, 
                                double *arrTotalGastadoCli, int numClientes, 
                                int *arrCodigoProd, double *arrPrecioProd, 
                                double *arrCantidadProd, double *arrTotalProd, 
                                int numProd){
    ordenarProductos(arrCodigoProd,arrPrecioProd,arrCantidadProd,arrTotalProd,
            numProd);
    ordenarClientes(arrDNI_Cli,arrTelefonoCli,arrTotalGastadoCli,numClientes);    
}

void ordenarProductos(int *arrCodigoProd, double *arrPrecioProd, 
                      double *arrCantidadProd, double *arrTotalProd, int numProd){
    //Ordenada ascendentemente por el código
    for(int i=0; i<numProd-1; i++)
        for(int j=i+1; j<numProd; j++)
            if(arrCodigoProd[i]>arrCodigoProd[j]){                
                cambiarInt(arrCodigoProd,i,j);
                cambiarDouble(arrPrecioProd,i,j);                
                cambiarDouble(arrCantidadProd,i,j);                
                cambiarDouble(arrTotalProd,i,j);
            }
}

void ordenarClientes(int *arrDNI_Cli, int *arrTelefonoCli, 
                     double *arrTotalGastadoCli, int numClientes){    
    //Ordenada descendentemente por el total gastado
    for(int i=0; i<numClientes-1; i++)
        for(int j=i+1; j<numClientes; j++)
            if(arrTotalGastadoCli[i]<arrTotalGastadoCli[j]){                
                cambiarInt(arrDNI_Cli,i,j);
                cambiarInt(arrTelefonoCli,i,j);
                cambiarDouble(arrTotalGastadoCli,i,j);                
            }
}

void cambiarDouble(double *arrDouble, int i, int k){
    //Cambio de valor entre dos datos de un mismo arreglo con indice diferente
    double aux=arrDouble[i];
    arrDouble[i]=arrDouble[k];
    arrDouble[k]=aux;
}

void imprimirCabeceraPrincipal(FILE *archReporteDeVentas){    
    fprintf(archReporteDeVentas,"%54s\n","EMPRESA COMERCIALIZADORA ABC S.A.");
    fprintf(archReporteDeVentas,"%54s\n","REPOETE DE VENTAS");
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirIngresosPorProducto(FILE *archReporteDeVentas,int *arrCodigoProd, 
                                 double *arrPrecioProd, double *arrCantidadProd, 
                                 double *arrTotalProd, int numProd){    
    double totalRecaudado=0;
    imprimirCabeceraIngresosPorProducto(archReporteDeVentas);
    //Impresión de los ingresos por producto
    for(int i=0; i<numProd; i++){
        fprintf(archReporteDeVentas,"%2d) %8c %06d",i+1,' ',arrCodigoProd[i]);
        fprintf(archReporteDeVentas,"%22.2lf %18.2lf",arrPrecioProd[i],
                arrCantidadProd[i]);
        fprintf(archReporteDeVentas,"%22.2lf\n",arrTotalProd[i]);   
        totalRecaudado+=arrTotalProd[i];
    }
    //Total recaudado
    imprimirTotalRecaudado(archReporteDeVentas,totalRecaudado);
}

void imprimirCabeceraIngresosPorProducto(FILE *archReporteDeVentas){    
    imprimirLinea(archReporteDeVentas,'=',MAX_LINEA);
    fprintf(archReporteDeVentas,"INGRESOS POR PRODUCTO\n");
    fprintf(archReporteDeVentas,"%s %15s %22s %20s %20s\n","No.","CODIOG",
            "PRECIO","CANTIDAD VENDIDA","MONTO RECAUDADO");    
}

void imprimirTotalRecaudado(FILE *archReporteDeVentas, double totalRecaudado){
    imprimirLinea(archReporteDeVentas,'-',MAX_LINEA);
    fprintf(archReporteDeVentas,"%73s %.2lf\n","TOTAL RECAUDADO:",totalRecaudado);
}

void imprimirGastosPorCliente(FILE *archReporteDeVentas, int *arrDNI_Cli,
                              int *arrTelefonoCli, double *arrTotalGastadoCli,
                              int numClientes){
    int iMayorGasto, iMenorGasto;
    double mayorGasto=0, menorGasto=9999999;
    imprimirCabeceraGastosPorCliente(archReporteDeVentas);
    //Impresión de los gastos por cliente
    for(int i=0; i<numClientes; i++){
        fprintf(archReporteDeVentas,"%2d) %8c %08d",i+1,' ',arrDNI_Cli[i]);
        fprintf(archReporteDeVentas,"%16d",arrTelefonoCli[i]);
        fprintf(archReporteDeVentas,"%19.2lf\n",arrTotalGastadoCli[i]);
        determinarMayorYMenorGasto(arrTotalGastadoCli,i,&mayorGasto,&menorGasto,
                &iMayorGasto,&iMenorGasto);
    }
    //Clientes con mayor y menor gasto
    imprimirCliMayorYMenorGasto(archReporteDeVentas,arrDNI_Cli,
            arrTotalGastadoCli,iMayorGasto,iMenorGasto);
}

void imprimirCabeceraGastosPorCliente(FILE *archReporteDeVentas){
    imprimirLinea(archReporteDeVentas,'=',MAX_LINEA);
    fprintf(archReporteDeVentas,"GASTOS POR CLIENTE\n");
    fprintf(archReporteDeVentas,"%s %12s %20s %20s\n","NO.","DNI","TELEFONO",
            "TOTAL GASTADO");
}

void determinarMayorYMenorGasto(double *arrTotalGastadoCli, int i, 
                                double *mayorGasto, double *menorGasto,
                                int *iMayorGasto, int *iMenorGasto){
    //Cambio de indices y mayor y menor gasto
    if(arrTotalGastadoCli[i]>*mayorGasto){
        *mayorGasto=arrTotalGastadoCli[i];
        *iMayorGasto=i;
    }
    if(arrTotalGastadoCli[i]<*menorGasto){
        *menorGasto=arrTotalGastadoCli[i];
        *iMenorGasto=i;
    }
}

void imprimirCliMayorYMenorGasto(FILE *archReporteDeVentas, int *arrDNI_Cli,
                                 double *arrTotalGastadoCli, int iMayorGasto,
                                 int iMenorGasto){
    imprimirLinea(archReporteDeVentas,'-',MAX_LINEA);
    fprintf(archReporteDeVentas,"Cliente con mayor gasto: %d - S/. %.2lf\n",
            arrDNI_Cli[iMayorGasto],arrTotalGastadoCli[iMayorGasto]);    
    fprintf(archReporteDeVentas,"Cliente con mayor gasto: %d - S/. %.2lf\n",
            arrDNI_Cli[iMenorGasto],arrTotalGastadoCli[iMenorGasto]);    
}