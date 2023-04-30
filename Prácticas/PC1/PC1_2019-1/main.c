/* 
 * Proyecto: PC1_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de marzo de 2022, 04:18 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FuncionesAdicionales.h"

int main(int argc, char** argv) {
    
    // Datos de lectura:
    int horaInicio, minutoInicio, segundoInicio, horaFin, minutoFin, segundoFin;
    double volumenLluvia;

    // Estadística:
    int datoEstadistico1=0, datoEstadistico2=0;
    int tiempoEnSegundos, hora, minuto, segundo, i=1, mayorDuracion=0;
    double datoEstadistico3, suma=0, volumenMayorDuracion, menorVolumen=999999;
    
    printf("Ingrese las precipitaciones:\n"); 
    
    while(1){        
        
        scanf("%d %d %d %d %d %d %lf", &horaInicio, &minutoInicio,
                &segundoInicio, &horaFin, &minutoFin, &segundoFin,
                &volumenLluvia);    
        
        if(verificarFinDePrograma(horaInicio, minutoInicio, segundoInicio) &&
           verificarFinDePrograma(horaFin, minutoFin, segundoFin) &&
           fabs(volumenLluvia-0.0)<=0.0001) break;
        
        // Evaluamos las estadísticas.
        primerContadorEstadistico(&datoEstadistico1,volumenLluvia);               
        segundoContadorEstadistico(&datoEstadistico2,horaFin,minutoFin);        
        tiempoEnSegundos = calcularTiempo(horaInicio,minutoInicio,segundoInicio,
                horaFin,minutoFin,segundoFin);
        tercerDatoEstadistico(&i,&suma,tiempoEnSegundos, volumenLluvia);     
        cuartoDatoEstadistico(&volumenMayorDuracion,&mayorDuracion,
                tiempoEnSegundos,volumenLluvia);
        quintoDatoEstadistico(&hora,&minuto,&segundo,&menorVolumen,
                              volumenLluvia,tiempoEnSegundos);
    }
    
    datoEstadistico3 = suma/i;
    imprimirEstadisticas(datoEstadistico1,datoEstadistico2,datoEstadistico3,
            hora,minuto,segundo);
    
    return (EXIT_SUCCESS);
}