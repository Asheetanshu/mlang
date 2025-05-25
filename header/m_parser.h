#ifndef M_PARSER_H
#define M_PARSER_H    

#include "m_tokenizer.h"


// defining structs and enums 


struct Parser_Node{
    char value[token_nameLen];
    TokenType type;
    struct Parser_Node *left ;
    struct Parser_Node *right;
};

typedef struct Parser_Node P_Node;


// defining funcitions 
void print_tree(P_Node *root);
void free_tree(P_Node *root);
P_Node* get_root_node();
P_Node* get_token_node(Token *token);
P_Node* parse(Token* tokens);


#endif
