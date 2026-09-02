%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern FILE *yyin; // Puntero al archivo de entrada de Flex/Bison

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int entero;
    float flotante;
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
%token <flotante> FLOAT
%token <texto> ID

%type <node> expresion
%type <node> asignacion

%left SUMA
%left MULTIPLICACION

%%

input:
    /* vacío */
    | input main
    ;

main:
    expresion PUNTO_COMA { print_ast($1, 0); }
    | asignacion         { print_ast($1, 0); }
    | declaracion
    ;

expresion:
    expresion SUMA expresion                        { $$ = create_op_node(NODE_ADD, $1, $3); } // { printf("Suma\n"); }
    | expresion MULTIPLICACION expresion            { $$ = create_op_node(NODE_MUL, $1, $3); } // { printf("Multiplicacion\n"); }
    | PARENTESIS_ABRE expresion PARENTESIS_CIERRA   { $$ = $2 }
    | INTEGER                                       { $$ = create_int_node($1); } // { printf("Entero: (%d)\n", $1); }
    | FLOAT                                         { $$ = create_float_node($1); } // { printf("Flotante (%f)\n", $1); }
    | ID                                            { $$ = create_id_node($1); } // { printf("ID: (%s)\n", $1); }
    ;

asignacion:
    ID IGUAL expresion PUNTO_COMA { $$ = create_asignacion_node(NODE_ASIG, create_id_node($1), $3) } // { printf("Asignacion: %s = exp;", $1); }
    ;

declaracion:
    TYPE ID PUNTO_COMA // { $$ = create_declaracion_node(NODE_DECL, $1, create_id_node()) } // { printf("Declaracion: %s %s;", $1, $2); }
    ;
    
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        // Intentar abrir el archivo pasado por argumento
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            perror(argv[1]);
            return 1;
        }
        yyin = archivo; // Redirigir la entrada de Flex al archivo
    }
    
    // Iniciar el análisis sintáctico
    yyparse();
    
    return 0;
}