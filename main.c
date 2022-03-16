#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Files/Configuracion/Config.h"
static void bienvenida();
static void despedida();

void main(){
	
	int nConfiguraciones;
	//IMPLEMENTACION DE FUNCIONES DE LOS MÓDULOS
	Configuracion *Configuraciones;





	Configuraciones= getConfiguracion(&nConfiguraciones);
	setConfiguracion(Configuraciones, nConfiguraciones);



	bienvenida();
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
