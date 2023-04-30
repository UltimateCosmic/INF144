/* 
 * Proyecto: LAB2_2019-2_H0431
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 03:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 112
#define MAX_ESPACIO 35
#define FECHA_HOY 20220418

void imprimirListado(FILE *archAlumnos, FILE *archListado){
     
    fprintf(archListado,"LISTADO DE ALUMNOS\n");
    fprintf(archListado,"\n%s %13s %47s %15s %24s\n","CODIGO","NOMBRE",
            "FECHA DE NACIMIENTO","EDAD","LONGITUD DEL NOMBRE");
    imprimirLinea(archListado,'=',MAX_LINEA);
    int cantTotalDeAlumnos=0;
    imprimirAlumnos(archAlumnos,archListado,&cantTotalDeAlumnos);
    imprimirLinea(archListado,'-',MAX_LINEA);
    fprintf(archListado,"Cantidad total de alumnos: %d\n",cantTotalDeAlumnos);
}

void imprimirAlumnos(FILE *archAlumnos, FILE *archListado, int *cantAlumnos){
    
    int codigo, dd, mm, aaaa, longitudNombre, edad;    
    while(1){        
        fscanf(archAlumnos,"%d",&codigo);
        if(feof(archAlumnos)) break;        
        fprintf(archListado,"%07d %2c",codigo,' ');
        longitudNombre = imprimirNombre(archAlumnos,archListado);
        imprimirEspacios(archListado,longitudNombre);
        fscanf(archAlumnos,"%d/%d/%d",&dd,&mm,&aaaa);
        edad = imprimirFecha(dd,mm,aaaa,archListado);
        fprintf(archListado,"%7d %11d caracteres\n",edad,longitudNombre);
        (*cantAlumnos)++;
    }    
}

int imprimirNombre(FILE *archAlumnos, FILE *archListado){
    
    int cantCaracteres=0, cantEspacios=0;
    char letra;
    
    while(1){
        
        while((letra=fgetc(archAlumnos))==' ');        
        
        if(letra>='1' && letra<='9'){
            ungetc(letra,archAlumnos);
            break;
        }        
        convertirLetraAMayuscula(&letra);   //Primera letra (Nombre/Apellido)
        fputc(letra,archListado);
        cantCaracteres++;
        
        while((letra=fgetc(archAlumnos))!=' '){            
            convertirLetraAMinuscula(&letra);
            fputc(letra,archListado);
            if(letra==',') break;
            cantCaracteres++;
        }
        if(letra!=','){
            fputc(' ',archListado);
            cantEspacios++;
        }
    }  
    if(cantEspacios==2) fputc(' ',archListado);    
    return cantCaracteres;
}

void convertirLetraAMayuscula(char *letra){    
    if((*letra)>='a' && (*letra)<='z')                  
        (*letra)-=32;    
}

void convertirLetraAMinuscula(char *letra){
    if((*letra)>='A' && (*letra)<='Z')                  
        (*letra)+=32;    
}

void imprimirEspacios(FILE *archListado, int longitudNombre){    
    for(int i=0; i<MAX_ESPACIO-longitudNombre; i++) fputc(' ',archListado);    
}

int imprimirFecha(int dd, int mm, int aaaa, FILE *archListado){    
    
    fprintf(archListado,"%02d, de ",dd);
    
    if(mm==1)
        fprintf(archListado,"enero del %04d     ",aaaa);
    else if(mm==2)
        fprintf(archListado,"febrero del %04d   ",aaaa);
    else if(mm==3)
        fprintf(archListado,"marzo del %04d     ",aaaa);
    else if(mm==4)
        fprintf(archListado,"abril del %04d     ",aaaa);
    else if(mm==5)
        fprintf(archListado,"mayo del %04d      ",aaaa);
    else if(mm==6)
        fprintf(archListado,"junio del %04d     ",aaaa);
    else if(mm==7)
        fprintf(archListado,"julio del %04d     ",aaaa);
    else if(mm==8)
        fprintf(archListado,"agosto del %04d    ",aaaa);
    else if(mm==9)
        fprintf(archListado,"septiembre del %04d",aaaa);
    else if(mm==10)
        fprintf(archListado,"octuvbre del %04d  ",aaaa);
    else if(mm==11)
        fprintf(archListado,"noviembre del %04d ",aaaa);
    else if(mm==12)
        fprintf(archListado,"diciembre del %04d ",aaaa);    
    
    int fechaDeNacimiento = convertirFecha(dd,mm,aaaa); 
    return (FECHA_HOY-fechaDeNacimiento)/10000;
}

int convertirFecha(int dd, int mm, int aaaa){
    return aaaa*10000 + mm*100 + dd;
}

void imprimirLinea(FILE *archListado, char caracter, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(caracter,archListado);
    fputc('\n',archListado);
}

void cerrarArchivos(FILE *archAlumnos, FILE *archListado){
    fclose(archAlumnos);
    fclose(archListado);        
}