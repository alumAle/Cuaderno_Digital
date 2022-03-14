#include "alumnos.h"
#include "saltos.h"




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cargar_alumnos (alumnos **v_alumnos, int *n){

FILE *fichero;          //Creamos el objeto para guardar el contenido del fichero

    char linea[130];             //para copiar cada linea entera y luego ponerla en el struct
    char *token;

    *v_alumnos=NULL;           //nos aseguramos de vaciar la estructura para evitar problemas
    *n=0;

    fichero=fopen("DATA/alumnos.txt","r");         //abrimos el fichero

    if (fichero==NULL){         //establecemos un mensaje de error para en caso de éste, poder localizarlo rápidamente

        puts("Error al abrir el fichero DATA/alumnos.txt.");

    }else{

        do{

            fgets(linea,130,fichero);           //copiamos una linea completa del fichero, dependiendo de la iteración del bucle

            if (strcmp(linea,"\0")){            //el valor de la condición es diferente de 0 hasta que se alcance el final de linea

                *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n)+1)*sizeof(alumnos));           //modificamos el struct dinámicamente para hacer sitio a los datos que entran en cada iteración del bucle

                token=strtok(linea,"-");
                strcpy((*v_alumnos)[*n].id,token);

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].nombre,token);

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].direccion,token);

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].localidad,token);

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].curso,token);

                token=strtok(NULL,"\n");
                strcpy((*v_alumnos)[*n].grupo,token);

                (*n)++;

            }

        }while(!feof(fichero));
    }

    fclose(fichero);
}



void guardar_alumnos(alumnos *v_alumnos, int tam){
    FILE *fich;
    int i;


    fich=fopen("DATA/alumnos.txt","w");
    i = 0;
    if (fich==NULL)
            puts("No se ha podido modificar el fichero");
        else{
            while( i < tam-1 )
            {
                fprintf( fich, "%s-%s-%s-%s-%s-%s\n", v_alumnos[i].id,v_alumnos[i].nombre,v_alumnos[i].direccion,v_alumnos[i].localidad,v_alumnos[i].curso,v_alumnos[i].grupo);
                i++;
            }
            fprintf( fich, "%s-%s-%s-%s-%s-%s", v_alumnos[i].id,v_alumnos[i].nombre,v_alumnos[i].direccion,v_alumnos[i].localidad,v_alumnos[i].curso,v_alumnos[i].grupo);

    puts("Se ha guardado alumnos correctamente");

    }
}


void crear_alumno(alumnos **v_alumnos, int *n_alumnos)
{


        (*n_alumnos)++;                                                                        //incrementa en 1 el número de jugadores
        *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));    //aumenta el tamaño del vector de forma dinámica

        puts("Introduzca la id del alumno (6 digitos):");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->id,7,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->id);

        puts("Introduzca el nombre del alumno:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->nombre,20,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->nombre);

        puts("Introduzca la direccion:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->direccion,30,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->direccion);

        puts("Introduzca la localidad:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->localidad,30,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->localidad);

        puts("Introduzca el curso:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->curso,30,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->curso);

        puts("Introduzca el grupo:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->grupo,10,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->grupo);


}
