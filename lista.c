#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"


Simbolo *buscar_simbolo(Lista *lista, char *nombre)
{
    if (nombre == NULL) return NULL;
    Lista *actual = lista;

    while (actual != NULL)
    {
        if (strcmp(actual->simbolo->nombre, nombre) == 0)
        {
            return actual->simbolo;
        }

        actual = actual->siguiente;
    }

    return NULL;
}


void insertarCabeza(Lista **lista, Simbolo *simbolo)
{
    Lista *nuevo = malloc(sizeof(Lista));

    if (nuevo == NULL)
    {
        printf("Error al reservar memoria\n");
        return;
    }

    nuevo->simbolo = simbolo;

    nuevo->siguiente = *lista;

    *lista = nuevo;
}




void imprimir_lista(Lista *lista)
{
    Lista *actual = lista;

    printf("\n--- TABLA DE SIMBOLOS ---\n");

    while (actual != NULL)
    {
        printf(
            "Nombre: %s | Tipo: %s\n",
            actual->simbolo->nombre,
            actual->simbolo->type
        );

        actual = actual->siguiente;
    }
}