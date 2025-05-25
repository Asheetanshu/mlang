#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/m_tokenizer.h"
#include "../header/m_parser.h"

P_Node* parse(Token* tokens){
    P_Node *root = get_root_node();

    size_t len = 0;
    char *str;
    printf("\n\n");
    while(tokens[len].type != END_OF_TOKENS){
        str = which_token_type(tokens[len].type);
        if(tokens[len].type == SPACEBAR) len++;
        else {
            printf("%20s -> %20s\n", str, tokens[len].value);
            len++;
        }
    }
    free(str);
    print_tree(root);

    return root;

}

P_Node* get_root_node(){
    P_Node *node = calloc(1 , sizeof(P_Node));
    if (node == NULL){
        printf("Mem allocation failed \n\nAborting compilation\n\n");
        exit(1);
    }
    return node;
}



P_Node* get_token_node(Token *token){
    P_Node *node = calloc(1 , sizeof(P_Node));
    if (node == NULL){
        printf("Mem allocation failed \n\nAborting compilation\n\n");
        exit(1);
    }
    strcpy(node->value , token->value);
    node->type = token->type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(P_Node *root){
    if (root == NULL) return ;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(P_Node *root){
    if (root == NULL){
        return ;
    }
    printf("==================================\n");
    printf("ROOT : %s\n",root->value);
    printf("ROOT : %d\n",root->type);
    printf("==================================\n");
    print_tree(root->left);
    print_tree(root->right);
}
