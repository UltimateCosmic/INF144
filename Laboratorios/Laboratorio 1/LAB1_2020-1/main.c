/* 
 * Proyecto: LAB1_2020-1
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 30 de abril de 2022, 11:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX 100

int main(int argc, char** argv) {
    
    //Lectura del anio y del ciclo
    int anio, ciclo;
    printf("Ingrese el anio y ciclo: ");
    scanf("%d %d",&anio,&ciclo);    
    
    //Archivo Asistencia_clases.txt
    int arrCodCurso[MAX]={0}, arrCantHorarios[MAX]={0}, 
            arrCantAlumnos[MAX]={0}, cantCursos=0;
    double arrPromPonderado[MAX]={0};        
    leerArrArchAsistenciaClases(arrCodCurso,arrCantHorarios,arrPromPonderado,
            arrCantAlumnos,&cantCursos,anio,ciclo);    
    
    //Archivo Encuestas_Alumnos.txt
    double arrPromEncuesta[MAX]={0}, arrPorcEncuestaAjust[MAX]={0};
    leerArrArchEncuestasAlumnos(anio,ciclo,arrPromEncuesta,arrPorcEncuestaAjust,
            cantCursos,arrCodCurso);
    calcularPorcEncuestaAjustada(arrPorcEncuestaAjust,cantCursos,
            arrPromPonderado,arrPromEncuesta);
    
    //Ordenar arreglos (por el promedio de la encuesta ajustada)
    ordenarArreglos(arrCodCurso,arrCantHorarios,arrCantAlumnos,arrPromPonderado,
            arrPromEncuesta,arrPorcEncuestaAjust,cantCursos);
    
    //Impresion de reporte
    abrirReporte(arrCodCurso,arrCantHorarios,arrCantAlumnos,arrPromPonderado,
            arrPromEncuesta,arrPorcEncuestaAjust,cantCursos,anio,ciclo);
    
    return (EXIT_SUCCESS);
}

