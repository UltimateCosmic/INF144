/* 
 * Proyecto: PC4_2021-1
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 01:34 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncionesAuxiliares.h"
#include "funcionesCadenas.h"
#include "StructBus.h"
#define MAX_LINEA 68
#define NO_SE_ENCONTRO -1

void leerBuses(struct Bus *arrBus, int *cantBuses){    
    FILE *arch = abrirArchivo("Buses.csv","r");
    int np, nc, i=0, tPas;
    char linea[200], *palabra[30], nombreMod[60];
    while(1){         
        //Lectura de la cadena
        leerCadena(linea,200,arch);
        if(feof(arch)) break;
        sacaPalabras(linea,palabra,&np,',');     
        
        //Placa
        nc = strlen(palabra[0]);
        arrBus[i].placa = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(arrBus[i].placa,palabra[0]); 
        //Chofer
        modificarNombreDelChofer(palabra[1],nombreMod);        
        nc = strlen(nombreMod);
        arrBus[i].chofer = (char *)malloc(sizeof(char)*(nc+1));
        strcpy(arrBus[i].chofer,nombreMod);
        
        //Numero máximo de pasajeros        
        arrBus[i].numeroDeAsientos = atoi(palabra[np-1]);
        //Numero de pasajeros (inicializamos en 0)    
        arrBus[i].numeroDePasajeros = 0;        
        //Numero total de pasajeros máximo (MAX_PASAJEROS*MAX_CIUDADES)
        tPas = arrBus[i].numeroDeAsientos*10;
        arrBus[i].pasajeros = (struct Pasajero *)malloc(sizeof(struct Pasajero)*(tPas));
        
        //Numero de ciudades
        arrBus[i].numeroDeCiudades = np-3;
        //Ciudades
        for(int j=0, k=2; j<arrBus[i].numeroDeCiudades; j++, k++){
            nc = strlen(palabra[k]);
            arrBus[i].ciudadesDestino[j] = (char *)malloc(sizeof(char)*(nc+1));
            strcpy(arrBus[i].ciudadesDestino[j],palabra[k]);
        }
        i++;
        //Free
        for(int l=0; l<np; l++) free(palabra[l]);
    }
    *cantBuses = i;
    fclose(arch);
}

void modificarNombreDelChofer(char *nombre, char *nombreMod){
    //Inicializamos el nombre para concatenar correctamente
    nombreMod[0]=0;
    int np;
    char *palabra[6];
    sacaPalabras(nombre,palabra,&np,' ');    
    for(int i=0; i<np; i++)
        corregirPalabra(palabra[i]);    
    for(int j=0; j<np; j++){        
        strcat(nombreMod,palabra[j]);
        strcat(nombreMod," ");
    }
}

void corregirPalabra(char *palabra){    
    for(int i=1; palabra[i]; i++){
        palabra[i] = convertirMinusc(palabra[i]);
        if(palabra[i]==' '||palabra[i]=='/'){
            if(palabra[i]=='/') palabra[i]=' ';
            i++;    //Respetamos el segundo nombre
        }
    }
}

char convertirMinusc(char c){
    return c+=(c>='A'&&c<='Z'?'a'-'A':0); 
}

void ordenarBuses(struct Bus *arrBus, int cantBuses){    
    for(int i=0; i<cantBuses-1; i++)
        for(int j=i+1; j<cantBuses; j++)
            if(arrBus[i].numeroDeCiudades<arrBus[j].numeroDeCiudades||
              (arrBus[i].numeroDeCiudades==arrBus[j].numeroDeCiudades &&
               arrBus[i].numeroDeAsientos>arrBus[j].numeroDeAsientos))
                cambiarStructBus(arrBus,i,j);    
}

void cambiarStructBus(struct Bus *arrBus, int i, int j){    
    struct Bus aux = arrBus[i];
    arrBus[i] = arrBus[j];
    arrBus[j] = aux;    
}

void leerPasajeros(struct Bus *arrBus, int cantBuses,
                   struct Pasajero *listaDeEspera, int *cantLista){
    FILE *arch = abrirArchivo("Pasajeros.csv","r");
    int np, nc, numPas, i, cl=0;
    char linea[200], *palabra[3], nombreMod[60]={};
    while(1){        
        //Lectura de la cadena
        leerCadena(linea,200,arch);
        if(feof(arch)) break;   
        sacaPalabras(linea,palabra,&np,',');        
        corregirPalabra(palabra[1]);        
        //Buscamos el primer bus del arreglo que pase por ciudad de destino
        i = buscarIndice(palabra[2],arrBus,cantBuses);        
        if(i!=NO_SE_ENCONTRO){            
            numPas = arrBus[i].numeroDePasajeros;            
            //DNI
            arrBus[i].pasajeros[numPas].dni = atoi(palabra[0]);            
            //Nombre
            nc = strlen(palabra[1]);
            arrBus[i].pasajeros[numPas].nombre = (char *)malloc(sizeof(char)*(nc+1));
            strcpy(arrBus[i].pasajeros[numPas].nombre,palabra[1]);                        
            //Destino
            nc = strlen(palabra[2]);
            arrBus[i].pasajeros[numPas].destino = (char *)malloc(sizeof(char)*(nc+1));
            strcpy(arrBus[i].pasajeros[numPas].destino,palabra[2]);                        
            arrBus[i].numeroDePasajeros++;
        }else{
            //DNI
            listaDeEspera[cl].dni = atoi(palabra[0]);
            //Nombre
            nc = strlen(palabra[1]);
            listaDeEspera[cl].nombre = (char *)malloc(sizeof(char)*(nc+1));
            strcpy(listaDeEspera[cl].nombre,palabra[1]);        
            //Destino
            nc = strlen(palabra[2]);
            listaDeEspera[cl].destino = (char *)malloc(sizeof(char)*(nc+1));
            strcpy(listaDeEspera[cl].destino,palabra[2]);        
            cl++;
        }
        //Free
        for(int j=0; j<np; j++) free(palabra[j]);
    }
    *cantLista = cl;
    fclose(arch);
}

int buscarIndice(char *ciudad, struct Bus *arrBus, int cantBuses){
    for(int i=0; i<cantBuses; i++)
        for(int j=0; j<arrBus[i].numeroDeCiudades; j++)
            if(strcmp(ciudad,arrBus[i].ciudadesDestino[j])==0 &&
                    arrBus[i].numeroDeAsientos>0){
                    arrBus[i].numeroDeAsientos--;
                    return i;
                }
    return NO_SE_ENCONTRO;
}

void imprimirReporteDePasajeros(struct Bus *arrBus, int cantBuses, 
                                struct Pasajero *listaDeEspera, int cantLista){    
    FILE *arch = abrirArchivo("ReporteDePasajeros.txt","w");
    imprimirCabeceraPrincipal(arch);    
    for(int i=0; i<cantBuses; i++){        
        fprintf(arch,"Vehiculo No. %d\n",i+1);
        fprintf(arch,"Placa: %s\n",arrBus[i].placa);
        fprintf(arch,"Chofer: %s\n",arrBus[i].chofer);        
        imprimirRuta(arch,arrBus[i]);
        imprimirPasajeros(arch,arrBus[i]);
        imprimirLinea(arch,'-',MAX_LINEA);
    }
    imprimirPasajerosEnListaDeEspera(arch,listaDeEspera,cantLista);
    fclose(arch);
}

void imprimirCabeceraPrincipal(FILE *arch){    
    fprintf(arch,"%43s\n","Lista de pasajeros");
    imprimirLinea(arch,'=',MAX_LINEA);
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);
}

void imprimirRuta(FILE *arch, struct Bus arrBus){
    fprintf(arch,"Ruta: ");
    for(int i=0; i<arrBus.numeroDeCiudades; i++){
        fprintf(arch,"%s",arrBus.ciudadesDestino[i]);
        if(i+1!=arrBus.numeroDeCiudades) fprintf(arch," - ");
    }
    fputc('\n',arch);
}

void imprimirPasajeros(FILE *arch, struct Bus arrBus){
    fprintf(arch,"Pasajeros:\n");
    for(int i=0; i<arrBus.numeroDeCiudades; i++){
        imprimirCabeceraDePasajeros(arch,arrBus.ciudadesDestino[i]);
        for(int j=0, k=1; j<arrBus.numeroDePasajeros; j++)
            if(strcmp(arrBus.pasajeros[j].destino,arrBus.ciudadesDestino[i])==0){
                fprintf(arch,"%-4d %08d %4c %s\n",k,arrBus.pasajeros[j].dni,
                        ' ',arrBus.pasajeros[j].nombre);
                k++;
            }
    }    
}

void imprimirCabeceraDePasajeros(FILE *arch, char *ciudad){    
    fprintf(arch,"%s:\n",ciudad);
    fprintf(arch,"%s %6s %14s\n","No.","DNI","Nombre");    
}

void imprimirPasajerosEnListaDeEspera(FILE *arch, struct Pasajero *listaDeEspera,
                                      int cantLista){    
    imprimirCabeceraDeListaDeEspera(arch);
    for(int i=0; i<cantLista; i++)
        fprintf(arch,"%3d %2c %08d %2c %-39s %s\n",i+1,' ',listaDeEspera[i].dni,
                ' ',listaDeEspera[i].nombre,listaDeEspera[i].destino);
}

void imprimirCabeceraDeListaDeEspera(FILE *arch){    
    fputc('\n',arch);
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"PASAJEROS EN LISTA DE ESPERA\n");
    imprimirLinea(arch,'-',MAX_LINEA);    
    fprintf(arch,"%s %7s %13s %40s\n","No.","DNI","Nombre","Destino");
}