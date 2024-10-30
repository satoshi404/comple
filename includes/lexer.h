#ifndef _LEXER_HEADER_H
#define _LEXER_HEADER_H
#include <tvec.h>
#include <token.h>
#include <string.h>


typedef struct {
    char* src;
    int lptr;
} Lexer;

Lexer* lexer_init(char* src);
TVec* lexer_tokenize(Lexer* lexer);

#endif // _LEXER_HEADER_H