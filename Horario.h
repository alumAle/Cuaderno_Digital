#include <stdio.h>
#ifndef HORARIOS
#define HORARIOS

typedef struct{
  char id_prof[3];
  char dia[5];
  char hora[6];
  char id_mat[4];
  char grupo[10];
}Horario;

Horario* getHorario(int *arraySize);
void setHorario(Horario* data, int i);
void listarhorario(Horario* Horarios, int nHorarios);
void editarHorario();
void eliminarHorario();
void crearHorario();






#endif // !HORARIO

