/* 
 * Proyecto: LAB6_2021-2
 * Archivo:  funcionesAuxiliares.c
 * Autor:    Johan Carlo Amador Egoavil
 * Codigo:   20203350
 * 
 * Creado el 28 de junio de 2022, 04:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "funcionesCadenas.h"
#include "StructCurso.h"
#include "StructEscala.h"
#include "StructAlumno.h"
#include "StructCursoMatriculado.h"
#include "StructCurso.h"
#define MAX_LINEA 105

void crearArchCursosBin(const char *nomArchTxt, const char *nomArchBin){    
    FILE *archTxt, *archBin;
    archTxt = abrirArchivo(nomArchTxt,"r");
    archBin = abrirArchivo(nomArchBin,"wb");    
    struct Curso curso;
    int numPal;
    char cadena[200], *pal[3];
    while(1){        
        leerCadena(cadena,200,archTxt);
        if(feof(archTxt)) break;
        sacaPalabras(cadena,pal,&numPal,',');        
        strcpy(curso.codigo,pal[0]);       
        strcpy(curso.nombre,pal[1]);    
        curso.creditos=atof(pal[2]);
        fwrite(&curso,sizeof(struct Curso),1,archBin);
        for(int i=0; i<numPal; i++) free(pal[i]);
    }   
    fclose(archTxt);
    fclose(archBin);
}

void crearArchEscalasBin(const char *nomArchTxt, const char *nomArchBin){    
    FILE *archTxt, *archBin;
    archTxt = abrirArchivo(nomArchTxt,"r");
    archBin = abrirArchivo(nomArchBin,"wb");    
    struct Escala escala;
    int aaaa, s;
    char cod[3];
    double cred;
    while(1){        
        fscanf(archTxt,"%s",cod);
        if(feof(archTxt)) break;                
        fscanf(archTxt,"%lf %d-%d",&cred,&aaaa,&s);        
        strcpy(escala.codigo,cod);
        escala.valorCredito=cred;
        escala.semestre=aaaa*10+s;
        fwrite(&escala,sizeof(struct Escala),1,archBin);
    }   
    fclose(archTxt);
    fclose(archBin);
}

void crearArchAlumnosBin(const char *nomArchTxt, const char *nomArchBin){    
    FILE *archTxt, *archBin;
    archTxt = abrirArchivo(nomArchTxt,"r");
    archBin = abrirArchivo(nomArchBin,"wb");    
    struct Alumno alumno;
    int numPal;
    char cadena[200], *pal[3];
    while(1){        
        leerCadena(cadena,200,archTxt);
        if(feof(archTxt)) break;                
        sacaPalabras(cadena,pal,&numPal,',');
        alumno.codigo=atoi(pal[0]);
        strcpy(alumno.nombre,pal[1]);
        strcpy(alumno.escala,pal[2]);
        alumno.numCursos=alumno.promedio=alumno.creditos=alumno.totalPagado=0;
        fwrite(&alumno,sizeof(struct Alumno),1,archBin);
        for(int i=0; i<numPal; i++) free(pal[i]);
    }   
    fclose(archTxt);
    fclose(archBin);
}

void leerArchNotasCsv(const char *nomArchCsv, const char *nomArchBin){    
    FILE *archCsv, *archBin;
    archCsv = abrirArchivo(nomArchCsv,"r");
    archBin = abrirArchivo(nomArchBin,"rb+");    
    int numPal;
    char cadena[100], *pal[4];
    while(1){
        leerCadena(cadena,100,archCsv);
        if(feof(archCsv)) break;
        sacaPalabras(cadena,pal,&numPal,',');
        completarDatosDeAlumnos(pal,archBin);
        for(int i=0; i<numPal; i++) free(pal[i]);
    }
    fclose(archCsv);
    fclose(archBin);
}

void completarDatosDeAlumnos(char **pal, FILE *archBin){  
    struct Alumno alumno;    
    int tamReg, tamArch, cantReg, codAlumno, dd, mm, aa;
    tamReg = sizeof(struct Alumno);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);        
    codAlumno=atoi(pal[0]);
    extraerFecha(pal[3],&dd,&mm,&aa);    
    for(int i=0; i<cantReg; i++){        
        fread(&alumno,tamReg,1,archBin);         
        if(alumno.codigo==codAlumno){            
            strcpy(alumno.cursos[alumno.numCursos].codigo,pal[1]);
            alumno.cursos[alumno.numCursos].nota=atoi(pal[2]);
            alumno.cursos[alumno.numCursos].fecha=juntarFecha(dd,mm,aa);            
            alumno.numCursos++;            
            fseek(archBin,tamReg*i,SEEK_SET);            
            fwrite(&alumno,tamReg,1,archBin);
            fflush(archBin);
            break;
        }        
    }    
}

void datosDelArchivo(FILE *archBin, int tamReg, int *tamArch, int *cantReg){    
    fseek(archBin,0,SEEK_END);  //Cursor al final
    *tamArch = ftell(archBin);
    *cantReg = (*tamArch)/tamReg;
    fseek(archBin,0,SEEK_SET);
}

void extraerFecha(char *cadena, int *dd, int *mm, int *aa){    
    int numPal;
    char *fecha[3];
    sacaPalabras(cadena,fecha,&numPal,'/');
    *dd=atoi(fecha[0]);
    *mm=atoi(fecha[1]);
    *aa=atoi(fecha[2]);
}

int juntarFecha(int dd, int mm, int aa){
    return aa*10000+mm*100+dd;    
}

void calcularDatosArchAlumnosBin(const char *nomArchBin){
    FILE *archBin;
    archBin = abrirArchivo(nomArchBin,"rb+");    
    struct Alumno alumno;
    int tamReg, tamArch, cantReg;
    double cantCred;
    tamReg = sizeof(struct Alumno);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);
    for(int i=0; i<cantReg; i++){
        fread(&alumno,tamReg,1,archBin);                
        for(int j=0; j<alumno.numCursos; j++){
            cantCred=buscarCreditos(alumno.cursos[j],"Cursos.bin");            
            alumno.promedio+=alumno.cursos[j].nota;            
            if(alumno.cursos[j].nota>=11) alumno.creditos+=cantCred;
            alumno.totalPagado+=calcularPago(alumno.cursos[j],
                    alumno.escala,"Escalas.bin")*cantCred;
        }        
        alumno.promedio/=alumno.numCursos;        
        fseek(archBin,tamReg*i,SEEK_SET);            
        fwrite(&alumno,tamReg,1,archBin);
        fflush(archBin);
    }
    fclose(archBin);
}

double buscarCreditos(struct CursoMatriculado cursoMat, char const *nomArchBin){  
    FILE *archBin=abrirArchivo(nomArchBin,"rb");
    struct Curso curso;
    int tamReg, tamArch, cantReg;
    tamReg = sizeof(struct Curso);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);
    for(int i=0; i<cantReg; i++){
        fread(&curso,tamReg,1,archBin);                
        if(strcmp(curso.codigo,cursoMat.codigo)==0){
            fclose(archBin);
            return curso.creditos;            
        }
    }
    fclose(archBin);
    printf("ERROR: No se encontró el curso\n");
    exit(1);
}

double calcularPago(struct CursoMatriculado cursoMat, char *alumnoEscala,
                    char const *nomArchBin){
    FILE *archBin=abrirArchivo(nomArchBin,"rb");
    struct Escala escala;
    int tamReg, tamArch, cantReg, aaaa, s, dd, mm, aa;
    tamReg = sizeof(struct Escala);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);
    separarFecha(cursoMat.fecha,&dd,&mm,&aa);
    for(int i=0; i<cantReg; i++){
        fread(&escala,tamReg,1,archBin);
        separarSemestre(escala.semestre,&aaaa,&s);        
        if(strcmp(alumnoEscala,escala.codigo)==0 && verificarCiclo(aa,aaaa,mm,s)){                        
            fclose(archBin);
            return escala.valorCredito;            
        }
    }
    fclose(archBin);
    printf("ERROR: No se encontró el curso\n");
    exit(1);
}

void separarFecha(int fecha, int *dd, int *mm, int *aa){    
    *aa = fecha/10000;
    fecha-=(*aa)*10000;
    *mm = fecha/100;
    *dd = fecha-(*mm)*100;
}

void separarSemestre(int semestre, int *aaaa, int *s){    
    *s = semestre%10;
    *aaaa = semestre/10;    
}

int verificarCiclo(int aa, int aaaa, int mm, int s){    
    if(aa==aaaa){        
        if(s==0 && mm>=1 && mm<=3)          return 1;
        else if(s==1 && mm>=4 && mm<=7)     return 1;            
        else if(s==2 && mm>=8 && mm<=12)    return 1;
    }
    return 0;
}

void imprimirReporteDeCuentas(char const *nomArchTxt,char const *nomArchBin){
    FILE *archTxt, *archBin;
    archTxt=abrirArchivo(nomArchTxt,"w");
    archBin=abrirArchivo(nomArchBin,"rb");   
    imprimirCabecera(archTxt);
    struct Alumno alumno;
    int tamReg, tamArch, cantReg;
    double totalRecaudado=0.0;
    tamReg = sizeof(struct Alumno);
    datosDelArchivo(archBin,tamReg,&tamArch,&cantReg);
    for(int i=0; i<cantReg; i++){
        fread(&alumno,tamReg,1,archBin);
        fprintf(archTxt,"%2d) %-11d %-37s",i+1,alumno.codigo,alumno.nombre); 
        fprintf(archTxt,"%s %12.2lf %14.2lf %17.2lf\n",alumno.escala,
                alumno.promedio,alumno.creditos,alumno.totalPagado);
        totalRecaudado+=alumno.totalPagado;        
    }
    imprimirTotalRecaudado(archTxt,totalRecaudado);
    fclose(archTxt);
    fclose(archBin);
}

void imprimirCabecera(FILE *arch){    
    fprintf(arch,"%55s\n","INSTITUTO ABC");
    fprintf(arch,"%65s\n","Estado de cuenta de los alumnos");
    imprimirLinea(arch,'=',MAX_LINEA);
    fprintf(arch,"%10s %11s %35s %10s %20s %13s\n","Codigo","Nombre","Escala",
            "Promedio","Créditos Aprobados","Total pagado");
}

void imprimirLinea(FILE *arch, char c, int cantVeces){
    for(int i=0; i<cantVeces; i++) fputc(c,arch);
    fputc('\n',arch);    
}

void imprimirTotalRecaudado(FILE *arch, double totalRecaudado){
    imprimirLinea(arch,'-',MAX_LINEA);
    fprintf(arch,"Total recaudado: %.2lf\n",totalRecaudado);
}