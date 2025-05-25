#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/m_tokenizer.h"

Token* tokenise(FILE* fin){
    size_t i = 0;
    size_t initial_allc = 10 ; 
    size_t len = 0 ;
    int flag = 0;
    Token* tokens = calloc(sizeof(Token) , initial_allc); 
    if (tokens == NULL){
        printf("Mem allocation failed \n\nStopping compilation\n\n");
        exit(1);
    }
    char ch = fgetc(fin);
    char token_name[token_nameLen] = "";
    for (int i = 0 ; i < 1024 ; i++) token_name[i] = '\0'; 
    while(ch != EOF ){ 
        printf("%c",ch);
        if (flag != 0){
            //TODO: 
            //actual comparison of token to keyword / type / operator / identifier by better method than this... 
            if (len == initial_allc){
                initial_allc += 5;
                Token* temp = realloc(tokens , initial_allc * sizeof(Token));
                if (temp == NULL){
                    printf("Mem allocation failed \n\nStopping compilation\n\n");
                    exit(1);
                }
                tokens = temp;
            }
            tokens[len].type = which_token(token_name);
            strcpy(tokens[len].value , token_name);
            len++;
            i = 0 ;
            for (int i = 0 ; token_name[i] != '\0' || i <= token_nameLen ; i++) token_name[i] = '\0'; 
            flag = 0;
        }
        //TODO:
        //getting each token char by char by better method 
        if (is_valsym(ch)){
            flag = 1;
            token_name[i] = ch; 
            i++;
        }else if (is_equal(ch)){
            if (i != 0){
                token_name[i] = ch;
                i++;
                flag = 1;
            }else {
                token_name[i] = ch;
                i++;
                check_next(fin , is_equal , &flag);
            }
        }else if (is_underscore(ch)){
            if (i != 0){
                if (is_alpha(token_name[0])){
                    int alnum = 0 , underscore = 0;
                    check_next(fin , is_alnum , &alnum);
                    check_next(fin , is_underscore , &underscore);
                    if (alnum && underscore){
                        flag = 1;
                    }
                    token_name[i] = ch;
                    i++;
                }
                else if (is_digit(token_name[0])){
                    int number = 0 , underscore = 0;
                    check_next(fin , is_digit , &number);
                    check_next(fin , is_underscore , &underscore);
                    if (number && underscore) {
                        flag = 1;
                    }
                }
            }else {
                printf("Unwanted underscore \n\nAborting compilation\n\n");
                exit(1);
            }
        }
        else if (is_alpha(ch)){
            if (i != 0){
                if (is_alpha(token_name[0])){
                    int alnum = 0 , underscore = 0;
                    check_next(fin , is_alnum , &alnum);
                    check_next(fin , is_underscore , &underscore);
                    if (alnum && underscore){
                        flag = 1;
                    }
                    token_name[i] = ch;
                    i++;
                }
                else {
                    printf("Unwanted Charecter \n\nAborting compilation\n\n");
                    exit(1);
                }
            }
            else {
                token_name[i] = ch;
                i++;
                int alnum = 0 , underscore = 0;
                check_next(fin , is_alnum , &alnum);
                check_next(fin , is_underscore , &underscore);
                if (alnum && underscore){
                    flag = 1;
                }
            }
        }else if (is_digit(ch)){
            if (i != 0) {
                if(is_digit(token_name[0])){
                    int number = 0 , underscore = 0;
                    check_next(fin , is_digit , &number);
                    check_next(fin , is_underscore , &underscore);
                    if (number && underscore) {
                        flag = 1;
                    }
                }else if(is_alpha(token_name[0])){
                    int alnum = 0 , underscore = 0;
                    check_next(fin , is_alnum , &alnum);
                    check_next(fin , is_underscore , &underscore);
                    if (alnum && underscore){
                        flag = 1;
                    }
                }
            }else {
                int number = 0 , underscore = 0;
                check_next(fin , is_digit , &number);
                check_next(fin , is_underscore , &underscore);
                if (number && underscore) {
                    flag = 1;
                }
            }
            token_name[i] = ch;
            i++;
        }
        ch = fgetc(fin);
        if (i == (token_nameLen - 1) && flag == 0){
            printf("Compilation Failed \n\nToo long identifier\n\nexceeded name_limit\n\n");
            exit(1);
        }
    }
    tokens[len].type = END_OF_TOKENS;
    return tokens;
}

TokenType which_token(const char* token_name){
    if      (!strcmp(token_name , "(" ))        return OP_PAREN;
    else if (!strcmp(token_name , ")"))         return CL_PAREN;
    else if (!strcmp(token_name , "{"))         return OP_CURLY;
    else if (!strcmp(token_name , "}"))         return CL_CURLY;
    else if (!strcmp(token_name , "["))         return OP_SQUARE;
    else if (!strcmp(token_name , "]"))         return CL_SQUARE;
    else if (!strcmp(token_name , ";"))         return SEMI;
    else if (!strcmp(token_name , ","))         return COMMA;
    else if (!strcmp(token_name , "exit"))      return EXIT;
    else if (!strcmp(token_name , "fn"))        return FN;
    else if (!strcmp(token_name , "return"))    return RETURN;
    else if (!strcmp(token_name , "if"))        return IF;
    else if (!strcmp(token_name , "else"))      return ELSE;
    else if (!strcmp(token_name , "int"))       return K_INT;
    else if (!strcmp(token_name , "float"))     return K_FLOAT;
    else if (!strcmp(token_name , "char"))      return K_CHAR;
    else if (!strcmp(token_name , "+"))         return PLUS ;
    else if (!strcmp(token_name , "-"))         return MINUS;
    else if (!strcmp(token_name , "*"))         return MULTIPLY;
    else if (!strcmp(token_name , "/"))         return DIVIDE;
    else if (!strcmp(token_name , " "))         return SPACEBAR;
    else if (!strcmp(token_name , "="))         return ASSIGN_EQUAL;
    else if (!strcmp(token_name , "=="))        return COMPARE_EQUAL;
    // TODO : 
    // actually build the diff function for identifying int floats and rest ... 
    else if (is_digit(token_name[0]))           return L_INT;
    else if (is_alpha(token_name[0]))           return VARIABLE_NAME;
    else return END_OF_TOKENS;
}

char* which_token_type(TokenType type){
    char* res = (char*) malloc(sizeof(char) * token_Len);
    if(res == NULL){
        printf("Mem allocation failed \n\naborting compilation\n\n");
        exit(1);
    }
    if (type <= SEPARATOR_END) strcpy(res , "SEPARATOR");
    else if (type <= OPERATOR_END) strcpy(res , "OPERATOR");
    else if (type <= KEYWORD_END) strcpy(res , "KEYWORD");
    else if (type <= LITERAL_END) strcpy(res , "LITERAL");
    else if (type < END_OF_TOKENS) strcpy(res ,"IDENTIFIER");
    else strcpy(res , "OTHERS");
    return res;
}

void check_next(FILE *fin , int (*fn)(char ch) , int *flag){
    long pos = ftell(fin);
    char fch = fgetc(fin);
    if (!fn(fch)){
        *flag = 1;
    }
    fseek(fin , pos , SEEK_SET);
}
int is_alnum(char ch){
    return 
        (ch>= 'A' && ch<= 'Z') || 
        (ch>= 'a' && ch<= 'z') ||
        (ch>= '0' && ch<= '9');
}


int is_alpha(char ch){
    return 
        (ch>= 'A' && ch<= 'Z') || 
        (ch>= 'a' && ch<= 'z') ;
}

int is_digit(char ch){
    return (ch >= '0' && ch <= '9');
}


int is_valsym(char ch){
    char* valid_symbol = "(){}[];,+-*/ ";
    for (int i = 0 ; valid_symbol[i] != '\0';i++){
        if (valid_symbol[i] == ch) {
            return 1;
        }
    }
    return 0;
}

int is_equal(char ch){
    return ch == '=';
}

int is_underscore(char ch){
    return ch == '_';
}
