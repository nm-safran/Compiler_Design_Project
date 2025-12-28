#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symboltable.h"
#include "semantic.h"
#include "codegen.h"

#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

// External declarations from lexer and parser
extern FILE *yyin;
extern int yyparse();
extern ASTNode *root;
extern int line, column;
extern void set_token_output(FILE *output);
extern void set_lexical_error_output(FILE *output);
extern int has_lexical_error();
extern void set_syntax_error_output(FILE *output);
extern int has_syntax_error();

void print_usage(const char *program_name)
{
  printf("Usage: %s <input_file> [options]\n", program_name);
  printf("Options:\n");
  printf("  -o <output>   Specify output assembly file (default: output.s)\n");
  printf("  -ast          Generate AST output file (ast.out)\n");
  printf("  -lex          Generate lexical tokens output file\n");
  printf("  -sym          Generate symbol table output file (symboltable.out)\n");
  printf("  -sem          Generate semantic errors output file (semantic_errors.out)\n");
  printf("  -all          Generate all intermediate outputs\n");
  printf("  -h, --help    Show this help message\n");
}

int main(int argc, char *argv[])
{
  // Default options
  char *input_file = NULL;
  char *output_file = NULL; // Will be set based on input file
  int gen_ast = 0;
  int gen_lex = 0;
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
    else if (strcmp(argv[i], "-lex") == 0)
    {
      gen_lex = 1;
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
      gen_ast = gen_sym = gen_sem = gen_lex = 1;
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

  // Derive base file name and name without extension for output files
  char base_name[256];
  char base_no_ext[256];
  {
    const char *base_ptr = strrchr(input_file, '\\');
    if (!base_ptr)
      base_ptr = strrchr(input_file, '/');
    base_ptr = base_ptr ? base_ptr + 1 : input_file;

    strncpy(base_name, base_ptr, sizeof(base_name) - 1);
    base_name[sizeof(base_name) - 1] = '\0';

    const char *ext = strrchr(base_name, '.');
    if (ext)
    {
      size_t len = ext - base_name;
      if (len >= sizeof(base_no_ext))
        len = sizeof(base_no_ext) - 1;
      memcpy(base_no_ext, base_name, len);
      base_no_ext[len] = '\0';
    }
    else
    {
      strncpy(base_no_ext, base_name, sizeof(base_no_ext) - 1);
      base_no_ext[sizeof(base_no_ext) - 1] = '\0';
    }
  }

  // Generate output filename if not specified
  if (!output_file)
  {
    char *output_name = (char *)malloc(256);
    snprintf(output_name, 256, "test_results/%s.s", base_no_ext);
    output_file = output_name;
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

  // Optional lexical token logging
  FILE *token_output = NULL;
  char token_output_path[512] = {0};
  int token_output_created = 0;
  set_token_output(NULL);
  if (gen_lex)
  {
    snprintf(token_output_path, sizeof(token_output_path), "tokens_%s.txt", base_no_ext);
    token_output = fopen(token_output_path, "w");
    if (token_output)
    {
      fprintf(token_output, "================================================================================\n");
      fprintf(token_output, "                         LEXICAL TOKENS\n");
      fprintf(token_output, "================================================================================\n\n");
      fprintf(token_output, "Format: [line:col] CATEGORY     lexeme\n\n");
      set_token_output(token_output);
      token_output_created = 1;
    }
    else
    {
      fprintf(stderr, "[WARN] Could not open token log file: %s\n", token_output_path);
    }
  }

  // Setup lexical error output file (always created)
  FILE *lexical_error_output = NULL;
  char lexical_error_path[512];
  snprintf(lexical_error_path, sizeof(lexical_error_path), "lexical_errors_%s.txt", base_no_ext);
  lexical_error_output = fopen(lexical_error_path, "w");
  if (lexical_error_output)
  {
    fprintf(lexical_error_output, "================================================================================\n");
    fprintf(lexical_error_output, "                      LEXICAL ERROR REPORT\n");
    fprintf(lexical_error_output, "================================================================================\n\n");
    fprintf(lexical_error_output, "Input file: %s\n\n", input_file);
    fflush(lexical_error_output);
    set_lexical_error_output(lexical_error_output);
  }

  // Setup syntax error output file (always created)
  FILE *syntax_error_output = NULL;
  char syntax_error_path[512];
  snprintf(syntax_error_path, sizeof(syntax_error_path), "syntax_errors_%s.txt", base_no_ext);
  syntax_error_output = fopen(syntax_error_path, "w");
  if (syntax_error_output)
  {
    fprintf(syntax_error_output, "================================================================================\n");
    fprintf(syntax_error_output, "                       SYNTAX ERROR REPORT\n");
    fprintf(syntax_error_output, "================================================================================\n\n");
    fprintf(syntax_error_output, "Input file: %s\n\n", input_file);
    fflush(syntax_error_output);
    set_syntax_error_output(syntax_error_output);
  }

  // ========================================================================
  // PHASE 1: LEXICAL ANALYSIS & SYNTAX ANALYSIS
  // ========================================================================
  printf("[PHASE 1] Lexical & Syntax Analysis...\n");

  int parse_result = yyparse();

  // Close error output files
  if (lexical_error_output)
  {
    set_lexical_error_output(NULL);
    fclose(lexical_error_output);
    // Delete the file if no errors occurred
    if (!has_lexical_error())
    {
      remove(lexical_error_path);
    }
  }
  if (syntax_error_output)
  {
    set_syntax_error_output(NULL);
    fclose(syntax_error_output);
    // Delete the file if no errors occurred
    if (!has_syntax_error())
    {
      remove(syntax_error_path);
    }
  }

  if (parse_result != 0)
  {
    if (token_output)
    {
      fclose(token_output);
      set_token_output(NULL);
    }
    fprintf(stderr, "\n[ERROR] Parsing failed!\n");
    if (has_lexical_error())
      fprintf(stderr, "[INFO] Lexical errors written to %s\n", lexical_error_path);
    if (has_syntax_error())
      fprintf(stderr, "[INFO] Syntax errors written to %s\n", syntax_error_path);
    fclose(yyin);
    return 1;
  }

  if (!root)
  {
    if (token_output)
    {
      fclose(token_output);
      set_token_output(NULL);
    }
    fprintf(stderr, "\n[ERROR] No AST generated!\n");
    fclose(yyin);
    return 1;
  }

  printf("[PASS] Parsing completed successfully\n\n");

  if (token_output)
  {
    fclose(token_output);
    set_token_output(NULL);
    if (token_output_created)
      printf("[INFO] Lexical tokens written to %s\n", token_output_path);
    token_output = NULL;
  }

  // Optionally output AST
  if (gen_ast)
  {
    char ast_path[512];
    snprintf(ast_path, sizeof(ast_path), "ast_%s.out", base_no_ext);
    FILE *ast_file = fopen(ast_path, "w");
    if (ast_file)
    {
      fprintf(ast_file, "================================================================================\n");
      fprintf(ast_file, "                        ABSTRACT SYNTAX TREE\n");
      fprintf(ast_file, "================================================================================\n\n");
      print_ast(root, 0, ast_file);
      fclose(ast_file);
      printf("[INFO] AST written to %s\n", ast_path);
    }
  }

  // ========================================================================
  // PHASE 2: SEMANTIC ANALYSIS
  // ========================================================================
  printf("[PHASE 2] Semantic Analysis...\n");

  char error_log_path[512];
  snprintf(error_log_path, sizeof(error_log_path), "semantic_errors_%s.txt", base_no_ext);

  SemanticContext *sem_ctx = create_semantic_context(error_log_path);

  printf("  [2.1] Building symbol tables...\n");
  semantic_analysis(root, sem_ctx);

  // Always write per-test semantic log (append-only behavior controlled by file open mode)
  if (sem_ctx->error_file)
  {
    print_errors(sem_ctx, sem_ctx->error_file);
    fflush(sem_ctx->error_file);
  }

  // Generate per-test symbol table output (always, not just with -sym flag)
  {
    // Build symbol table filename: symboltable_<inputfilename>.out
    char sym_log_path[512];
    snprintf(sym_log_path, sizeof(sym_log_path), "symboltable_%s.out", base_no_ext);

    FILE *sym_file = fopen(sym_log_path, "w");
    if (sym_file)
    {
      fprintf(sym_file, "================================================================================\n");
      fprintf(sym_file, "                        SYMBOL TABLE REPORT\n");
      fprintf(sym_file, "================================================================================\n");
      print_symbol_table(sem_ctx->global_table, sym_file);
      fclose(sym_file);
      printf("[INFO] Symbol table written to %s\n", sym_log_path);
    }
  }

  // Generate legacy symbol table output if -sym flag used
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
      printf("[INFO] Symbol table also written to symboltable.out\n");
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

// Ensure test_results directory exists
#ifdef _WIN32
  mkdir("test_results");
#else
  mkdir("test_results", 0755);
#endif

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
  if (gen_lex && token_output_created)
    printf("  - tokens_%s.txt (lexical tokens)\n", base_no_ext);
  if (gen_ast)
    printf("  - ast_%s.out (abstract syntax tree)\n", base_no_ext);
  printf("  - symboltable_%s.out (symbol tables)\n", base_no_ext);
  printf("  - semantic_errors_%s.txt (semantic report)\n", base_no_ext);
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
