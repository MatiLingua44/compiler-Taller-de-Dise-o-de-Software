#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantica.h"

extern Lista *tabla_simbolos;


int check_semantics(ASTNode *node) {
    if (!node) return 1; // Un nodo vacío es semánticamente válido

    switch (node->type) {
        case NODE_SEQ:
            // Validar que ambas sentencias en la secuencia sean correctas
            return check_semantics(node->left) && check_semantics(node->right);
        case NODE_DECL: {
            if(buscar_simbolo(tabla_simbolos, node->simbolo->nombre)) {
                printf("-> Error Semantico: declaracion multiple del simbolo: (%s).\n", node->simbolo->nombre);
                return 0;
            }
            insertarCabeza(&tabla_simbolos ,node->simbolo);
            return 1;
        }
        case NODE_ID: {
            // Verificar si la variable usada en una expresión existe
            if (!buscar_simbolo(tabla_simbolos, node->simbolo->nombre)) {
                fprintf(stderr, "Error Semantico: Uso de variable no declarada (%s).\n", node->simbolo->nombre);
                return 0;
            }
            return 1;
        }
        case NODE_ASIG:{
            // Verificar si la variable a la que se le asigna un valor existe
            if (!buscar_simbolo(tabla_simbolos, node->left->simbolo->nombre)) {
                fprintf(stderr, "Error Semantico: Asignacion a variable no declarada (%s).\n", node->left->simbolo->nombre);
                return 0;
            }
            // Validar recursivamente la expresión que se le está asignando
            return check_semantics(node->right);
        }
/*

        case NODE_ASSIGNMENT: {
            // Verificar si la variable a la que se le asigna un valor existe
            Symbol *sym = lookup_symbol(node->id_name);
            if (sym == NULL) {
                fprintf(stderr, "Error Semántico: Asignación a variable no declarada '%s'.\n", node->id_name);
                return 0;
            }
            // Validar recursivamente la expresión que se le está asignando
            return check_semantics(node->left);
        }

        case NODE_IDENTIFIER: {
            // Verificar si la variable usada en una expresión existe
            if (lookup_symbol(node->id_name) == NULL) {
                fprintf(stderr, "Error Semántico: Uso de variable no declarada '%s'.\n", node->id_name);
                return 0;
            }
            return 1;
        }

        case NODE_LITERAL:
            return 1; // Los literales puros (5, 3.14, "hola") siempre son válidos
*/
        default: // Operadores como NODE_ADD, NODE_MUL
            return check_semantics(node->left) && check_semantics(node->right);
    }
}
