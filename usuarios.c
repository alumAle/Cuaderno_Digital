#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include <string.h>

#define PatchUsuarios "Files/Usuarios/usuarios.txt"

//cabecera: Usuarios* getUsuarios(int *arraySize);
//precondicion:El fichero usuarios.txt contenga elementos
//postcondicion:Devuelve la estructura cargada con los datos de los ficheros

Usuarios* getUsuarios(int *arraySize){
	FILE *fich;
	Usuarios *data;
	char c;
	int lineas=1,i,size;
	
	if(( fich = fopen(PatchUsuarios, "r+"))== NULL){
		printf("NO SE HA PODIDO ABRIR EL ARCHIVO DE USUARIOS, SE VA A CREAR UNO NUEVO.\n");
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
	
	//REALIZAMOS LA RESERVA DE MEMORIA PARA LA ESTRUCTURA "USUARIOS" teniendo en cuenta el numero de lineas 
	//que contiene el fichero.
	
	if((data=(Usuarios*)(malloc(lineas * sizeof(Usuarios)))) == NULL){
		printf("ERROR EN EL FALLO DE LA RESERVA DE MEMORIA PARA LA ESTRUCTURA USUARIOS.\n");
	}
	
	//LEEMOS EL FICHERO Y CARGAMOS LA ESTRUCTURA DINAMICA (YA INICIALIZADA CORRECTAMENTE) CON LOS DATOS DE USUARIOS.
	for (i=0; i<=lineas; i++){
		fscanf(fich, "%[^-]-%[^-]-%[^-]-%[^-]-%s\n",data[i].id,data[i].nombre,data[i].perfil,data[i].usuario,data[i].pass);
	}
	if(size==0) lineas =0; //si el tamaño del fichero es 0 pues no tendrá ninguna linea y por consiguiente estará vacío.
}
	fclose(fich); 		//cerramos el fichero.

	*arraySize = lineas; // el tamaño del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setUsuarios(Usuarios data, int i);
//precondicion 'data' debe de estar inicializado correctamente y 'i' debe de contener el numero de usuarios que hay en el sistema
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setUsuarios(Usuarios *data, int i){
	FILE *fich;
	int lineas;
	
	if((fich=fopen(PatchUsuarios, "w"))==NULL){
		printf("ERROR, NO SE ENCUENTRA EL FICHERO.\n");
	}
	else{
		for(lineas= 0; lineas < i; lineas ++){		//guardamos los datos actualizados en la estructura
			fprintf(fich,"%s-%s-%s-%s-%s",data[i].id,data[i].nombre,data[i].perfil,data[i].usuario,data[i].pass);
		}
		if(lineas+1 < i){
			fprintf(fich,"\n");
		}
	}
	fclose(fich);	//cerramos el fichero
}

//cabecera void listarUsuarios(Usuarios *data, int arraySize);
//precondicion 'data' debe estar inicializada correctamente y 'arraySize' tiene que contener el numero de usuarios que hay en el sistema
//postcondicion muestra por pantalla todos los usuarios del sistema
void listarUsuarios(Usuarios *data, int arraySize){
	int i;
	printf("ID-NOMBRE-PERFIL-USUARIO-PASSWORD\n");
	
	for(i=0; i<arraySize; i++){
		printf("%s-%s-%s-%s-%s",data[i].id,data[i].nombre,data[i].perfil,data[i].usuario,data[i].pass);
		printf("\n");
	}
}

