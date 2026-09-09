#!/bin/bash

# Detener el script inmediatamente si ocurre un error
set -e

echo "=== 1. Compilando el proyecto ==="
echo "[Bison] Generando parser..."
bison -d bison.y

echo "[Flex] Generando lexer..."
flex lex.l

echo "[GCC] Compilando binarios..."
gcc -Wall -Wextra -g -o compilador main.c bison.tab.c lex.yy.c ast.c lista.c semantica.c
echo "✅ Compilacion exitosa."