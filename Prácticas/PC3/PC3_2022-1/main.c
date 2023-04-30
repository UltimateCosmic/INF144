/* 
 * Proyecto: 2022-1_ArregosConCadenas_Practica03
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de junio de 2022, 07:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_CURSOS 100
#define MAX_ALUMNOS 100

int main(int argc, char** argv) {

    //Archivo: Cursos.txt
    int cantCursos=0;
    double credCurso[MAX_CURSOS];
    char *codCurso[MAX_CURSOS], *nomCurso[MAX_CURSOS];    
    leerCursos(codCurso,nomCurso,credCurso,&cantCursos);
    
    //Archivo: Alumnos.txt
    int cantAlumnos=0;
    char *codAlumno[MAX_ALUMNOS], *nomAlumno[MAX_ALUMNOS];
    leerAlumnos(codAlumno,nomAlumno,&cantAlumnos);
    
    //Archivo: Notas.txt y ReportedeConsolidadoDeCursos.txt    
    imprimirReportedeConsolidado(codCurso,nomCurso,credCurso,cantCursos,
            codAlumno,nomAlumno,cantAlumnos);    
    
    return (EXIT_SUCCESS);
}

