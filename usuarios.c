#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

//cabecera: Usuario* getUsuarios(int *arraySize);
//precondicion:El fichero usuarios.txt contenga elementos
//postcondicion:Devuelve la estructura cargada con los datos de los ficheros

Usuario* getUsuarios(int *arraySize){
	FILE *fich;
	Usuario *data;
	char c;
	int lineas=1,i,size;
	
	fich = fopen("Files/Usuarios/usuarios.txt", "r+");
	if(fich== NULL){
		printf("NO SE HA PODIDO ABRIR EL ARCHIVO DE USUARIOS, SE VA A CREAR UNO NUEVO.\n");
	}else{
		
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
	
	if((data=(Usuario*)(malloc(lineas * sizeof(Usuario)))) == NULL){
		printf("ERROR EN EL FALLO DE LA RESERVA DE MEMORIA PARA LA ESTRUCTURA USUARIOS.\n");
	}
	
	//LEEMOS EL FICHERO Y CARGAMOS LA ESTRUCTURA DINAMICA (YA INICIALIZADA CORRECTAMENTE) CON LOS DATOS DE USUARIOS.
	for (i=0; i<=lineas; i++){
		fscanf(fich, "%i-%[^-]-%[^-]-%[^-]-%[^\n]\n", &(data[i].id), data[i].nombre, data[i].perfil, data[i].usuario, data[i].pass);
	}
	if(size==0) lineas =0; //si el tamaño del fichero es 0 pues no tendrá ninguna linea y por consiguiente estará vacío.
	}
	fclose(fich); 		//cerramos el fichero.
	

	*arraySize = lineas; // el tamaño del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setUsuarios(Usuarios *data, int i);
//precondicion 'data' debe de estar inicializado correctamente y 'i' debe de contener el numero de usuarios que hay en el sistema
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setUsuarios(Usuario *data, int i){
	FILE *fich;
	int lineas;
	
	if((fich=fopen("Files/Usuarios/usuarios.txt", "w"))==NULL){
		printf("ERROR, NO SE ENCUENTRA EL FICHERO.\n");
	}
	else{
		for(lineas= 0; lineas < i; lineas ++){		//guardamos los datos actualizados en la estructura
			fprintf(fich,"%.3d-%s-%s-%s-%s",data[lineas].id,data[lineas].nombre,data[lineas].perfil,data[lineas].usuario,data[lineas].pass);
			
			if(lineas+1 < i){
			fprintf(fich,"\n");
			}
		}
		
	}
	fclose(fich);	//cerramos el fichero
}

// Cabereza void menuAdminUsuarios(Usuario* usuarios, int* nUsuarios)
// Precondicion recibe un array de tipo usuario ,inicializado, y el tamaÃ±o del array
// Poscondicion imprime por pantalla opciones de administrador que tiene para trabajar con los usuarios del sistema
void menuAdminUsuarios(Usuario** usuarios, int* nUsuarios){
	int aux;
	do{
		printf("USUARIOS\n\t1.-Listar usuarios\n\t2.-Modificar usuarios\n\t3.-A%cadir usuarios\n\t4.-Eliminar usuarios\n\t5.-Volver al men%c anterior\n", 164, 163);
		printf("Introduzca que desea hacer: ");
		do{
			scanf("%d",&aux);
			fflush(stdin);
		
			switch(aux){
				case 1:	system("cls");
						printf("LISTADO DE USUARIOS\n");
				 		listarUsuarios(*usuarios, *nUsuarios);//lista todos los usuarios del sistema
						system("pause");
					break;
				case 2:	system("cls");
						modificarUsuario(&*usuarios, *nUsuarios);//menu para modificar un usuario
						system("pause");
					break;
				case 3:	system("cls");
						addUsuario(&*usuarios, &*nUsuarios);//menu para añadir un usuario
						system("pause");
					break;
				case 4: system("cls");
						eliminarUsuario(&*usuarios, &*nUsuarios);//menu para eliminar un usuario
						system("pause");
					break;
				case 5:			// vuelve a el menu anterior
					break;
				default: printf("Error, introduzca un valor v%clido: ", 160);
					break;
			}
		}while (aux<1 || aux>5); // Si no es un valor valido se repite el switch hasta que se introduzca uno entre el rango de opciones	
			system("cls");
	}while(aux!=5);
}

//cabecera void listarUsuarios(Usuarios *data, int arraySize);
//precondicion 'data' debe estar inicializada correctamente y 'arraySize' tiene que contener el numero de usuarios que hay en el sistema
//postcondicion muestra por pantalla todos los usuarios del sistema
void listarUsuarios(Usuario *data, int arraySize){
	int i;
	
	for(i=0; i<arraySize; i++){
		imprimeUsuario(data[i]);
		printf("\n");
	}
	
	printf("Total: %d usuarios\n", arraySize);
}

// Cabecera void imprimeUsuario(usuario u)
// Precondicion recibe un usuario "u"
// Poscondicion imprime por pantalla un usuario "u"
void imprimeUsuario(Usuario u){
   printf("-Id:%.3d\n -Nombre: %s\n -Perfil: %s\n -Usuario: %s\n -Contrase%ca: %s\n",u.id, u.nombre, u.perfil, u.usuario,164, u.pass);
}

// Cabecera void addUsuario(Usuario** usuarios, int* nUsuarios)
// Precondicion recibe un array de usuarios inicializado, su tamaño
// Postcondicion permite añadir un usuario
void addUsuario(Usuario** usuarios, int* nUsuarios){
	int i, idUsuario=0;
	
	printf("A%cADIR USUARIO\n\n", 165);
	
	for(i = 0; i < *nUsuarios; i++){
		if (idUsuario < (*usuarios)[i].id)
		idUsuario = (*usuarios)[i].id;
	}
		
		i=(*nUsuarios);
		idUsuario++;
	
	if(((*usuarios) = realloc((*usuarios), (*nUsuarios+1) * sizeof(Usuario))) == NULL){
			printf("Error, no hay suficiente memoria disponible.\n");
		}
		
	*nUsuarios=*nUsuarios + 1;
	(*usuarios)[i].id = idUsuario;
		
	//cambiar el nombre completo
	cambiarNombreCompletoUsuario(i, &*usuarios, *nUsuarios);
	
	//cambiar el tipo de perfil
	cambiarPerfilUsuario(i, &*usuarios, *nUsuarios);
		
	// cambiar el nombre del usuario
	cambiarUsuarioUsuario(i, &*usuarios, *nUsuarios);
	
	// cambiar el precio
	cambiarPasswordUsuario(i, &*usuarios, *nUsuarios);

	imprimeUsuario((*usuarios)[i]);
}

// Cabecera void cambiarPerfilUsuario(int idVec, Usuario** usuarios, int nUsuarios)
// Precondicion recibe el vector de usuarios, el numero de usuarios que hay y el id del usuario
// Postcondicion cambia el nombre completo del usuario
void cambiarNombreCompletoUsuario(int idVec, Usuario** usuarios, int nUsuarios){
	int aux=0;
	char nombre[21];
	printf("Introduzca el nuevo nombre completo del usuario %.3d: ", (*usuarios)[idVec].id);
		do{
			fgets(nombre, 21, stdin);		
			nombre[strlen(nombre)-1] = '\0';			//fgets guarda como ultimo caracter '\n', con esto lo solucionamos
			fflush(stdin);
						
			aux=existeNombreUsuario(&*usuarios, nUsuarios, nombre, idVec);
			if (aux==1) printf("Error, ya existe un usuario con ese nombre, introduzca otro: ");
		}while(aux==1);
	
	strcpy((*usuarios)[idVec].nombre, nombre);		//copia el valor de la variable auxiliar en el apartado nombre del array
	printf("\n");
}

// Cabecera void cambiarPerfilUsuario(int idVec, Usuario** usuarios, int nUsuarios)
// Precondicion recibe el vector de usuarios, el numero de usuarios que hay y el id del usuario
// Postcondicion cambia el tipo de perfil del usuario
void cambiarPerfilUsuario(int idVec, Usuario** usuarios, int nUsuarios){
	int aux=0, p;
	printf("Tipos de perfiles\n 1.-Profesor\n 2.-Administrador\n");
	printf("Introduzca una opcion para el perfil: ");
		do{
			scanf("%d", &p);
			fflush(stdin);
						
			switch(p){
				case 1:
					strcpy((*usuarios)[idVec].perfil, "profesor");
					break;
				case 2:
					strcpy((*usuarios)[idVec].perfil, "administrador");
					break;
				default:
					printf("Tipo de perfil erroneo. Introduzca uno valido:");
					aux=1;				
			}
		}while(aux==1);
}

// Cabecera void cambiarPerfilUsuario(int idVec, Usuario** usuarios, int nUsuarios)
// Precondicion recibe el vector de usuarios, el numero de usuarios que hay y el id del usuario
// Postcondicion cambia el usuario del usuario
void cambiarUsuarioUsuario(int idVec, Usuario** usuarios, int nUsuarios){
	int aux=0;
	char usuario[6];
	printf("Introduzca el nuevo nick de %s (5 digitos): ", (*usuarios)[idVec].nombre);
		do{
			fgets(usuario, 6, stdin);
			fflush(stdin);
			
			aux=existeNickUsuario(&*usuarios, nUsuarios, usuario, idVec);
			if (aux==1) printf("Error, ya existe un usuario con ese nick, introduzca otro: ");
		}while(aux==1);
	
	strcpy((*usuarios)[idVec].usuario, usuario);		//copia el valor de la variable auxiliar en el apartado nombre del array
	printf("\n");
}

// Cabecera int existeNombreUsuario(Usuario** usuarios, int nUsuarios, char* usuario, int indice)
// Precondicion recibe el vector de usuarios, el numero de usuarios que hay y el nombre del usuario
// Postcondicion devuelve 1 si existe el nombre del usuario y 0 si no existe
int existeNombreUsuario(Usuario** usuarios, int nUsuarios, char* usuario, int indice){
	int i;
	for(i=0;i<nUsuarios;i++){
		if (i==indice);
		else if(strcmp((*usuarios)[i].nombre,usuario)==0){
           return 1;
		}
	}
	return 0;
}

// Cabecera int existeNickUsuario(Usuario** usuarios, int nUsuarios, char* usuario, int indice)
// Precondicion recibe el vector de usuarios, el numero de usuarios que hay y el nombre del usuario
// Postcondicion devuelve 1 si existe el nick del usuario y 0 si no existe
int existeNickUsuario(Usuario** usuarios, int nUsuarios, char* nick, int indice){
	int i;
	for(i=0;i<nUsuarios;i++){
		if (i==indice);
		else if(strcmp((*usuarios)[i].usuario,nick)==0){
           return 1;
		}
	}
	return 0;
}

// Cabecera void cambiarPerfilUsuario(int idVec, Usuario** usuarios, int nUsuarios)
// Precondicion recibe el vector de usuarios, el numero de usuarios que hay y el id del usuario
// Postcondicion cambia la contraseï¿½a del usuario
void cambiarPasswordUsuario(int idVec, Usuario** usuarios, int nUsuarios){
	char password[9];
	printf("Introduzca la contrase%ca de %s (8 digitos): ",164, (*usuarios)[idVec].nombre);
	fgets(password, 9, stdin);
	fflush(stdin);
	
	strcpy((*usuarios)[idVec].pass, password);		//copia el valor de la variable auxiliar en el apartado nombre del array
	printf("\n");
}

// Cabecera void modificarUsuario(Usuario** usuarios, int nUsuarios)
// Precondicion recibe un array de usuarios inicializado y su tamaï¿½o
// Postcondicion permite modificar los datos de un usuario
void modificarUsuario(Usuario** usuarios, int nUsuarios){
	int i, idVec, idMod, aux;
	char nombre[21], perfil[15];		//variable auxiliar que podemos modificar sin tener que tocar el elemento nombre del array equipos
	
	printf("MODIFICAR USUARIOS\n\n");
	
	printf("Introduzca el ID del usuario a modificar: ");
	do{
		scanf("%d", &idMod);
		fflush(stdin);
		
		if (idMod<=0) printf("Error, introduzca una ID v%clida (positiva no nula): ", 160); //mensaje de error si no es una id vï¿½lida
		else {
			for (i=0 ; i<nUsuarios; i++){ 							//recorremos todo el array de usuario
				if ((idMod)==((*usuarios)[i].id)){				//si el id introducido es igual a uno de los que estï¿½n en el array...

					imprimeUsuario((*usuarios)[i]);					//muestra al usuario que ha cambiado
					idVec=i;
					i=nUsuarios+1; //sale del bucle
				}	
			}
			if (i==nUsuarios) printf("Error, no existe ningun usuario con el ID: %.3d, introduzca otro: ", idMod);
		}				
	}while ((idMod<=0) || (i==nUsuarios));
	
	//cambiar el nombre completo
	cambiarNombreCompletoUsuario(idVec, &*usuarios, nUsuarios);
	
	//cambiar el tipo de perfil
	cambiarPerfilUsuario(idVec, &*usuarios, nUsuarios);
		
	// cambiar el nombre del usuario
	cambiarUsuarioUsuario(idVec, &*usuarios, nUsuarios);
	
	// cambiar el precio
	cambiarPasswordUsuario(idVec, &*usuarios, nUsuarios);
}

// Cabecera void eliminarUsuario(Usuario** usuarios, int* nUsuarios)
// Precondicion recibe un array de usuarios inicializado y su tamaï¿½o
// Postcondicion permite eliminar un usuario
void eliminarUsuario(Usuario** usuarios, int* nUsuarios){
		int i, aux, aux1, idBorrar; // i: variable para bucles, aux: variable para lectura, aux1: almacenara la id del que se almacena
	printf("ELIMINAR USUARIOS\n\n");
	printf("Introduzca el id del usuario que desea eliminar: ");
	
	// lectura del id del usuario a eliminara
	do{
		scanf("%d", &aux);
		fflush(stdin);
		aux1=0;

		if (aux < 0) printf("Error, introduzca una ID v%clida (positiva y no nula): ", 160);
		else {
			for(i=0; ( i<*nUsuarios || aux1 == i ) ;i++){
				if((*usuarios)[i].id == aux){
					
					idBorrar=i;
					printf("Ha seleccionado: \n\n");
					imprimeUsuario((*usuarios)[i]);
					aux1=1;
				}
			}
			if (aux1==0) printf("Error, no hay ningun usuario con esa id, introduzca otra: ");
		}
		
	}while (aux < 0 || aux1 == 0);
		
	// Confirmacion de que se va a borrar el usuario
		printf("\nQuiere borrar el usuario? Introduzca 1: ");
		scanf("%d", &i);
		fflush(stdin);
		
		if (i!=1) printf("Operacion cancelada, volviendo al men%c\n", 163);
		else{
			
	// El metodo de eliminar es mover el ultimo elemento del array a el hueco del array a eliminar, 'machacando' lo que haya encima
	
			((*usuarios)[idBorrar].id) = ((*usuarios)[(*nUsuarios-1)].id);
			strcpy((*usuarios)[idBorrar].nombre, (*usuarios)[(*nUsuarios-1)].nombre);
			strcpy((*usuarios)[idBorrar].perfil, (*usuarios)[(*nUsuarios-1)].perfil);
			strcpy((*usuarios)[idBorrar].usuario, (*usuarios)[(*nUsuarios-1)].usuario);
			strcpy((*usuarios)[idBorrar].pass, (*usuarios)[(*nUsuarios-1)].pass);
		
	// Reasignamos la memoria reservada y actualizamos el numero de usuarios
			(*usuarios) = realloc((*usuarios), (*nUsuarios-1) * sizeof(Usuario));
			(*nUsuarios)=(*nUsuarios-1);
		}
}
