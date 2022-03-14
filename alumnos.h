#ifndef _ALUMNOS_H_
#define _ALUMNOS_H_

typedef struct{
    char id[7];
    char nombre[21];
    char direccion[31];
    char localidad[31];
    char curso[31];
    char grupo[11];
}alumnos;

int n_alumnos;
alumnos *v_alumnos;

void cargar_alumnos (alumnos **, int *);
void guardar_alumnos (alumnos *, int);

void crear_alumno(alumnos **, int *);

#endif
