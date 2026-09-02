// ast.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *create_int_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_INT;
    node->simbolo.value.i_val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode *create_float_node(float value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT;
    node->simbolo.value.f_val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode *create_id_node(char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ID;
    node->simbolo.value.s_val = strdup(value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode *create_op_node(NodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->simbolo.value.i_val = 0;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *create_asignacion_node(NodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->simbolo.value.i_val = 0;
    node->left = left;
    node->right = right;
    return node;
}

void print_ast(ASTNode *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");

    if (node->type == NODE_ASIG) {
        printf("Nodo asignacion\n");
        print_ast(node->left, 0);
        print_ast(node->right, 0);
        return;
    }
    
    if (node->type == NODE_ID) {
        printf("ID: %s\n", node->simbolo.value.s_val);
        return;
    }
    if (node->type == NODE_FLOAT) {
        printf("FLOAT: %f\n", node->simbolo.value.f_val);
        return;
    }
    if (node->type == NODE_INT) {
        printf("INT: %d\n", node->simbolo.value.i_val);
    }
    if (node->type == NODE_ADD) {
        printf("+");
    }
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

void free_ast(ASTNode *node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}
