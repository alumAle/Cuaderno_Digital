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

    if (fichero==NULL){         //establecemos un mensaje de error para en caso de éste, poder localizarlo rápidamente

        puts("Error al abrir el fichero DATA/materias.txt.");

    }else{

        do{

            fgets(linea,130,fichero);           //copiamos una linea completa del fichero, dependiendo de la iteración del bucle

            if (strcmp(linea,"\0")){            //el valor de la condición es diferente de 0 hasta que se alcance el final de linea

                *v_materias=realloc((materias *)(*v_materias),((*n)+1)*sizeof(materias));           //modificamos el struct dinámicamente para hacer sitio a los datos que entran en cada iteración del bucle

                token=strtok(linea,"-");
                strcpy((*v_materias)[*n].id,token);

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
                fprintf( fich, "%s-%s-%s\n", v_materias[i].id,v_materias[i].nombre,v_materias[i].abreviatura);
                i++;
            }
            fprintf( fich, "%s-%s-%s", v_materias[i].id,v_materias[i].nombre,v_materias[i].abreviatura);

    puts("Se ha guardado materias correctamente");

    }
}


void crear_materias(materias **v_materias, int *n_materias){

        int i, flag=1;

        (*n_materias)++;
        *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));

        puts("Introduzca la id de la materia (4 digitos):");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->id,5,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->id);

        for (i=0; i<(*n_materias-1); i++){
            flag = strcmp(((*v_materias+(*n_materias)-1)->id), (*v_materias+i)->id);

            if (flag == 0){
                (*n_materias)--;
                *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));
                i=*n_materias;
            }
        }

        if (flag!=0){

        puts("Introduzca el nombre de la materia:");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->nombre,51,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->nombre);

        puts("Introduzca la abreviatura:");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->abreviatura,4,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->abreviatura);
        }
        else puts("Ya existe una materia con esa ID");

}


void listar_materias(materias *v_materias, int *n_materias){
    int i;
    printf("\nMATERIAS:\n\n");
    for (i=0; i<*n_materias; i++)    //recorre el vector de usuarios y lo muestra en pantalla
        printf("%s-%s\n", v_materias[i].id, v_materias[i].nombre);
}


void eliminar_materias(materias **v_materias, int *n_materias){
    int i=0, idborrar=0, auxid=0, error=1;

    listar_materias(*v_materias, n_materias);

    printf("Introduzca la id de la materia a eliminar: ");
    scanf("%i", &idborrar);



    while(i<*n_materias)
    {
        auxid = atoi((*v_materias+i)->id);
        if((auxid-idborrar)==0)
        {
            while(i<*n_materias-1) //bucle para sobreescribir datos en el alumno a borrar, se reasignan las id para mantener el orden
            {
                strcpy((*v_materias+i)->id,(*v_materias+i+1)->id);
                strcpy((*v_materias+i)->nombre,(*v_materias+i+1)->nombre);
                strcpy((*v_materias+i)->abreviatura,(*v_materias+i+1)->abreviatura);
                i++;
            }
            (*n_materias)--;                                                                      //decrementa en 1 el número de materias
            *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));      //disminuye el tamaño del vector de forma dinamica
            error = 0;
            puts("Alumno eliminado corretamente.");
        }
        else i++;
    }
    if (error == 1){
        puts ("No existe ningun alumno con ese ID");
    }
}
