
#ifndef FUNCIONESCADENAS_H
#define FUNCIONESCADENAS_H

FILE *abrirArchivo(const char *,const char*);
void leerCadena(char *,int , FILE *);
char *leeCadenaExacta(FILE *arch);
void sacaPalabras(char *,char **,int *,char );
#endif /* FUNCIONESCADENAS_H */

