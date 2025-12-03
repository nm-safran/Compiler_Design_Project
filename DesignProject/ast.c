#include "ast.h"

ASTNode *create_node(NodeType type, const char *value, int line, int column)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Error: Memory allocation failed for AST node\n");
        exit(1);
    }

    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->line = line;
    node->column = column;
    node->children = NULL;
    node->num_children = 0;
    node->capacity = 0;
    node->data_type = NULL;
    node->symbol = NULL;
    node->scope_level = -1;

    return node;
}

void add_child(ASTNode *parent, ASTNode *child)
{
    if (!parent || !child)
        return;

    if (parent->num_children >= parent->capacity)
    {
        parent->capacity = parent->capacity == 0 ? 4 : parent->capacity * 2;
        parent->children = (ASTNode **)realloc(parent->children,
                                               parent->capacity * sizeof(ASTNode *));
        if (!parent->children)
        {
            fprintf(stderr, "Error: Memory allocation failed for AST children\n");
            exit(1);
        }
    }

    parent->children[parent->num_children++] = child;
}

void free_ast(ASTNode *node)
{
    if (!node)
        return;

    for (int i = 0; i < node->num_children; i++)
    {
        free_ast(node->children[i]);
    }

    free(node->children);
    free(node->value);
    free(node->data_type);
    free(node);
}

static const char *node_type_name(NodeType type)
{
    switch (type)
    {
    case NODE_PROG:
        return "PROGRAM";
    case NODE_CLASS_DECL:
        return "CLASS_DECL";
    case NODE_IMPL_DEF:
        return "IMPL_DEF";
    case NODE_FUNC_DEF:
        return "FUNC_DEF";
    case NODE_FUNC_DECL:
        return "FUNC_DECL";
    case NODE_VAR_DECL:
        return "VAR_DECL";
    case NODE_PARAM:
        return "PARAM";
    case NODE_ARRAY_SIZE:
        return "ARRAY_SIZE";
    case NODE_ASSIGN_STAT:
        return "ASSIGN";
    case NODE_IF_STAT:
        return "IF";
    case NODE_WHILE_STAT:
        return "WHILE";
    case NODE_READ_STAT:
        return "READ";
    case NODE_WRITE_STAT:
        return "WRITE";
    case NODE_RETURN_STAT:
        return "RETURN";
    case NODE_EXPR:
        return "EXPR";
    case NODE_REL_EXPR:
        return "REL_EXPR";
    case NODE_ADD_EXPR:
        return "ADD_EXPR";
    case NODE_MULT_EXPR:
        return "MULT_EXPR";
    case NODE_NOT_EXPR:
        return "NOT_EXPR";
    case NODE_SIGN_EXPR:
        return "SIGN_EXPR";
    case NODE_FUNC_CALL:
        return "FUNC_CALL";
    case NODE_VARIABLE:
        return "VARIABLE";
    case NODE_INTLIT:
        return "INTLIT";
    case NODE_FLOATLIT:
        return "FLOATLIT";
    case NODE_ID:
        return "ID";
    case NODE_TYPE:
        return "TYPE";
    case NODE_LIST:
        return "LIST";
    default:
        return "UNKNOWN";
    }
}

void print_ast(ASTNode *node, int depth, FILE *output)
{
    if (!node)
        return;

    // Print indentation
    for (int i = 0; i < depth; i++)
    {
        fprintf(output, "  ");
    }

    // Print node type
    fprintf(output, "%s", node_type_name(node->type));

    // Print value if exists
    if (node->value)
    {
        fprintf(output, " (%s)", node->value);
    }

    // Print type information if exists
    if (node->data_type)
    {
        fprintf(output, " [type: %s]", node->data_type);
    }

    // Print line number
    fprintf(output, " [line: %d]", node->line);

    fprintf(output, "\n");

    // Print children
    for (int i = 0; i < node->num_children; i++)
    {
        print_ast(node->children[i], depth + 1, output);
    }
}
