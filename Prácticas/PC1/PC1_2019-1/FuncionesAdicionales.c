/* 
 * Proyecto: PC1_2019-2
 * Archivo:  FuncionesAdicionales.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de marzo de 2022, 04:23 PM
 */

#include <stdio.h>
#include <stdlib.h>

int verificarFinDePrograma(int hora, int minuto, int segundo){    
    if(hora==0 && minuto==0 && segundo==0) return 1;
    else return 0;
}

void primerContadorEstadistico(int *ptr_datoEstadistico1, double volumenLluvia){
    if(volumenLluvia>150 && volumenLluvia<=300) (*ptr_datoEstadistico1)++;    
}   

void segundoContadorEstadistico(int *ptr_datoEstadistico2, int hora, int minuto){    
    if((hora==22 && minuto<30)||hora<22) (*ptr_datoEstadistico2)++;     
}

int calcularTiempo(int horaInicio, int minutoInicio, int segundoInicio, 
                   int horaFin, int minutoFin, int segundoFin){
    
    int tiempoInicio = (horaInicio*60*60) + (minutoInicio*60) + segundoInicio;
    int tiempoFin = (horaFin*60*60) + (minutoFin*60) + segundoFin;   
    return tiempoFin-tiempoInicio;
}

void tercerDatoEstadistico(int *i, double *suma, double tiempoEnSegundos,
                           double volumen){
    //            2 horas   30 minutos
    int tiempo = (2*60*60) + (30*60);
    if(tiempoEnSegundos>=tiempo){
        (*suma) += volumen;
        (*i)++;
    }
}

void cuartoDatoEstadistico(double *volumenMayorDuracion, int *mayorDuracion,
                           int tiempoEnSegundos, double volumen){    
    if(tiempoEnSegundos>(*mayorDuracion)) (*volumenMayorDuracion)=volumen;
}

void quintoDatoEstadistico(int *ptr_hora, int *ptr_minuto, int *ptr_segundo, 
                           double *menorVolumen, double volumenLluvia,
                           int tiempo){    
    int hora, minuto, segundo;
    if(volumenLluvia<(*menorVolumen)){
        convertirTiempo(&hora,&minuto,&segundo,tiempo);    
        *ptr_hora = hora;
        *ptr_minuto = minuto;
        *ptr_segundo = segundo;
    }
}

void convertirTiempo(int *hora, int *minuto, int *segundo, int tiempo){    
    *hora = (tiempo/60)/60;
    *minuto = ((*minuto)/60)-((*hora)*60);
    *segundo -= (*minuto)-((*hora)*60*60)-((*minuto)*60);
}

void imprimirEstadisticas(int datoEstadistico1, int datoEstadistico2,
        double datoEstadistico3, int hora, int minuto, int segundo){    
    printf("Resultados:\n");   
    printf("El número de precipitaciones que superaron los 150 pero que no "
            "sobrepasaron los 300 mm/m2: %d\n",datoEstadistico1);
    printf("El número de precipitaciones que terminaron antes de las "
            "10:30 pm. %d\n",datoEstadistico2);
    printf("El promedio de volumen precipitaciones que duraron más de 2horas y "
            "media: %.2lf mm/m2\n",datoEstadistico3);
    printf("El tiempo de aquella lluvia que tuvo el menor volumen:"
            " %02d:%02d:%02d\n",hora,minuto,segundo);
}