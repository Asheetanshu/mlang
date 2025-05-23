#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"


// main function________________
int main(int argc , char* argv[]){

    if (argc != 2  ){
        printf("Please enter a valid input file name\n");
        printf("mlang <path/to/your/file.mg>\n");
        return -1;
    }

    FILE* fptr = fopen(argv[1] , "r");

    if (fptr == NULL){
        printf("File does not exist \n\n");
        return -1;
    }

    Token* tokens = tokenise(fptr);
    printf("Tokenisation was successfull i think....\n");

    fclose(fptr);

    size_t i = 0;
    while(tokens[i].type != END_OF_TOKENS){
        printf("%20s -> %20s\n",which_token_type(tokens[i].type) , tokens[i].value);
        i++;
    }

    free(tokens);
    printf("File compiled successfully\n");
    return 0;

}
