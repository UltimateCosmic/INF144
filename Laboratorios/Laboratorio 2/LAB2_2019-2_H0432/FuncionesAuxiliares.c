/* 
 * Proyecto: LAB2_2019-2_H0432
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 18 de abril de 2022, 04:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_LINEA 124
#define MAX_NOMBRE 40
#define FECHA_HOY 20220418

void imprimirListado(FILE *archAlumnos, FILE *archListado){
    
    fprintf(archListado,"LISTADO DE ALUMNOS\n\n");
    fprintf(archListado,"%s %15s %48s %24s %25s\n","CODIGO","NOMBRE",
            "FECHA DE NACIMIENTO","EDAD POR CUMPLIR","LONGITUD DEL NOMBRE");
    imprimirLinea(archListado,'=',MAX_LINEA);
    int cantTotalAlumnos = imprimirAlumnos(archAlumnos,archListado);
    imprimirLinea(archListado,'-',MAX_LINEA);
    fprintf(archListado,"Cantidad total de alumnos: %d\n",cantTotalAlumnos);
}

int imprimirAlumnos(FILE *archAlumnos, FILE *archListado){
    
    int cantAlumnos=0, codigo, dd, mm, aaaa, longitudDelNombre, edadPorCumplir;
    
    while(1){        
        fscanf(archAlumnos,"%d",&codigo);
        if(feof(archAlumnos)) break;        
        fprintf(archListado,"%07d   ",codigo);
        longitudDelNombre = imprimirNombreAlumno(archAlumnos,archListado);
        imprimirEspacios(archListado,MAX_NOMBRE-longitudDelNombre);
        fscanf(archAlumnos,"%d/%d/%d",&dd,&mm,&aaaa);
        edadPorCumplir = imprimirFechaDeNacimiento(archListado,dd,mm,aaaa);
        fprintf(archListado,"%10d %15d caracteres\n",edadPorCumplir,
                longitudDelNombre);
        cantAlumnos++;
    }    
    return cantAlumnos;
}

int imprimirNombreAlumno(FILE *archAlumnos, FILE *archListado){
    
    int cantCaracteres=0, cantEspacios=0;
    char letra;     
    
    while(1){
        
        while((letra=fgetc(archAlumnos))==' ');        
        if(letra>='1' && letra<='9'){
            ungetc(letra,archAlumnos);
            break;            
        }        
        convertirLetraMayuscula(&letra);     //Primera letra
        fputc(letra,archListado);
        cantCaracteres++;
        
        while((letra = fgetc(archAlumnos))!=' '){       
            convertirLetraMinuscula(&letra);
            if(letra>='a'&&letra<='z'){
                fputc(letra,archListado);
                cantCaracteres++;
            }else if(letra==','){
                fputc(letra,archListado);
                break;
            }
        }
        if(letra!=','){
            fputc(' ',archListado);
            cantEspacios++;
        }
    }
    if(cantEspacios==2) fputc(' ',archListado);    
    return cantCaracteres;
}

void imprimirEspacios(FILE *archListado, int cantVeces){    
    for(int i=0; i<cantVeces; i++) fputc(' ',archListado);    
}

int imprimirFechaDeNacimiento(FILE *archListado, int dd, int mm, int aaaa){
      
    fprintf(archListado,"%2d de ",dd);    
    if(mm==1)  fprintf(archListado,"de enero del %d     ",aaaa);
    if(mm==2)  fprintf(archListado,"de febrero del %d   ",aaaa);
    if(mm==3)  fprintf(archListado,"de marzo del %d     ",aaaa);
    if(mm==4)  fprintf(archListado,"de abril del %d     ",aaaa);
    if(mm==5)  fprintf(archListado,"de mayo del %d      ",aaaa);
    if(mm==6)  fprintf(archListado,"de junio del %d     ",aaaa);
    if(mm==7)  fprintf(archListado,"de julio del %d     ",aaaa);
    if(mm==8)  fprintf(archListado,"de agosto del %d    ",aaaa);
    if(mm==9)  fprintf(archListado,"de septiembre del %d",aaaa);
    if(mm==10) fprintf(archListado,"de octubre del %d   ",aaaa);
    if(mm==11) fprintf(archListado,"de noviembre del %d ",aaaa);
    if(mm==12) fprintf(archListado,"de diciembre del %d ",aaaa);
    
    int fechaDeNacimiento = calcularFecha(dd,mm,aaaa);
    return (FECHA_HOY-fechaDeNacimiento)/10000+1;
}

int calcularFecha(int dd, int mm, int aaaa){
    return aaaa*10000+mm*100+dd;
}

void convertirLetraMayuscula(char *c){
    if(((*c)>='a')&&((*c)<='z')) (*c)-=32;
}

void convertirLetraMinuscula(char *c){
    if(((*c)>='A')&&((*c)<='Z')) (*c)+=32;
}

void imprimirLinea(FILE *archListado, char caracter, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(caracter,archListado);
    fputc('\n',archListado);
}

void cerrarListado(FILE *archAlumnos, FILE *archListado){
    fclose(archAlumnos);
    fclose(archListado);    
}