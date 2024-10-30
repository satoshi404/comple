#include <token.h>
#include <stdlib.h>
Token* token_init(TT type, int value, char* name) {
    Token* token = (Token*) calloc(1, sizeof(Token));
    token->type = type;
    token->value = value;
    token->name = name;
    return token;
}
