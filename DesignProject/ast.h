#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AST Node Types
typedef enum
{
    // Program structure
    NODE_PROG,
    NODE_CLASS_DECL,
    NODE_IMPL_DEF,
    NODE_FUNC_DEF,
    NODE_FUNC_DECL,

    // Declarations
    NODE_VAR_DECL,
    NODE_PARAM,
    NODE_ARRAY_SIZE,

    // Statements
    NODE_ASSIGN_STAT,
    NODE_IF_STAT,
    NODE_WHILE_STAT,
    NODE_READ_STAT,
    NODE_WRITE_STAT,
    NODE_RETURN_STAT,

    // Expressions
    NODE_EXPR,
    NODE_REL_EXPR,
    NODE_ADD_EXPR,
    NODE_MULT_EXPR,
    NODE_NOT_EXPR,
    NODE_SIGN_EXPR,
    NODE_FUNC_CALL,
    NODE_VARIABLE,
    NODE_INTLIT,
    NODE_FLOATLIT,

    // Other
    NODE_ID,
    NODE_TYPE,
    NODE_LIST
} NodeType;

// AST Node structure
typedef struct ASTNode
{
    NodeType type;
    char *value;
    int line;
    int column;
    struct ASTNode **children;
    int num_children;
    int capacity;
    char *data_type;
    void *symbol;
    int scope_level;
} ASTNode;

// AST creation functions
ASTNode *create_node(NodeType type, const char *value, int line, int column);
void add_child(ASTNode *parent, ASTNode *child);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int depth, FILE *output);

#endif
