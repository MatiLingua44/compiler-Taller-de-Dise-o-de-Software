%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin; // Puntero al archivo de entrada de Flex/Bison

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int entero;
    float flotante;
    char *texto;
    struct ASTNode *node_val;
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

%left SUMA
%left MULTIPLICACION

%%

input:
    /* vacío */
    | input main
    ;

main:
    expresion PUNTO_COMA
    | asignacion
    | declaracion
    ;

expresion:
    expresion SUMA expresion                        { printf("Suma\n"); }
    | expresion MULTIPLICACION expresion            { printf("Multiplicacion\n"); }
    | PARENTESIS_ABRE expresion PARENTESIS_CIERRA   // { $$ = $2 }
    | INTEGER                                       { printf("Entero: (%d)\n", $1); }
    | FLOAT                                         { printf("Flotante (%f)\n", $1); }
    | ID                                            { printf("ID: (%s)\n", $1); }
    ;

asignacion:
    ID IGUAL expresion PUNTO_COMA { printf("Asignacion: %s = exp;", $1); }
    ;

declaracion:
    TYPE ID PUNTO_COMA { printf("Declaracion: %s %s;", $1, $2); }
    | TYPE asignacion { printf("<- Con declaracion"); }
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