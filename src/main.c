#include <stdio.h>
#include <stdlib.h>
#include <parser.h>

/*
  Plans: for make this compiler/interpreter 
*/

int main(int argc, char** argv) {
    FILE* file = open_file("examples/main.co",  "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: main.co\n");
        exit(EXIT_FAILURE);
    }
    char* code = read_file(file);
    close_file(file);

    Lexer* lexer =  lexer_init(code);
    TVec* tokens = lexer_tokenize(lexer);
    Parser* parser = parser_init(tokens);
    parser_parse(parser);
    // for (int i = 0; i < tokens->count; i++) {
    //     Token* token = tokens->data[i];
    //     printf("Token types: %s -> ", token->name);
    //     printf("Token value: %i\n", token->value);
    //     free(token);
    // }

    free(lexer);
    free(tokens->data);
    return EXIT_SUCCESS;
}