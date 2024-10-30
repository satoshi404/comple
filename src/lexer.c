#include <lexer.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


Lexer* lexer_init(char* src) {
    Lexer* lexer = (Lexer*) calloc(1, sizeof(Lexer));
    lexer->src = src;
    lexer->lptr = 0;
    return lexer;
}

TVec* lexer_tokenize(Lexer* lexer) {
    TVec* tokens = init_tvec();
    while (lexer->lptr < strlen(lexer->src)) {
        char c = lexer->src[lexer->lptr];
        
        // Skip whitespace
        if (c == ' ' || c == '\t' || c == '\n') {
            lexer->lptr++;
            continue;
        }
        
        // Check for operators and punctuation marks
        if (strncmp(&lexer->src[lexer->lptr], "var", 3) == 0) {
            tvec_push(tokens, token_init(TT_VAR_, 0, "VAR"));
            lexer->lptr+=3;
            continue;
        }  else if (strncmp(&lexer->src[lexer->lptr], "puts", 4) == 0) {
            tvec_push(tokens, token_init(TT_PUTS_, 0, "PUTS"));
            lexer->lptr+=4;
            continue;
        } else if (strncmp(&lexer->src[lexer->lptr], "i32", 3) == 0) {
            tvec_push(tokens, token_init(TT_I32_, 0, "I32"));
            lexer->lptr+=3;
            continue;
        } else if (isalpha(c)) {
            char* name = (char*) malloc(sizeof(char));
            size_t cap = 1;
            int i = 0;
            while (isalpha(lexer->src[lexer->lptr])) {
                if (i == cap) {
                    cap*=2;
                    name = realloc(name, cap * sizeof(char));
                }
                name[i++] = lexer->src[lexer->lptr];
                lexer->lptr++;
            }
            name[i] = '\0';
            tvec_push(tokens, token_init(TT_IDENTIFIER_, 0, name));
        
            continue;
        }  else if (isdigit(c)) {
            int value = 0;
            while (lexer->lptr < strlen(lexer->src) &&
                   lexer->src[lexer->lptr] >= '0' && lexer->src[lexer->lptr] <= '9') {
                value = value * 10 + (lexer->src[lexer->lptr] - '0');
                lexer->lptr++;
            }
            tvec_push(tokens, token_init(TT_NUMBER_, value, "NUMBER"));
            continue;
        } else if (c == '+') {
            tvec_push(tokens, token_init(TT_PLUS_, 0, "PLUS"));
            lexer->lptr++;
            continue;
        } else if (c == '=') {
            tvec_push(tokens, token_init(TT_EQ_, 0, "EQUAL"));
            lexer->lptr++;
            continue;
        } else if (c == ':') {
            tvec_push(tokens, token_init(TT_COMMA_, 0, "COMMA"));
            lexer->lptr++;
            continue;
        } else if (c == ';') {
            tvec_push(tokens, token_init(TT_SEMI_, 0, "SEMI"));
            lexer->lptr++;
            continue;
        } else {
            printf("ERROR::Lexer_tokenize -> Unknown token\n");
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}
