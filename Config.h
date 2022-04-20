#include <stdio.h>
#ifndef CONFIGS
#define CONFIGS

typedef struct{
 char nombreConfig[30];
 int valorConfig; 
}Configuracion;

Configuracion* getConfiguracion(int *arraySize);
void setConfiguracion(Configuracion* data, int i);
void listarConfiguracion (Configuracion* Configuraciones, int nConfiguraciones);
void editarConfiguracion(Configuracion** Configuraciones, int nConfiguraciones);
void menuAdminConfiguracion(Configuracion** Configuraciones, int nConfiguraciones);
int valorConfig (Configuracion* c, int nC, char const *var);
void imprimeConfiguracion(Configuracion *, int );
#endif // !CONFIGS
