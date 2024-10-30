#include <tvec.h>
#include <stdlib.h>

TVec* init_tvec(void) {
    TVec* vec = (TVec*) calloc(1, sizeof(TVec));
    vec->capacity = 1;
    vec->count = 0;
    vec->data = (Token**) malloc(vec->capacity * sizeof(Token*));
    return vec;
}

void tvec_push(TVec* vec, Token* token) {
    if (vec->count == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(Token*));
    }
    vec->data[vec->count++] = token;
}

