%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include AST and semantic headers first
#include "ast.h"
#include "symboltable.h"
#include "semantic.h"

struct token {
    char* type;
    char* lexeme;
    int line;
    int column;
};

ASTNode* root = NULL;
extern int yylex();
extern FILE* yyin;
extern int line, column;

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", line, s);
}
%}

%union {
    struct token* tok;
    ASTNode* node;
}

%token <tok> ID INTLIT FLOATLIT
%token <tok> CLASS ISA IMPLEMENT FUNC CONSTRUCTOR PUBLIC PRIVATE ATTRIBUTE LOCAL
%token <tok> IF THEN ELSE WHILE READ WRITE RETURN
%token <tok> INTEGER_TYPE FLOAT_TYPE VOID NOT AND OR SELF
%token <tok> ASSIGN EQ NE LE GE LT GT PLUS MINUS MULT DIV ARROW
%token <tok> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA SEMI DOT COLON

%type <node> prog classOrImplOrFunc_list classOrImplOrFunc classDecl implDef funcDef
%type <node> member_list_opt memberDecl funcDecl funcHead funcBody stmt_list_opt
%type <node> varDeclOrStmt attributeDecl localVarDecl varDecl statement assignStat
%type <node> statBlock expr arithExpr term factor variable functionCall
%type <node> type returnType fParams_opt aParams_opt primary_factor
%type <node> array_list_opt arraySize indices_opt visibility
%type <node> isa_opt id_list_opt func_list_opt statement_list_opt
%type <node> rel_expr_opt arith_expr_tail term_tail fParams_tail_opt aParams_tail_opt
%type <node> relOp addOp multOp sign qualified_id

%start prog

%%

prog: classOrImplOrFunc_list
    {
        $$ = create_node(NODE_PROG, "program", 1, 1);
        add_child($$, $1);
        root = $$;
    }
    ;

classOrImplOrFunc_list: classOrImplOrFunc classOrImplOrFunc_list
                      {
                          $$ = create_node(NODE_LIST, "list", $1->line, 1);
                          add_child($$, $1);
                          add_child($$, $2);
                      }
                      | classOrImplOrFunc
                      { $$ = $1; }
                      ;

classOrImplOrFunc: classDecl { $$ = $1; }
                 | implDef { $$ = $1; }
                 | funcDef { $$ = $1; }
                 ;

classDecl: CLASS ID isa_opt LBRACE member_list_opt RBRACE SEMI
         {
             $$ = create_node(NODE_CLASS_DECL, "class", $2->line, $2->column);
             ASTNode* id = create_node(NODE_ID, $2->lexeme, $2->line, $2->column);
             add_child($$, id);
             if ($3) add_child($$, $3);
             if ($5) add_child($$, $5);
         }
         ;

isa_opt: ISA ID id_list_opt
       {
           $$ = create_node(NODE_LIST, "inherits", $2->line, $2->column);
           ASTNode* id = create_node(NODE_ID, $2->lexeme, $2->line, $2->column);
           add_child($$, id);
           if ($3) add_child($$, $3);
       }
       | /* empty */ { $$ = NULL; }
       ;

id_list_opt: COMMA ID id_list_opt
           {
               $$ = create_node(NODE_LIST, "id_list", $2->line, $2->column);
               ASTNode* id = create_node(NODE_ID, $2->lexeme, $2->line, $2->column);
               add_child($$, id);
               if ($3) add_child($$, $3);
           }
           | /* empty */ { $$ = NULL; }
           ;

implDef: IMPLEMENT ID LBRACE func_list_opt RBRACE
       {
           $$ = create_node(NODE_IMPL_DEF, "implement", $2->line, $2->column);
           ASTNode* id = create_node(NODE_ID, $2->lexeme, $2->line, $2->column);
           add_child($$, id);
           if ($4) add_child($$, $4);
       }
       ;

func_list_opt: funcDef func_list_opt
             {
                 $$ = create_node(NODE_LIST, "func_list", $1->line, 1);
                 add_child($$, $1);
                 if ($2) add_child($$, $2);
             }
             | /* empty */ { $$ = NULL; }
             ;

funcDef: funcHead funcBody
       {
           $$ = create_node(NODE_FUNC_DEF, "funcDef", $1->line, 1);
           add_child($$, $1);
           add_child($$, $2);
       }
       ;

member_list_opt: visibility memberDecl member_list_opt
               {
                   $$ = create_node(NODE_LIST, "members", $2->line, 1);
                   add_child($$, $1);
                   add_child($$, $2);
                   if ($3) add_child($$, $3);
               }
               | /* empty */ { $$ = NULL; }
               ;

visibility: PUBLIC
          { $$ = create_node(NODE_ID, "public", $1->line, $1->column); }
          | PRIVATE
          { $$ = create_node(NODE_ID, "private", $1->line, $1->column); }
          ;

memberDecl: funcDecl { $$ = $1; }
          | attributeDecl { $$ = $1; }
          ;

funcDecl: funcHead SEMI
        {
            $$ = create_node(NODE_FUNC_DECL, "funcDecl", $1->line, 1);
            add_child($$, $1);
        }
        ;

funcHead: FUNC ID LPAREN fParams_opt RPAREN ARROW returnType
        {
            $$ = create_node(NODE_FUNC_DEF, "funcHead", $2->line, $2->column);
            ASTNode* id = create_node(NODE_ID, $2->lexeme, $2->line, $2->column);
            add_child($$, id);
            if ($4) add_child($$, $4);
            add_child($$, $7);
        }
        | CONSTRUCTOR LPAREN fParams_opt RPAREN
        {
            $$ = create_node(NODE_FUNC_DEF, "constructor", $1->line, $1->column);
            if ($3) add_child($$, $3);
        }
        ;

funcBody: LBRACE stmt_list_opt RBRACE
        {
            $$ = create_node(NODE_LIST, "funcBody", $1->line, $1->column);
            if ($2) add_child($$, $2);
        }
        ;

stmt_list_opt: varDeclOrStmt stmt_list_opt
             {
                 $$ = create_node(NODE_LIST, "stmts", $1->line, 1);
                 add_child($$, $1);
                 if ($2) add_child($$, $2);
             }
             | /* empty */ { $$ = NULL; }
             ;

varDeclOrStmt: localVarDecl { $$ = $1; }
             | statement { $$ = $1; }
             ;

attributeDecl: ATTRIBUTE varDecl
             {
                 $$ = $2;
                 $$->type = NODE_VAR_DECL;
             }
             ;

localVarDecl: LOCAL varDecl
            {
                $$ = $2;
            }
            ;

varDecl: ID COLON type array_list_opt SEMI
       {
           $$ = create_node(NODE_VAR_DECL, "varDecl", $1->line, $1->column);
           ASTNode* id = create_node(NODE_ID, $1->lexeme, $1->line, $1->column);
           add_child($$, id);
           add_child($$, $3);
           if ($4) add_child($$, $4);
       }
       ;

array_list_opt: arraySize array_list_opt
              {
                  $$ = create_node(NODE_LIST, "arrays", $1->line, 1);
                  add_child($$, $1);
                  if ($2) add_child($$, $2);
              }
              | /* empty */ { $$ = NULL; }
              ;

statement: assignStat SEMI
         { $$ = $1; }
         | IF LPAREN expr RPAREN THEN statBlock ELSE statBlock SEMI
         {
             $$ = create_node(NODE_IF_STAT, "if", $1->line, $1->column);
             add_child($$, $3);
             add_child($$, $6);
             add_child($$, $8);
         }
         | WHILE LPAREN expr RPAREN statBlock SEMI
         {
             $$ = create_node(NODE_WHILE_STAT, "while", $1->line, $1->column);
             add_child($$, $3);
             add_child($$, $5);
         }
         | READ LPAREN variable RPAREN SEMI
         {
             $$ = create_node(NODE_READ_STAT, "read", $1->line, $1->column);
             add_child($$, $3);
         }
         | WRITE LPAREN expr RPAREN SEMI
         {
             $$ = create_node(NODE_WRITE_STAT, "write", $1->line, $1->column);
             add_child($$, $3);
         }
         | RETURN LPAREN expr RPAREN SEMI
         {
             $$ = create_node(NODE_RETURN_STAT, "return", $1->line, $1->column);
             add_child($$, $3);
         }
         | functionCall SEMI
         { $$ = $1; }
         ;

assignStat: variable ASSIGN expr
          {
              $$ = create_node(NODE_ASSIGN_STAT, ":=", $1->line, 1);
              add_child($$, $1);
              add_child($$, $3);
          }
          ;

statBlock: LBRACE statement_list_opt RBRACE
         { $$ = $2; }
         | statement
         { $$ = $1; }
         | /* empty */ { $$ = NULL; }
         ;

statement_list_opt: statement statement_list_opt
                  {
                      $$ = create_node(NODE_LIST, "stat_list", $1->line, 1);
                      add_child($$, $1);
                      if ($2) add_child($$, $2);
                  }
                  | /* empty */ { $$ = NULL; }
                  ;

expr: arithExpr rel_expr_opt
    {
        if ($2) {
            $$ = create_node(NODE_REL_EXPR, "relExpr", $1->line, 1);
            add_child($$, $1);
            add_child($$, $2);
        } else {
            $$ = $1;
        }
    }
    ;

rel_expr_opt: relOp arithExpr
            {
                $$ = create_node(NODE_EXPR, "rel", $1->line, 1);
                add_child($$, $1);
                add_child($$, $2);
            }
            | /* empty */ { $$ = NULL; }
            ;

arithExpr: term arith_expr_tail
         {
             if ($2) {
                 $$ = create_node(NODE_ADD_EXPR, "addExpr", $1->line, 1);
                 add_child($$, $1);
                 add_child($$, $2);
             } else {
                 $$ = $1;
             }
         }
         ;

arith_expr_tail: addOp term arith_expr_tail
               {
                   $$ = create_node(NODE_EXPR, "add_tail", $1->line, 1);
                   add_child($$, $1);
                   add_child($$, $2);
                   if ($3) add_child($$, $3);
               }
               | /* empty */ { $$ = NULL; }
               ;

term: factor term_tail
    {
        if ($2) {
            $$ = create_node(NODE_MULT_EXPR, "multExpr", $1->line, 1);
            add_child($$, $1);
            add_child($$, $2);
        } else {
            $$ = $1;
        }
    }
    ;

term_tail: multOp factor term_tail
         {
             $$ = create_node(NODE_EXPR, "mult_tail", $1->line, 1);
             add_child($$, $1);
             add_child($$, $2);
             if ($3) add_child($$, $3);
         }
         | /* empty */ { $$ = NULL; }
         ;

factor: primary_factor
      { $$ = $1; }
      | NOT factor
      {
          $$ = create_node(NODE_NOT_EXPR, "not", $2->line, 1);
          add_child($$, $2);
      }
      | sign factor
      {
          $$ = create_node(NODE_SIGN_EXPR, $1->value, $2->line, 1);
          add_child($$, $2);
      }
      ;

primary_factor: variable
              { $$ = $1; }
              | functionCall
              { $$ = $1; }
              | INTLIT
              { $$ = create_node(NODE_INTLIT, $1->lexeme, $1->line, $1->column); }
              | FLOATLIT
              { $$ = create_node(NODE_FLOATLIT, $1->lexeme, $1->line, $1->column); }
              | LPAREN arithExpr RPAREN
              { $$ = $2; }
              ;

variable: qualified_id indices_opt
        {
            $$ = create_node(NODE_VARIABLE, "var", $1->line, 1);
            add_child($$, $1);
            if ($2) add_child($$, $2);
        }
        ;

functionCall: qualified_id LPAREN aParams_opt RPAREN
            {
                $$ = create_node(NODE_FUNC_CALL, "call", $1->line, 1);
                add_child($$, $1);
                if ($3) add_child($$, $3);
            }
            ;

qualified_id: ID
            { $$ = create_node(NODE_ID, $1->lexeme, $1->line, $1->column); }
            | SELF
            { $$ = create_node(NODE_ID, "self", $1->line, $1->column); }
            | qualified_id DOT ID
            {
                $$ = create_node(NODE_EXPR, "member", $1->line, 1);
                add_child($$, $1);
                add_child($$, create_node(NODE_ID, $3->lexeme, $3->line, $3->column));
            }
            | qualified_id LBRACKET arithExpr RBRACKET DOT ID
            {
                $$ = create_node(NODE_EXPR, "array_member", $1->line, 1);
                add_child($$, $1);
                add_child($$, $3);
                add_child($$, create_node(NODE_ID, $6->lexeme, $6->line, $6->column));
            }
            | qualified_id LPAREN aParams_opt RPAREN DOT ID
            {
                $$ = create_node(NODE_EXPR, "call_member", $1->line, 1);
                add_child($$, $1);
                if ($3) add_child($$, $3);
                add_child($$, create_node(NODE_ID, $6->lexeme, $6->line, $6->column));
            }
            ;

indices_opt: LBRACKET arithExpr RBRACKET indices_opt
           {
               $$ = create_node(NODE_LIST, "indices", $2->line, 1);
               add_child($$, $2);
               if ($4) add_child($$, $4);
           }
           | /* empty */ { $$ = NULL; }
           ;

arraySize: LBRACKET INTLIT RBRACKET
         {
             $$ = create_node(NODE_ARRAY_SIZE, $2->lexeme, $2->line, $2->column);
         }
         | LBRACKET RBRACKET
         {
             $$ = create_node(NODE_ARRAY_SIZE, "0", $1->line, $1->column);
         }
         ;

type: INTEGER_TYPE
    { $$ = create_node(NODE_TYPE, "integer", $1->line, $1->column); }
    | FLOAT_TYPE
    { $$ = create_node(NODE_TYPE, "float", $1->line, $1->column); }
    | ID
    { $$ = create_node(NODE_TYPE, $1->lexeme, $1->line, $1->column); }
    ;

returnType: type
          { $$ = $1; }
          | VOID
          { $$ = create_node(NODE_TYPE, "void", $1->line, $1->column); }
          ;

fParams_opt: ID COLON type array_list_opt fParams_tail_opt
           {
               $$ = create_node(NODE_PARAM, "param", $1->line, $1->column);
               ASTNode* id = create_node(NODE_ID, $1->lexeme, $1->line, $1->column);
               add_child($$, id);
               add_child($$, $3);
               if ($4) add_child($$, $4);
               if ($5) add_child($$, $5);
           }
           | /* empty */ { $$ = NULL; }
           ;

fParams_tail_opt: COMMA ID COLON type array_list_opt fParams_tail_opt
                {
                    $$ = create_node(NODE_PARAM, "param", $2->line, $2->column);
                    ASTNode* id = create_node(NODE_ID, $2->lexeme, $2->line, $2->column);
                    add_child($$, id);
                    add_child($$, $4);
                    if ($5) add_child($$, $5);
                    if ($6) add_child($$, $6);
                }
                | /* empty */ { $$ = NULL; }
                ;

aParams_opt: expr aParams_tail_opt
           {
               $$ = create_node(NODE_LIST, "args", $1->line, 1);
               add_child($$, $1);
               if ($2) add_child($$, $2);
           }
           | /* empty */ { $$ = NULL; }
           ;

aParams_tail_opt: COMMA expr aParams_tail_opt
                {
                    $$ = create_node(NODE_LIST, "args", $2->line, 1);
                    add_child($$, $2);
                    if ($3) add_child($$, $3);
                }
                | /* empty */ { $$ = NULL; }
                ;

relOp: EQ { $$ = create_node(NODE_EXPR, "==", $1->line, $1->column); }
     | NE { $$ = create_node(NODE_EXPR, "<>", $1->line, $1->column); }
     | LT { $$ = create_node(NODE_EXPR, "<", $1->line, $1->column); }
     | GT { $$ = create_node(NODE_EXPR, ">", $1->line, $1->column); }
     | LE { $$ = create_node(NODE_EXPR, "<=", $1->line, $1->column); }
     | GE { $$ = create_node(NODE_EXPR, ">=", $1->line, $1->column); }
     ;

addOp: PLUS { $$ = create_node(NODE_EXPR, "+", $1->line, $1->column); }
     | MINUS { $$ = create_node(NODE_EXPR, "-", $1->line, $1->column); }
     | OR { $$ = create_node(NODE_EXPR, "or", $1->line, $1->column); }
     ;

multOp: MULT { $$ = create_node(NODE_EXPR, "*", $1->line, $1->column); }
      | DIV { $$ = create_node(NODE_EXPR, "/", $1->line, $1->column); }
      | AND { $$ = create_node(NODE_EXPR, "and", $1->line, $1->column); }
      ;

sign: PLUS { $$ = create_node(NODE_EXPR, "+", $1->line, $1->column); }
    | MINUS { $$ = create_node(NODE_EXPR, "-", $1->line, $1->column); }
    ;

%%

int main(int argc, char* argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
            return 1;
        }
    }

    printf("Starting parse and semantic analysis...\n");

    int result = yyparse();

    if (result == 0 && root) {
        printf("\n=== Parse completed successfully! ===\n");

        // Print AST
        FILE* ast_file = fopen("ast.out", "w");
        fprintf(ast_file, "Abstract Syntax Tree:\n");
        fprintf(ast_file, "=====================\n\n");
        print_ast(root, 0, ast_file);
        fclose(ast_file);
        printf("AST written to ast.out\n");

        // Semantic Analysis
        SemanticContext* sem_ctx = create_semantic_context();
        semantic_analysis(root, sem_ctx);

        // Print symbol table
        FILE* sym_file = fopen("symboltable.out", "w");
        fprintf(sym_file, "================================================================================\n");
        fprintf(sym_file, "                        SYMBOL TABLE REPORT\n");
        fprintf(sym_file, "================================================================================\n");
        print_symbol_table(sem_ctx->global_table, sym_file);
        fclose(sym_file);
        printf("Symbol table written to symboltable.out\n");

        // Print errors
        FILE* err_file = fopen("semantic_errors.out", "w");
        print_errors(sem_ctx, err_file);
        print_errors(sem_ctx, stdout);
        fclose(err_file);
        printf("Errors written to semantic_errors.out\n");

        printf("\n=== Output files generated ===\n");
        printf("- ast.out: Abstract Syntax Tree\n");
        printf("- symboltable.out: Symbol Table\n");
        printf("- semantic_errors.out: Semantic Errors and Warnings\n");

        free_semantic_context(sem_ctx);
        free_ast(root);
    } else {
        printf("\n=== Parse failed with errors ===\n");
    }

    if (yyin != stdin) fclose(yyin);
    return result;
}
