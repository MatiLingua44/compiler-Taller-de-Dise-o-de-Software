#ifndef LISTA_H
#define LISTA_H

#include "ast.h"


typedef struct Lista {

    Simbolo *simbolo;

    struct Lista *siguiente;

} Lista;


// Busca un símbolo por nombre
Simbolo *buscar_simbolo(Lista *lista, char *nombre);


// Inserta un símbolo al comienzo de la lista
void insertarCabeza(Lista **lista, Simbolo *simbolo);


// Recorre el AST y agrega las declaraciones
void recorrer_lista(ASTNode *node, Lista **lista);


// Mostrar lista
void imprimir_lista(Lista *lista);


#endif