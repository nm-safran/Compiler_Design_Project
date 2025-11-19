%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
    char* type;
    char* lexeme;
    int line;
    int column;
};

struct symbol {
    char* lexeme;
    struct token* tok;
    struct symbol* next;
};

struct symbol* sym_table = NULL;

void add_to_symbol_table(struct token* tok) {
    struct symbol* s = malloc(sizeof(struct symbol));
    s->lexeme = strdup(tok->lexeme);
    s->tok = tok;
    s->next = sym_table;
    sym_table = s;
}

void print_symbol_table() {
    printf("\nSymbol Table\n");
    printf("-----------------------------------\n");
    printf("%-12s%-17s%-20s\n", "Token Type", "Lexeme", "Location");
    printf("-----------------------------------\n");
    for (struct symbol* s = sym_table; s; s = s->next) {
        printf("%-12s%-17sLine: %d, Column: %d\n",
               s->tok->type, s->lexeme, s->tok->line, s->tok->column);
    }
}

void print_token(struct token* tok) {
    printf("%-12s%-17sLine: %d, Column: %d\n",
           tok->type, tok->lexeme, tok->line, tok->column);
}

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}

extern int yylex();
%}

%union {
    struct token* tok;
}

%token <tok> ID INTEGER FLOAT_NUM ELSE FLOAT IF CLASS ATTRIBUTE
%token <tok> PLUS MINUS MULT DIV EQ LPAREN RPAREN LBRACE RBRACE COMMA SEMI GT

%%

program: stmt_list
       ;

stmt_list: stmt
         | stmt_list stmt
         ;

stmt: ID            { add_to_symbol_table($1); print_token($1); }
    | INTEGER       { print_token($1); }
    | FLOAT_NUM     { print_token($1); }
    | ELSE          { print_token($1); }
    | FLOAT         { print_token($1); }
    | IF            { print_token($1); }
    | CLASS         { print_token($1); }
    | ATTRIBUTE     { print_token($1); }
    | PLUS          { print_token($1); }
    | MINUS         { print_token($1); }
    | MULT          { print_token($1); }
    | DIV           { print_token($1); }
    | EQ            { print_token($1); }
    | LPAREN        { print_token($1); }
    | RPAREN        { print_token($1); }
    | LBRACE        { print_token($1); }
    | RBRACE        { print_token($1); }
    | COMMA         { print_token($1); }
    | SEMI          { print_token($1); }
    | GT            { print_token($1); }
    ;

%%

int main() {
    printf("Token Type  Lexeme           Location\n");
    printf("-----------------------------------\n");
    yyparse();
    print_symbol_table();
    return 0;
}