#ifndef _PARSER_HEADER_H
#define _PARSER_HEADER_H

#include <lexer.h>
#include <tvec.h>
#include <token.h>

typedef struct {
    //Lexer* lexer;
    TVec* tokens;
    int current_token_index;
} Parser;

Parser* parser_init(TVec* tokens);
void parser_advance(Parser* parser);
Token* parser_expect(Parser* parser, TT expected_type);
int parser_parse_number(Parser* parser);
Types parser_parse_check_type(Parser* parser);
int parser_parse_identifier(Parser* parser);
void parser_parse_function_definition(Parser* parser);
void parser_parse_parameter_list(Parser* parser);
void parser_parse_block(Parser* parser);
void parser_parse_expression(Parser* parser);
int parser_parse_primary_expression(Parser* parser);
void parser_parse(Parser* parser);
#endif // _PARSER_HEADER_H