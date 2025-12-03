#include "symboltable.h"

#define TABLE_SIZE 101

static unsigned int hash(const char *str)
{
  unsigned int hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % TABLE_SIZE;
}

SymbolTable *create_symbol_table(const char *name, int level, SymbolTable *parent)
{
  SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
  table->scope_name = strdup(name);
  table->level = level;
  table->parent = parent;
  table->size = TABLE_SIZE;
  table->symbols = (Symbol **)calloc(TABLE_SIZE, sizeof(Symbol *));
  table->children = NULL;
  table->num_children = 0;
  return table;
}

TypeInfo *create_type_info(const char *base_type)
{
  TypeInfo *type = (TypeInfo *)malloc(sizeof(TypeInfo));
  type->base_type = strdup(base_type);
  type->dimensions = NULL;
  type->num_dimensions = 0;
  return type;
}

void add_dimension(TypeInfo *type, int size)
{
  type->dimensions = (int *)realloc(type->dimensions,
                                    (type->num_dimensions + 1) * sizeof(int));
  type->dimensions[type->num_dimensions++] = size;
}

char *type_to_string(TypeInfo *type)
{
  if (!type)
    return strdup("unknown");

  char buffer[256];
  strcpy(buffer, type->base_type);

  for (int i = 0; i < type->num_dimensions; i++)
  {
    char dim[32];
    if (type->dimensions[i] > 0)
      sprintf(dim, "[%d]", type->dimensions[i]);
    else
      sprintf(dim, "[]");
    strcat(buffer, dim);
  }

  return strdup(buffer);
}

Symbol *create_symbol(const char *name, SymbolKind kind, const char *type, int line, int col)
{
  Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
  symbol->name = strdup(name);
  symbol->kind = kind;
  symbol->type = create_type_info(type);
  symbol->visibility = NULL;
  symbol->line = line;
  symbol->column = col;
  symbol->class_scope = NULL;
  symbol->parameters = NULL;
  symbol->num_params = 0;
  symbol->next = NULL;
  return symbol;
}

void add_symbol(SymbolTable *table, Symbol *symbol)
{
  unsigned int index = hash(symbol->name);
  symbol->next = table->symbols[index];
  table->symbols[index] = symbol;
}

void add_child_scope(SymbolTable *parent, SymbolTable *child)
{
  if (!parent || !child)
    return;

  parent->children = (SymbolTable **)realloc(parent->children,
                                             (parent->num_children + 1) * sizeof(SymbolTable *));
  parent->children[parent->num_children++] = child;
}

Symbol *lookup_symbol(SymbolTable *table, const char *name)
{
  unsigned int index = hash(name);
  Symbol *symbol = table->symbols[index];

  while (symbol)
  {
    if (strcmp(symbol->name, name) == 0)
      return symbol;
    symbol = symbol->next;
  }
  return NULL;
}

Symbol *lookup_symbol_recursive(SymbolTable *table, const char *name)
{
  Symbol *symbol = lookup_symbol(table, name);
  if (symbol)
    return symbol;

  if (table->parent)
    return lookup_symbol_recursive(table->parent, name);

  return NULL;
}

static const char *kind_to_string(SymbolKind kind)
{
  switch (kind)
  {
  case SYM_CLASS:
    return "class";
  case SYM_FUNCTION:
    return "function";
  case SYM_PARAMETER:
    return "parameter";
  case SYM_VARIABLE:
    return "variable";
  case SYM_ATTRIBUTE:
    return "attribute";
  default:
    return "unknown";
  }
}

void print_symbol_table(SymbolTable *table, FILE *output)
{
  fprintf(output, "\n========================================\n");
  fprintf(output, "SCOPE: %s (Level %d)\n", table->scope_name, table->level);
  fprintf(output, "========================================\n\n");

  fprintf(output, "%-20s %-12s %-12s %-12s %-10s %s\n",
          "Name", "Kind", "Type", "Visibility", "Line", "Details");
  fprintf(output, "--------------------------------------------------------------------------------\n");

  int has_symbols = 0;
  for (int i = 0; i < table->size; i++)
  {
    Symbol *symbol = table->symbols[i];
    while (symbol)
    {
      has_symbols = 1;
      char *type_str = type_to_string(symbol->type);

      fprintf(output, "%-20s %-12s %-12s %-12s %-10d ",
              symbol->name,
              kind_to_string(symbol->kind),
              type_str,
              symbol->visibility ? symbol->visibility : "-",
              symbol->line);

      if (symbol->kind == SYM_FUNCTION && symbol->num_params > 0)
      {
        fprintf(output, "params: %d", symbol->num_params);
      }

      fprintf(output, "\n");
      free(type_str);
      symbol = symbol->next;
    }
  }

  if (!has_symbols)
  {
    fprintf(output, "(empty scope)\n");
  }

  // Print child scopes recursively
  for (int i = 0; i < table->num_children; i++)
  {
    if (table->children[i])
    {
      print_symbol_table(table->children[i], output);
    }
  }
}

void free_symbol_table(SymbolTable *table)
{
  if (!table)
    return;

  for (int i = 0; i < table->size; i++)
  {
    Symbol *symbol = table->symbols[i];
    while (symbol)
    {
      Symbol *next = symbol->next;
      free(symbol->name);
      free(symbol->type->base_type);
      free(symbol->type->dimensions);
      free(symbol->type);
      free(symbol->visibility);
      free(symbol->parameters);
      free(symbol);
      symbol = next;
    }
  }

  free(table->symbols);
  free(table->scope_name);
  free(table);
}
