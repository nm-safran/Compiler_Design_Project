
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INTEGER = 259,
     FLOAT_NUM = 260,
     ELSE = 261,
     FLOAT = 262,
     IF = 263,
     CLASS = 264,
     ATTRIBUTE = 265,
     PLUS = 266,
     MINUS = 267,
     MULT = 268,
     DIV = 269,
     EQ = 270,
     LPAREN = 271,
     RPAREN = 272,
     LBRACE = 273,
     RBRACE = 274,
     COMMA = 275,
     SEMI = 276,
     GT = 277
   };
#endif
/* Tokens.  */
#define ID 258
#define INTEGER 259
#define FLOAT_NUM 260
#define ELSE 261
#define FLOAT 262
#define IF 263
#define CLASS 264
#define ATTRIBUTE 265
#define PLUS 266
#define MINUS 267
#define MULT 268
#define DIV 269
#define EQ 270
#define LPAREN 271
#define RPAREN 272
#define LBRACE 273
#define RBRACE 274
#define COMMA 275
#define SEMI 276
#define GT 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 52 "parser.y"

    struct token* tok;



/* Line 1676 of yacc.c  */
#line 102 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


