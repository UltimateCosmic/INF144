/* 
 * Proyecto: Consolidado_de_cursos_LAB04
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 31 de mayo de 2022, 08:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_ALUMNOS 100
#define MAX_CURSOS 50

int main(int argc, char** argv) {

    //Archivo: Cursos.txt
    int arrCurso[MAX_CURSOS], cantCursos=0;
    double arrCredCurso[MAX_CURSOS];
    leerCursos(arrCurso,arrCredCurso,&cantCursos);
    
    //Archivo: Alumnos.txt
    int arrAlumno[MAX_ALUMNOS], cantAlumnos=0;
    double arrCredApro[MAX_ALUMNOS], arrCredDesa[MAX_ALUMNOS], 
            arrCredFalt[MAX_ALUMNOS];
    leerAlumnos(arrAlumno,arrCredApro,arrCredDesa,arrCredFalt,&cantAlumnos);
    
    //Archivo: Notas.txt
    int arrCursosApro[MAX_ALUMNOS]={}, arrCursosDesa[MAX_ALUMNOS]={}, 
            arrCantAproDeCurso[MAX_CURSOS]={}, arrCantDesaDeCurso[MAX_CURSOS]={};
    double arrPromPond[MAX_ALUMNOS]={};
    leerNotas(arrAlumno,arrCredApro,arrCredDesa,arrCredFalt,arrCursosApro,
            arrCursosDesa,arrPromPond,cantAlumnos,arrCurso,arrCredCurso,
            arrCantAproDeCurso,arrCantDesaDeCurso,cantCursos);
    
    //Archivo ReporteDeConsolidadoResultados.txt
    imprimirReporteDeConsolidado(arrCurso,arrCredCurso,arrCantAproDeCurso,
            arrCantDesaDeCurso,cantCursos,arrAlumno,arrCredApro,arrCredDesa,
            arrCredFalt,arrCursosApro,arrCursosDesa,arrPromPond,cantAlumnos);

    return (EXIT_SUCCESS);
}

