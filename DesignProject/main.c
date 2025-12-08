#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symboltable.h"
#include "semantic.h"
#include "codegen.h"

// External declarations from lexer and parser
extern FILE *yyin;
extern int yyparse();
extern ASTNode *root;
extern int line, column;

void print_usage(const char *program_name)
{
  printf("Usage: %s <input_file> [options]\n", program_name);
  printf("Options:\n");
  printf("  -o <output>   Specify output assembly file (default: output.s)\n");
  printf("  -ast          Generate AST output file (ast.out)\n");
  printf("  -sym          Generate symbol table output file (symboltable.out)\n");
  printf("  -sem          Generate semantic errors output file (semantic_errors.out)\n");
  printf("  -all          Generate all intermediate outputs\n");
  printf("  -h, --help    Show this help message\n");
}

int main(int argc, char *argv[])
{
  // Default options
  char *input_file = NULL;
  char *output_file = "output.s";
  int gen_ast = 0;
  int gen_sym = 0;
  int gen_sem = 0;

  // Parse command line arguments
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {
      print_usage(argv[0]);
      return 0;
    }
    else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
    {
      output_file = argv[++i];
    }
    else if (strcmp(argv[i], "-ast") == 0)
    {
      gen_ast = 1;
    }
    else if (strcmp(argv[i], "-sym") == 0)
    {
      gen_sym = 1;
    }
    else if (strcmp(argv[i], "-sem") == 0)
    {
      gen_sem = 1;
    }
    else if (strcmp(argv[i], "-all") == 0)
    {
      gen_ast = gen_sym = gen_sem = 1;
    }
    else if (argv[i][0] != '-')
    {
      input_file = argv[i];
    }
    else
    {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      print_usage(argv[0]);
      return 1;
    }
  }

  if (!input_file)
  {
    fprintf(stderr, "Error: No input file specified\n");
    print_usage(argv[0]);
    return 1;
  }

  // Open input file
  yyin = fopen(input_file, "r");
  if (!yyin)
  {
    fprintf(stderr, "Error: Cannot open input file '%s'\n", input_file);
    return 1;
  }

  printf("================================================================================\n");
  printf("                    CUSTOM LANGUAGE COMPILER\n");
  printf("================================================================================\n");
  printf("Input file: %s\n", input_file);
  printf("Output file: %s\n", output_file);
  printf("================================================================================\n\n");

  // ========================================================================
  // PHASE 1: LEXICAL ANALYSIS & SYNTAX ANALYSIS
  // ========================================================================
  printf("[PHASE 1] Lexical & Syntax Analysis...\n");

  int parse_result = yyparse();

  if (parse_result != 0)
  {
    fprintf(stderr, "\n[ERROR] Parsing failed!\n");
    fclose(yyin);
    return 1;
  }

  if (!root)
  {
    fprintf(stderr, "\n[ERROR] No AST generated!\n");
    fclose(yyin);
    return 1;
  }

  printf("[PASS] Parsing completed successfully\n\n");

  // Optionally output AST
  if (gen_ast)
  {
    FILE *ast_file = fopen("ast.out", "w");
    if (ast_file)
    {
      fprintf(ast_file, "================================================================================\n");
      fprintf(ast_file, "                        ABSTRACT SYNTAX TREE\n");
      fprintf(ast_file, "================================================================================\n\n");
      print_ast(root, 0, ast_file);
      fclose(ast_file);
      printf("[INFO] AST written to ast.out\n");
    }
  }

  // ========================================================================
  // PHASE 2: SEMANTIC ANALYSIS
  // ========================================================================
  printf("[PHASE 2] Semantic Analysis...\n");

  char error_log_path[512];
  {
    // Build per-test semantic error log: semantic_errors_<inputfilename>.txt
    const char *base = strrchr(input_file, '\\');
    if (!base)
      base = strrchr(input_file, '/');
    base = base ? base + 1 : input_file;

    // Replace extension dot with underscore for clarity
    snprintf(error_log_path, sizeof(error_log_path), "semantic_errors_%s.txt", base);
    for (char *p = error_log_path; *p; ++p)
    {
      if (*p == '.')
        *p = '_';
    }
  }

  SemanticContext *sem_ctx = create_semantic_context(error_log_path);

  printf("  [2.1] Building symbol tables...\n");
  semantic_analysis(root, sem_ctx);

  // Always write per-test semantic log (append-only behavior controlled by file open mode)
  if (sem_ctx->error_file)
  {
    print_errors(sem_ctx, sem_ctx->error_file);
    fflush(sem_ctx->error_file);
  }

  // Generate symbol table output
  if (gen_sym)
  {
    FILE *sym_file = fopen("symboltable.out", "w");
    if (sym_file)
    {
      fprintf(sym_file, "================================================================================\n");
      fprintf(sym_file, "                        SYMBOL TABLE REPORT\n");
      fprintf(sym_file, "================================================================================\n");
      print_symbol_table(sem_ctx->global_table, sym_file);
      fclose(sym_file);
      printf("[INFO] Symbol table written to symboltable.out\n");
    }
  }

  // Generate semantic errors output
  if (gen_sem)
  {
    FILE *err_file = fopen("semantic_errors.out", "w");
    if (err_file)
    {
      print_errors(sem_ctx, err_file);
      fclose(err_file);
      printf("[INFO] Semantic errors written to semantic_errors.out\n");
    }
  }

  // Check for semantic errors
  if (sem_ctx->error_count > 0)
  {
    printf("\n[ERROR] Semantic analysis failed with %d error(s)\n", sem_ctx->error_count);
    print_errors(sem_ctx, stdout);

    free_semantic_context(sem_ctx);
    free_ast(root);
    fclose(yyin);
    return 1;
  }

  printf("[PASS] Semantic analysis completed successfully\n");
  if (sem_ctx->warning_count > 0)
  {
    printf("[WARN] %d warning(s) generated\n", sem_ctx->warning_count);
  }
  printf("\n");

  // ========================================================================
  // PHASE 3: CODE GENERATION
  // ========================================================================
  printf("[PHASE 3] Code Generation...\n");

  FILE *output = fopen(output_file, "w");
  if (!output)
  {
    fprintf(stderr, "[ERROR] Cannot create output file '%s'\n", output_file);
    free_semantic_context(sem_ctx);
    free_ast(root);
    fclose(yyin);
    return 1;
  }

  CodeGenContext *codegen_ctx = create_codegen_context(output);

  printf("  [3.1] Generating assembly code...\n");
  generate_program(root, codegen_ctx, sem_ctx->global_table);

  fclose(output);
  printf("[PASS] Assembly code generated: %s\n\n", output_file);

  // ========================================================================
  // CLEANUP
  // ========================================================================
  free_codegen_context(codegen_ctx);
  free_semantic_context(sem_ctx);
  free_ast(root);
  fclose(yyin);

  printf("================================================================================\n");
  printf("                    COMPILATION SUCCESSFUL\n");
  printf("================================================================================\n");
  printf("Generated files:\n");
  printf("  - %s (assembly code)\n", output_file);
  if (gen_ast)
    printf("  - ast.out (abstract syntax tree)\n");
  if (gen_sym)
    printf("  - symboltable.out (symbol tables)\n");
  if (gen_sem)
    printf("  - semantic_errors.out (semantic report)\n");
  printf("\nTo assemble and link (Linux/macOS):\n");
  printf("  gcc %s -o program\n", output_file);
  printf("  ./program\n");
  printf("\nTo assemble and link (Windows with MinGW):\n");
  printf("  gcc %s -o program.exe\n", output_file);
  printf("  program.exe\n");
  printf("================================================================================\n");

  return 0;
}
