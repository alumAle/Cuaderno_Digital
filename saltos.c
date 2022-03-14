#include "saltos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Cabecera: void quitar_saltos (string cadena)
Precondición: string de caracteres no vacía
Postcondición: le quita al string el salto de línea de producto de la función "fgets"
*/
void quitar_saltos(char *cadena)
{
    char *p;
    p = strchr(cadena, '\n');
    if (p)
        *p = '\0';
}
