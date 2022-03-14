#include "alumnos.h"
#include "usuarios.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){

    //cargar_alumnos(&v_alumnos, &n_alumnos);
	cargar_usuarios(&v_usuarios, &n_usuarios);

    //crear_alumno(&v_alumnos, &n_alumnos);
    crear_usuario(&v_usuarios, &n_usuarios);

    //guardar_alumnos(v_alumnos, n_alumnos);
	guardar_usuarios(v_usuarios, n_usuarios);

    return 1;
}
