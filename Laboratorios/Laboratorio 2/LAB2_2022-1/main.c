/* 
 * Proyecto: Laboratorio02-2022-1-Archivos
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de abril de 2022, 08:02 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    FILE *archClientes, *archProductos, *archPedidos, *archCategorias, 
            *archImpuestos, *archReportePorProducto;
     
    //Apertura de archivos.
    archClientes = fopen("Clientes.txt","r");
    if(archClientes==NULL){
        printf("ERROR: No se pudo abrir el archivo Clientes.txt\n");
        exit(1);        
    }
    archProductos = fopen("Productos.txt","r");
    if(archProductos==NULL){
        printf("ERROR: No se pudo abrir el archivo Productos.txt\n");
        exit(1);        
    }
    archPedidos = fopen("Pedidos.txt","r");
    if(archPedidos==NULL){
        printf("ERROR: No se pudo abrir el archivo Pedidos.txt\n");
        exit(1);        
    }
    archCategorias = fopen("Categorias.txt","r");
    if(archCategorias==NULL){
        printf("ERROR: No se pudo abrir el archivo Categorias.txt\n");
        exit(1);        
    }
    archImpuestos = fopen("Impuestos.txt","r");
    if(archImpuestos==NULL){
        printf("ERROR: No se pudo abrir el archivo Impuestos.txt\n");
        exit(1);        
    }
    archReportePorProducto = fopen("ReportePorProducto.txt","w");
    if(archReportePorProducto==NULL){
        printf("ERROR: No se pudo abrir el archivo ReportePorProducto.txt\n");
        exit(1);        
    }
    procesarArchivos(archClientes,archProductos,archPedidos,archCategorias,
            archImpuestos,archReportePorProducto);
    cerrarArchivos(archClientes,archProductos,archPedidos,archCategorias,
            archImpuestos,archReportePorProducto);

    return (EXIT_SUCCESS);
}

