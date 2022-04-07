#include <stdio.h>
#include <stdlib.h>
#include "Horario.h"
#include <string.h>

#define PatchHorario "Files/Horario/Horario.h"

//cabecera Horario* getHorario(int *arraysize)
//precondicion el fichero debe de tener elementos dentro
//postcondicion carga la estructura con los elementos del fichero

Horario *Horarios(int *arraySize){
	FILE *fich;
	Horario *data;
	char c;
	int lineas=1,i,size;
	
	if((fich = fopen(PatchHorario,"r+"))==NULL){
		printf("NO SE HA PODIDO ABRIR EL FICHERO DE HORARIO, SE CREARA UNO NUEVO\n");
	}
	else{
		fseek(fich,0,SEEK_END);
		size=ftell(fich);   //guardamos el tamaño del fichero
		rewind(fich); //volvemos al inicio del fichero
		
		
		while((c=fgetc(fich))!= EOF){ //Realizar bucle mientras que el fichero no se termine "End Of File"
			if(c=='\n'); //comprobamos que es un salto de linea
			lineas ++; // incrementamos el valor del numero de lineas que tiene el fichero
		}
		
	  rewind(fich); //volvemos al inicio del fichero
	  
	  //AHORA REALIZAMOS LA RESERVA DE MEMORIA PARA INTRODUCIR LOS ELEMENTOS DEL FICHERO EN LA ESTRUCTURA Y COMPROBAMOS QUE SEA CORRECTA
	  if((data=(Horario*)(malloc(lineas * sizeof(Horario)))) == NULL){
		printf("ERROR EN EL FALLO DE LA RESERVA DE MEMORIA PARA LA ESTRUCTURA HORARIO.\n");
	}
		//LEEMOS EL FICHERO Y CARGAMOS EN LA ESTRUCTURA TODOS LOS ELEMENTOS DEL FICHERO HORARIO
	for (i=0; i<=lineas; i++){
		fscanf(fich, "%s-%s-%s-%s-%s\n",data[i].id_prof,data[i].dia,data[i].hora,data[i].id_mat,data[i].grupo);
	}
	if(size==0) lineas =0; //comprobamos que el tamaño del fichero es 0 para ver si este está vacío
}
	fclose(fich); //cerramos el fichero.

	*arraySize = lineas; // el tamaÃ±o del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setHorario(Horario* data);
//precondicion 'data' debe de estar inicializado correctamente
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setHorarios(Horario *data, int i ){
	FILE *fich;
	int l,exit;
	
	
	if((fich = fopen(PatchHorario, "w")) == NULL){ //Comprobamos que se puede abrir el fichero o que existe
		printf("Error, no se encuentra el fichero.\n");
	}else{
		for(l = 0; l < i; l++){		//	Itera para todas las lineas
			fprintf(fich, "%s-%s-%s-%s-%s",data[l].id_prof,data[l].dia,data[l].hora,data[l].hora,data[l].id_mat,data[l].grupo);
			
			if(l+1 < i){			//	evita \n al inicio del fichero
				fprintf(fich, "\n");
			}
		}
		fclose(fich);
	}	
	fclose(fich);	//cerramos el fichero
}

// Cabecera void listaHorario (Horario *Horario, int nHorarios)
// Precondicion recibe un array de tipo Equipo,inicializado, y el numero de equipos que contiene
// Postcondicion imprime el numero de equipos totales en el fichero
void listarHorarios (Horario *Horarios, int nHorarios){
    int i;
    printf("--------------\n");
    for(i=0;i<nHorarios;i++){          //recorre el array de horarios
	 imprimirHorario(Horarios[i]);
    printf("--------------\n");
    }
    printf("Total: %d horarios\n", nHorarios);
}

// Cabecera void imprimirHorarios(horarios h)
// Precondicion recibe un horario
// Postcondicion imprime por pantalla el horario
void imprimirHorarios(Horario h){
   printf("\tprofesor:%s\n dia:%s\n hora:$s\n materia:%s\n grupo:%s\n",h.id_prof,h.hora,h.dia,h.id_mat,h.grupo);
}

