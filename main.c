#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Files/Configuracion/Config.h"
#include "Files/Usuarios/usuarios.h"
#include "Files/Calificaciones/calificaciones.h"
static void bienvenida();
static void despedida();

void main(){
	
	int nConfiguraciones, nUsuarios, nCalificaciones;
	//IMPLEMENTACION DE FUNCIONES DE LOS MÓDULOS
	Configuracion *Configuraciones;
	Usuario *usuarios;
	Calificacion *calificaciones;


	Configuraciones= getConfiguracion(&nConfiguraciones);
	usuarios = getUsuarios(&nUsuarios);
	calificaciones = getCalificaciones(&nCalificaciones);
	bienvenida();
	
	setConfiguracion(Configuraciones, nConfiguraciones);
	setUsuarios(usuarios, nUsuarios);
	setCalificaciones(calificaciones, nCalificaciones);


	despedida();
	
	system("pause");
	return 0;
}

//Cabecera: static void bienvenida
//Precondicion: ninguna
//Postcondición: muestra el mensaje de bienvenida
static void bienvenida(){
	printf("-------------------------------------\n");
	printf("BIENVENIDO A TU CUARDERNO DIGITAL: \n");
	printf("-------------------------------------\n");
}


//Cabecera: static void despedida
//Precondicion: se debe colocar despues del set(cuando los datos actualizados se guardan en los ficheros)
//postcondicion: muestra el mensaje de despedida.
static void despedida(){
		printf("-------------------------------------\n");
		printf("SALIENDO DEL CUARDENO, GUARDANDO DATOS...");
		printf("\n-------------------------------------\n");
		printf("\nGuardado completado\n");
}
