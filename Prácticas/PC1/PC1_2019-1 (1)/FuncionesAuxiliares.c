/* 
 * Proyecto: PC1.2_2019-2
 * Archivo:  FuncionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de marzo de 2022, 07:09 PM
 */

#include <stdio.h>
#include <stdlib.h>

void imprimirResumenDelPartido(int ganador, int jugadorA, int jugadorB, 
                               int victoriasJugadorA, int victoriasJugadorB){
    printf("RESUMEN DEL PARTIDO\n");
    printf("El ganador del partido es el jugador: %d\n",ganador);
    printf("El jugador %d gano %d sets\n",jugadorA,victoriasJugadorA);
    printf("El jugador %d gano %d sets\n",jugadorB,victoriasJugadorB);
}

int verificarSaque(int iteracion, int iInicial){    
    int i=iInicial;    
    while(1){        
        if(i==iteracion||(i+1)==iteracion) return 1;
        else if(i>iteracion) return 0;
        i+=4;
    }    
}

int esPar(int num){    
    if(num%2==0)
        return 1;
    else
        return 0;
}