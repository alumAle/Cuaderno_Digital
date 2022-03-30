#include <stdio.h>
#ifndef CALIFICACIONES
#define CALIFICACIONES

typedef struct{
    char fecha[11];
    char desc[31];
    int id_mat;
    int id_alum;
    int calif;
}Calificacion;


Calificacion* getCalificaciones(int *arraySize);
void setCalificaciones (Calificacion* data, int i);

void listarCalificaciones(Calificacion *data, int arraySize);
void imprimeCalificacion(Calificacion c);

/*Funcion que reciba id_alumno y id_materia y devuelva la lista de las calificaciones que tiene ese alumno*/
void listaCalificacionesAlumno(Calificacion *data, int arraySize, int id_alum, int id_mat);
/*Menu*/
void menuProfeCalificaciones(Calificacion** calificaciones, int* nCalificaciones, int id_alum, int id_mat);
/*Modificar calificacion*/
void modificarCalificacion(Calificacion** data, int nCalificaciones, int id_alum, int id_mat);
/*Borrar calificacion*/
void eliminarCalificacion(Calificacion** data, int* nCalificaciones, int id_alum, int id_mat);
/*Añadir calificacion*/
void addCalificacion(Calificacion** calificaciones, int* nCalificaciones, int id_alum, int id_mat);
/*Funciones necesarias para addCalificacion y modificarCalificacion*/
void cambiarFecha(int id, Calificacion** data);
void cambiarDesc(int id,Calificacion** data);
void cambiarCalif(int id, Calificacion** data);
#endif