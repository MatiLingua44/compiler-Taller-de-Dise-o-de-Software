// ast.h
#ifndef AST_H
#define AST_H

typedef enum { NODE_INT, NODE_FLOAT, NODE_ID, NODE_ADD, NODE_MUL, NODE_ASIG } NodeType;

typedef struct Simbolo {
    char *type;
    char *nombre;
    union {
        int i_val;
        float f_val;
        char *s_val;
        int b_val; // 0 para false, 1 para true
    } value;
} Simbolo;


typedef struct ASTNode {
    NodeType type;
    // int value;                 // Solo para constantes numéricas
    struct Simbolo simbolo;
    struct ASTNode *left;      // Hijo izquierdo
    struct ASTNode *right;     // Hijo derecho
} ASTNode;

// Funciones para crear nodos
ASTNode *create_int_node(int value);
ASTNode *create_float_node(float value);
ASTNode *create_id_node(char *value);
ASTNode *create_op_node(NodeType type, ASTNode *left, ASTNode *right);
ASTNode *create_asignacion_node(NodeType type, ASTNode *left, ASTNode *right);
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);

#endif
