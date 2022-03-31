#include <stdio.h>
#include <stdlib.h>
#include "calificaciones.h"
#include <string.h>

//cabecera: Calificacion* getCalificaciones(int *arraySize)
//precondicion:El fichero usuarios.txt contenga elementos
//postcondicion:Devuelve la estructura cargada con los datos de los ficheros

Calificacion* getCalificaciones(int *arraySize){
	FILE *fich;
	Calificacion *data;
	char c;
	int lineas=1,i,size;
	
	if((fich = fopen("Files/Calificaciones/calificaciones.txt", "r+"))== NULL){
		printf("NO SE HA PODIDO ABRIR EL ARCHIVO DE CALIFICACIONES, SE VA A CREAR UNO NUEVO.\n");
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
	
	//REALIZAMOS LA RESERVA DE MEMORIA PARA LA ESTRUCTURA "CALIFICACIONES" teniendo en cuenta el numero de lineas 
	//que contiene el fichero.
	
	if((data=(Calificacion*)(malloc(lineas * sizeof(Calificacion)))) == NULL){
		printf("ERROR EN EL FALLO DE LA RESERVA DE MEMORIA PARA LA ESTRUCTURA CALIFICACIONES.\n");
	}
	
	//LEEMOS EL FICHERO Y CARGAMOS LA ESTRUCTURA DINAMICA (YA INICIALIZADA CORRECTAMENTE) CON LOS DATOS DE USUARIOS.
	for (i=0; i<=lineas; i++){
		fscanf(fich, "%[^-]-%[^-]-%d-%d-%d\n", data[i].fecha, data[i].desc, &(data[i].id_mat), &(data[i].id_alum), &(data[i].calif));
	}
	if(size==0) lineas =0; //si el tamaño del fichero es 0 pues no tendrá ninguna linea y por consiguiente estará vacío.
	}
	fclose(fich); 		//cerramos el fichero.

	*arraySize = lineas; // el tamaño del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setCalificaciones (Calificacion* data, int i)
//precondicion 'data' debe de estar inicializado correctamente y 'i' debe de contener el numero de usuarios que hay en el sistema
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setCalificaciones (Calificacion* data, int i){
	FILE *fich;
	int lineas;
	
	if((fich=fopen("Files/Calificaciones/calificaciones.txt", "w"))==NULL){
		printf("ERROR, NO SE ENCUENTRA EL FICHERO.\n");
	}
	else{
		for(lineas= 0; lineas < i; lineas ++){		//guardamos los datos actualizados en la estructura
			fprintf(fich,"%s-%s-%.4d-%.6d-%d",data[lineas].fecha, data[lineas].desc, data[lineas].id_mat, data[lineas].id_alum, data[lineas].calif);
			if(lineas+1 < i){
				fprintf(fich,"\n");
			}
		}
		
	}
	fclose(fich);	//cerramos el fichero
}

//cabecera void listarCalificaciones(Calificacion *data, int arraySize);
//precondicion 'data' debe estar inicializada correctamente y 'arraySize' tiene que contener el numero de calificaciones que hay en el sistema
//postcondicion muestra por pantalla todas las calificaciones que nos podemos encontrar en el sistema
void listarCalificaciones(Calificacion *data, int arraySize){
	int i;
	
	for(i=0; i<arraySize; i++){
		imprimeCalificacion(data[i]);
		printf("\n");
	}
}

// Cabecera void imprimeCalificacion(Calificacion c)
// Precondicion recibe una calificacion "c"
// Poscondicion imprime por pantalla una calificacion "c"
void imprimeCalificacion(Calificacion c){
   printf("\n -Fecha:%s\n -Descripcion: %s\n -Id_Materia: %.4d\n -Id_Alumno: %.6d\n -Calificacion: %d\n",c.fecha, c.desc, c.id_mat, c.id_alum, c.calif);
}
// Cabecera void menuProfeCalificaciones(Calificacion** calificaciones, int* nCalificaciones, int id_alum, int id_mat)
// Precondicion recibe un array de calificaciones ya inicializada, el tamaño de ese array, la id de un alumno y materia en especifico
// Poscondicion devuelve un menu para trabajar con las calificaciones de un alumno en una materia en concreta
void menuProfeCalificaciones(Calificacion** calificaciones, int* nCalificaciones, int id_alum, int id_mat){
	int aux;
	
	do{
		printf("\nCALIFICACIONES DEL ALUMNO %.6d EN LA MATERIA %.4d:\n\n",id_alum,id_mat);
		listaCalificacionesAlumno(*calificaciones,*nCalificaciones,id_alum,id_mat);
		printf("\n1.-Modificar una calificaci%cn\n2.-Borrar una calificaci%cn\n3.-A%cadir una calificaci%cn\n4.-Volver al men%c anterior\n",162, 162, 164, 162, 163);
		printf("Que desea hacer?: ");
		do{
			scanf("%d",&aux);
				fflush(stdin);
			
				switch(aux){
					case 1:	system("cls");
					 		modificarCalificacion(&*calificaciones, *nCalificaciones, id_alum, id_mat);//Modificar calificacion
						break;
					case 2:	system("cls");
							eliminarCalificacion(&*calificaciones, &*nCalificaciones, id_alum, id_mat);//Borrar calificacion
						break;
					case 3:	system("cls");
							addCalificacion(&*calificaciones, &*nCalificaciones, id_alum, id_mat);//Añadir calificacion
						break;
					case 4:			// vuelve a el menu anterior
						break;
					default: printf("Error, introduzca un valor v%clido: ", 160);
						break;
				}		
		}while(aux<1||aux>4);
		system("cls");
	}while(aux!=4);
	
}
//cabecera listaCalificacionesAlumno(Calificacion *data, int arraySize, int id_alum, int id_mat)
//precondicion recibe un array de calificaciones inicializado, su tamaño, y los identificadores de un alumno y una materia
//postcondicion nos devuelve todas las calificaciones de un alumno en una materia en concreto
void listaCalificacionesAlumno(Calificacion *data, int arraySize, int id_alum, int id_mat){
	int i;
	
	for(i=0; i<arraySize;i++){
		if(id_alum==data[i].id_alum && id_mat==data[i].id_mat){
			printf("CALIFICACION %d\n",i+1);
			imprimeCalificacion(data[i]);
			printf("\n");
		}
	}	
}
// Cabecera void eliminarCalificacion(Calificacion** calificaciones, int* nCalificaciones)
// Precondicion recibe un array de calificaciones inicializada y su tamaï¿½o
// Postcondicion permite eliminar una calificacion
void eliminarCalificacion(Calificacion** data, int* nCalificaciones, int id_alum, int id_mat){
	int i, j, aux, aux1, idBorrar, cont=1, encontrado=0; // i: variable para bucles, aux: variable para lectura, aux1: almacenara la id del que se almacena
	printf("ELIMINAR CALIFICACIONES\n\n");
	
	
	listaCalificacionesAlumno(&**data, *nCalificaciones, id_alum, id_mat);

	printf("Que calificacion desea eliminar?: ");
	scanf("%d",&aux);
	fflush(stdin);
	
	imprimeCalificacion((*data)[aux-1]);
	
	printf("\nDesea eliminar la calificacion %d?(Escriba '1' si asi lo desea): ",aux);
	scanf("%d",&i);
	fflush(stdin);
	if (i!=1) printf("Operacion cancelada, volviendo al men%c\n", 163);
	else{			
	// El metodo de eliminar es mover el ultimo elemento del array a el hueco del array a eliminar, 'machacando' lo que haya encima
	
		strcpy((*data)[aux-1].fecha, (*data)[(*nCalificaciones-1)].fecha);
		strcpy((*data)[aux-1].desc, (*data)[(*nCalificaciones-1)].desc);
		((*data)[aux-1].id_mat) = ((*data)[(*nCalificaciones-1)].id_mat);
		((*data)[aux-1].id_alum) = ((*data)[(*nCalificaciones-1)].id_alum);
		((*data)[aux-1].calif) = ((*data)[(*nCalificaciones-1)].calif);
		
	// Reasignamos la memoria reservada y actualizamos el numero de calificaciones
		(*data) = realloc((*data), (*nCalificaciones-1) * sizeof(Calificacion));
		(*nCalificaciones)=(*nCalificaciones-1);
	}
}

//Cabecera void modificarCalificacion(Calificacion** calificaciones, int nCalificaciones)
//Precondicion recibe un array de calificaciones inicializado y su tamaño
//Postcondicion permite modificar los datos de una calificacion de un alumno y materia en especifico
void modificarCalificacion(Calificacion** data, int nCalificaciones, int id_alum, int id_mat){
	
	int i, j, aux, encontrado=0, cont=1; 
	
	printf("MODIFICAR CALIFICACION\n\n");
	//listamos las calificaciones de un alumno y materia 
	listaCalificacionesAlumno(&**data, nCalificaciones, id_alum, id_mat);
	//seleccionamos la calificacion que deseamos modificar mediante un menu basico
	printf("Que calificacion desea modificar?: ");
	scanf("%d",&aux);
	fflush(stdin);
	
	//hacemos los cambios que necesitamos en concreto
	//cambiar fecha
	cambiarFecha(aux-1, &*data);
	//cambiar descripcion
	cambiarDesc(aux-1, &*data);
	//cambiar calificacion
	cambiarCalif(aux-1, &*data);
}

// Cabecera void addCalificacion(Calificacion** calificaciones, int* nCalificaciones)
// Precondicion recibe un array de calificaciones inicializado, su tamaño
// Postcondicion permite añadir una calificacion
void addCalificacion(Calificacion** calificaciones, int* nCalificaciones, int id_alum, int id_mat){
	int i;
	
	printf("A%cADIR CALIFICACION\n\n", 165);
	
	if(((*calificaciones) = realloc((*calificaciones), (*nCalificaciones+1) * sizeof(Calificacion))) == NULL){
			printf("Error, no hay suficiente memoria disponible.\n");
	}
	
	i = (*nCalificaciones);
		
	*nCalificaciones=*nCalificaciones + 1;
	(*calificaciones)[i].id_alum = id_alum;
	(*calificaciones)[i].id_mat = id_mat;
	
	//cambiar fecha
	cambiarFecha(i, &*calificaciones);
	//cambiar descripcion
	cambiarDesc(i, &*calificaciones);
	//cambiar calificacion
	cambiarCalif(i, &*calificaciones);
	
	listaCalificacionesAlumno(&**calificaciones, *nCalificaciones, id_alum, id_mat);
}
// Cabecera void cambiarFecha(int id, Calificacion** data)
// Precondicion recibe una id que se refiere a que calificacion estamos trabajando y un array de calificaciones inicializado
// Postcondicion permite cambiar la fecha de una calificacion
void cambiarFecha(int id, Calificacion** data){
	char fecha[12];
	
	printf("Introduzca la nueva fecha: ");

	fgets(fecha, 12, stdin);		
	fecha[strlen(fecha)-1] = '\0';			//fgets guarda como ultimo caracter '\n', con esto lo solucionamos
	fflush(stdin);
	
	strcpy((*data)[id].fecha, fecha);		//copia el valor de la variable auxiliar en el apartado nombre del array
	printf("\n");
}
// Cabecera void cambiarDesc(int id, Calificacion** data)
// Precondicion recibe una id que se refiere a que calificacion estamos trabajando y un array de calificaciones inicializado
// Postcondicion permite cambiar la descripcion de una calificacion
void cambiarDesc(int id, Calificacion** data){
	char desc[31];
	
	printf("Introduzca la nueva descripcion: ");

	fgets(desc, 31, stdin);		
	desc[strlen(desc)-1] = '\0';			//fgets guarda como ultimo caracter '\n', con esto lo solucionamos
	fflush(stdin);
	
	strcpy((*data)[id].desc, desc);		//copia el valor de la variable auxiliar en el apartado nombre del array
	printf("\n");
}
// Cabecera void cambiarCalif(int id, Calificacion** data)
// Precondicion recibe una id que se refiere a que calificacion estamos trabajando y un array de calificaciones inicializado
// Postcondicion permite cambiar la calificacion de una calificacion
void cambiarCalif(int id, Calificacion** data){
	int calif;
	
	printf("Introduzca la nueva calificacion: ");
	scanf("%d",&calif);
	
	(*data)[id].calif = calif;
	printf("\n");
}








