%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin; // Puntero al archivo de entrada de Flex/Bison

int yylex(void);
void yyerror(const char *s);
%}

%token MAIN
%token BOOLEAN
%token TYPE
%token SUMA MULTIPLICACION
%token IGUAL
%token PUNTO_COMA
%token PARENTESIS_ABRE PARENTESIS_CIERRA
%token CORCHETE_ABRE CORCHETE_CIERRA
%token RETURN

%token INTEGER
%token ID

%left SUMA
%left MULTIPLICACION

%%

input:
    /* vacío */
    | input main
    ;

main:
    expresion '\n'
    | asignacion
    | declaracion
    ;

expresion:
    expresion SUMA expresion                        { printf("Suma\n"); }
    | expresion MULTIPLICACION expresion            { printf("Multiplicacion\n"); }
    | PARENTESIS_ABRE expresion PARENTESIS_CIERRA
    | INTEGER
    | ID
    ;

asignacion:
    ID IGUAL expresion PUNTO_COMA { printf("asignacion"); }
    ;

declaracion:
    TYPE ID PUNTO_COMA { printf("declaracion"); }
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