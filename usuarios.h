#include <stdio.h>
#ifndef USUARIOS
#define USUARIOS

typedef struct{
    int id;
    char nombre[21];
    char perfil[14];
    char usuario[6];
    char pass[9];
}Usuario;


Usuario* getUsuarios(int *arraySize);
void setUsuarios (Usuario* data, int i);

void menuAdminUsuarios(Usuario** usuarios, int* nUsuarios);
void listarUsuarios(Usuario *data, int arraySize);
void imprimeUsuario(Usuario u);
void addUsuario(Usuario** usuarios, int* nUsuarios);
void cambiarUsuarioUsuario(int idVec, Usuario** usuarios, int nUsuarios);
void cambiarPasswordUsuario(int idVec, Usuario** usuarios, int nUsuarios);
void cambiarNombreCompletoUsuario(int idVec, Usuario** usuarios, int nUsuarios);
void cambiarPerfilUsuario(int idVec, Usuario** usuarios, int nUsuarios);
int existeNickUsuario(Usuario** usuarios, int nUsuarios, char* nick, int indice);
int existeNombreUsuario(Usuario** usuarios, int nUsuarios, char* usuario, int indice);
void modificarUsuario(Usuario** usuarios, int nUsuarios);
void eliminarUsuario(Usuario** usuarios, int* nUsuarios);

#endif
