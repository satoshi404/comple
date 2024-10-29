#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef enum {
    TT_INT,
    TT_PLUS,
    TT_SEMI,
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

#define VEC_T Token
#define VEC_PREFIX t
#define VEC_NAME Tokens
#include "vector.h"

typedef struct {
    char* src;
    size_t size;
    int lptr;
} Lexer;

typedef enum {
    NODE_INT,
    NODE_ADD,
} NodeType;

typedef struct Node {
    NodeType type;
    struct Node* left;
    struct Node* right;
    int value; // Usado apenas para NODE_INT
} Node;

typedef struct {
    Tokens tokens;
    int pptr;
} Parser;

// Funções de inicialização
Token* token_init(TokenType type, int value);
Lexer* lexer_init(char* src);
Tokens lexer_tokenize(Lexer* lexer);
uint8_t lexer_writespace(char wor);
Parser* parser_init(Tokens tokens);
void parser_parse(Parser* parser);
Node* init_int_node(int value);
Node* init_add_node(Node* left, Node* right);
Node* parser_expression(Parser* parser);
Node* parser_term(Parser* parser);
Node* parser_factor(Parser* parser);
int evaluate(Node* node);

int main(void) {
    char* code = "4 + 5 + 4; 5 + 6;";

    Lexer* lexer = lexer_init(code);
    Tokens tokens = lexer_tokenize(lexer);
    Parser* parser = parser_init(tokens);
    parser_parse(parser);

    free(tokens.data);
    free(lexer);
    free(parser);
    
    return 0;
}

Token* token_init(TokenType type, int value) {
    Token* token = (Token*) calloc(1, sizeof(Token));
    token->type  = type;
    token->value = value;
    return token;
}

Lexer* lexer_init(char* src) {
    Lexer* lexer = (Lexer*) calloc(1, sizeof(Lexer));
    lexer->src   = src;
    lexer->size  = strlen(src);
    lexer->lptr  = 0;
    return lexer;
}

Tokens lexer_tokenize(Lexer* lexer) {
    Tokens tokens = {0};
    
    while (lexer->lptr < lexer->size) {
        char word = lexer->src[lexer->lptr];
        if (lexer_writespace(word)) {
            lexer->lptr++;
            continue;
        }
        if (isdigit(word)) {
            tpush(&tokens, *token_init(TT_INT, word - '0'));
            lexer->lptr++;
            continue;
        } else if (word == '+') {
            tpush(&tokens, *token_init(TT_PLUS, 0));
            lexer->lptr++;
            continue;
        } else if (word == ';') {
            tpush(&tokens, *token_init(TT_SEMI, 0));
            lexer->lptr++;
            continue;
        }
        lexer->lptr++;
    }
    
    return tokens;
}

uint8_t lexer_writespace(char word) {
    return (word == ' ' || word == '\n' || word == '\t');
}

Parser* parser_init(Tokens tokens) {
    Parser* parser = (Parser*) calloc(1, sizeof(Parser));
    parser->tokens = tokens;
    parser->pptr = 0;
    
    return parser;
}

void parser_parse(Parser* parser) {
    while (parser->pptr < parser->tokens.count) {
        Node* root = parser_expression(parser);

        if (parser->pptr < parser->tokens.count && 
            parser->tokens.data[parser->pptr].type == TT_SEMI) {
            printf("Value is %i\n", evaluate(root));
            free(root); // Libere a memória da árvore após a avaliação
            parser->pptr++; // Consome ';'
        } else {
            printf("Parser::ERROR: Expected ; after expression\n");
            free(root); // Libere a memória da árvore em caso de erro
            break;
        }
        
        // Verifica se ainda há mais tokens para processar
        if (parser->pptr >= parser->tokens.count) break; 
    }
}

Node* init_int_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->type = NODE_INT;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node* init_add_node(Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->type = NODE_ADD;
    node->left = left;
    node->right = right;

    return node;
}

Node* parser_expression(Parser* parser) {
    Node* left = parser_term(parser);

    while (parser->pptr < parser->tokens.count &&
           (parser->tokens.data[parser->pptr].type == TT_PLUS)) {
        parser->pptr++; // Consume '+'
        
        Node* right = parser_term(parser);
        left = init_add_node(left, right);
        
        // Verifica se ainda há mais tokens para processar
        if (parser->pptr >= parser->tokens.count) break; 
    }

    return left; // Retorna a árvore construída
}

Node* parser_term(Parser* parser) {
     return parser_factor(parser); // Para simplificação, não estamos lidando com multiplicação/divisão
}

Node* parser_factor(Parser* parser) {
     if (parser->pptr < parser->tokens.count && 
         parser->tokens.data[parser->pptr].type == TT_INT) {
         int value = parser->tokens.data[parser->pptr].value;
         parser->pptr++; // Consume integer token
         return init_int_node(value);
     }

     // Aqui você pode adicionar suporte para parênteses se necessário
     return NULL; // Retorna NULL se não houver fator válido
}

int evaluate(Node* node) {
     switch (node->type) {
         case NODE_INT:
             return node->value;
         case NODE_ADD:
             return evaluate(node->left) + evaluate(node->right);
         default:
             return 0; // Erro inesperado
     }
}
