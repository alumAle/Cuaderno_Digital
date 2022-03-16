
#ifndef _MATERIAS_H_
#define _MATERIAS_H_

typedef struct{
    char id[5];
    char nombre[51];
    char abreviatura[4];
}materias;

int n_materias;
materias *v_materias;

void cargar_materias (materias **, int *);
void guardar_materias (materias *, int);

void crear_materias(materias **, int *);
void eliminar_materias(materias **, int *);
void listar_materias(materias *, int *);

#endif
