/* 
 * Proyecto: PC1.2_2019-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 26 de marzo de 2022, 07:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {

    int jugadorA, jugadorB, jugadorInicial;
    printf("Ingrese los jugadores del partido y "
            "el jugador que inicia el saque:\n");    
    scanf("%d %d %d", &jugadorA, &jugadorB, &jugadorInicial);
    
    int i=1, ganador, victoriasJugadorA=0, victoriasJugadorB=0, puntoA, puntoB, 
            puntoSaqueA, puntoSaqueB, puntoAuxiliarA, puntoAuxiliarB;
    int a=1, b=3;    
    
    while(1){
        
        printf("Ingrese el detalle del puntaje en el set %d\n",i);        
        puntoSaqueA=0;
        puntoSaqueB=0;
        
        int j=1;        
        while(1){            
                       
            scanf("%d %d",&puntoA, &puntoB);  
            
            if(j==1){
                puntoAuxiliarA = puntoA;
                puntoAuxiliarB = puntoB;
            }
            
            /*Puntos en las jugadas que tuvo el saque*/            
            if(puntoA>puntoAuxiliarA && verificarSaque(j,a)) puntoSaqueA++;
            else if(puntoB>puntoAuxiliarB && verificarSaque(j,b)) puntoSaqueB++;           
            
            puntoAuxiliarA = puntoA;
            puntoAuxiliarB = puntoB;            
                         
            if(puntoA-puntoB>=2 && puntoA>=10 && puntoB>=10){
                ganador = jugadorA;
                victoriasJugadorA++;
                break;
            }
            else if(puntoB-puntoA>=2 && puntoA>=10 && puntoB>=10){
                ganador = jugadorB;
                victoriasJugadorB++;
                break;
            }                    
            else if(puntoA==11 && puntoB<10){
                ganador = jugadorA;
                victoriasJugadorA++;  
                break;
            }
            else if(puntoB==11 && puntoA<10){
                ganador = jugadorB;
                victoriasJugadorB++; 
                break;
            }
            j++;
        }

        printf("\nEl ganador del set %d es el jugador %d\n",i,ganador);
        printf("El jugador %d hizo %d puntos\n",jugadorA,puntoA);
        printf("El jugador %d hizo %d puntos\n",jugadorB,puntoB);
        printf("El jugador %d hizo %d puntos en las jugadas "
                "que tuvo el saque\n",jugadorA,puntoSaqueA);
        printf("El jugador %d hizo %d puntos en las jugadas "
                "que tuvo el saque\n\n",jugadorB,puntoSaqueB);
        
        // Condición de fin:
        if(victoriasJugadorA>=3){
            ganador = jugadorA;
            break;
        }else if(victoriasJugadorB>=3){
            ganador = jugadorB;
            break;
        }
        
        i++;        
        if(esPar(i)){
            a = 3;
            b = 1;
        }else{
            a = 1;
            b = 3;
        }        
    }
    
    imprimirResumenDelPartido(ganador, jugadorA, jugadorB, victoriasJugadorA,
                              victoriasJugadorB);
    return (EXIT_SUCCESS);
}