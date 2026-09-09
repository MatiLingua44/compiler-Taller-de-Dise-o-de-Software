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
            // printf("  // Declarada variable: %s\n", node->simbolo->nombre);
            return -1;
            
        case NODE_ASIG: {
            int right_reg = gen_asm(node->right);
            printf("  Store_Mem R%d, %s\n", right_reg, node->left->simbolo->nombre);
            return -1;
        }
        
        case NODE_ADD: {
            int left_reg = gen_asm(node->left);
            int right_reg = gen_asm(node->right);
            int res_reg = temp_count++;
            printf("  Add_Reg R%d, R%d, R%d\n", left_reg, right_reg, res_reg);
            return res_reg;
        }
        
        case NODE_MUL: {
            int left_reg = gen_asm(node->left);
            int right_reg = gen_asm(node->right);
            int res_reg = temp_count++;
            printf("  Mul_Reg R%d, R%d, R%d\n", left_reg, right_reg, res_reg);
            return res_reg;
        }
        
        case NODE_INT: {
            int res_reg = temp_count++;
            printf("  Load_Const %d, R%d\n", node->simbolo->value.i_val, res_reg);
            return res_reg;
        }
        
        case NODE_ID: {
            int res_reg = temp_count++;
            printf("  Load_Mem %s, R%d\n", node->simbolo->nombre, res_reg);
            return res_reg;
        }
        default:
            return -1;
    }
}

void generate_assembly(ASTNode *node) {
    printf("\n--- Codigo Tres Direcciones ---\n");
    temp_count = 0;
    gen_asm(node);
}
