@echo off
echo === 1. Compilando el proyecto ===

echo [Bison] Generando parser...
bison -d bison.y
if %errorlevel% neq 0 (echo ❌ Error en Bison && exit /b %errorlevel%)

echo [Flex] Generando lexer...
flex lex.l
if %errorlevel% neq 0 (echo ❌ Error en Flex && exit /b %errorlevel%)

echo [GCC] Compilando binarios...
gcc -Wall -Wextra -g -o compilador main.c bison.tab.c lex.yy.c ast.c lista.c semantica.c assembly.c
if %errorlevel% neq 0 (echo ❌ Error en GCC && exit /b %errorlevel%)
echo Compilacion exitosa.