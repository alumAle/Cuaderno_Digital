#include "materias.h"
#include "saltos.h"




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cargar_materias (materias **v_materias, int *n){

FILE *fichero;          //Creamos el objeto para guardar el contenido del fichero

    char linea[130];             //para copiar cada linea entera y luego ponerla en el struct
    char *token;

    *v_materias=NULL;           //nos aseguramos de vaciar la estructura para evitar problemas
    *n=0;

    fichero=fopen("DATA/materias.txt","r");         //abrimos el fichero

    if (fichero==NULL){         //establecemos un mensaje de error para en caso de �ste, poder localizarlo r�pidamente

        puts("Error al abrir el fichero DATA/materias.txt.");

    }else{

        do{

            fgets(linea,130,fichero);           //copiamos una linea completa del fichero, dependiendo de la iteraci�n del bucle

            if (strcmp(linea,"\0")){            //el valor de la condici�n es diferente de 0 hasta que se alcance el final de linea

                *v_materias=realloc((materias *)(*v_materias),((*n)+1)*sizeof(materias));           //modificamos el struct din�micamente para hacer sitio a los datos que entran en cada iteraci�n del bucle

                token=strtok(linea,"-");
                (*v_materias)[*n].id=atoi(token);

                token=strtok(NULL,"-");
                strcpy((*v_materias)[*n].nombre,token);

                token=strtok(NULL,"\n");
                strcpy((*v_materias)[*n].abreviatura,token);



                (*n)++;

            }

        }while(!feof(fichero));
    }

    fclose(fichero);
}


void guardar_materias(materias *v_materias, int tam){
    FILE *fich;
    int i;


    fich=fopen("DATA/materias.txt","w");
    i = 0;
    if (fich==NULL)
            puts("No se ha podido modificar el fichero");
        else{
            while( i < tam-1 )
            {
                fprintf( fich, "%.4d-%s-%s\n", v_materias[i].id,v_materias[i].nombre,v_materias[i].abreviatura);
                i++;
            }
            fprintf( fich, "%.4d-%s-%s", v_materias[i].id,v_materias[i].nombre,v_materias[i].abreviatura);

    puts("Se ha guardado materias correctamente");

    }
}


void crear_materias(materias **v_materias, int *n_materias){


        (*n_materias)++;
        *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));

        (*v_materias+(*n_materias)-1)->id = *n_materias;


        puts("Introduzca el nombre de la materia:");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->nombre,51,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->nombre);

        puts("Introduzca la abreviatura:");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->abreviatura,4,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->abreviatura);


}


void listar_materias(materias *v_materias, int *n_materias){
    int i;
    printf("\nMATERIAS:\n\n");
    for (i=0; i<*n_materias; i++)    //recorre el vector de usuarios y lo muestra en pantalla
        printf("%.4d-%s\n", v_materias[i].id, v_materias[i].nombre);
}


void eliminar_materias(materias **v_materias, int *n_materias){
    int idborrar=0, i=0, error=1;

    listar_materias(*v_materias, n_materias);

    printf("Introduzca la id de la materia a eliminar: ");
    scanf("%i", &idborrar);



    while(i<*n_materias)
    {
        if(((*v_materias+i)->id)== idborrar)
        {
            while(i<*n_materias-1) //bucle para sobreescribir datos en el alumno a borrar, se reasignan las id para mantener el orden
            {
                ((*v_materias+i)->id = (*v_materias+i+1)->id);
                strcpy((*v_materias+i)->nombre,(*v_materias+i+1)->nombre);
                strcpy((*v_materias+i)->abreviatura,(*v_materias+i+1)->abreviatura);
                i++;
            }
            (*n_materias)--;                                                                      //decrementa en 1 el n�mero de materias
            *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));      //disminuye el tama�o del vector de forma dinamica
            error = 0;
            puts("Materia eliminada corretamente.");
        }
        else i++;
    }
    if (error == 1){
        puts ("No existe ninguna materia con ese ID");
    }
}
