#ifndef _USUARIOS_H_
#define _USUARIOS_H_

typedef struct{
    char id[4];
    char nombre[21];
    char perfil[14];
    char usuario[6];
    char pass[9];
}Usuarios;


Usuarios* getUsuarios(int *arraySize);
void setUsuarios (Usuarios* data, int i);
void listarUsuarios(Usuarios *data, int arraySize);

#endif
