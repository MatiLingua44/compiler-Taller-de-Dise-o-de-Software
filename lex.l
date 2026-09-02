%{
#include <stdio.h>
#include <string.h>
#include "bison.tab.h"
#include "ast.h"
%}

%option noyywrap

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
(0|[1-9][0-9]*)\.[0-9]+     { yylval.flotante = atof(yytext); return FLOAT; }
[a-zA-Z][a-zA-Z0-9]*        { yylval.texto = strdup(yytext); return ID; }
.        { /* Ignore other characters */ }
%%