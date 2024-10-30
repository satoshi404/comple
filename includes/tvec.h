#ifndef _TVEC_H
#define _TVEC_H
#include <token.h>
#include <stdio.h>

typedef struct {
    Token** data;    
    size_t capacity;
    size_t count;
} TVec;

TVec* init_tvec(void);
void tvec_push(TVec* vec, Token* token);

#endif // _TVEC_H
