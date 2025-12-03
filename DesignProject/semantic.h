#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symboltable.h"

// Semantic error structure
typedef struct SemanticError
{
  char *message;
  int line;
  int column;
  char *error_type; // ERROR or WARNING
  struct SemanticError *next;
} SemanticError;

// Semantic analyzer context
typedef struct
{
  SymbolTable *global_table;
  SymbolTable *current_table;
  SemanticError *errors;
  int error_count;
  int warning_count;
  FILE *error_file;
} SemanticContext;

// Semantic analysis functions
SemanticContext *create_semantic_context();
void semantic_analysis(ASTNode *ast, SemanticContext *context);
void generate_symbol_tables(ASTNode *node, SemanticContext *context);
void type_check(ASTNode *node, SemanticContext *context);
void report_error(SemanticContext *context, const char *type, const char *msg, int line, int col);
void print_errors(SemanticContext *context, FILE *output);
void free_semantic_context(SemanticContext *context);

#endif
