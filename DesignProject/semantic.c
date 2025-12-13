#include "semantic.h"

SemanticContext *create_semantic_context(const char *error_log_path)
{
  SemanticContext *ctx = (SemanticContext *)malloc(sizeof(SemanticContext));
  ctx->global_table = create_symbol_table("global", 0, NULL);
  ctx->current_table = ctx->global_table;
  ctx->errors = NULL;
  ctx->error_count = 0;
  ctx->warning_count = 0;

  // Allow per-test or shared logging; default to semantic_errors.txt
  const char *path = error_log_path ? error_log_path : "semantic_errors.txt";
  ctx->error_file = fopen(path, "w");
  // Note: Header will be written when print_errors is called

  return ctx;
}

void report_error(SemanticContext *context, const char *type, const char *msg, int line, int col)
{
  SemanticError *error = (SemanticError *)malloc(sizeof(SemanticError));
  error->message = strdup(msg);
  error->line = line;
  error->column = col;
  error->error_type = strdup(type);
  error->next = context->errors;
  context->errors = error;

  if (strcmp(type, "ERROR") == 0)
    context->error_count++;
  else
    context->warning_count++;
}

static void traverse_class_decl(ASTNode *node, SemanticContext *ctx)
{
  if (node->num_children < 1)
    return;

  ASTNode *id_node = node->children[0];
  char *class_name = id_node->value;

  // Check if class already declared
  if (lookup_symbol(ctx->current_table, class_name))
  {
    char msg[256];
    sprintf(msg, "Class '%s' already declared", class_name);
    report_error(ctx, "ERROR", msg, node->line, node->column);
    return;
  }

  // Add class to symbol table
  Symbol *class_sym = create_symbol(class_name, SYM_CLASS, class_name, node->line, node->column);
  add_symbol(ctx->current_table, class_sym);

  // Create scope for class members
  SymbolTable *class_table = create_symbol_table(class_name, ctx->current_table->level + 1, ctx->current_table);
  class_sym->class_scope = class_table;

  // Add class scope as child of current table
  add_child_scope(ctx->current_table, class_table);

  SymbolTable *prev_table = ctx->current_table;
  ctx->current_table = class_table;

  // Process members
  for (int i = 1; i < node->num_children; i++)
  {
    generate_symbol_tables(node->children[i], ctx);
  }

  ctx->current_table = prev_table;
}

static void traverse_func_def(ASTNode *node, SemanticContext *ctx)
{
  if (node->num_children < 1)
    return;

  ASTNode *func_head = node->children[0];
  if (func_head->num_children < 1)
    return;

  ASTNode *id_node = func_head->children[0];
  char *func_name = id_node->value;

  // Determine return type
  char *return_type = "void";
  for (int i = 0; i < func_head->num_children; i++)
  {
    if (func_head->children[i]->type == NODE_TYPE)
    {
      return_type = func_head->children[i]->value;
      break;
    }
  }

  // Check if function already declared in current scope
  if (lookup_symbol(ctx->current_table, func_name))
  {
    char msg[256];
    sprintf(msg, "Function '%s' already declared", func_name);
    report_error(ctx, "ERROR", msg, node->line, node->column);
    return;
  }

  Symbol *func_sym = create_symbol(func_name, SYM_FUNCTION, return_type, node->line, node->column);
  add_symbol(ctx->current_table, func_sym);

  // Create function scope
  SymbolTable *func_table = create_symbol_table(func_name, ctx->current_table->level + 1, ctx->current_table);

  // Add function scope as child of current table
  add_child_scope(ctx->current_table, func_table);

  SymbolTable *prev_table = ctx->current_table;
  ctx->current_table = func_table;

  // Process parameters and body
  for (int i = 1; i < node->num_children; i++)
  {
    generate_symbol_tables(node->children[i], ctx);
  }

  ctx->current_table = prev_table;
}

static void traverse_var_decl(ASTNode *node, SemanticContext *ctx)
{
  if (node->num_children < 2)
    return;

  ASTNode *id_node = node->children[0];
  ASTNode *type_node = node->children[1];

  char *var_name = id_node->value;
  char *var_type = type_node->value;

  // Check if variable already declared in current scope
  if (lookup_symbol(ctx->current_table, var_name))
  {
    char msg[256];
    sprintf(msg, "Variable '%s' already declared in this scope", var_name);
    report_error(ctx, "ERROR", msg, node->line, node->column);
    return;
  }

  Symbol *var_sym = create_symbol(var_name, SYM_VARIABLE, var_type, node->line, node->column);

  // Process array dimensions
  for (int i = 2; i < node->num_children; i++)
  {
    if (node->children[i]->type == NODE_ARRAY_SIZE)
    {
      int size = node->children[i]->value ? atoi(node->children[i]->value) : 0;
      add_dimension(var_sym->type, size);
    }
  }

  add_symbol(ctx->current_table, var_sym);
}

void generate_symbol_tables(ASTNode *node, SemanticContext *ctx)
{
  if (!node)
    return;

  switch (node->type)
  {
  case NODE_CLASS_DECL:
    traverse_class_decl(node, ctx);
    break;
  case NODE_FUNC_DEF:
  case NODE_FUNC_DECL:
    traverse_func_def(node, ctx);
    break;
  case NODE_VAR_DECL:
    traverse_var_decl(node, ctx);
    break;
  case NODE_PARAM:
    traverse_var_decl(node, ctx);
    break;
  default:
    for (int i = 0; i < node->num_children; i++)
    {
      generate_symbol_tables(node->children[i], ctx);
    }
    break;
  }
}

static char *check_expr_type(ASTNode *node, SemanticContext *ctx)
{
  if (!node)
    return strdup("unknown");

  switch (node->type)
  {
  case NODE_INTLIT:
    return strdup("integer");
  case NODE_FLOATLIT:
    return strdup("float");
  case NODE_ID:
  {
    Symbol *sym = lookup_symbol_recursive(ctx->current_table, node->value);
    if (!sym)
    {
      char msg[256];
      sprintf(msg, "Undeclared identifier '%s'", node->value);
      report_error(ctx, "ERROR", msg, node->line, node->column);
      return strdup("unknown");
    }
    return type_to_string(sym->type);
  }
  case NODE_VARIABLE:
  {
    // Variable node has qualified_id as first child
    if (node->num_children > 0 && node->children[0]->type == NODE_ID)
    {
      Symbol *sym = lookup_symbol_recursive(ctx->current_table, node->children[0]->value);
      if (!sym)
      {
        char msg[256];
        sprintf(msg, "Undeclared variable '%s'", node->children[0]->value);
        report_error(ctx, "ERROR", msg, node->line, node->column);
        return strdup("unknown");
      }
      return type_to_string(sym->type);
    }
    return strdup("unknown");
  }
  case NODE_ADD_EXPR:
  case NODE_MULT_EXPR:
  case NODE_REL_EXPR:
  {
    if (node->num_children >= 2)
    {
      char *left_type = check_expr_type(node->children[0], ctx);
      char *right_type = check_expr_type(node->children[1], ctx);

      if (strcmp(left_type, "unknown") != 0 && strcmp(right_type, "unknown") != 0)
      {
        if (strcmp(left_type, right_type) != 0)
        {
          char msg[256];
          sprintf(msg, "Type mismatch in expression: %s and %s", left_type, right_type);
          report_error(ctx, "WARNING", msg, node->line, node->column);
        }
      }

      free(right_type);
      return left_type;
    }
    return strdup("unknown");
  }
  case NODE_EXPR:
    // Generic expression node - check first child
    if (node->num_children > 0)
      return check_expr_type(node->children[0], ctx);
    return strdup("unknown");
  default:
    if (node->num_children > 0)
      return check_expr_type(node->children[0], ctx);
    return strdup("unknown");
  }
}

static void check_statement(ASTNode *node, SemanticContext *ctx);

static void check_assign(ASTNode *node, SemanticContext *ctx)
{
  if (node->num_children < 2)
    return;

  char *lhs_type = check_expr_type(node->children[0], ctx);
  char *rhs_type = check_expr_type(node->children[1], ctx);

  if (strcmp(lhs_type, rhs_type) != 0 &&
      strcmp(lhs_type, "unknown") != 0 &&
      strcmp(rhs_type, "unknown") != 0)
  {
    char msg[256];
    sprintf(msg, "Type mismatch in assignment: cannot assign %s to %s", rhs_type, lhs_type);
    report_error(ctx, "ERROR", msg, node->line, node->column);
  }

  free(lhs_type);
  free(rhs_type);
}

static void check_func_call(ASTNode *node, SemanticContext *ctx)
{
  if (node->num_children > 0 && node->children[0]->type == NODE_ID)
  {
    char *func_name = node->children[0]->value;
    Symbol *func_sym = lookup_symbol_recursive(ctx->current_table, func_name);
    if (!func_sym)
    {
      char msg[256];
      sprintf(msg, "Undeclared function '%s'", func_name);
      report_error(ctx, "ERROR", msg, node->line, node->column);
    }
    else if (func_sym->kind != SYM_FUNCTION && func_sym->kind != SYM_CLASS)
    {
      char msg[256];
      sprintf(msg, "'%s' is not a function", func_name);
      report_error(ctx, "ERROR", msg, node->line, node->column);
    }
  }
}

static void check_statement(ASTNode *node, SemanticContext *ctx)
{
  if (!node)
    return;

  switch (node->type)
  {
  case NODE_FUNC_DEF:
    // Enter function scope for type checking
    if (node->num_children > 0 && node->children[0]->num_children > 0)
    {
      ASTNode *func_head = node->children[0];
      ASTNode *id_node = func_head->children[0];
      char *func_name = id_node->value;

      // Find the function's scope table
      for (int i = 0; i < ctx->current_table->num_children; i++)
      {
        if (ctx->current_table->children[i] &&
            strcmp(ctx->current_table->children[i]->scope_name, func_name) == 0)
        {
          SymbolTable *prev_table = ctx->current_table;
          ctx->current_table = ctx->current_table->children[i];

          // Check function body
          for (int j = 1; j < node->num_children; j++)
          {
            check_statement(node->children[j], ctx);
          }

          ctx->current_table = prev_table;
          return;
        }
      }
    }
    break;
  case NODE_CLASS_DECL:
    // Enter class scope for type checking
    if (node->num_children > 0)
    {
      ASTNode *id_node = node->children[0];
      char *class_name = id_node->value;

      // Find the class's scope table
      for (int i = 0; i < ctx->current_table->num_children; i++)
      {
        if (ctx->current_table->children[i] &&
            strcmp(ctx->current_table->children[i]->scope_name, class_name) == 0)
        {
          SymbolTable *prev_table = ctx->current_table;
          ctx->current_table = ctx->current_table->children[i];

          // Check class members
          for (int j = 1; j < node->num_children; j++)
          {
            check_statement(node->children[j], ctx);
          }

          ctx->current_table = prev_table;
          return;
        }
      }
    }
    break;
  case NODE_ASSIGN_STAT:
    check_assign(node, ctx);
    break;
  case NODE_FUNC_CALL:
    check_func_call(node, ctx);
    break;
  case NODE_IF_STAT:
  case NODE_WHILE_STAT:
    // Check condition and body
    for (int i = 0; i < node->num_children; i++)
    {
      check_statement(node->children[i], ctx);
    }
    break;
  case NODE_RETURN_STAT:
  case NODE_WRITE_STAT:
  case NODE_READ_STAT:
    // Check expressions
    for (int i = 0; i < node->num_children; i++)
    {
      check_expr_type(node->children[i], ctx);
    }
    break;
  default:
    // Recursively check children
    for (int i = 0; i < node->num_children; i++)
    {
      check_statement(node->children[i], ctx);
    }
    break;
  }
}

void type_check(ASTNode *node, SemanticContext *ctx)
{
  if (!node)
    return;

  check_statement(node, ctx);
}

void semantic_analysis(ASTNode *ast, SemanticContext *context)
{
  printf("\n=== Phase 1: Symbol Table Generation ===\n");
  generate_symbol_tables(ast, context);

  printf("=== Phase 2: Type Checking ===\n");
  type_check(ast, context);
}

void print_errors(SemanticContext *context, FILE *output)
{
  fprintf(output, "================================================================================\n");
  fprintf(output, "                        SEMANTIC ERROR REPORT\n");
  fprintf(output, "================================================================================\n\n");
  fprintf(output, "Total Errors: %d\n", context->error_count);
  fprintf(output, "Total Warnings: %d\n\n", context->warning_count);

  if (!context->errors)
  {
    fprintf(output, "No semantic errors or warnings found.\n");
    return;
  }

  // Print errors in reverse order (they were added to front of list)
  SemanticError *curr = context->errors;
  while (curr)
  {
    fprintf(output, "[%s] Line %d, Column %d: %s\n",
            curr->error_type, curr->line, curr->column, curr->message);
    curr = curr->next;
  }
}

void free_semantic_context(SemanticContext *context)
{
  if (!context)
    return;

  SemanticError *error = context->errors;
  while (error)
  {
    SemanticError *next = error->next;
    free(error->message);
    free(error->error_type);
    free(error);
    error = next;
  }

  free_symbol_table(context->global_table);
  if (context->error_file)
    fclose(context->error_file);
  free(context);
}
