#include <parser.h>
#include <stdlib.h>

Parser* parser_init(TVec* tokens) {
    Parser* parser = (Parser*) calloc(1, sizeof(Parser));
    parser->tokens = tokens;
    parser->current_token_index = 0;
   return parser;
}

void parser_advance(Parser* parser) {
    parser->current_token_index++;
}

Token* parser_expect(Parser* parser, TT expected_type) {
    Token* token = parser->tokens->data[parser->current_token_index];
    if (token->type != expected_type) {
        fprintf(stderr, "Expected token type %s, got %s\n", token_type_to_string(expected_type), token_type_to_string(token->type));
        exit(EXIT_FAILURE);
    }
    parser_advance(parser);
    return token;
}

void parser_parse(Parser* parser) {
    while (parser->current_token_index < parser->tokens->count) {
        Token* token = parser->tokens->data[parser->current_token_index];
        if (token->type == TT_FUNCTION_) {
            parser_advance(parser); // Consume the function
            parser_parse_function_definition(parser);
            continue;
        }
        parser_parse_expression(parser);
    }
}

void parser_parse_function_definition(Parser* parser) {
    parser_expect(parser, TT_COLON_);
    // TODO: This is type return of function i32 (int)
    Types type = parser_parse_check_type(parser);
    parser_expect(parser, TT_TYPE_);
    Token* func = parser_expect(parser, TT_IDENTIFIER_);
    printf("function name: %s\n", func->name);
    parser_expect(parser, TT_LPAREN_);
    parser_parse_parameter_list(parser);
    parser_expect(parser, TT_RPAREN_);
    parser_expect(parser, TT_LBRACE_);
    parser_parse_block(parser);
    parser_expect(parser, TT_RBRACE_);
    // FIXME: Implement function body parsing
    // TODO: Handle return statement
    // TODO: Handle variable declaration
}


void parser_parse_parameter_list(Parser* parser) {
    Token* arg1 = parser_expect(parser, TT_IDENTIFIER_);
    parser_expect(parser, TT_COLON_);
    // FIXME: This works only i32 (int) type
    Types type = parser_parse_check_type(parser);
    parser_expect(parser, TT_TYPE_);
    parser_expect(parser, TT_COMMA_);
    Token* arg2 = parser_expect(parser, TT_IDENTIFIER_);
    parser_expect(parser, TT_COLON_);
    parser_expect(parser, TT_VECTOR_);
    parser_expect(parser, TT_LPAREN_);
    parser_expect(parser, TT_TYPE_);
    parser_expect(parser, TT_RPAREN_);
}

void parser_parse_block(Parser* parser) {
    printf("--------------------------------\n");
    while (parser->current_token_index < parser->tokens->count) {
        Token* token = parser->tokens->data[parser->current_token_index];
        if (token->type == TT_RBRACE_) {
            break;
        }
        parser_parse_expression(parser);
    }
    printf("--------------------------------\n");

}

void parser_parse_expression(Parser* parser) {
    // TODO: Implement expression parsing
    Token* token = parser->tokens->data[parser->current_token_index];
    printf("Parsing expression: %s\n", token_type_to_string(token->type));
    parser_advance(parser);
}


Types parser_parse_check_type(Parser* parser) {
    Token* token = parser->tokens->data[parser->current_token_index];
    if (token->value == TYPE_I32_ || token->value == TYPE_STRING_) {
        return token->value; 
    } else {
        printf("Invalid token type \n");
        exit(EXIT_FAILURE);
    }
}