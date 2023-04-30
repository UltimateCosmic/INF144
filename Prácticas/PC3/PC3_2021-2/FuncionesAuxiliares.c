/* 
 * Proyecto: PC3_2021-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 5 de junio de 2022, 03:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 120
#define NO_SE_ENCONTRO -1

FILE *abrirArchivo(const char *nombreDeArchivo, const char *modoDeApertura){
    FILE *arch = fopen(nombreDeArchivo,modoDeApertura);
    if(arch==NULL){
        printf("ERROR: No se pudo abrir el archivo %s\n",nombreDeArchivo);
        exit(1);
    }
    return arch;
}

void leerVentas(int *arrLibro, int *arrVentas, int *i){    
    FILE *arch = abrirArchivo("Ventas.txt","r");
    int libro, ventas, pos;
    while(1){
        fscanf(arch,"%d %d",&libro,&ventas);
        if(feof(arch)) break;
        pos = buscarRepeticion(libro,arrLibro,*i);        
        if(pos==NO_SE_ENCONTRO){
            arrLibro[*i]=libro;
            arrVentas[*i]=ventas;
            (*i)++;
        }else
            arrVentas[pos]+=ventas;      //Acumulamos la venta de libros        
    }    
    fclose(arch);
}

int buscarRepeticion(int codigo, int *arrCod, int cantCod){
    for(int i=0; i<cantCod; i++)
        if(codigo==arrCod[i]) return i;
    return NO_SE_ENCONTRO;
}

void ordenarLibros(int *arrLibro, int *arrVentas, int cantLibros){
    for(int i=0; i<cantLibros-1; i++)
        for(int j=i+1; j<cantLibros; j++)
            if(arrLibro[j]<arrLibro[i]){
                cambiarInt(arrLibro,i,j);
                cambiarInt(arrVentas,i,j);                
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

void leerLibros(int *arrLibro, char **arrNombreLibro, double *arrPrecioLibro,
                int cantLibros){    
    FILE *arch = abrirArchivo("Libros.txt","r");
    int libro, pos, nc;
    char nombreAux[100];
    while(1){
        fscanf(arch,"%d",&libro);
        if(feof(arch)) break;
        pos = buscarIndice(libro,arrLibro,cantLibros);
        if(pos!=NO_SE_ENCONTRO){
            leerNombreDelLibro(arch,nombreAux);
            nc=strlen(nombreAux);
            arrNombreLibro[pos]=(char*)malloc(sizeof(char)*(nc+1));
            strcpy(arrNombreLibro[pos],nombreAux);            
            fscanf(arch,"%lf",&arrPrecioLibro[pos]);
        }else
            while(fgetc(arch)!='\n');        
    }    
    fclose(arch);    
}

int buscarIndice(int codigo, int *arrCod, int cantCod){
    int limSup=cantCod-1, limInf=0, pm;
    while(1){
        if(limSup<limInf) return NO_SE_ENCONTRO;
        pm = (limSup+limInf)/2;
        if(codigo==arrCod[pm]) return pm;
        else if(codigo>arrCod[pm]) limInf=pm+1;
        else limSup=pm-1;       
    }
}

void leerNombreDelLibro(FILE *arch, char *arrNombre){    
    int condicion=1;
    char palabra[20], nombre[60]={};        
    while(condicion){
        fscanf(arch,"%s",palabra);  
        if(verificarUltimoNombre(palabra)) condicion=0;
        modificarPalabra(palabra);
        strcat(nombre,palabra);
    }
    strcpy(arrNombre,nombre);    
}

int verificarUltimoNombre(char *nombre){
    int i;
    for(i=0; nombre[i]; i++);
    if(nombre[i-1]==','){
        nombre[i-1]=0;
        return 1;
    }
    else return 0;
}

void modificarPalabra(char *palabra){    
    for(int i=0; palabra[i]; i++){
        if(i==3) palabra[i]=0;
        else if(i==0) palabra[i]=convertirMayuscula(palabra[i]);
        else if(palabra[i]==0) palabra[i]='X';
        else palabra[i]=convertirMinuscula(palabra[i]);
    }
}

char convertirMayuscula(char c){
    return c-=(c>='a'&&c<='z'?'a'-'A':0);
}

char convertirMinuscula(char c){
    return c+=(c>='A'&&c<='Z'?'a'-'A':0);
}

void calcularMontoTotal(int *arrVentas, double *arrPrecio, double *arrMonto,
                        int cantLibros){
    for(int i=0; i<cantLibros; i++)
        arrMonto[i]=arrVentas[i]*arrPrecio[i];    
}

void ordenarPorVentas(int *arrLibro, char **arrNombreLibro, int *arrVentas,
                      double *arrMonto, int cantLibros){    
    for(int i=0; i<cantLibros; i++)
        for(int j=i+1; j<cantLibros; j++)
            if(arrVentas[j]<arrVentas[i] || (arrVentas[j]==arrVentas[i] && 
                    arrMonto[j]>arrMonto[j])){
                cambiarInt(arrLibro,i,j);
                cambiarChar(arrNombreLibro,i,j);
                cambiarInt(arrVentas,i,j);
                cambiarDouble(arrMonto,i,j);                
            }
}

void cambiarChar(char **arr, int i, int j){
    char *aux = arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}

void procesarReporteDeEditorial(int *arrLibro, int *arrVentas, int cantLibros){    
    FILE *archAutores, *archLibros, *archReporte;
    archAutores = abrirArchivo("Autores.txt","r");
    archReporte = abrirArchivo("ReporteDeEditorial.txt","w");
    imprimirReporteDeEditorial(archAutores,archReporte,arrLibro,arrVentas,
            cantLibros);
    fclose(archAutores);
    fclose(archLibros);
    fclose(archReporte);    
}

void imprimirReporteDeEditorial(FILE *archAutores, FILE *archReporte, 
                                int *arrLibro, int *arrVentas, int cantLibros){    
    imprimirCabeceraPrincipal(archReporte);
    int autor;
    while(1){
        fscanf(archAutores,"%d",&autor);
        if(feof(archAutores)) break;
        imprimirNombreDelAutor(archAutores,archReporte);
        fprintf(archReporte,"%s %08d\n","DNI:",autor);
        imprimirLibrosVendidos(archAutores,archReporte,arrLibro,arrVentas,
                cantLibros);
        while(fgetc(archAutores)!='\n');        
    }    
}

void imprimirCabeceraPrincipal(FILE *archReporte){    
    fprintf(archReporte,"EDITORIAL XYZ\n");
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"VENTAS DE LIBROS POR AUTOR:\n");
    imprimirLinea(archReporte,'-',MAX_LINEA);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirNombreDelAutor(FILE *archAutores, FILE *archReporte){    
    //Nombres (puede tener varios nombres)
    char nombre[15], nombreCat[100]={};       
    while(1){
        fscanf(archAutores,"%s",nombre);        
        if(verificarUltimoNombre(nombre)){
            strcat(nombreCat,nombre);
            break;              
        }
        strcat(nombreCat,nombre);
        strcat(nombreCat," ");
    }
    nombreConMayusculas(nombreCat);
    //Apellidos (solo dos apellidos)
    char apellidoCat[30], apellidoAux[15];
    fscanf(archAutores,"%s %s",apellidoCat,apellidoAux);    
    strcat(apellidoCat," ");
    strcat(apellidoCat,apellidoAux);
    strcat(apellidoCat," ");    
    apellidoConMayusculas(apellidoCat);    
    strcat(apellidoCat,nombreCat);
    fprintf(archReporte,"Autor:  %-55s",apellidoCat);
}

void nombreConMayusculas(char *nombre){    
    for(int i=0; nombre[i]; i++){
        if(i==0) nombre[i] = convertirMayuscula(nombre[i]);
        else if(nombre[i]==' '){  
            i++;
            nombre[i] = convertirMayuscula(nombre[i]);            
        }else
            nombre[i] = convertirMinuscula(nombre[i]);        
    }
}

void apellidoConMayusculas(char *apellido){
    for(int i=0; apellido[i]; i++){
        if(i==0) apellido[i] = convertirMayuscula(apellido[i]);
        else if(apellido[i]==' '){  
            apellido[i] = '/';
            i++;
            apellido[i] = convertirMayuscula(apellido[i]);            
        }else
            apellido[i] = convertirMinuscula(apellido[i]);        
    }
}

void imprimirCabeceraDeLibrosVendidos(FILE *archReporte){
    imprimirLinea(archReporte,'-',MAX_LINEA);
    fprintf(archReporte,"Libros Vendidos:\n");
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"%s %10s %30s %20s\n","CODIGO","TITULO",
            "TOTAL VENDIDO","MONTO TOTAL");
    imprimirLinea(archReporte,'-',MAX_LINEA);    
}

void imprimirLibrosVendidos(FILE *archAutores, FILE *archReporte, int *arrLibro,
                            int *arrVentas, int cantLibros){    
    imprimirCabeceraDeLibrosVendidos(archReporte);    
    int libros[30], pos[30], i=0;
    double montoTotalVend=0.0, montoTotal, monto;
    while(1){
        fscanf(archAutores,"%d",libros[i]);
        i++;
        if(fgetc(archAutores)=='\n') break;
    }
    asignarPos(libros,pos,i,arrLibro,cantLibros);
    ordenarLibros(pos,libros,i);
    for(int j=0; j<i; j++){
        
        fprintf(archReporte,"%-10d",arrLibro[pos[j]]);
        imprimirNombreDelAutor(archAutores,archReporte);
        fprintf(archReporte,"%d\n",arrVentas[pos[j]]);
        
        
    }
    imprimirMontoTotalVendido(archReporte,montoTotalVend);
}

void asignarPos(int *arrL, int *arrPos, int cantL, int *arrLibro, int cantLibros){    
    for(int i=0; i<cantL; i++)
        for(int j=0; j<cantLibros; j++)
            if(arrL[i]==arrLibro[j]){
                arrPos[i]=j;
                break;
            }
}

void imprimirMontoTotalVendido(FILE *archReporte, double montoTotalVend){
    imprimirLinea(archReporte,'=',MAX_LINEA);
    fprintf(archReporte,"Monto total vendido: %10.2lf\n",montoTotalVend);
    imprimirLinea(archReporte,'=',MAX_LINEA);    
}