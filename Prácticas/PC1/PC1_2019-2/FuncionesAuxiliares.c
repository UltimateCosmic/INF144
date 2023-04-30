/* 
 * Proyecto: PC1_2019-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 8 de abril de 2022, 01:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FuncionesAuxiliares.h"
#define PRECISION 0.0001

void leerDatos(int *resultado1, double *resultado2, double *resultado3, 
               int *resultado4_1, int *resultado4_2, int *resultado5){
    
    int dni, dia, mes, anio, pais, ciudad, numero, hora, minuto, 
            segundo, i=0, j=0, mayorTiempo=0;
    double tarifa, mayorTarifa=0, menorTarifa=999, menorTarifa2=999;
    
    printf("Ingrese los datos de los clientes:\n");
    
    while(1){     
        
        scanf("%d",&dni);
        
        if(feof(stdin)) break;
        
        scanf("%d/%d/%d",&dia,&mes,&anio);
        scanf("%1d%2d%6d",&pais,&ciudad,&numero);
        scanf("%d:%d:%d",&hora,&minuto,&segundo);
        scanf("%lf",&tarifa);
                        
        if(verificarFinDeDatos(dni,dia,mes,anio,pais,ciudad,numero,hora,minuto,
                segundo,tarifa)) break;
        
        actualizarResultado1(resultado1,ciudad,pais);
        actualizarResultado2(resultado2,dia,mes,anio,hora,minuto,segundo,tarifa);
        actualizarResultado3(resultado3,ciudad,dia,mes,anio,tarifa,&j);
        actualizarResultado4(resultado4_1,resultado4_2,dni,
                calcularPromedioTarifa(hora,minuto,segundo,tarifa),
                &mayorTarifa,&menorTarifa);
        actualizarResultado5(resultado5,hora,minuto,segundo,tarifa,dni,
                &mayorTiempo,&menorTarifa2);                
        
        i++;
    }  
    (*resultado2) = (*resultado2)/i*100;
    (*resultado3) /= j;
}

void actualizarResultado1(int *resultado1, int ciudad, int pais){    
    if((ciudad==21 || ciudad==45 || ciudad==67) && pais==3) (*resultado1)++;    
}

void actualizarResultado2(double *resultado2, int dia, int mes, int anio, 
                          int hora, int minuto, int segundo, double tarifa){    
    
    int tiempoDeServicio = calcularTiempo(dia,mes,anio);
    int tiempoFechaHoy = calcularTiempo(8,4,2022);          //Fecha de hoy.
    
    if(((tiempoFechaHoy-tiempoDeServicio)<=calcularTiempo(0,0,5)) && 
            calcularPromedioTarifa(hora,minuto,segundo,tarifa)>50.0)
        (*resultado2)++;    
}

void actualizarResultado3(double *resultado3, int ciudad, int dia, int mes, 
                          int anio, double tarifa, int *j){    
    
    if((calcularTiempo(dia,mes,anio)<calcularTiempo(1,7,2004)) && ciudad==60){
        (*resultado3) += tarifa;
        (*j)++;
    }    
}

void actualizarResultado4(int *resultado4_1, int *resultado4_2, int dni,
               double promedioTarifa, double *mayorTarifa, double *menorTarifa){    
    actualizarMayorTarifa(resultado4_1,mayorTarifa,dni,promedioTarifa);
    actualizarMenorTarifa(resultado4_2,menorTarifa,dni,promedioTarifa);
}

void actualizarMayorTarifa(int *resultado4_1, double *mayorTarifa, int dni, 
                           double promedioTarifa){    
    if(promedioTarifa>=(*mayorTarifa)){
        (*resultado4_1) = dni;    
        (*mayorTarifa) = promedioTarifa;
    }
}

void actualizarMenorTarifa(int *resultado4_2, double *menorTarifa, int dni, 
                           double promedioTarifa){    
    if(promedioTarifa<=(*menorTarifa)){
        (*resultado4_2) = dni;
        (*menorTarifa) = promedioTarifa;
    }
}

void actualizarResultado5(int *resultado5, int hora, int minuto, int segundo, 
                          int tarifa, int dni, int *mayorTiempo, 
                          double *menorTarifa){
    
    int tiempo = hora*60*60 + minuto*60 + segundo;
    
    if(tiempo>=(*mayorTiempo) && tarifa<=(*menorTarifa)){        
        (*resultado5) = dni;
        (*mayorTiempo) = tiempo;
        (*menorTarifa) = tarifa;
    }
}

double calcularPromedioTarifa(int hora, int minuto, int segundo, double tarifa){
    return (hora*60 + minuto + (double)segundo/60)*tarifa;
}

// Por ejemplo:     03/06/2019  ->  20190603
int calcularTiempo(int dia, int mes, int anio){
    return anio*10000 + mes*100 + dia;    
}

int verificarFinDeDatos(int dni, int dia, int mes, int anio, int pais, 
                        int ciudad, int numero, int hora, int minuto, 
                        int segundo, double tarifa){    
    if(dni==0 && dia==0 && mes==0 && anio==0 && pais==0 && ciudad==0 && 
            numero==0 && hora==0 && minuto==0 && segundo==0 && 
            tarifa<=PRECISION) return 1;
    else return 0;
}

void imprimirResultados(int resultado1, double resultado2, double resultado3, 
        int resultado4_1, int resultado4_2, int resultado5){
    
    printf("\nResultados:\n");
    
    printf("El número de clientes que reside en las ciudades "
            "21, 45 y 67 del pais 3: %d\n",resultado1);
    
    printf("El porcentaje de clientes que tiene menos de 5 años de servicio y "
            "que pagan en promedio más de 50.00 diarios: %.2lf%c\n",
            resultado2,'%');
    
    printf("La tarifa promedio de los clientes que viven en la ciudad 60 y que "
            "ingresaron al servicio antes del 1/7/2004: %.4lf\n",resultado3);
        
    printf("El cliente que más pagó y el que menos pago por su consumo "
            "promedio:\n");
    
    printf("Mas: %10d\n",resultado4_1);
    printf("Menos: %7d\n",resultado4_2);
    
    printf("El cliente con mayor tiempo promedio en llamadas pero con menor "
            "tarifa: %d\n",resultado5);
}