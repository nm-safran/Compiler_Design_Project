%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include AST header before parser.tab.h
#include "ast.h"

// Forward declaration of token structure
struct token {
    char* type;
    char* lexeme;
    int line;
    int column;
};

// Now include parser header
#include "parser.tab.h"

struct token* create_token(char* type, char* lexeme, int line, int column) {
    struct token* t = malloc(sizeof(struct token));
    t->type = strdup(type);
    t->lexeme = strdup(lexeme);
    t->line = line;
    t->column = column;
    return t;
}

static FILE* token_output = NULL;
static FILE* lexical_error_output = NULL;

void set_token_output(FILE* output) {
    token_output = output;
}

void set_lexical_error_output(FILE* output) {
    lexical_error_output = output;
}

int line = 1, column = 1;

void update_position(char* text) {
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
    }
}

#define RETURN_TOKEN(type, category) { \
    int start_line = line; \
    int start_col = column; \
    yylval.tok = create_token(category, yytext, start_line, start_col); \
    if (token_output) { \
        fprintf(token_output, "[%d:%d] %-12s %s\n", start_line, start_col, category, yytext); \
    } \
    update_position(yytext); \
    return type; \
}
%}

%option noyywrap

%%

[ \t]               { update_position(yytext); }
\n                  { line++; column = 1; }
\/\/.*\n            { line++; column = 1; }
\/\*([^*]|\*+[^*/])*\*+\/  { update_position(yytext); }

"class"             RETURN_TOKEN(CLASS, "KEYWORD")
"isa"               RETURN_TOKEN(ISA, "KEYWORD")
"implement"         RETURN_TOKEN(IMPLEMENT, "KEYWORD")
"func"              RETURN_TOKEN(FUNC, "KEYWORD")
"constructor"       RETURN_TOKEN(CONSTRUCTOR, "KEYWORD")
"public"            RETURN_TOKEN(PUBLIC, "KEYWORD")
"private"           RETURN_TOKEN(PRIVATE, "KEYWORD")
"attribute"         RETURN_TOKEN(ATTRIBUTE, "KEYWORD")
"local"             RETURN_TOKEN(LOCAL, "KEYWORD")
"if"                RETURN_TOKEN(IF, "KEYWORD")
"then"              RETURN_TOKEN(THEN, "KEYWORD")
"else"              RETURN_TOKEN(ELSE, "KEYWORD")
"while"             RETURN_TOKEN(WHILE, "KEYWORD")
"read"              RETURN_TOKEN(READ, "KEYWORD")
"write"             RETURN_TOKEN(WRITE, "KEYWORD")
"return"            RETURN_TOKEN(RETURN, "KEYWORD")
"integer"           RETURN_TOKEN(INTEGER_TYPE, "KEYWORD")
"float"             RETURN_TOKEN(FLOAT_TYPE, "KEYWORD")
"void"              RETURN_TOKEN(VOID, "KEYWORD")
"not"               RETURN_TOKEN(NOT, "KEYWORD")
"and"               RETURN_TOKEN(AND, "KEYWORD")
"or"                RETURN_TOKEN(OR, "KEYWORD")
"self"              RETURN_TOKEN(SELF, "KEYWORD")

[a-zA-Z][a-zA-Z0-9]* RETURN_TOKEN(ID, "IDENTIFIER")

[1-9][0-9]*         RETURN_TOKEN(INTLIT, "CONSTANT")
0                   RETURN_TOKEN(INTLIT, "CONSTANT")

([1-9][0-9]*|0)(\.[0-9]*[1-9]|\.0)([eE][+\-]?([1-9][0-9]*|0))? RETURN_TOKEN(FLOATLIT, "CONSTANT")

":="                RETURN_TOKEN(ASSIGN, "DELIMITER")
"=="                RETURN_TOKEN(EQ, "DELIMITER")
"<>"                RETURN_TOKEN(NE, "DELIMITER")
"<="                RETURN_TOKEN(LE, "DELIMITER")
">="                RETURN_TOKEN(GE, "DELIMITER")
"<"                 RETURN_TOKEN(LT, "DELIMITER")
">"                 RETURN_TOKEN(GT, "DELIMITER")
"+"                 RETURN_TOKEN(PLUS, "DELIMITER")
"-"                 RETURN_TOKEN(MINUS, "DELIMITER")
"*"                 RETURN_TOKEN(MULT, "DELIMITER")
"/"                 RETURN_TOKEN(DIV, "DELIMITER")
"=>"                RETURN_TOKEN(ARROW, "DELIMITER")

"("                 RETURN_TOKEN(LPAREN, "DELIMITER")
")"                 RETURN_TOKEN(RPAREN, "DELIMITER")
"{"                 RETURN_TOKEN(LBRACE, "DELIMITER")
"}"                 RETURN_TOKEN(RBRACE, "DELIMITER")
"["                 RETURN_TOKEN(LBRACKET, "DELIMITER")
"]"                 RETURN_TOKEN(RBRACKET, "DELIMITER")
","                 RETURN_TOKEN(COMMA, "DELIMITER")
";"                 RETURN_TOKEN(SEMI, "DELIMITER")
"."                 RETURN_TOKEN(DOT, "DELIMITER")
":"                 RETURN_TOKEN(COLON, "DELIMITER")

.                   {
    char error_msg[256];
    snprintf(error_msg, sizeof(error_msg), "Invalid character: %c at line %d, column %d\n", yytext[0], line, column);
    fprintf(stderr, "%s", error_msg);
    if (lexical_error_output) {
        fprintf(lexical_error_output, "%s", error_msg);
        fflush(lexical_error_output);
    }
    column++;
}

%%
