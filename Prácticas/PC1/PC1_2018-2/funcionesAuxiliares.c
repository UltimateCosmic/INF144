/* 
 * Proyecto: PC1_2018-2
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 11:57 AM
 */

#include <stdio.h>
#include <stdlib.h>

int verificarFin(int sexo, int edad, int canal, int horaInicio, int horaFin){
    if(sexo==-1 && edad==-1 && canal==-1 && horaInicio==-1 && horaFin==-1)
        return 1;
    else return 0;    
}

void primerPromedio(int *suma, int *cantidad, int canal, int edad){
    if(canal>=50){
        (*suma) += edad;  
        (*cantidad)++;
    }
}

void hombresMenores(int *total, int *k, int edad, int sexo, 
                    int horaInicio, int horaFin){    
    if(sexo==0 && edad<12){        
        if(horaFin-horaInicio>3) *k++;
        *total++;
    }
}

void segundoPromedio(int *suma2, int *j, int horaInicio, int horaFin, 
                     int edad, int sexo){    
    if(sexo==1 && edad<50 && edad>35){       
        (*suma2) += (horaFin-horaInicio);
        (*j)++;
    }
}

double calcularPorcentaje(int total, int x){
    return (double)x*100/total;
}