%{
#include <stdio.h>
#include <string.h>
#include "bison.tab.h"
#include "ast.h"

// Variable global para rastrear la columna actual
int current_column = 1;

// YY_USER_ACTION se ejecuta automáticamente antes de la acción de CUALQUIER token
#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = current_column; \
    yylloc.last_column = current_column + yyleng - 1; \
    current_column += yyleng;
%}

%option noyywrap
%option yylineno

%% 
"main"              return MAIN;
"True"|"False"      return BOOLEAN;
"int"|"bool"|"void" { yylval.texto = strdup(yytext); return TYPE; }
"+"                 return SUMA;
"*"                 return MULTIPLICACION;
"="                 return IGUAL;
";"                 return PUNTO_COMA;
"("                 return PARENTESIS_ABRE;
")"                 return PARENTESIS_CIERRA;
"{"                 return CORCHETE_ABRE;
"}"                 return CORCHETE_CIERRA;
"return"            return RETURN;


0|[1-9][0-9]*               { yylval.entero = atoi(yytext); return INTEGER; }
[a-zA-Z][a-zA-Z0-9]*        { yylval.texto = strdup(yytext); return ID; }

\n                          { current_column = 1; }
[ \t]                       { /* Ignorar espacios y tabulaciones */ }
.        { printf("Lexema inesperado: %s en linea %d, columna %d\n", yytext, yylineno, yylloc.first_column); return yytext; }
%%