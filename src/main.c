#include <stdio.h>
#include <stdlib.h>
#include <lexer.h>

/*
  Plans: for make this compiler/interpreter 

*/

int main(int argc, char** argv) {
    char* code_example = "var number: i32 = 5; puts number;";
    Lexer* lexer =  lexer_init(code_example);
    TVec* tokens = lexer_tokenize(lexer);
    for (int i = 0; i < tokens->count; i++) {
        Token* token = tokens->data[i];
        printf("Token types: %s -> ", token->name);
        printf("Token value: %i\n", token->value);
        free(token);
    }
    free(lexer);
    free(tokens->data);
    return EXIT_SUCCESS;
}