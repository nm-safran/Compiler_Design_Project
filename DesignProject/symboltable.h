#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol kinds
typedef enum
{
  SYM_CLASS,
  SYM_FUNCTION,
  SYM_PARAMETER,
  SYM_VARIABLE,
  SYM_ATTRIBUTE
} SymbolKind;

// Type information
typedef struct TypeInfo
{
  char *base_type; // integer, float, void, or class name
  int *dimensions; // Array dimensions
  int num_dimensions;
} TypeInfo;

// Symbol table entry
typedef struct Symbol
{
  char *name;
  SymbolKind kind;
  TypeInfo *type;
  char *visibility; // public, private, or NULL
  int line;
  int column;
  struct SymbolTable *class_scope; // For class members
  struct Symbol **parameters;      // For functions
  int num_params;
  struct Symbol *next; // For hash table chaining
} Symbol;

// Symbol table (one per scope)
typedef struct SymbolTable
{
  char *scope_name;
  int level;
  Symbol **symbols; // Hash table
  int size;
  struct SymbolTable *parent;
  struct SymbolTable **children;
  int num_children;
} SymbolTable;

// Symbol table functions
SymbolTable *create_symbol_table(const char *name, int level, SymbolTable *parent);
Symbol *create_symbol(const char *name, SymbolKind kind, const char *type, int line, int col);
void add_symbol(SymbolTable *table, Symbol *symbol);
void add_child_scope(SymbolTable *parent, SymbolTable *child);
Symbol *lookup_symbol(SymbolTable *table, const char *name);
Symbol *lookup_symbol_recursive(SymbolTable *table, const char *name);
void print_symbol_table(SymbolTable *table, FILE *output);
void free_symbol_table(SymbolTable *table);

TypeInfo *create_type_info(const char *base_type);
void add_dimension(TypeInfo *type, int size);
char *type_to_string(TypeInfo *type);

#endif
