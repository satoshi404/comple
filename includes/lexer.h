#ifndef _LEXER_HEADER_H
#define _LEXER_HEADER_H
#include <tvec.h>
#include <token.h>
#include <string.h>

typedef enum {
    TYPE_I32_,
    TYPE_I64_,
    TYPE_F32_,
    TYPE_F64_,
    TYPE_BOOL_,
    TYPE_CHAR,
    TYPE_STRING_,
}  Types;

typedef struct {
    char* src;
    int lptr;
} Lexer;

Lexer* lexer_init(char* src);
TVec* lexer_tokenize(Lexer* lexer);

#endif // _LEXER_HEADER_H