#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "semantica.h"
#include "lista.h"

// Declaramos los elementos externos de Flex y Bison
extern int yyparse(void);
extern ASTNode *root;
extern FILE *yyin; // Puntero de archivo que lee Flex

Lista *tabla_simbolos;

int main(int argc, char *argv[]) {
    // Verificar si el usuario proporcionó la ruta del archivo
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <archivo_de_entrada>\n", argv[0]);
        return 1;
    }

    // Intentar abrir el archivo en modo lectura
    FILE *archivo = fopen(argv[1], "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Redirigir la entrada de Flex hacia nuestro archivo
    yyin = archivo;

    printf("Procesando el archivo: %s...\n", argv[1]);
    
    // Ejecutar el analizador
    if (yyparse() == 0) {
        printf("\n--- Arbol de Sintaxis Abstracta (AST) Generado ---\n");
        print_ast(root, 0);

        if ( check_semantics(root) == 1 ) {
            printf("Semantica correcta\n");
        } else {
            printf("Semantica incorrecta\n");
        }
        imprimir_lista(tabla_simbolos);
        
        // Liberar memoria
        free_ast(root);
        printf("\nMemoria del AST liberada correctamente.\n");
    } else {
        printf("\nError al procesar el archivo.\n");
    }

    // Cerrar el archivo al finalizar
    fclose(archivo);
    return 0;
}