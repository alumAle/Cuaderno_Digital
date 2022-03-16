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
		printf("NO SE HA PODIDO ABRIR EL ARCHIVO DE CONFIGURACION, SE VA A CREAR UNO NUEVO.\n");
	}
	
	else{
	fseek(fich,0,SEEK_END);     //ponemos el puntero al inicio del fichero.
	size=ftell(fich);			//guardamos el tamaÃ±o del fichero.
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
	if(size==0) lineas =0; //si el tamaÃ±o del fichero es 0 pues no tendrÃ¡ ninguna linea y por consiguiente estarÃ¡ vacÃ­o.
}
	fclose(fich); 		//cerramos el fichero.

	arraySize = lineas; // el tamaÃ±o del array es el numero de lineas.
	return data; //devuelve la estructura cargada con los elementos perfectamente.
}

//cabecera void setConfiguracion(Configuracion data, int i);
//precondicion 'data' debe de estar inicializado correctamente y 'i' debe de contener el numero de configuracones
//postcondicion actualiza los ficheros con los datos contenidos en 'data'
void setConfiguracion(Configuracion *data, int i){
	FILE *fich;
	int lineas;
	
	if((fich = fopen(PatchConfig, "w")) == NULL){
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
//precondicion recibe un array de tipo Configuracion inicializado y el tamaÃ±o del array
//postcondicion imprime por pantalla opciones de configracion para el admin
void menuAdminConfig(Configuracion** Configuraciones, int nConfiguraciones){
	int aux;
	do{
		do{
			printf("CONFIGURACION\n\t1.-Ver Configuracion Actual\n\t2.-Editar Configuracion\n\t3.-Volver al men%c anterior\n", 163);
			printf("Introduzca que desea hacer: ");
			scanf("%d",&aux);
			fflush(stdin);
		
			system("cls");
		
			switch(aux){
				case 1: listarConfiguracion(Configuraciones, nConfiguraciones);
					system("pause");
					break;
				case 2: editarConfiguracion(&Configuraciones, nConfiguraciones);
					system("pause");
					break;
				case 3:
					break;	
				default: printf("Error, introduzca un valor v%clido: ", 160);
					break;
			}
			system("cls");

		}while (aux<1 || aux>3);
	}while (aux !=3);
}

//cabecera void listarConfiguracion (Configuracion* Configuraciones, int nConfiguraciones)
//precondicion recibe un array de tipo Configuracion ,inicializado, y el tamaÃƒÂ±o del array
//poscondicion imprime las configuraciones actuales
void listarConfiguracion (Configuracion* Configuraciones, int nConfiguraciones){
    int i;
    printf("CONFIGURACION ACTUAL\n");
    for(i=0;i<nConfiguraciones;i++){
        imprimeConfiguracion(Configuraciones[i]);
    }
}

//cabecera void imprimeConfiguracion(Configuracion c)
//precondicion recibe una configuracion c
//poscondicion imprime por pantalla una configuracion c
void imprimeConfiguracion(Configuracion c){
   printf("\t%s: %.2d\n",c.nombreConfig, c.valorConfig);
}

//cabecera void editarConfiguracion(Configuracion* Configuraciones, int nConfiguraciones)
//precondicion recibe un array de tipo Configuracion ,inicializado, y el tamaÃƒÂ±o del array
//poscondicion imprime por pantalla el valor del nuevo parametro cambiado
void editarConfiguracion(Configuracion** Configuraciones, int nConfiguraciones){
	char nombre[30];
	int i;
	
	listarConfiguracion(*Configuraciones, nConfiguraciones);
	
	printf("Introduzca el nombre del parametro a modificar: ");
	scanf("%s", nombre);
	fflush(stdin);
	for(i=0;i<nConfiguraciones;i++){
		if (strcmp ((*Configuraciones)[i].nombreConfig , nombre) ==0 ){
			
			printf("Introduzca el nuevo valor del par%cmetro %s: ",160, (*Configuraciones)[i].nombreConfig);
			scanf("%d", &(*Configuraciones)[i].valorConfig);
			fflush(stdin);
			imprimeConfiguracion ((*Configuraciones)[i]);
			i=nConfiguraciones+1;
		} 
    }
	if (i==nConfiguraciones) printf("ERROR, no se ha encontrado ningun par%cmerto con ese nombre\n", 160);
}

//cabecera int valorConfig (Configuracion* c, int nC, char const *var)
//precondicion recibe un array de configuraciones inicializado, el numero de lineas de ese array y una cadena de caracteres
//poscondicion devuelve en un entero el valor que busques en concreto
int valorConfig (Configuracion* c, int nC, char const *var){
	int i, aux=0;
	for(i=0;i<nC;i++){
        if ((strcmp (c[i].nombreConfig , var)) == 0 ){
        	aux=c[i].valorConfig;
        	i=nC+1;
		}
    }
    return aux;
}

