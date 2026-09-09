#ifndef SEMANTICA_H
#define SEMANTICA_H

#include "ast.h"
#include "lista.h"

// Función principal para chequear la semántica del AST
// Retorna 1 si es válido, 0 si encuentra algún error semántico
int check_semantics(ASTNode *node);

#endif
