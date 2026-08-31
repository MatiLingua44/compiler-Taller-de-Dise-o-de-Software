// ast.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *create_num_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode *create_op_node(NodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = 0;
    node->left = left;
    node->right = right;
    return node;
}

void print_ast(ASTNode *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    
    if (node->type == NODE_NUM) {
        printf("NUM: %d\n", node->value);
    } else {
        char *op = (node->type == NODE_ADD) ? "+" : 
                   (node->type == NODE_SUB) ? "-" : 
                   (node->type == NODE_MUL) ? "*" : "/";
        printf("OP: %s\n", op);
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
