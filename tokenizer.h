#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>

#define token_nameLen 1024
#define token_Len 20


// definig enums and structs for tokenizer
typedef enum {    

    // defining separators
    SEPARATOR_START,
    OP_PAREN = SEPARATOR_START,
    CL_PAREN,
    OP_CURLY,
    CL_CURLY,
    OP_SQUARE,
    CL_SQUARE,
    SEMI,
    COMMA,
    SPACEBAR,
    SEPARATOR_END = SPACEBAR,

    // defining operators
    OPERATOR_START,
    PLUS = OPERATOR_START,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN_EQUAL,
    COMPARE_EQUAL, 
    OPERATOR_END = COMPARE_EQUAL,

    // defining keywords
    KEYWORD_START,
    EXIT = KEYWORD_START,
    RETURN,
    IF,
    ELSE,
    K_INT,
    K_FLOAT,
    K_CHAR,
    KEYWORD_END = K_CHAR,

    // defining literals
    LITERAL_START,
    L_INT = LITERAL_START,
    L_FLOAT,
    L_CHAR,
    LITERAL_END = L_CHAR,

    // defining others...
    VARIABLE_NAME,
    END_OF_TOKENS,
}TokenType;

typedef struct {
    TokenType type;
    char value[token_nameLen];
}Token;

// helper function
int is_alnum(char ch);
int is_alpha(char ch);
int is_digit(char ch);
int is_valsym(char ch);
int is_equal(char ch);
void check_next(FILE *fin , int (*fn)(char ch) , int *flag);

// actual tokenizer funtions...
TokenType which_token(const char* token_name);
char* which_token_type(TokenType type);
Token* tokenise(FILE* fin);



#endif
