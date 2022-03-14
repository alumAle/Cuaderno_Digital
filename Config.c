#include <stdio.h>
#include <stdlib.h>
#include "Files/Configuracion/Config.h"
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
	
	if(( fich = fopen(PatchConfig, "r+"))== NULL){
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

	arraySize = lineas; // el tamaño del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setConfiguracion(Configuracion data, int i);
//precondicion 'data' debe de estar inicializado correctamente y 'i' debe de contener el numero de configuracones
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setConfiguracion(Configuracion *data, int i){
	FILE *fich;
	int lineas;
	
	if((fich=fopen(PatchConfig, "w"))==NULL){
		printf("ERROR, NO SE ENCUENTRA EL FICHERO.\n");
	}
	else{
		for(lineas= 0; lineas < i; lineas ++){		//guardamos los datos actualizados en la estructura
			fprintf(fich,"%s-%d",data[lineas].nombreConfig, &(data[lineas].valorConfig));
		}
		if(lineas+1 < i){
			fprintf(fich,"\n");
		}
	}
	fclose(fich);	//cerramos el fichero
}

//cabecera void menuAdminConfig(Configuracion** Configs, int nConfigs);
//precondicion recibe un array de tipo Configuracion inicializado y el tamaño del array
//postcondicion imprime por pantalla opciones de configracion para el admin
void menuAdminConfig(Configuracion** Configuraciones, int nConfiguraciones){
	int aux;
	do{
		printf("BIENVENIDO AL MENU DE CONFIGURACION\n\t1.-Ver Configuracion Actual\n\t2.-Editar Configuracion\n\t3.-Volver atras.\n ");
		printf("Introduce que deseas hacer: ");
		scanf("%d",&aux);
		fflush(stdin);
		
		system("cls");
		do{
			switch(aux){
				case 1: listarConfiguracion(Configuraciones, nConfiguraciones);
					system("pause");
					break;
				case 2: editarConfiguracion(&Configuraciones,nConfiguraciones);
					system("pause");
					break;
				case 3: 
					break;
				default: printf("ERROR, INTRODUZCA UNA OPCION VALIDA PORFAVOR: ");
					break;
			}
			system("cls");
		}while(aux <1 || aux > 3);
	}while(aux !=3);
}
