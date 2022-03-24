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



void crear_alumno(alumnos **v_alumnos, int *n_alumnos){

        int i, flag=1;

        (*n_alumnos)++;
        *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));

        puts("Introduzca la id del alumno (6 digitos):");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->id,7,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->id);

        for (i=0; i<(*n_alumnos-1); i++){
            flag = strcmp(((*v_alumnos+(*n_alumnos)-1)->id), (*v_alumnos+i)->id);

            if (flag == 0){
                (*n_alumnos)--;
                *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));
                i=*n_alumnos;
            }
        }

        if (flag!=0){

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
        else puts("Ya existe un alumno con ese ID");
}



void listar_alumnos(alumnos *v_alumnos, int *n_alumnos){
    int i;
    printf("\nALUMNOS:\n\n");
    for (i=0; i<*n_alumnos; i++)    //recorre el vector de usuarios y lo muestra en pantalla
        printf("%s-%s\n", v_alumnos[i].id, v_alumnos[i].nombre);
}



void eliminar_alumno(alumnos **v_alumnos, int *n_alumnos){
    int i=0, idborrar=0, auxid=0, error=1;

    listar_alumnos(*v_alumnos, n_alumnos);

    printf("Introduzca la id del usuario a eliminar: ");
    scanf("%i", &idborrar);



    while(i<*n_alumnos)
    {
        auxid = atoi((*v_alumnos+i)->id);
        if((auxid-idborrar)==0)
        {
            while(i<*n_alumnos-1) //bucle para sobreescribir datos en el alumno a borrar, se reasignan las id para mantener el orden
            {
                strcpy((*v_alumnos+i)->id,(*v_alumnos+i+1)->id);
                strcpy((*v_alumnos+i)->nombre,(*v_alumnos+i+1)->nombre);
                strcpy((*v_alumnos+i)->direccion,(*v_alumnos+i+1)->direccion);
                strcpy((*v_alumnos+i)->localidad,(*v_alumnos+i+1)->localidad);
                strcpy((*v_alumnos+i)->curso,(*v_alumnos+i+1)->curso);
                strcpy((*v_alumnos+i)->grupo,(*v_alumnos+i+1)->grupo);
                i++;
            }
            (*n_alumnos)--;                                                                      //decrementa en 1 el número de alumnos
            *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));      //disminuye el tamaño del vector de forma dinamica
            error = 0;
            puts("Alumno eliminado corretamente.");
        }
        else i++;
    }
    if (error == 1){
        puts ("No existe ningun alumno con ese ID");
    }
}



void mod_alumno(alumnos *v_alumnos, int *n_alumnos)          //el admin introduce la id del equipo que desea modificar e introduce los nuevos datos
{
    int idmod, auxid, i, flag=1;
    listar_alumnos(v_alumnos, n_alumnos);
    printf("Introduzca la id del alumno a modificar: ");
    scanf("%i", &idmod);


    for (i=0; i<*n_alumnos; i++){
        auxid = atoi(v_alumnos[i].id);
        if((auxid-idmod)==0){

                flag=0;

                puts("Introduzca el nombre del alumno:");
                fflush(stdin);
                fgets(v_alumnos[i].nombre,21,stdin);
                quitar_saltos(v_alumnos[i].nombre);

                puts("Introduzca la direccion del alumno:");
                fflush(stdin);
                fgets(v_alumnos[i].direccion,31,stdin);
                quitar_saltos(v_alumnos[i].direccion);

                puts("Introduzca la localidad:");
                fflush(stdin);
                fgets(v_alumnos[i].localidad,31,stdin);
                quitar_saltos(v_alumnos[i].localidad);

                puts("Introduzca el curso del alumno:");
                fflush(stdin);
                fgets(v_alumnos[i].curso,31,stdin);
                quitar_saltos(v_alumnos[i].curso);

                puts("Introduzca el grupo:");
                fflush(stdin);
                fgets(v_alumnos[i].grupo,11,stdin);
                quitar_saltos(v_alumnos[i].grupo);

            }
    }
    if (flag==1) puts("No existe ningun alumno con ese id");

}


void datos_alumno(alumnos *v_alumnos, int *n_alumnos, char *id){
    int flag=1, i;
    for (i=0; i<(*n_alumnos); i++){
            flag = strcmp(v_alumnos[i].id, id);

            if (flag == 0){
                printf("ID: %s \nNombre: %s \nDireccion: %s \nLocalidad: %s \nCurso y grupo: %s %s", v_alumnos[i].id, v_alumnos[i].nombre, v_alumnos[i].direccion, v_alumnos[i].localidad, v_alumnos[i].curso, v_alumnos[i].grupo);
            }
        }
}
