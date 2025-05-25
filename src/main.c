#include <stdio.h>
#include <stdlib.h>
#include "../header/m_tokenizer.h"
#include "../header/m_parser.h"


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

    P_Node *root = parse(tokens);

    free(tokens);
    free_tree(root);
    printf("File compiled successfully\n");
    return 0;

}
