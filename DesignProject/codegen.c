#include "codegen.h"
#include <stdarg.h>

// Register names for x86-64
static const char *reg_names_64[] = {
    "%rax", "%rbx", "%rcx", "%rdx", "%rsi", "%rdi",
    "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15"};

static const char *reg_names_32[] = {
    "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi",
    "%r8d", "%r9d", "%r10d", "%r11d", "%r12d", "%r13d", "%r14d", "%r15d"};

static const char *reg_names_8[] = {
    "%al", "%bl", "%cl", "%dl", "%sil", "%dil",
    "%r8b", "%r9b", "%r10b", "%r11b", "%r12b", "%r13b", "%r14b", "%r15b"};

// ============================================================================
// Context Management
// ============================================================================

CodeGenContext *create_codegen_context(FILE *output)
{
  CodeGenContext *ctx = (CodeGenContext *)malloc(sizeof(CodeGenContext));
  ctx->output = output;
  ctx->label_count = 0;
  ctx->string_count = 0;
  ctx->current_scope = NULL;

  // Initialize all registers as free
  for (int i = 0; i < REG_COUNT; i++)
  {
    ctx->registers[i].reg = i;
    ctx->registers[i].is_free = 1;
    ctx->registers[i].var_name = NULL;
  }

  // Reserve some registers
  ctx->registers[REG_RAX].is_free = 0; // Return value/accumulator
  ctx->registers[REG_RBX].is_free = 0; // Base pointer usage

  ctx->current_frame = (StackFrame *)malloc(sizeof(StackFrame));
  ctx->current_frame->offset = 0;
  ctx->current_frame->max_offset = 0;
  ctx->current_frame->temp_count = 0;

  return ctx;
}

void free_codegen_context(CodeGenContext *ctx)
{
  if (!ctx)
    return;

  for (int i = 0; i < REG_COUNT; i++)
  {
    if (ctx->registers[i].var_name)
    {
      free(ctx->registers[i].var_name);
    }
  }

  if (ctx->current_frame)
  {
    free(ctx->current_frame);
  }

  free(ctx);
}

// ============================================================================
// Register Allocation
// ============================================================================

Register allocate_register(CodeGenContext *ctx)
{
  // Try to find a free register (prefer caller-saved registers)
  // Priority: R10, R11 (temps) -> RCX, RDX -> RSI, RDI -> others

  int priority[] = {REG_R10, REG_R11, REG_RCX, REG_RDX, REG_RSI, REG_RDI,
                    REG_R8, REG_R9, REG_R12, REG_R13, REG_R14, REG_R15};

  for (int i = 0; i < sizeof(priority) / sizeof(priority[0]); i++)
  {
    if (ctx->registers[priority[i]].is_free)
    {
      ctx->registers[priority[i]].is_free = 0;
      return priority[i];
    }
  }

  // No free register - need to spill
  fprintf(stderr, "Warning: Register spilling not implemented, reusing R10\n");
  return REG_R10;
}

void free_register(CodeGenContext *ctx, Register reg)
{
  if (reg < 0 || reg >= REG_COUNT)
    return;

  ctx->registers[reg].is_free = 1;
  if (ctx->registers[reg].var_name)
  {
    free(ctx->registers[reg].var_name);
    ctx->registers[reg].var_name = NULL;
  }
}

void free_all_registers(CodeGenContext *ctx)
{
  for (int i = 0; i < REG_COUNT; i++)
  {
    if (i != REG_RAX && i != REG_RBX)
    {
      free_register(ctx, i);
    }
  }
}

const char *get_register_name(Register reg)
{
  if (reg < 0 || reg >= REG_COUNT)
    return "%rax";
  return reg_names_64[reg];
}

const char *get_register_name_32bit(Register reg)
{
  if (reg < 0 || reg >= REG_COUNT)
    return "%eax";
  return reg_names_32[reg];
}

const char *get_register_name_8bit(Register reg)
{
  if (reg < 0 || reg >= REG_COUNT)
    return "%al";
  return reg_names_8[reg];
}

// ============================================================================
// Stack Management
// ============================================================================

void enter_function(CodeGenContext *ctx, const char *func_name, int param_count)
{
  emit_comment(ctx, "Function prologue");
  emit(ctx, "%s:", func_name);
  emit_push(ctx, "%rbp");
  emit_mov(ctx, "%rbp", "%rsp");

  // Reset stack frame
  ctx->current_frame->offset = 0;
  ctx->current_frame->max_offset = 0;
  ctx->current_frame->temp_count = 0;

  // Reserve space for locals (will be adjusted later)
  emit_comment(ctx, "Reserve space for local variables");
}

void leave_function(CodeGenContext *ctx)
{
  emit_comment(ctx, "Function epilogue");

  // Restore stack
  if (ctx->current_frame->max_offset > 0)
  {
    emit_add(ctx, "%rsp", "$" + ctx->current_frame->max_offset);
  }

  emit_mov(ctx, "%rsp", "%rbp");
  emit_pop(ctx, "%rbp");
  emit_ret(ctx);
}

int allocate_stack_space(CodeGenContext *ctx, int size)
{
  // Align to 8 bytes
  size = (size + 7) & ~7;

  ctx->current_frame->offset += size;
  if (ctx->current_frame->offset > ctx->current_frame->max_offset)
  {
    ctx->current_frame->max_offset = ctx->current_frame->offset;
  }

  return ctx->current_frame->offset;
}

void deallocate_stack_space(CodeGenContext *ctx, int size)
{
  size = (size + 7) & ~7;
  ctx->current_frame->offset -= size;
}

// ============================================================================
// Code Emission
// ============================================================================

void emit(CodeGenContext *ctx, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  fprintf(ctx->output, "    ");
  vfprintf(ctx->output, format, args);
  fprintf(ctx->output, "\n");
  va_end(args);
}

void emit_comment(CodeGenContext *ctx, const char *comment)
{
  fprintf(ctx->output, "    # %s\n", comment);
}

void emit_label(CodeGenContext *ctx, const char *label)
{
  fprintf(ctx->output, "%s:\n", label);
}

char *generate_label(CodeGenContext *ctx, const char *prefix)
{
  char *label = (char *)malloc(64);
  sprintf(label, ".L%s%d", prefix, ctx->label_count++);
  return label;
}

// ============================================================================
// Assembly Directives
// ============================================================================

void emit_data_section(CodeGenContext *ctx)
{
  fprintf(ctx->output, ".data\n");
}

void emit_text_section(CodeGenContext *ctx)
{
  fprintf(ctx->output, ".text\n");
}

void emit_global(CodeGenContext *ctx, const char *symbol)
{
  fprintf(ctx->output, ".globl %s\n", symbol);
}

void emit_string_literal(CodeGenContext *ctx, const char *str, int id)
{
  fprintf(ctx->output, ".LC%d:\n", id);
  fprintf(ctx->output, "    .string \"%s\"\n", str);
}

// ============================================================================
// Basic Instructions
// ============================================================================

void emit_push(CodeGenContext *ctx, const char *operand)
{
  emit(ctx, "pushq %s", operand);
}

void emit_pop(CodeGenContext *ctx, const char *operand)
{
  emit(ctx, "popq %s", operand);
}

void emit_mov(CodeGenContext *ctx, const char *dest, const char *src)
{
  emit(ctx, "movq %s, %s", src, dest);
}

void emit_add(CodeGenContext *ctx, const char *dest, const char *src)
{
  emit(ctx, "addq %s, %s", src, dest);
}

void emit_sub(CodeGenContext *ctx, const char *dest, const char *src)
{
  emit(ctx, "subq %s, %s", src, dest);
}

void emit_mul(CodeGenContext *ctx, const char *operand)
{
  emit(ctx, "imulq %s", operand);
}

void emit_div(CodeGenContext *ctx, const char *operand)
{
  emit(ctx, "idivq %s", operand);
}

void emit_cmp(CodeGenContext *ctx, const char *op1, const char *op2)
{
  emit(ctx, "cmpq %s, %s", op2, op1);
}

void emit_jmp(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "jmp %s", label);
}

void emit_je(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "je %s", label);
}

void emit_jne(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "jne %s", label);
}

void emit_jl(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "jl %s", label);
}

void emit_jg(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "jg %s", label);
}

void emit_jle(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "jle %s", label);
}

void emit_jge(CodeGenContext *ctx, const char *label)
{
  emit(ctx, "jge %s", label);
}

void emit_call(CodeGenContext *ctx, const char *function)
{
  emit(ctx, "call %s", function);
}

void emit_ret(CodeGenContext *ctx)
{
  emit(ctx, "ret");
}

// ============================================================================
// Variable Access
// ============================================================================

int get_variable_offset(CodeGenContext *ctx, const char *var_name)
{
  // Lookup variable in symbol table and return its stack offset
  // For now, simple implementation
  Symbol *sym = lookup_symbol_recursive(ctx->current_scope, var_name);
  if (!sym)
  {
    fprintf(stderr, "Error: Variable '%s' not found\n", var_name);
    return -8; // Default offset
  }

  // Variables are at negative offsets from RBP
  // First local at -8, second at -16, etc.
  return -(sym->line * 8); // Simplified - should use proper offset tracking
}

void load_variable(CodeGenContext *ctx, const char *var_name, Register reg)
{
  int offset = get_variable_offset(ctx, var_name);
  char offset_str[32];
  sprintf(offset_str, "%d(%%rbp)", offset);
  emit_mov(ctx, get_register_name(reg), offset_str);
}

void store_variable(CodeGenContext *ctx, const char *var_name, Register reg)
{
  int offset = get_variable_offset(ctx, var_name);
  char offset_str[32];
  sprintf(offset_str, "%d(%%rbp)", offset);
  emit_mov(ctx, offset_str, get_register_name(reg));
}

// ============================================================================
// High-Level Code Generation
// ============================================================================

void generate_program(ASTNode *ast, CodeGenContext *ctx, SymbolTable *symtab)
{
  if (!ast || !ctx)
    return;

  ctx->current_scope = symtab;

  // Emit assembly header
  emit_comment(ctx, "Generated by Custom Compiler");
  emit_comment(ctx, "Target: x86-64 Assembly (AT&T syntax)");
  fprintf(ctx->output, "\n");

  // Emit runtime support
  emit_runtime_support(ctx);

  // Generate code for all top-level declarations
  emit_text_section(ctx);

  for (int i = 0; i < ast->num_children; i++)
  {
    ASTNode *child = ast->children[i];

    if (child->type == NODE_FUNC_DEF)
    {
      generate_function(child, ctx);
    }
    // Handle classes and other declarations
  }
}

void generate_function(ASTNode *node, CodeGenContext *ctx)
{
  if (!node || node->num_children < 1)
    return;

  // Get function name
  ASTNode *func_head = node->children[0];
  if (func_head->num_children < 1)
    return;

  ASTNode *id_node = func_head->children[0];
  char *func_name = id_node->value;

  emit_comment(ctx, "==========================================");
  emit_comment(ctx, func_name);
  emit_comment(ctx, "==========================================");

  // Make main global
  if (strcmp(func_name, "main") == 0)
  {
    emit_global(ctx, "main");
  }

  enter_function(ctx, func_name, 0);

  // Allocate space for local variables
  // This should be calculated from symbol table
  emit_sub(ctx, "%rsp", "$64"); // Reserve 64 bytes for locals

  // Generate function body
  if (node->num_children > 1)
  {
    ASTNode *func_body = node->children[1];
    for (int i = 0; i < func_body->num_children; i++)
    {
      generate_statement(func_body->children[i], ctx);
    }
  }

  // Default return if no explicit return
  emit_mov(ctx, "%rax", "$0");
  leave_function(ctx);
  fprintf(ctx->output, "\n");
}

void generate_statement(ASTNode *node, CodeGenContext *ctx)
{
  if (!node)
    return;

  switch (node->type)
  {
  case NODE_ASSIGN_STAT:
    generate_assignment(node, ctx);
    break;
  case NODE_IF_STAT:
    generate_if_statement(node, ctx);
    break;
  case NODE_WHILE_STAT:
    generate_while_statement(node, ctx);
    break;
  case NODE_RETURN_STAT:
    generate_return_statement(node, ctx);
    break;
  case NODE_FUNC_CALL:
    generate_function_call(node, ctx, REG_RAX);
    break;
  case NODE_LIST:
    // Process statement list
    for (int i = 0; i < node->num_children; i++)
    {
      generate_statement(node->children[i], ctx);
    }
    break;
  case NODE_VAR_DECL:
    // Variable declarations are handled in symbol table
    break;
  default:
    emit_comment(ctx, "Unhandled statement type");
    break;
  }
}

void generate_expression(ASTNode *node, CodeGenContext *ctx, Register target)
{
  if (!node)
    return;

  switch (node->type)
  {
  case NODE_INTLIT:
  {
    // Load integer literal
    char value[32];
    sprintf(value, "$%s", node->value);
    emit_mov(ctx, get_register_name(target), value);
    break;
  }

  case NODE_FLOATLIT:
  {
    // Floating point handling would require SSE registers
    emit_comment(ctx, "Float literal (simplified)");
    break;
  }

  case NODE_ID:
  case NODE_VARIABLE:
  {
    // Load variable
    char *var_name = node->value;
    if (node->type == NODE_VARIABLE && node->num_children > 0)
    {
      var_name = node->children[0]->value;
    }
    load_variable(ctx, var_name, target);
    break;
  }

  case NODE_ADD_EXPR:
  {
    if (node->num_children >= 2)
    {
      // Generate left operand
      generate_expression(node->children[0], ctx, target);

      // Generate right operand in temp register
      Register temp = allocate_register(ctx);
      generate_expression(node->children[1], ctx, temp);

      // Add
      emit_add(ctx, get_register_name(target), get_register_name(temp));
      free_register(ctx, temp);
    }
    break;
  }

  case NODE_MULT_EXPR:
  {
    if (node->num_children >= 2)
    {
      generate_expression(node->children[0], ctx, target);
      Register temp = allocate_register(ctx);
      generate_expression(node->children[1], ctx, temp);

      // Multiply (result in RAX)
      emit_mov(ctx, "%rax", get_register_name(target));
      emit_mul(ctx, get_register_name(temp));
      emit_mov(ctx, get_register_name(target), "%rax");

      free_register(ctx, temp);
    }
    break;
  }

  case NODE_EXPR:
  case NODE_LIST:
    // Process first child
    if (node->num_children > 0)
    {
      generate_expression(node->children[0], ctx, target);
    }
    break;

  default:
    emit_comment(ctx, "Unhandled expression type");
    emit_mov(ctx, get_register_name(target), "$0");
    break;
  }
}

void generate_assignment(ASTNode *node, CodeGenContext *ctx)
{
  if (!node || node->num_children < 2)
    return;

  emit_comment(ctx, "Assignment");

  // Generate right-hand side into RAX
  generate_expression(node->children[1], ctx, REG_RAX);

  // Get variable name from left-hand side
  ASTNode *lhs = node->children[0];
  char *var_name = lhs->value;
  if (lhs->type == NODE_VARIABLE && lhs->num_children > 0)
  {
    var_name = lhs->children[0]->value;
  }

  // Store to variable
  store_variable(ctx, var_name, REG_RAX);
}

void generate_if_statement(ASTNode *node, CodeGenContext *ctx)
{
  if (!node || node->num_children < 2)
    return;

  emit_comment(ctx, "If statement");

  char *else_label = generate_label(ctx, "else");
  char *end_label = generate_label(ctx, "endif");

  // Evaluate condition
  generate_expression(node->children[0], ctx, REG_RAX);
  emit_cmp(ctx, "%rax", "$0");
  emit_je(ctx, else_label);

  // Then branch
  generate_statement(node->children[1], ctx);
  emit_jmp(ctx, end_label);

  // Else branch
  emit_label(ctx, else_label);
  if (node->num_children > 2)
  {
    generate_statement(node->children[2], ctx);
  }

  emit_label(ctx, end_label);

  free(else_label);
  free(end_label);
}

void generate_while_statement(ASTNode *node, CodeGenContext *ctx)
{
  if (!node || node->num_children < 2)
    return;

  emit_comment(ctx, "While loop");

  char *start_label = generate_label(ctx, "while_start");
  char *end_label = generate_label(ctx, "while_end");

  emit_label(ctx, start_label);

  // Evaluate condition
  generate_expression(node->children[0], ctx, REG_RAX);
  emit_cmp(ctx, "%rax", "$0");
  emit_je(ctx, end_label);

  // Loop body
  generate_statement(node->children[1], ctx);
  emit_jmp(ctx, start_label);

  emit_label(ctx, end_label);

  free(start_label);
  free(end_label);
}

void generate_return_statement(ASTNode *node, CodeGenContext *ctx)
{
  emit_comment(ctx, "Return statement");

  if (node->num_children > 0)
  {
    // Evaluate return expression into RAX
    generate_expression(node->children[0], ctx, REG_RAX);
  }
  else
  {
    emit_mov(ctx, "%rax", "$0");
  }

  leave_function(ctx);
}

void generate_function_call(ASTNode *node, CodeGenContext *ctx, Register target)
{
  if (!node || node->num_children < 1)
    return;

  char *func_name = node->children[0]->value;

  emit_comment(ctx, "Function call");

  // Generate arguments (simplified - supports up to 6 args in registers)
  // Arguments passed in: RDI, RSI, RDX, RCX, R8, R9

  emit_call(ctx, func_name);

  // Result is in RAX
  if (target != REG_RAX)
  {
    emit_mov(ctx, get_register_name(target), "%rax");
  }
}

// ============================================================================
// Runtime Support
// ============================================================================

void emit_runtime_support(CodeGenContext *ctx)
{
  emit_comment(ctx, "Runtime support functions");
  emit_data_section(ctx);

  // String format for write statement
  emit_string_literal(ctx, "%d\\n", 0);
  emit_string_literal(ctx, "%f\\n", 1);

  fprintf(ctx->output, "\n");
}
