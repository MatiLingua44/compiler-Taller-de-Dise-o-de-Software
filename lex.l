%{
#include <stdio.h>
#include "bison.tab.h"
%}

%% 
"main"              return MAIN;
"True"|"False"      return BOOLEAN;
"int"|"bool"|"void" return TYPE;
"+"                 return SUMA;
"*"                 return MULTIPLICACION;
"="                 return IGUAL;
";"                 return PUNTO_COMA;
"("                 return PARENTESIS_ABRE;
")"                 return PARENTESIS_CIERRA;
"{"                 return CORCHETE_ABRE;
"}"                 return CORCHETE_CIERRA;
"return"            return RETURN;


0|[1-9][0-9]*               return INTEGER;
(0|[1-9][0-9]*)\.[0-9]+     return FLOAT;
[a-zA-Z][a-zA-Z0-9]*        return ID;
.        { /* Ignore other characters */ }
%%

//int main() {
//    yyin = fopen("texto.txt", "r");
//    yylex();
//    fclose(yyin);
    
//    return 0;
//}

int yywrap() {
    return 1;
}