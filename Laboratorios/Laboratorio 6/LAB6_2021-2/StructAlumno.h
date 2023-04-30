/* 
 * Proyecto: LAB6_2021-2
 * Archivo:  StructAlumno.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 04:38 AM
 */

#ifndef STRUCTALUMNO_H
#define STRUCTALUMNO_H
#include "StructCursoMatriculado.h"

struct Alumno{
    int codigo;
    char nombre[60];
    char escala[3];
    struct CursoMatriculado cursos[30];
    int numCursos;
    double promedio;
    double creditos;
    double totalPagado;
};

#endif /* STRUCTALUMNO_H */

