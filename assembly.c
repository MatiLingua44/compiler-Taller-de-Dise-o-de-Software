#include <stdio.h>
#include <stdlib.h>
#include "assembly.h"

static int temp_count = 0;

int gen_asm(ASTNode *node) {
    if (!node) return -1;
    
    switch (node->type) {
        case NODE_SEQ:
            gen_asm(node->left);
            gen_asm(node->right);
            return -1;
            
        case NODE_DECL:
            printf("  // Declarada variable: %s\n", node->simbolo->nombre);
            return -1;
            
        case NODE_ASIG: {
            int right_reg = gen_asm(node->right);
            printf("  STORE %s, R%d\n", node->left->simbolo->nombre, right_reg);
            return -1;
        }
        
        case NODE_ADD: {
            int left_reg = gen_asm(node->left);
            int right_reg = gen_asm(node->right);
            int res_reg = temp_count++;
            printf("  ADD R%d, R%d, R%d\n", res_reg, left_reg, right_reg);
            return res_reg;
        }
        
        case NODE_MUL: {
            int left_reg = gen_asm(node->left);
            int right_reg = gen_asm(node->right);
            int res_reg = temp_count++;
            printf("  MUL R%d, R%d, R%d\n", res_reg, left_reg, right_reg);
            return res_reg;
        }
        
        case NODE_INT: {
            int res_reg = temp_count++;
            printf("  LOAD R%d, %d\n", res_reg, node->simbolo->value.i_val);
            return res_reg;
        }
        
        case NODE_ID: {
            int res_reg = temp_count++;
            printf("  LOAD R%d, %s\n", res_reg, node->simbolo->nombre);
            return res_reg;
        }
        default:
            return -1;
    }
}

void generate_assembly(ASTNode *node) {
    printf("\n--- Codigo Assembly ---\n");
    temp_count = 0;
    gen_asm(node);
}
