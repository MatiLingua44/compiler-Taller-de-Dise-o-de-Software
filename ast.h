// ast.h
#ifndef AST_H
#define AST_H

typedef enum { NODE_NUM, NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV } NodeType;

typedef struct ASTNode {
    NodeType type;
    int value;                 // Solo para constantes numéricas
    struct ASTNode *left;      // Hijo izquierdo
    struct ASTNode *right;     // Hijo derecho
} ASTNode;

// Funciones para crear nodos
ASTNode *create_num_node(int value);
ASTNode *create_op_node(NodeType type, ASTNode *left, ASTNode *right);
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);

#endif
