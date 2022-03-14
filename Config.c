#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include <string.h>

#define PatchConfig "Files/Configuracion/Config.txt"

//cabecera: Configuracion* getConfiguracion(int arraySize);
//precondicion:Que el fichero contenga elementos dentro
//postcondicion:Devuelve la estructura cargada con los datos de los ficheros

Configuracion* getConfiguracion(int arraySize){
	FILE *fich;
	Configuracion *data;
	char c;
	int lineas=1,i,size;
	
	if(fich=fopen(PatchConfig, "r+")==NULL){
		printf("NO SE HA PODIDO ABRIR EL ARCHIVO DE CONFIGURACIÓN, SE VA A CREAR UNO NUEVO.\n");
	}
	
	else{
	fseek(fich,0,SEEK_END);     //ponemos el puntero al inicio del fichero.
	size=ftell(fich);			//guardamos el tamaño del fichero.
	rewind(fich);		//ponemos de nuevo el puntero al inicio del fichero.
		
	while((c=fgetc(fich))!=EOF){ //contamos las lineas del fichero siempre y cuando este no se haya acabado
		if(c=='\n'){			 // y se produzca un salto de linea que indica que esa linea se ha acabado.
			lineas ++;
		}
	}
	rewind(fich); //volvemos a poner el puntero al inicio del fichero.
	
	//REALIZAMOS LA RESERVA DE MEMORIA PARA LA ESTRUCTURA "CONFIGURACION" teniendo en cuenta el numero de lineas 
	//que contiene el fichero.
	
	if((data=(Configuracion*)(malloc(lineas * sizeof(Configuracion)))) == NULL){
		printf("ERROR EN EL FALLO DE LA RESERVA DE MEMORIA PARA LA ESTRUCTURA CONFIGURACION.\n");
	}
	
	//LEEMOS EL FICHERO Y CARGAMOS LA ESTRUCTURA DINAMICA (YA INICIALIZADA CORRECTAMENTE) CON LOS DATOS DE CONFIGURACION.
	for (i=0; i<=lineas; i++){
		fscanf(fich, "%[^-]-%d\n",data[i].nombreConfig,&(data[i].valorConfig));
	}
	
	if(size==0) lineas =0; //si el tamaño del fichero es 0 pues no tendrá ninguna linea y por consiguiente estará vacío.
}
	fclose(fich); 		//cerramos el fichero.

	*arraySize = lineas; // el tamaño del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

