/* 
 * Proyecto: LAB6_2021-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 04:35 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"

int main(int argc, char** argv) {
    
    crearArchCursosBin("Cursos.csv","Cursos.bin");
    crearArchEscalasBin("Escalas.txt","Escalas.bin");
    crearArchAlumnosBin("Alumnos.csv","Alumnos.bin");    
    leerArchNotasCsv("Notas.csv","Alumnos.bin");
    calcularDatosArchAlumnosBin("Alumnos.bin");
    imprimirReporteDeCuentas("ReporteDeEstadoDeCuenta.txt","Alumnos.bin");
    
    return (EXIT_SUCCESS);
}

