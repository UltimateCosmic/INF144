/* 
 * Proyecto: PC1_2020-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 12:54 PM
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int numCuenta, numClientesAtendidos=0, cantDepositos, cantRetiros, centinela=1;
    double saldoInicial, haber, debe, monto;
    char estado, transaccion;

    while(centinela){
        
        printf("Ingrese el numero de cuenta y el saldo inicial: ");
        scanf("%d %lf",&numCuenta,&saldoInicial);
        
        cantDepositos = cantRetiros = 0;
        
        if(saldoInicial>=0){
            haber=saldoInicial;
            debe=0;
            estado='H';
        }else{
            haber=0;
            debe=-saldoInicial;
            estado='I';               
        }
        
        while(1){
            
            printf("Estado de la cuenta: %d\n",numCuenta);
            printf("%s %10s %10s %10s\n","SALDO INICIAL","HABER","DEBE","ESTADO");
            printf("%.2lf %13.2lf %14.2lf %5c\n\n",saldoInicial,haber,debe,estado);
            
            printf("Ingrese una transaccion: ");
            scanf(" %c %lf",&transaccion,&monto);
            
            if(transaccion=='C'){                
                if(estado=='H')
                    printf("SALDO FINAL: %.2lf - Cuenta habilitada\n",haber);
                else
                    printf("SALDO FINAL: %.2lf - Cuenta inhabilitada\n",debe*-1);
                printf("Cantidad de depositos: %d",cantDepositos);
                printf("%25s %d\n\n","Cantidad de retiros:",cantRetiros);              
                break;
            }
            else if(transaccion=='F'){
                centinela=0;
                break;
            }
            else if(transaccion=='D'){
                
                if(debe>=0){
                    debe -= monto;
                    estado = 'I';
                    if(debe<=0){
                        haber = -debe;
                        debe=0;
                        estado = 'H';
                    }                    
                }
                cantDepositos++;                
            }else if(transaccion=='R'){
                
                if(haber>=0){                    
                    haber -= monto;
                    estado = 'H';
                    if(haber<=0){
                        debe += haber*-1;
                        
                        haber = 0;
                        estado = 'I';
                    }
                }
                cantRetiros++;
            }    
        }        
        numClientesAtendidos++;
    }
    printf("**FIN DE PROCESO***\n");
    printf("Numero de clientes atendidos: %d\n",numClientesAtendidos);

    return (EXIT_SUCCESS);
}

