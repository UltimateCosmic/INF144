/* 
 * Proyecto: LAB5_2020-2
 * Archivo:  main.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 6 de junio de 2022, 04:51 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesAuxiliares.h"
#define MAX_ALUMNOS 100
#define MAX_CURSOS 200

int main(int argc, char** argv) {

    //Archivo: Alumnos.txt
    int codAlumno[MAX_ALUMNOS], cantAlumnos=0;
    char *nomAlumno[MAX_ALUMNOS];
    leerAlumnos(codAlumno,nomAlumno,&cantAlumnos);
    ordenarAlumnos(codAlumno,nomAlumno,cantAlumnos);
    
    //Archivo: Cursos.txt
    int cantCursos=0;
    char *codCurso[MAX_CURSOS], *codFacu[MAX_CURSOS], *nomCurso[MAX_CURSOS];
    double credCurso[MAX_CURSOS];
    leerCursos(codCurso,credCurso,codFacu,nomCurso,&cantCursos);
    ordenarCursos(codCurso,credCurso,codFacu,nomCurso,cantCursos);    
    
    //Archivo: Notas.txt
    double promGen[MAX_ALUMNOS]={}, promApro[MAX_ALUMNOS]={},
            credApro[MAX_ALUMNOS]={}, credDesa[MAX_ALUMNOS]={};
    int cantApro[MAX_CURSOS]={}, cantDesa[MAX_CURSOS]={},
            cantCurApro[MAX_ALUMNOS]={}, cantCurDesa[MAX_ALUMNOS]={};
    leerNotas(codAlumno,cantAlumnos,codCurso,cantCursos,promGen,promApro,
            credApro,credDesa,cantApro,cantDesa,cantCurApro,cantCurDesa,
            credCurso);
    calcularPromedios(promGen,promApro,cantCurApro,cantCurDesa,cantAlumnos);    
    
    //Consola: Reporte
    imprimirReporte(codAlumno,nomAlumno,promGen,promApro,credApro,credDesa,
            cantAlumnos,codCurso,nomCurso,credCurso,codFacu,cantApro,cantDesa);
    
    return (EXIT_SUCCESS);
}

