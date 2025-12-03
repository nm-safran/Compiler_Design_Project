#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symboltable.h"

// Target architecture: x86-64 assembly (AT&T syntax)

// Register enumeration
typedef enum
{
  REG_RAX = 0, // Accumulator, return value
  REG_RBX,     // Base register (callee-saved)
  REG_RCX,     // Counter register
  REG_RDX,     // Data register
  REG_RSI,     // Source index
  REG_RDI,     // Destination index (1st arg)
  REG_R8,      // 2nd argument
  REG_R9,      // 3rd argument
  REG_R10,     // Temporary
  REG_R11,     // Temporary
  REG_R12,     // Callee-saved
  REG_R13,     // Callee-saved
  REG_R14,     // Callee-saved
  REG_R15,     // Callee-saved
  REG_COUNT
} Register;

// Register state
typedef struct
{
  Register reg;
  int is_free;
  char *var_name; // Variable currently in this register
} RegisterState;

// Stack frame management
typedef struct
{
  int offset;     // Current stack offset from RBP
  int max_offset; // Maximum stack space needed
  int temp_count; // Temporary variable counter
} StackFrame;

// Code generation context
typedef struct
{
  FILE *output; // Output assembly file
  RegisterState registers[REG_COUNT];
  StackFrame *current_frame;
  SymbolTable *current_scope;
  int label_count;  // For generating unique labels
  int string_count; // For string literals
} CodeGenContext;

// Register allocation functions
CodeGenContext *create_codegen_context(FILE *output);
void free_codegen_context(CodeGenContext *ctx);

Register allocate_register(CodeGenContext *ctx);
void free_register(CodeGenContext *ctx, Register reg);
void free_all_registers(CodeGenContext *ctx);
const char *get_register_name(Register reg);
const char *get_register_name_32bit(Register reg); // For 32-bit operations
const char *get_register_name_8bit(Register reg);  // For byte operations

// Stack management functions
void enter_function(CodeGenContext *ctx, const char *func_name, int param_count);
void leave_function(CodeGenContext *ctx);
int allocate_stack_space(CodeGenContext *ctx, int size);
void deallocate_stack_space(CodeGenContext *ctx, int size);

// Code emission functions
void emit(CodeGenContext *ctx, const char *format, ...);
void emit_comment(CodeGenContext *ctx, const char *comment);
void emit_label(CodeGenContext *ctx, const char *label);
char *generate_label(CodeGenContext *ctx, const char *prefix);

// Assembly directive emitters
void emit_data_section(CodeGenContext *ctx);
void emit_text_section(CodeGenContext *ctx);
void emit_global(CodeGenContext *ctx, const char *symbol);
void emit_string_literal(CodeGenContext *ctx, const char *str, int id);

// Instruction emitters
void emit_push(CodeGenContext *ctx, const char *operand);
void emit_pop(CodeGenContext *ctx, const char *operand);
void emit_mov(CodeGenContext *ctx, const char *dest, const char *src);
void emit_add(CodeGenContext *ctx, const char *dest, const char *src);
void emit_sub(CodeGenContext *ctx, const char *dest, const char *src);
void emit_mul(CodeGenContext *ctx, const char *operand);
void emit_div(CodeGenContext *ctx, const char *operand);
void emit_cmp(CodeGenContext *ctx, const char *op1, const char *op2);
void emit_jmp(CodeGenContext *ctx, const char *label);
void emit_je(CodeGenContext *ctx, const char *label);
void emit_jne(CodeGenContext *ctx, const char *label);
void emit_jl(CodeGenContext *ctx, const char *label);
void emit_jg(CodeGenContext *ctx, const char *label);
void emit_jle(CodeGenContext *ctx, const char *label);
void emit_jge(CodeGenContext *ctx, const char *label);
void emit_call(CodeGenContext *ctx, const char *function);
void emit_ret(CodeGenContext *ctx);

// High-level code generation functions
void generate_program(ASTNode *ast, CodeGenContext *ctx, SymbolTable *symtab);
void generate_function(ASTNode *node, CodeGenContext *ctx);
void generate_statement(ASTNode *node, CodeGenContext *ctx);
void generate_expression(ASTNode *node, CodeGenContext *ctx, Register target);
void generate_assignment(ASTNode *node, CodeGenContext *ctx);
void generate_if_statement(ASTNode *node, CodeGenContext *ctx);
void generate_while_statement(ASTNode *node, CodeGenContext *ctx);
void generate_return_statement(ASTNode *node, CodeGenContext *ctx);
void generate_function_call(ASTNode *node, CodeGenContext *ctx, Register target);

// Variable access
int get_variable_offset(CodeGenContext *ctx, const char *var_name);
void load_variable(CodeGenContext *ctx, const char *var_name, Register reg);
void store_variable(CodeGenContext *ctx, const char *var_name, Register reg);

// Runtime support
void emit_runtime_support(CodeGenContext *ctx);

#endif // CODEGEN_H
