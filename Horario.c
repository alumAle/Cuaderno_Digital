#include <stdio.h>
#include <stdlib.h>
#include "Horario.h"
#include <string.h>

#define PatchHorario "Files/Horario/Horario.txt"

//cabecera Horario* getHorario(int *arraysize)
//precondicion el fichero debe de tener elementos dentro
//postcondicion carga la estructura con los elementos del fichero

Horario* getHorarios(int *arraySize){
	FILE *fich;
	Horario *data;
	char c;
	int lineas=1,i,size;
	
	if((fich = fopen(PatchHorario,"r+"))==NULL){
		printf("NO SE HA PODIDO ABRIR EL FICHERO DE HORARIO, SE CREARA UNO NUEVO\n");
	}
	else{
		fseek(fich,0,SEEK_END);
		size=ftell(fich);   //guardamos el tamaÃƒÂ±o del fichero
		rewind(fich); //volvemos al inicio del fichero
		
		
		while((c=fgetc(fich))!= EOF){ //Realizar bucle mientras que el fichero no se termine "End Of File"
			if(c=='\n'){//comprobamos que es un salto de linea
				lineas ++; 
			}// incrementamos el valor del numero de lineas que tiene el fichero
		}
		
	  rewind(fich); //volvemos al inicio del fichero
	  
	  //AHORA REALIZAMOS LA RESERVA DE MEMORIA PARA INTRODUCIR LOS ELEMENTOS DEL FICHERO EN LA ESTRUCTURA Y COMPROBAMOS QUE SEA CORRECTA
	  if((data=(Horario*)(malloc(lineas * sizeof(Horario)))) == NULL){
			printf("ERROR EN EL FALLO DE LA RESERVA DE MEMORIA PARA LA ESTRUCTURA HORARIO.\n");
		}
		//LEEMOS EL FICHERO Y CARGAMOS EN LA ESTRUCTURA TODOS LOS ELEMENTOS DEL FICHERO HORARIO
	for (i=0; i<=lineas; i++){
		fscanf(fich, "%d-%d-%d-%d-%s\n", &(data[i].id_prof), &(data[i].dia), &(data[i].hora), &(data[i].id_mat), data[i].grupo);
	}
	if(size==0) lineas =0; //comprobamos que el tamaÃƒÂ±o del fichero es 0 para ver si este estÃƒÂ¡ vacÃƒÂ­o
}
	fclose(fich); //cerramos el fichero.

	*arraySize = lineas; // el tamaÃƒÆ’Ã‚Â±o del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setHorario(Horario* data);
//precondicion 'data' debe de estar inicializado correctamente
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setHorarios(Horario *data, int i ){
	FILE *fich;
	int l;
	
	if((fich = fopen(PatchHorario, "w")) == NULL){ //Comprobamos que se puede abrir el fichero o que existe
		printf("Error, no se encuentra el fichero.\n");
	}
	else{
		for(l = 0; l < i; l++){		//	Itera para todas las lineas
			fprintf(fich, "%.3d-%d-%d-%.4d-%s", data[l].id_prof, data[l].dia, data[l].hora, data[l].id_mat, data[l].grupo);
			
			if(l+1 < i){			//	evita \n al inicio del fichero
				fprintf(fich, "\n");
			}
		}
	}	
	fclose(fich);	//cerramos el fichero
}
//cabecera void listarhorario(Horario* Horarios, int nHorarios);
//precondicion recibe un array de tipo horario ,inicializado, y el tamaÃƒÃ±o del array
//postcondicion imprime las configuraciones actuales
void listarhorario(Horario *Horarios, int nHorarios){
    int i;
    printf("HORARIO ACTUAL\n");
    for(i=0;i<nHorarios;i++){
    	printf("Horario %d\n: ",i+1);
        imprimeHorario(Horarios,i);
        printf("\n");
    }
}

//cabecera void listarhorario(Horario* Horarios, int nHorarios);
//precondicion recibe un array de tipo horario ,inicializado, y el tamaÃƒÃ±o del array
//postcondicion imprime las configuraciones actuales
void listarhorarioProfe(Horario *Horarios, int nHorarios, int id_prof){
    int i;
    printf("HORARIO ACTUAL\n");
    for(i=0;i<nHorarios;i++){
    	if(id_prof==Horarios[i].id_prof){
    		printf("Horario %d:\n",i+1);
        	imprimeHorario(Horarios,i);
        	printf("\n");
		}
    }
}

void imprimeHorario(Horario *h, int i){
	printf("  %.3d-%d-%d-%.4d-%s",h[i].id_prof,h[i].dia,h[i].hora,h[i].id_mat,h[i].grupo);
}

//cabecera modificarHorarioProfe(Horario** Horarios, int nHorarios, int id_prof):
//precondicion recibe un array de tipo Horario inicializado y el tamaÃƒÆ’Ã‚Â±o del array
//postcondicion imprime por pantalla opciones para modificar los horarios de un profesor
void modificarHorarioProfe(Horario** Horarios, int nHorarios, int id_prof){
	int aux;
	
	printf("MODIFICAR HORARIO\n\n");
	
	listarhorarioProfe(&**Horarios, nHorarios, id_prof);
	
	printf("Que horario desea cambiar?");
	scanf("%d",&aux);
	fflush(stdin);
	
	
	cambiarId(aux-1, &*Horarios);
	
	cambiarDia(aux-1, &*Horarios);
	
	cambiarHora(aux-1, &*Horarios);
	
	cambiarMat(aux-1, &*Horarios);
	
	cambiarGrupo(aux-1, &*Horarios);
}

//cabecera void voidcrearhorario(Horario** Horarios, int nHorarios,int id_prof);
//precondicion recibe un array de tipo horario, inicializado, su tamaÃ±o y el id_prof para aÃ±adirle un horario al profesor
//postcondicion se le aÃ±ade un horario nuevo a un profesor
void crearhorario(Horario** Horarios, int* nHorarios,int id_prof){
	int i;
	printf("AÃ‘ADIR NUEVO HORARIO\n", 165); 
	
	if(((*Horarios)= realloc ((*Horarios), (*nHorarios+1)*sizeof(Horario)))== NULL){ //comprobamos si se puede aumentar el tamaÃ±o
		printf("ERROR, NO SE HA PODIDO RESERVAR MEMOMIA\n");					  //del array para aÃ±adir horarios
	}																			  
 
	i = (*nHorarios); //asignamos a la variable el tamaÃ±o del array
	*nHorarios = *nHorarios + 1; //aumentamos el tamaÃ±o del array en 1
	(*Horarios)[i].id_prof = id_prof; 
	
	cambiarDia(i, &*Horarios);
	
	cambiarHora(i, &*Horarios);
	
	cambiarMat(i, &*Horarios);
	
	cambiarGrupo(i, &*Horarios);
}
//cabecera void voideliminarHorario(Horario** Horarios, int nHorarios,int id_prof);
//precondicion recibe un array de tipo horario, inicializado, su tamaÃ±o y el id_prof para aÃ±adirle un horario al profesor
//postcondicion se le aÃ±ade un horario nuevo a un profesor
void eliminarHorario(Horario** Horarios, int *nHorarios, int id_prof){
	int n, c;
	printf("ELIMINAR HORARIO\n");
	
	listarhorarioProfe(&**Horarios, *nHorarios, id_prof);
	
	printf("Selecciona que Horario quieres eliminar: ");
	scanf("%d",&n);
	fflush(stdin);
	
	imprimeHorario(*Horarios,n-1);
	
	printf("\nSI DESEAS ELIMINAR EL HORARIO SELECCIONADO PULSE 1: ");
	scanf("%d",&c);
	fflush(stdin);
	
	if(c != 1){
		printf("\nOPERACION CANCELADA CON EXITO.");
	}	
	else{
	// El metodo de eliminar es mover el ultimo elemento del array a el hueco del array a eliminar, 'machacando' lo que haya encima
	
		((*Horarios)[n-1].id_prof) = ((*Horarios)[(*nHorarios-1)].id_prof);
		((*Horarios)[n-1].dia) = ((*Horarios)[(*nHorarios-1)].dia);
		((*Horarios)[n-1].hora) = ((*Horarios)[(*nHorarios-1)].hora);
		((*Horarios)[n-1].id_mat) = ((*Horarios)[(*nHorarios-1)].id_mat);
		strcpy((*Horarios)[n-1].grupo, (*Horarios)[(*nHorarios-1)].grupo);
		
	// Reasignamos la memoria reservada y actualizamos el numero de calificaciones
		(*Horarios) = realloc((*Horarios), (*nHorarios-1) * sizeof(Horario));
		(*nHorarios)=(*nHorarios-1);
	}

}

// Cabecera void cambiarId(int id, Horario** Horarios)
// Precondicion recibe una id que se refiere a que horario estamos trabajando y un array de horarios inicializado
// Postcondicion permite cambiar el id del profesor de un horario
void cambiarId(int id, Horario** Horarios){
	int id_prof;
	
	printf("Introduzca el ID del profesor(3 digitos): ");
	scanf("%d",&id_prof);
	fflush(stdin);
	
	(*Horarios)[id].id_prof = id_prof;
	printf("\n");
}

// Cabecera void cambiarId(int id, Horario** Horarios)
// Precondicion recibe una id que se refiere a que horario estamos trabajando y un array de horarios inicializado
// Postcondicion permite cambiar el id del profesor de un horario
void cambiarDia(int id, Horario** Horarios){
	int dia;
	
	printf("Introduzca el dia: ");
	scanf("%d",&dia);
	fflush(stdin);
	
	(*Horarios)[id].dia = dia;
	printf("\n");
}

// Cabecera void cambiarHora(int id, Horario** Horarios)
// Precondicion recibe una id que se refiere a que horario estamos trabajando y un array de horarios inicializado
// Postcondicion permite cambiar la hora de un horario
void cambiarHora(int id, Horario** Horarios){
	int hora;
	
	printf("Introduzca la hora: ");
	scanf("%d",&hora);
	fflush(stdin);
	
	(*Horarios)[id].hora = hora;
	printf("\n");
}

// Cabecera void cambiarMat(int id, Horario** Horarios)
// Precondicion recibe una id que se refiere a que horario estamos trabajando y un array de horarios inicializado
// Postcondicion permite cambiar el id de la materia de un horario
void cambiarMat(int id, Horario** Horarios){
	int id_mat;
	
	printf("Introduzca el ID de la materia(4 digitos): ");
	scanf("%d",&id_mat);
	fflush(stdin);
	
	(*Horarios)[id].id_mat = id_mat;
	printf("\n");
}

// Cabecera void cambiarGrupo(int id, Horario** Horarios)
// Precondicion recibe una id que se refiere a que horario estamos trabajando y un array de horarios inicializado
// Postcondicion permite cambiar el grupo de un horario
void cambiarGrupo(int id, Horario** Horarios){
	char grupo[11];
	
	printf("Introduzca el grupo: ");

	fgets(grupo, 11, stdin);		
	grupo[strlen(grupo)-1] = '\0';			//fgets guarda como ultimo caracter '\n', con esto lo solucionamos
	fflush(stdin);
	
	strcpy((*Horarios)[id].grupo, grupo);		//copia el valor de la variable auxiliar en el apartado nombre del array
	printf("\n");
}
