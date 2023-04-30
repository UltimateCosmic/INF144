/* 
 * Proyecto: PC4_2021-1
 * Archivo:  StructBus.h
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 14 de junio de 2022, 01:20 AM
 */

#ifndef STRUCTBUS_H
#define STRUCTBUS_H
#include "StructPasajero.h"
#define MAX_CIUDADES 10

struct Bus{
    char *placa;
    char *chofer;
    int numeroDeAsientos;
    char *ciudadesDestino[MAX_CIUDADES];
    int numeroDeCiudades;
    struct Pasajero *pasajeros;
    int numeroDePasajeros;
};

#endif /* STRUCTBUS_H */

