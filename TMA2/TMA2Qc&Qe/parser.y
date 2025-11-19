%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
    char* type;
    char* lexeme;
    int line;
    int column;
};

FILE* derivation_file;
int production_num = 1;

void write_production(const char* production) {
    fprintf(derivation_file, "%d. %s\n", production_num++, production);
    printf("%s\n", production);  // Also print to console
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

extern int yylex();
extern FILE* yyin;
%}

%union {
    struct token* tok;
}

%token <tok> ID INTLIT FLOATLIT
%token <tok> CLASS ISA IMPLEMENT FUNC CONSTRUCTOR PUBLIC PRIVATE ATTRIBUTE LOCAL
%token <tok> IF THEN ELSE WHILE READ WRITE RETURN
%token <tok> INTEGER_TYPE FLOAT_TYPE VOID NOT AND OR SELF
%token <tok> ASSIGN EQ NE LE GE LT GT PLUS MINUS MULT DIV ARROW
%token <tok> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA SEMI DOT COLON

%start prog

%%

prog: classOrImplOrFunc_list
    { write_production("prog -> classOrImplOrFunc_list"); }
    ;

classOrImplOrFunc_list: classOrImplOrFunc classOrImplOrFunc_list
                      { write_production("classOrImplOrFunc_list -> classOrImplOrFunc classOrImplOrFunc_list"); }
                      | classOrImplOrFunc
                      { write_production("classOrImplOrFunc_list -> classOrImplOrFunc"); }
                      ;

classOrImplOrFunc: classDecl
                 { write_production("classOrImplOrFunc -> classDecl"); }
                 | implDef
                 { write_production("classOrImplOrFunc -> implDef"); }
                 | funcDef
                 { write_production("classOrImplOrFunc -> funcDef"); }
                 ;

classDecl: CLASS ID isa_opt LBRACE member_list_opt RBRACE SEMI
         { write_production("classDecl -> class id isa_opt { member_list_opt } ;"); }
         ;

isa_opt: ISA ID id_list_opt
       { write_production("isa_opt -> isa id id_list_opt"); }
       | /* empty */
       { write_production("isa_opt -> ε"); }
       ;

id_list_opt: COMMA ID id_list_opt
           { write_production("id_list_opt -> , id id_list_opt"); }
           | /* empty */
           { write_production("id_list_opt -> ε"); }
           ;

implDef: IMPLEMENT ID LBRACE func_list_opt RBRACE
       { write_production("implDef -> implement id { func_list_opt }"); }
       ;

func_list_opt: funcDef func_list_opt
             { write_production("func_list_opt -> funcDef func_list_opt"); }
             | /* empty */
             { write_production("func_list_opt -> ε"); }
             ;

funcDef: funcHead funcBody
       { write_production("funcDef -> funcHead funcBody"); }
       ;

member_list_opt: visibility memberDecl member_list_opt
               { write_production("member_list_opt -> visibility memberDecl member_list_opt"); }
               | /* empty */
               { write_production("member_list_opt -> ε"); }
               ;

visibility: PUBLIC
          { write_production("visibility -> public"); }
          | PRIVATE
          { write_production("visibility -> private"); }
          ;

memberDecl: funcDecl
          { write_production("memberDecl -> funcDecl"); }
          | attributeDecl
          { write_production("memberDecl -> attributeDecl"); }
          ;

funcDecl: funcHead SEMI
        { write_production("funcDecl -> funcHead ;"); }
        ;

funcHead: FUNC ID LPAREN fParams_opt RPAREN ARROW returnType
        { write_production("funcHead -> func id ( fParams_opt ) => returnType"); }
        | CONSTRUCTOR LPAREN fParams_opt RPAREN
        { write_production("funcHead -> constructor ( fParams_opt )"); }
        ;

funcBody: LBRACE stmt_list_opt RBRACE
        { write_production("funcBody -> { stmt_list_opt }"); }
        ;

stmt_list_opt: varDeclOrStmt stmt_list_opt
             { write_production("stmt_list_opt -> varDeclOrStmt stmt_list_opt"); }
             | /* empty */
             { write_production("stmt_list_opt -> ε"); }
             ;

varDeclOrStmt: localVarDecl
             { write_production("varDeclOrStmt -> localVarDecl"); }
             | statement
             { write_production("varDeclOrStmt -> statement"); }
             ;

attributeDecl: ATTRIBUTE varDecl
             { write_production("attributeDecl -> attribute varDecl"); }
             ;

localVarDecl: LOCAL varDecl
            { write_production("localVarDecl -> local varDecl"); }
            ;

varDecl: ID COLON type array_list_opt SEMI
       { write_production("varDecl -> id : type array_list_opt ;"); }
       ;

array_list_opt: arraySize array_list_opt
              { write_production("array_list_opt -> arraySize array_list_opt"); }
              | /* empty */
              { write_production("array_list_opt -> ε"); }
              ;

statement: assignStat SEMI
         { write_production("statement -> assignStat ;"); }
         | IF LPAREN expr RPAREN THEN statBlock ELSE statBlock SEMI
         { write_production("statement -> if ( expr ) then statBlock else statBlock ;"); }
         | WHILE LPAREN expr RPAREN statBlock SEMI
         { write_production("statement -> while ( expr ) statBlock ;"); }
         | READ LPAREN variable RPAREN SEMI
         { write_production("statement -> read ( variable ) ;"); }
         | WRITE LPAREN expr RPAREN SEMI
         { write_production("statement -> write ( expr ) ;"); }
         | RETURN LPAREN expr RPAREN SEMI
         { write_production("statement -> return ( expr ) ;"); }
         | functionCall SEMI
         { write_production("statement -> functionCall ;"); }
         ;

assignStat: variable ASSIGN expr
          { write_production("assignStat -> variable := expr"); }
          ;

statBlock: LBRACE statement_list_opt RBRACE
         { write_production("statBlock -> { statement_list_opt }"); }
         | statement
         { write_production("statBlock -> statement"); }
         | /* empty */
         { write_production("statBlock -> ε"); }
         ;

statement_list_opt: statement statement_list_opt
                  { write_production("statement_list_opt -> statement statement_list_opt"); }
                  | /* empty */
                  { write_production("statement_list_opt -> ε"); }
                  ;

expr: arithExpr rel_expr_opt
    { write_production("expr -> arithExpr rel_expr_opt"); }
    ;

rel_expr_opt: relOp arithExpr
            { write_production("rel_expr_opt -> relOp arithExpr"); }
            | /* empty */
            { write_production("rel_expr_opt -> ε"); }
            ;

arithExpr: term arith_expr_tail
         { write_production("arithExpr -> term arith_expr_tail"); }
         ;

arith_expr_tail: addOp term arith_expr_tail
               { write_production("arith_expr_tail -> addOp term arith_expr_tail"); }
               | /* empty */
               { write_production("arith_expr_tail -> ε"); }
               ;

term: factor term_tail
    { write_production("term -> factor term_tail"); }
    ;

term_tail: multOp factor term_tail
         { write_production("term_tail -> multOp factor term_tail"); }
         | /* empty */
         { write_production("term_tail -> ε"); }
         ;

factor: primary_factor
      { write_production("factor -> primary_factor"); }
      | NOT factor
      { write_production("factor -> not factor"); }
      | sign factor
      { write_production("factor -> sign factor"); }
      ;

primary_factor: simple_variable
              { write_production("primary_factor -> simple_variable"); }
              | simple_functionCall
              { write_production("primary_factor -> simple_functionCall"); }
              | INTLIT
              { write_production("primary_factor -> intLit"); }
              | FLOATLIT
              { write_production("primary_factor -> floatLit"); }
              | LPAREN arithExpr RPAREN
              { write_production("primary_factor -> ( arithExpr )"); }
              ;

simple_variable: qualified_id indices_opt
               { write_production("simple_variable -> qualified_id indices_opt"); }
               ;

simple_functionCall: qualified_id LPAREN aParams_opt RPAREN
                   { write_production("simple_functionCall -> qualified_id ( aParams_opt )"); }
                   ;

qualified_id: ID
            { write_production("qualified_id -> id"); }
            | SELF
            { write_production("qualified_id -> self"); }
            | qualified_id DOT ID
            { write_production("qualified_id -> qualified_id . id"); }
            | qualified_id LBRACKET arithExpr RBRACKET DOT ID
            { write_production("qualified_id -> qualified_id [ arithExpr ] . id"); }
            | qualified_id LPAREN aParams_opt RPAREN DOT ID
            { write_production("qualified_id -> qualified_id ( aParams_opt ) . id"); }
            ;

variable: simple_variable
        { write_production("variable -> simple_variable"); }
        ;

functionCall: simple_functionCall
            { write_production("functionCall -> simple_functionCall"); }
            ;

indices_opt: LBRACKET arithExpr RBRACKET indices_opt
           { write_production("indices_opt -> [ arithExpr ] indices_opt"); }
           | /* empty */
           { write_production("indices_opt -> ε"); }
           ;

arraySize: LBRACKET INTLIT RBRACKET
         { write_production("arraySize -> [ intLit ]"); }
         | LBRACKET RBRACKET
         { write_production("arraySize -> [ ]"); }
         ;

type: INTEGER_TYPE
    { write_production("type -> integer"); }
    | FLOAT_TYPE
    { write_production("type -> float"); }
    | ID
    { write_production("type -> id"); }
    ;

returnType: type
          { write_production("returnType -> type"); }
          | VOID
          { write_production("returnType -> void"); }
          ;

fParams_opt: ID COLON type array_list_opt fParams_tail_opt
           { write_production("fParams_opt -> id : type array_list_opt fParams_tail_opt"); }
           | /* empty */
           { write_production("fParams_opt -> ε"); }
           ;

fParams_tail_opt: COMMA ID COLON type array_list_opt fParams_tail_opt
                { write_production("fParams_tail_opt -> , id : type array_list_opt fParams_tail_opt"); }
                | /* empty */
                { write_production("fParams_tail_opt -> ε"); }
                ;

aParams_opt: expr aParams_tail_opt
           { write_production("aParams_opt -> expr aParams_tail_opt"); }
           | /* empty */
           { write_production("aParams_opt -> ε"); }
           ;

aParams_tail_opt: COMMA expr aParams_tail_opt
                { write_production("aParams_tail_opt -> , expr aParams_tail_opt"); }
                | /* empty */
                { write_production("aParams_tail_opt -> ε"); }
                ;

relOp: EQ { write_production("relOp -> =="); }
     | NE { write_production("relOp -> <>"); }
     | LT { write_production("relOp -> <"); }
     | GT { write_production("relOp -> >"); }
     | LE { write_production("relOp -> <="); }
     | GE { write_production("relOp -> >="); }
     ;

addOp: PLUS { write_production("addOp -> +"); }
     | MINUS { write_production("addOp -> -"); }
     | OR { write_production("addOp -> or"); }
     ;

multOp: MULT { write_production("multOp -> *"); }
      | DIV { write_production("multOp -> /"); }
      | AND { write_production("multOp -> and"); }
      ;

sign: PLUS { write_production("sign -> +"); }
    | MINUS { write_production("sign -> -"); }
    ;

%%

int main(int argc, char* argv[]) {
    // Open derivation file
    derivation_file = fopen("derivation.txt", "w");
    if (!derivation_file) {
        fprintf(stderr, "Error: Cannot create derivation.txt file\n");
        return 1;
    }

    // Handle input file if provided
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
            fclose(derivation_file);
            return 1;
        }
    }

    printf("Starting parse...\n");
    printf("Derivation steps:\n");
    printf("================\n");

    fprintf(derivation_file, "Derivation of the source program from start symbol 'prog':\n");
    fprintf(derivation_file, "=========================================================\n");

    int result = yyparse();

    if (result == 0) {
        printf("\n=== Parse completed successfully! ===\n");
        printf("Derivation has been written to 'derivation.txt'\n");
        fprintf(derivation_file, "\nParse completed successfully.\n");
    } else {
        printf("\n=== Parse failed with errors ===\n");
        fprintf(derivation_file, "\nParse failed with errors.\n");
    }

    fclose(derivation_file);
    if (yyin != stdin) fclose(yyin);

    return result;
}
