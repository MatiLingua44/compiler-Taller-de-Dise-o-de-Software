# compiler-Taller-de-Dise-o-de-Software

Cómo compilar:
- bison -d bison.y
- flex lex.l
- gcc bison.tab.c lex.yy.c ast.c -o compilador

Para correr el archivo de prueba:
- ./compilador texto.txt
