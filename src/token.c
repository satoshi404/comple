#include <token.h>
#include <stdlib.h>
Token* token_init(TT type, int value, char* name) {
    Token* token = (Token*) calloc(1, sizeof(Token));
    token->type = type;
    token->value = value;
    token->name = name;
    return token;
}

char* token_type_to_string(TT type) {
    switch (type) {
        case TT_NUMBER_:
            return "NUMBER"; break;
        case TT_PLUS_ :
            return "PLUS"; break;
        case TT_VECTOR_ :
            return "VECTOR"; break;
        case TT_COMMENT_ :
            return "COMMENT "; break;
        case TT_TYPE_ :
            return "TYPE"; break;
        case TT_MINUS_ :
            return "MINUS"; break;
        case TT_TIMES_ :
            return "TIMES"; break;
        case TT_DIV_ :
            return "DIV"; break;
        case TT_ASSIGN_ :
            return "ASSIGN"; break;
        case TT_LT_ :
            return "LT"; break;
        case TT_GT_ :
            return "GT"; break; 
        case TT_LE_ :
            return "LE";  break; 
        case TT_GE_ :
            return "GE";  break; 
        case TT_EQ_ :
            return "EQ";  break; 
        case TT_NEQ_ :
            return "NEQ";  break; 
        case TT_AND_ :
            return "AND";  break; 
        case TT_OR_ :
            return "OR";  break; 
        case TT_NOT_ :
            return "NOT";  break; 
        case TT_IF_ :
            return "IF";  break; 
        case TT_ELSE_ :
            return "ELSE";  break; 
        case TT_WHILE_ :
            return "WHILE";  break; 
        case TT_PUTS_ :
            return "PUTS";  break; 
        case TT_RETURN_ :
            return "RETURN";  break; 
        case TT_FUNCTION_:
            return "FUNCTION";  break; 
        case TT_LBRACE_:
            return "LBRACE";  break; 
        case TT_RBRACE_:
            return "RBRACE";  break; 
        case TT_LBRACKET_:
            return "LBRACKET";  break; 
        case TT_RBRACKET_:
            return "RBRACKET";  break; 
        case TT_COMMA_:
            return "COMMA";  break; 
        case TT_COLON_:
            return "COLON"; break; 
        case TT_DOT_:
            return "DOT"; break; 
        case TT_LPAREN_ :
            return "LPAREN"; break; 
        case TT_RPAREN_ :
            return "RPAREN"; break; 
        case TT_SEMI_ :
            return "SEMI"; break; 
        case TT_IDENTIFIER_:
            return "IDENTIFIER"; break; 
        case TT_VAR_ :
            return "VAR"; break;
        default:
            return "UNKNOWN";  break; 
        }
}
