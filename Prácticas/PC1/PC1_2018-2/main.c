/* 
 * Proyecto: PC1_2018-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 29 de marzo de 2022, 11:39 AM
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int sexo, edad, canal, horaInicio, horaFin, total, suma, suma2, i, j, k;
    double promedio1, porcentaje, promedio2;

    total=suma=suma2=i=j=k=0;
    printf("Ingrese las encuestas:\n");
        
    while(1){        
        scanf("%d %d %d %d %d",&sexo,&edad,&canal,&horaInicio,&horaFin);
        if(verificarFin(sexo,edad,canal,horaInicio,horaFin)) break;
        primerPromedio(&suma,&i,canal,edad);        
        hombresMenores(&total,&k,edad,sexo,horaInicio,horaFin);
        segundoPromedio(&suma2,&j,horaInicio,horaFin,edad,sexo);
    }
    promedio1 = (double)suma/i;
    promedio2 = (double)suma2/j;
    porcentaje = calcularPorcentaje(total,k);
    
    printf("\nResultados:\n");
    printf("Promedio de edades que prefieren los canales "
            "del 50 en adelante: %.1lf anos\n",promedio1);
    printf("Porcentaje de hombres menores de 12 años que "
            "ve mas de 3 hora de TV: %.1lf\n",porcentaje);
    printf("Promedio de tiempo que ven la TV las mujeres "
            "entre 35 y 50 anos: %.1lf horas\n",promedio2);
    
    return (EXIT_SUCCESS);
}

/*                          <Control de Lectura>
 
 1. (2 puntos) Se han buscado diferentes alternativas para representar en el 
    computador los números enteros con signo. Explique en que consistieron 
    esos métodos, muestre además con un ejemplo en cada caso por qué se 
    desecharon unos formatos y se aceptó otro.
 
 * Bit más significativo representando el signo, complemento, complemento a 2.
 * El primer método consiste en la representación de un número negativo usando
 * el primer bit como representación del signo (0 si es positivo y 1 si es
 * negativo). El segundo método consiste en cambiar los 0s por los 1s. El
 * último método es igual que el segundo solo que se suma +1 en binario. El
 * problema que existe con los dos primeros métodos es que hay un desbordamiento
 * a la hora de realizar operaciones y en el otro método no ocurre eso.
 
 2. (2 puntos) En la instalación del NetBeans, se debe instalar por separado 
    el compilador de C. NetBeans recomienda se instale uno de dos compiladores.
    Indique cuáles son esos compiladores y en qué se diferencian.
 
 * Se recomienda que se instale el MinGW, no hay otro compilador que recomiende
 * instalar el NetBeans. Por ende no hay diferencia.

 3. (1 punto) En la instalación del NetBeans, se debe editar las “variables de 
    entorno”, explique por qué se debe hacer esto.

 * Para enlazar el NetBeans con el compilador MinGW (añadimos el directorio).

 4. (1 punto) Cuando se quiere ejecutar un programa en NetBeans, se debe cambiar 
    el tipo de consola al “terminal externo”, indique por qué se debe realizar 
    esta acción.

 * Si corremos el programa en el terminal interno no podremos usar funciones
 * como el 'scanf'. Es por eso que lo corremos en la ventana cmd o en el terminal
 * externo que nos proporciona el NetBeans. 
 */