#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantica.h"

extern Lista *tabla_simbolos;

int typeToEnum(char *type) {
    if (strcmp(type, "int") == 0) {
        return NODE_INT;
    }
    return -1;
}

int check_semantics(ASTNode *node) {
    if (!node) return 1; // Un nodo vacío es semánticamente válido

    switch (node->type) {
        case NODE_SEQ:
            // Validar que ambas sentencias en la secuencia sean correctas
            return check_semantics(node->left) != -1 && check_semantics(node->right) != -1;
        case NODE_DECL: {
            if(buscar_simbolo(tabla_simbolos, node->simbolo->nombre)) {
                printf("-> Error Semantico: declaracion multiple del simbolo: (%s).\n", node->simbolo->nombre);
                return -1;
            }
            insertarCabeza(&tabla_simbolos ,node->simbolo);
            return 1;
        }
        case NODE_ID: {
            // Verificar si la variable usada en una expresión existe
            Simbolo *simbolo = buscar_simbolo(tabla_simbolos, node->simbolo->nombre);
            if (simbolo == NULL) {
                fprintf(stderr, "Error Semantico: Uso de variable no declarada (%s).\n", node->simbolo->nombre);
                return -1;
            }
            return typeToEnum(simbolo->type);
        }
        case NODE_ASIG: {
            int tipoID        = check_semantics(node->left);
            int tipoExpresion = check_semantics(node->right);
            if ( tipoID != tipoExpresion ) {
                fprintf(stderr, "Error Semantico: asignacion entre tipos incompatibles\n");
                return -1;
            }
            return tipoID;
        }
        case NODE_ADD: {
            int tipoIzquierdo = check_semantics(node->left);
            int tipoDerecho   = check_semantics(node->right);
            if( tipoIzquierdo != tipoDerecho ) {
                fprintf(stderr, "Error Semantico: suma entre tipos incompatibles\n");
                return -1;
            }
            return tipoIzquierdo;
        }
        case NODE_INT: {
            return NODE_INT;
        }
        default: // Operadores como NODE_ADD, NODE_MUL
            return check_semantics(node->left) != -1 && check_semantics(node->right) != -1;
    }
}
