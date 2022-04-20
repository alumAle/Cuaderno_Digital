#include <stdio.h>
#ifndef HORARIOS
#define HORARIOS

typedef struct{
  int id_prof;
  int dia;
  int hora;
  int id_mat;
  char grupo[11];
}Horario;

Horario* getHorarios(int *arraySize);
void setHorarios(Horario* data, int i);
void crearhorario(Horario** Horarios, int *nHorarios,int id_prof);
void eliminarHorario(Horario** Horarios, int *nHorarios, int id_prof);
void modificarHorarioProfe(Horario** Horarios, int nHorarios, int id_prof);
void imprimeHorario(Horario *h , int );
void listarHorarioProfe(Horario* Horarios, int nHorarios, int id_prof);
void cambiarId(int id, Horario** Horarios);
void cambiarDia(int id, Horario** Horarios);
void cambiarHora(int id, Horario** Horarios);
void cambiarMat(int id, Horario** Horarios);
void cambiarGrupo(int id, Horario** Horarios);

#endif // !HORARIO
