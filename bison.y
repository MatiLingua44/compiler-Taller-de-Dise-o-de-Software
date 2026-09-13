%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);

// Definición de la raíz global del AST
ASTNode *root = NULL;

%}

%locations

%union {
    int entero;
    char *texto;
    struct ASTNode *node;
}

%token MAIN
%token BOOLEAN
%token <texto> TYPE
%token SUMA MULTIPLICACION
%token IGUAL
%token PUNTO_COMA
%token PARENTESIS_ABRE PARENTESIS_CIERRA
%token CORCHETE_ABRE CORCHETE_CIERRA
%token RETURN

%token <entero> INTEGER
%token <texto> ID

%type <node> programa statement statement_list
%type <node> expresion
%type <node> asignacion
%type <node> declaracion

%left SUMA
%left MULTIPLICACION

%%

programa:
    /* INICIO PROGRAMA */
    statement_list { root = $1; }
    ;

statement_list:
    statement                  { $$ = $1; }
    | statement_list statement { $$ = create_seq_node($1, $2); }
    ;

statement:
    asignacion         { $$ = $1; }
    | declaracion      { $$ = $1; }
    ;

expresion:
    expresion SUMA expresion                        { $$ = create_op_node(NODE_ADD, $1, $3); }
    | expresion MULTIPLICACION expresion            { $$ = create_op_node(NODE_MUL, $1, $3); }
    | PARENTESIS_ABRE expresion PARENTESIS_CIERRA   { $$ = $2; }
    | INTEGER                                       { $$ = create_int_node($1); }
    | ID                                            { $$ = create_id_node($1); }
    ;

asignacion:
    ID IGUAL expresion PUNTO_COMA { $$ = create_asignacion_node(NODE_ASIG, create_id_node($1), $3); }
    ;

declaracion:
    TYPE ID PUNTO_COMA { $$ = create_declaracion_node($1, $2, NULL, NULL); }
    ;
    
%%

// Implementación de yyerror usando la variable global yylloc de Bison
void yyerror(const char *s) {
    fprintf(stderr, "Error Sintactico en la linea %d, columna %d: %s\n", 
            yylloc.first_line, yylloc.first_column, s);
}