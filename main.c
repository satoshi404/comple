#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef enum {
	TT_INT,
        TT_PLUS,
        TT_SEMI,
} TokenType;

typedef struct {
	TokenType type;
	char* value;
} Token;

typedef struct {
   	char* src;
        size_t size;
	int lptr;
} Lexer;

typedef struct {
	char identifier;
        int literal;
} Ast;

Token* token_init(TokenType type, char* value);
 
Lexer* lexer_init(char* src);
#define VEC_T Token
#define VEC_PREFIX t
#define VEC_NAME Tokens
#include "vector.h"
Tokens lexer_tokenize(Lexer* lexer);
uint8_t lexer_writespace(char wor);

int main(void){

    char* code = "4 + 4; 5 + 6;";

    Lexer* lexer = lexer_init(code);
    Tokens tokens = lexer_tokenize(lexer);
    
    for(size_t i = 0; i < tokens.count; i++){
        printf("Token -> (type:%i, value = %s)\n", tokens.data[i].type, tokens.data[i].value);
    }
    free(tokens.data);
    free(lexer);
    return 0;
}

Token* token_init(TokenType type, char* value) {
	Token* token = (Token*) calloc(1, sizeof(Token));
        token->type  = type;
        token->value = value;
        return token;
}

Lexer* lexer_init(char* src) {
	Lexer* lexer = (Lexer*) calloc(1, sizeof(Lexer));
	lexer->src   = src;
        lexer->size  = strlen(src);
	lexer->lptr  = 0;
        return lexer;
}

Tokens lexer_tokenize(Lexer* lexer) {
        Tokens tokens = {0};
	while (lexer->lptr < lexer->size) {
                char word = lexer->src[lexer->lptr];
		if (lexer_writespace(word)) {
			lexer->lptr++;
			continue;
		}
		if (isdigit(word)) {
			tpush(&tokens, *token_init(TT_INT, "INT"));
                        lexer->lptr++;
                        continue;
		} else if (word == '+') {
			tpush(&tokens, *token_init(TT_PLUS, "PLUS"));
                        lexer->lptr++;
                        continue;
		} else if (word == ';') {
			tpush(&tokens, *token_init(TT_SEMI, "SEMI"));
                        lexer->lptr++;
                        continue;
		}
		lexer->lptr++;
	}
	return tokens;
}

uint8_t lexer_writespace(char word) {
	if (word == ' ' || word == '\n' || word == '\t') return 1;
        return 0;
}
