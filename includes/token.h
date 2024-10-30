#ifndef _TOKEN_HEADER_H
#define _TOKEN_HEADER_H


typedef enum { 
    TT_NUMBER_ ,
    TT_PLUS_ ,
    TT_I32_ ,
    TT_MINUS_ ,
    TT_TIMES_ ,
    TT_ASSIGN_ ,
    TT_LT_ ,
    TT_GT_ ,
    TT_LE_ ,
    TT_GE_ ,
    TT_EQ_ ,
    TT_NEQ_ ,
    TT_AND_ ,
    TT_OR_ ,
    TT_NOT_ ,
    TT_IF_ ,
    TT_ELSE_ ,
    TT_WHILE_ ,
    TT_PUTS_ ,
    TT_RETURN_ ,
    TT_FUNCTION_ ,
    TT_LBRACE_ ,
    TT_RBRACE_ ,
    TT_LBRACKET_ ,
    TT_RBRACKET_ ,
    TT_COMMA_ ,
    TT_DOT_ ,
    TT_DIVIDE_ ,
    TT_LPAREN_ ,
    TT_RPAREN_ ,
    TT_SEMI_ ,
    TT_IDENTIFIER_ ,
    TT_VAR_ ,
}  TT;


typedef struct {
    TT type;
    int value;
    char* name;
} Token;

Token* token_init(TT type, int value, char* name);


#endif // _TOKEN_HEADER_H