#include <stdio.h>
#include <stdlib.h>
#include "Files/Configuracion/Config.h"

//DECLARACION DE FUNCIONES DEL MAIN
static void bienvenida();
static void despedida();

void main(){
	
	int nConfiguraciones;
	//IMPLEMENTACION DE FUNCIONES DE LOS MÓDULOS
	Configuracion *Configuraciones;

	Configuraciones= getConfiguracion(nConfiguraciones);

	bienvenida();
	//FALTAN TODOS LOS SETS Y EL MENÚ PARA ELEGIR SI ERES ADMIN O PROFESOR
	setConfiguracion(Configuraciones, nConfiguraciones);
	despedida();
	
	system("pause");
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
