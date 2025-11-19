/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 98 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTLIT = 4,                     /* INTLIT  */
  YYSYMBOL_FLOATLIT = 5,                   /* FLOATLIT  */
  YYSYMBOL_CLASS = 6,                      /* CLASS  */
  YYSYMBOL_ISA = 7,                        /* ISA  */
  YYSYMBOL_IMPLEMENT = 8,                  /* IMPLEMENT  */
  YYSYMBOL_FUNC = 9,                       /* FUNC  */
  YYSYMBOL_CONSTRUCTOR = 10,               /* CONSTRUCTOR  */
  YYSYMBOL_PUBLIC = 11,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 12,                   /* PRIVATE  */
  YYSYMBOL_ATTRIBUTE = 13,                 /* ATTRIBUTE  */
  YYSYMBOL_LOCAL = 14,                     /* LOCAL  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_THEN = 16,                      /* THEN  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_READ = 19,                      /* READ  */
  YYSYMBOL_WRITE = 20,                     /* WRITE  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_INTEGER_TYPE = 22,              /* INTEGER_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 23,                /* FLOAT_TYPE  */
  YYSYMBOL_VOID = 24,                      /* VOID  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_SELF = 28,                      /* SELF  */
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NE = 31,                        /* NE  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_GE = 33,                        /* GE  */
  YYSYMBOL_LT = 34,                        /* LT  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_PLUS = 36,                      /* PLUS  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_MULT = 38,                      /* MULT  */
  YYSYMBOL_DIV = 39,                       /* DIV  */
  YYSYMBOL_ARROW = 40,                     /* ARROW  */
  YYSYMBOL_LPAREN = 41,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 42,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 43,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 44,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 45,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 46,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_SEMI = 48,                      /* SEMI  */
  YYSYMBOL_DOT = 49,                       /* DOT  */
  YYSYMBOL_COLON = 50,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_prog = 52,                      /* prog  */
  YYSYMBOL_classOrImplOrFunc_list = 53,    /* classOrImplOrFunc_list  */
  YYSYMBOL_classOrImplOrFunc = 54,         /* classOrImplOrFunc  */
  YYSYMBOL_classDecl = 55,                 /* classDecl  */
  YYSYMBOL_isa_opt = 56,                   /* isa_opt  */
  YYSYMBOL_id_list_opt = 57,               /* id_list_opt  */
  YYSYMBOL_implDef = 58,                   /* implDef  */
  YYSYMBOL_func_list_opt = 59,             /* func_list_opt  */
  YYSYMBOL_funcDef = 60,                   /* funcDef  */
  YYSYMBOL_member_list_opt = 61,           /* member_list_opt  */
  YYSYMBOL_visibility = 62,                /* visibility  */
  YYSYMBOL_memberDecl = 63,                /* memberDecl  */
  YYSYMBOL_funcDecl = 64,                  /* funcDecl  */
  YYSYMBOL_funcHead = 65,                  /* funcHead  */
  YYSYMBOL_funcBody = 66,                  /* funcBody  */
  YYSYMBOL_stmt_list_opt = 67,             /* stmt_list_opt  */
  YYSYMBOL_varDeclOrStmt = 68,             /* varDeclOrStmt  */
  YYSYMBOL_attributeDecl = 69,             /* attributeDecl  */
  YYSYMBOL_localVarDecl = 70,              /* localVarDecl  */
  YYSYMBOL_varDecl = 71,                   /* varDecl  */
  YYSYMBOL_array_list_opt = 72,            /* array_list_opt  */
  YYSYMBOL_statement = 73,                 /* statement  */
  YYSYMBOL_assignStat = 74,                /* assignStat  */
  YYSYMBOL_statBlock = 75,                 /* statBlock  */
  YYSYMBOL_statement_list_opt = 76,        /* statement_list_opt  */
  YYSYMBOL_expr = 77,                      /* expr  */
  YYSYMBOL_rel_expr_opt = 78,              /* rel_expr_opt  */
  YYSYMBOL_arithExpr = 79,                 /* arithExpr  */
  YYSYMBOL_arith_expr_tail = 80,           /* arith_expr_tail  */
  YYSYMBOL_term = 81,                      /* term  */
  YYSYMBOL_term_tail = 82,                 /* term_tail  */
  YYSYMBOL_factor = 83,                    /* factor  */
  YYSYMBOL_primary_factor = 84,            /* primary_factor  */
  YYSYMBOL_variable = 85,                  /* variable  */
  YYSYMBOL_functionCall = 86,              /* functionCall  */
  YYSYMBOL_qualified_id = 87,              /* qualified_id  */
  YYSYMBOL_indices_opt = 88,               /* indices_opt  */
  YYSYMBOL_arraySize = 89,                 /* arraySize  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_returnType = 91,                /* returnType  */
  YYSYMBOL_fParams_opt = 92,               /* fParams_opt  */
  YYSYMBOL_fParams_tail_opt = 93,          /* fParams_tail_opt  */
  YYSYMBOL_aParams_opt = 94,               /* aParams_opt  */
  YYSYMBOL_aParams_tail_opt = 95,          /* aParams_tail_opt  */
  YYSYMBOL_relOp = 96,                     /* relOp  */
  YYSYMBOL_addOp = 97,                     /* addOp  */
  YYSYMBOL_multOp = 98,                    /* multOp  */
  YYSYMBOL_sign = 99                       /* sign  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  201

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    62,    68,    72,    73,    74,    77,    87,
      94,    97,   104,   107,   116,   122,   125,   133,   140,   143,
     145,   149,   150,   153,   160,   168,   175,   182,   188,   191,
     192,   195,   202,   208,   218,   224,   227,   229,   236,   242,
     247,   252,   257,   261,   269,   271,   273,   276,   282,   285,
     297,   303,   306,   318,   325,   328,   340,   347,   350,   352,
     357,   364,   366,   368,   370,   372,   376,   384,   392,   394,
     396,   402,   409,   418,   424,   427,   431,   437,   439,   441,
     445,   447,   451,   460,   463,   472,   475,   481,   484,   490,
     493,   494,   495,   496,   497,   498,   501,   502,   503,   506,
     507,   508,   511,   512
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTLIT",
  "FLOATLIT", "CLASS", "ISA", "IMPLEMENT", "FUNC", "CONSTRUCTOR", "PUBLIC",
  "PRIVATE", "ATTRIBUTE", "LOCAL", "IF", "THEN", "ELSE", "WHILE", "READ",
  "WRITE", "RETURN", "INTEGER_TYPE", "FLOAT_TYPE", "VOID", "NOT", "AND",
  "OR", "SELF", "ASSIGN", "EQ", "NE", "LE", "GE", "LT", "GT", "PLUS",
  "MINUS", "MULT", "DIV", "ARROW", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "COMMA", "SEMI", "DOT", "COLON", "$accept",
  "prog", "classOrImplOrFunc_list", "classOrImplOrFunc", "classDecl",
  "isa_opt", "id_list_opt", "implDef", "func_list_opt", "funcDef",
  "member_list_opt", "visibility", "memberDecl", "funcDecl", "funcHead",
  "funcBody", "stmt_list_opt", "varDeclOrStmt", "attributeDecl",
  "localVarDecl", "varDecl", "array_list_opt", "statement", "assignStat",
  "statBlock", "statement_list_opt", "expr", "rel_expr_opt", "arithExpr",
  "arith_expr_tail", "term", "term_tail", "factor", "primary_factor",
  "variable", "functionCall", "qualified_id", "indices_opt", "arraySize",
  "type", "returnType", "fParams_opt", "fParams_tail_opt", "aParams_opt",
  "aParams_tail_opt", "relOp", "addOp", "multOp", "sign", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-148)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      81,    19,    21,    27,     1,    60,  -148,    81,  -148,  -148,
    -148,    22,    67,    38,    42,    82,  -148,  -148,    58,  -148,
      89,    52,   101,    82,    66,    76,  -148,   118,    83,    84,
      85,    86,    87,  -148,    78,    58,  -148,  -148,    75,   100,
      88,     6,    90,   102,    91,   101,    92,    41,  -148,    80,
    -148,    34,    34,    18,    34,    34,  -148,  -148,  -148,    34,
    -148,    34,    34,   128,  -148,   129,  -148,  -148,  -148,    94,
      99,  -148,  -148,    93,  -148,  -148,  -148,    95,    41,  -148,
    -148,    34,  -148,  -148,    34,    97,    71,    31,    14,  -148,
    -148,  -148,    34,   103,   104,    39,   108,   109,  -148,   105,
     111,    96,  -148,    90,   106,   118,   102,  -148,   107,  -148,
      26,     8,   110,    95,    95,  -148,   114,   125,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,    34,  -148,  -148,  -148,  -148,
      34,  -148,  -148,  -148,  -148,    34,  -148,    13,   112,    34,
     113,   115,    34,  -148,   119,   -22,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,   116,  -148,   155,  -148,  -148,   121,
    -148,    13,  -148,    31,    14,    79,  -148,   122,  -148,   117,
    -148,  -148,   105,   161,    34,   168,  -148,  -148,   123,  -148,
     159,  -148,  -148,    79,   133,  -148,   119,  -148,  -148,   126,
    -148,    41,    13,  -148,  -148,   134,    95,   130,   110,  -148,
    -148
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     4,     5,     6,
       7,     0,    10,     0,     0,    83,     1,     3,    28,    16,
       0,     0,    15,    83,     0,     0,    68,     0,     0,     0,
       0,     0,     0,    69,     0,    28,    29,    30,     0,     0,
       0,    74,    12,    18,     0,    15,     0,     0,    25,     0,
      32,     0,     0,     0,     0,     0,    26,    27,    36,     0,
      42,    87,     0,     0,    66,     0,     9,    19,    20,     0,
       0,    13,    14,     0,    79,    77,    78,    35,     0,    63,
      64,     0,   102,   103,     0,     0,    51,    54,    57,    58,
      61,    62,     0,     0,     0,    74,     0,     0,    43,    89,
       0,     0,    70,    12,     0,     0,    18,    21,     0,    22,
       0,     0,    85,    35,    35,    59,     0,     0,    90,    91,
      94,    95,    92,    93,    49,     0,    98,    96,    97,    52,
       0,   101,    99,   100,    55,     0,    60,    46,     0,    87,
       0,     0,     0,    86,    67,    74,    11,     8,    31,    17,
      23,    81,    80,    24,     0,    76,     0,    82,    34,     0,
      65,    46,    50,    54,    57,    48,    45,     0,    39,     0,
      40,    41,    89,     0,     0,     0,    73,    75,     0,    33,
       0,    53,    56,    48,     0,    38,     0,    88,    72,     0,
      71,     0,    46,    47,    44,    74,    35,     0,    85,    37,
      84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,   173,  -148,  -148,  -148,    98,  -148,   136,    -2,
      77,  -148,  -148,  -148,   120,  -148,   147,  -148,  -148,  -148,
     124,  -103,   -16,  -148,  -147,     2,   -46,  -148,   -59,    23,
      54,    24,   -66,  -148,   -18,   -17,   138,  -138,  -148,   -74,
    -148,   164,    -9,    53,    25,  -148,  -148,  -148,  -148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    21,    66,     9,    44,    10,
      69,    70,   106,   107,    11,    19,    34,    35,   109,    36,
      50,   112,   166,    38,   167,   184,    99,   124,    86,   129,
      87,   134,    88,    89,    90,    91,    41,    64,   113,    77,
     153,    25,   157,   100,   143,   125,   130,   135,    92
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    40,    37,   101,   114,    85,    93,   176,    96,    97,
     158,   159,   154,    98,   180,   115,    26,    39,    40,    37,
      45,    26,    12,   174,    13,   116,   136,   175,    28,    74,
      14,    29,    30,    31,    32,    94,   152,    26,    79,    80,
     131,    33,    15,    45,    74,   197,    33,    61,    75,    76,
     151,    62,   132,   133,   155,    63,   165,   176,   126,    81,
      16,    26,    33,    75,    76,    18,   162,   127,   128,   164,
      82,    83,    27,    28,    20,    84,    29,    30,    31,    32,
     139,    22,    26,    23,    62,    24,    33,     1,    63,     2,
       3,     4,    42,   198,    28,    43,   172,    29,    30,    31,
      32,   118,   119,   120,   121,   122,   123,    33,     3,     4,
       3,     4,   105,    67,    68,   189,    47,   196,    48,    39,
      40,    49,    56,    58,    51,    52,    53,    54,    55,    59,
      78,   102,   103,   110,    73,    71,    60,    65,   104,   117,
     111,   161,   145,    39,    40,   137,   138,    39,    40,   183,
     140,   141,   142,   144,   147,   150,   160,   156,   178,   186,
     168,   170,   177,   171,   188,    39,    40,   183,   173,   179,
     185,   190,   195,   191,    39,    40,   192,   194,   199,   174,
      17,    72,    57,   149,   163,   193,   181,    46,   182,   200,
     108,    95,   169,     0,     0,     0,     0,   187,     0,     0,
       0,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148
};

static const yytype_int16 yycheck[] =
{
      18,    18,    18,    62,    78,    51,    52,   145,    54,    55,
     113,   114,     4,    59,   161,    81,     3,    35,    35,    35,
      22,     3,     3,    45,     3,    84,    92,    49,    15,     3,
       3,    18,    19,    20,    21,    53,   110,     3,     4,     5,
      26,    28,    41,    45,     3,   192,    28,    41,    22,    23,
      24,    45,    38,    39,    46,    49,    43,   195,    27,    25,
       0,     3,    28,    22,    23,    43,   125,    36,    37,   135,
      36,    37,    14,    15,     7,    41,    18,    19,    20,    21,
      41,    43,     3,    41,    45,     3,    28,     6,    49,     8,
       9,    10,     3,   196,    15,    43,   142,    18,    19,    20,
      21,    30,    31,    32,    33,    34,    35,    28,     9,    10,
       9,    10,    13,    11,    12,   174,    50,   191,    42,   137,
     137,     3,    44,    48,    41,    41,    41,    41,    41,    29,
      50,     3,     3,    40,    42,    44,    48,    47,    44,    42,
      45,    16,    46,   161,   161,    42,    42,   165,   165,   165,
      42,    42,    47,    42,    48,    48,    42,    47,     3,    42,
      48,    48,    46,    48,     3,   183,   183,   183,    49,    48,
      48,     3,    46,    50,   192,   192,    17,    44,    48,    45,
       7,    45,    35,   106,   130,   183,   163,    23,   164,   198,
      70,    53,   139,    -1,    -1,    -1,    -1,   172,    -1,    -1,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     8,     9,    10,    52,    53,    54,    55,    58,
      60,    65,     3,     3,     3,    41,     0,    53,    43,    66,
       7,    56,    43,    41,     3,    92,     3,    14,    15,    18,
      19,    20,    21,    28,    67,    68,    70,    73,    74,    85,
      86,    87,     3,    43,    59,    60,    92,    50,    42,     3,
      71,    41,    41,    41,    41,    41,    44,    67,    48,    29,
      48,    41,    45,    49,    88,    47,    57,    11,    12,    61,
      62,    44,    59,    42,     3,    22,    23,    90,    50,     4,
       5,    25,    36,    37,    41,    77,    79,    81,    83,    84,
      85,    86,    99,    77,    85,    87,    77,    77,    77,    77,
      94,    79,     3,     3,    44,    13,    63,    64,    65,    69,
      40,    45,    72,    89,    90,    83,    79,    42,    30,    31,
      32,    33,    34,    35,    78,    96,    27,    36,    37,    80,
      97,    26,    38,    39,    82,    98,    83,    42,    42,    41,
      42,    42,    47,    95,    42,    46,    57,    48,    71,    61,
      48,    24,    90,    91,     4,    46,    47,    93,    72,    72,
      42,    16,    79,    81,    83,    43,    73,    75,    48,    94,
      48,    48,    77,    49,    45,    49,    88,    46,     3,    48,
      75,    80,    82,    73,    76,    48,    42,    95,     3,    79,
       3,    50,    17,    76,    44,    46,    90,    75,    72,    48,
      93
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    55,    56,
      56,    57,    57,    58,    59,    59,    60,    61,    61,    62,
      62,    63,    63,    64,    65,    65,    66,    67,    67,    68,
      68,    69,    70,    71,    72,    72,    73,    73,    73,    73,
      73,    73,    73,    74,    75,    75,    75,    76,    76,    77,
      78,    78,    79,    80,    80,    81,    82,    82,    83,    83,
      83,    84,    84,    84,    84,    84,    85,    86,    87,    87,
      87,    87,    87,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    92,    92,    93,    93,    94,    94,    95,    95,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    98,
      98,    98,    99,    99
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     7,     3,
       0,     3,     0,     5,     2,     0,     2,     3,     0,     1,
       1,     1,     1,     2,     7,     4,     3,     2,     0,     1,
       1,     2,     2,     5,     2,     0,     2,     9,     6,     5,
       5,     5,     2,     3,     3,     1,     0,     2,     0,     2,
       2,     0,     2,     3,     0,     2,     3,     0,     1,     2,
       2,     1,     1,     1,     1,     3,     2,     4,     1,     1,
       3,     6,     6,     4,     0,     3,     2,     1,     1,     1,
       1,     1,     5,     0,     6,     0,     2,     0,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: classOrImplOrFunc_list  */
#line 55 "parser.y"
    {
        (yyval.node) = create_node(NODE_PROG, "program", 1, 1);
        add_child((yyval.node), (yyvsp[0].node));
        root = (yyval.node);
    }
#line 1336 "parser.tab.c"
    break;

  case 3: /* classOrImplOrFunc_list: classOrImplOrFunc classOrImplOrFunc_list  */
#line 63 "parser.y"
                      {
                          (yyval.node) = create_node(NODE_LIST, "list", (yyvsp[-1].node)->line, 1);
                          add_child((yyval.node), (yyvsp[-1].node));
                          add_child((yyval.node), (yyvsp[0].node));
                      }
#line 1346 "parser.tab.c"
    break;

  case 4: /* classOrImplOrFunc_list: classOrImplOrFunc  */
#line 69 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1352 "parser.tab.c"
    break;

  case 5: /* classOrImplOrFunc: classDecl  */
#line 72 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1358 "parser.tab.c"
    break;

  case 6: /* classOrImplOrFunc: implDef  */
#line 73 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1364 "parser.tab.c"
    break;

  case 7: /* classOrImplOrFunc: funcDef  */
#line 74 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1370 "parser.tab.c"
    break;

  case 8: /* classDecl: CLASS ID isa_opt LBRACE member_list_opt RBRACE SEMI  */
#line 78 "parser.y"
         {
             (yyval.node) = create_node(NODE_CLASS_DECL, "class", (yyvsp[-5].tok)->line, (yyvsp[-5].tok)->column);
             ASTNode* id = create_node(NODE_ID, (yyvsp[-5].tok)->lexeme, (yyvsp[-5].tok)->line, (yyvsp[-5].tok)->column);
             add_child((yyval.node), id);
             if ((yyvsp[-4].node)) add_child((yyval.node), (yyvsp[-4].node));
             if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
         }
#line 1382 "parser.tab.c"
    break;

  case 9: /* isa_opt: ISA ID id_list_opt  */
#line 88 "parser.y"
       {
           (yyval.node) = create_node(NODE_LIST, "inherits", (yyvsp[-1].tok)->line, (yyvsp[-1].tok)->column);
           ASTNode* id = create_node(NODE_ID, (yyvsp[-1].tok)->lexeme, (yyvsp[-1].tok)->line, (yyvsp[-1].tok)->column);
           add_child((yyval.node), id);
           if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
       }
#line 1393 "parser.tab.c"
    break;

  case 10: /* isa_opt: %empty  */
#line 94 "parser.y"
                     { (yyval.node) = NULL; }
#line 1399 "parser.tab.c"
    break;

  case 11: /* id_list_opt: COMMA ID id_list_opt  */
#line 98 "parser.y"
           {
               (yyval.node) = create_node(NODE_LIST, "id_list", (yyvsp[-1].tok)->line, (yyvsp[-1].tok)->column);
               ASTNode* id = create_node(NODE_ID, (yyvsp[-1].tok)->lexeme, (yyvsp[-1].tok)->line, (yyvsp[-1].tok)->column);
               add_child((yyval.node), id);
               if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
           }
#line 1410 "parser.tab.c"
    break;

  case 12: /* id_list_opt: %empty  */
#line 104 "parser.y"
                         { (yyval.node) = NULL; }
#line 1416 "parser.tab.c"
    break;

  case 13: /* implDef: IMPLEMENT ID LBRACE func_list_opt RBRACE  */
#line 108 "parser.y"
       {
           (yyval.node) = create_node(NODE_IMPL_DEF, "implement", (yyvsp[-3].tok)->line, (yyvsp[-3].tok)->column);
           ASTNode* id = create_node(NODE_ID, (yyvsp[-3].tok)->lexeme, (yyvsp[-3].tok)->line, (yyvsp[-3].tok)->column);
           add_child((yyval.node), id);
           if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
       }
#line 1427 "parser.tab.c"
    break;

  case 14: /* func_list_opt: funcDef func_list_opt  */
#line 117 "parser.y"
             {
                 (yyval.node) = create_node(NODE_LIST, "func_list", (yyvsp[-1].node)->line, 1);
                 add_child((yyval.node), (yyvsp[-1].node));
                 if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
             }
#line 1437 "parser.tab.c"
    break;

  case 15: /* func_list_opt: %empty  */
#line 122 "parser.y"
                           { (yyval.node) = NULL; }
#line 1443 "parser.tab.c"
    break;

  case 16: /* funcDef: funcHead funcBody  */
#line 126 "parser.y"
       {
           (yyval.node) = create_node(NODE_FUNC_DEF, "funcDef", (yyvsp[-1].node)->line, 1);
           add_child((yyval.node), (yyvsp[-1].node));
           add_child((yyval.node), (yyvsp[0].node));
       }
#line 1453 "parser.tab.c"
    break;

  case 17: /* member_list_opt: visibility memberDecl member_list_opt  */
#line 134 "parser.y"
               {
                   (yyval.node) = create_node(NODE_LIST, "members", (yyvsp[-1].node)->line, 1);
                   add_child((yyval.node), (yyvsp[-2].node));
                   add_child((yyval.node), (yyvsp[-1].node));
                   if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
               }
#line 1464 "parser.tab.c"
    break;

  case 18: /* member_list_opt: %empty  */
#line 140 "parser.y"
                             { (yyval.node) = NULL; }
#line 1470 "parser.tab.c"
    break;

  case 19: /* visibility: PUBLIC  */
#line 144 "parser.y"
          { (yyval.node) = create_node(NODE_ID, "public", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1476 "parser.tab.c"
    break;

  case 20: /* visibility: PRIVATE  */
#line 146 "parser.y"
          { (yyval.node) = create_node(NODE_ID, "private", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1482 "parser.tab.c"
    break;

  case 21: /* memberDecl: funcDecl  */
#line 149 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1488 "parser.tab.c"
    break;

  case 22: /* memberDecl: attributeDecl  */
#line 150 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1494 "parser.tab.c"
    break;

  case 23: /* funcDecl: funcHead SEMI  */
#line 154 "parser.y"
        {
            (yyval.node) = create_node(NODE_FUNC_DECL, "funcDecl", (yyvsp[-1].node)->line, 1);
            add_child((yyval.node), (yyvsp[-1].node));
        }
#line 1503 "parser.tab.c"
    break;

  case 24: /* funcHead: FUNC ID LPAREN fParams_opt RPAREN ARROW returnType  */
#line 161 "parser.y"
        {
            (yyval.node) = create_node(NODE_FUNC_DEF, "funcHead", (yyvsp[-5].tok)->line, (yyvsp[-5].tok)->column);
            ASTNode* id = create_node(NODE_ID, (yyvsp[-5].tok)->lexeme, (yyvsp[-5].tok)->line, (yyvsp[-5].tok)->column);
            add_child((yyval.node), id);
            if ((yyvsp[-3].node)) add_child((yyval.node), (yyvsp[-3].node));
            add_child((yyval.node), (yyvsp[0].node));
        }
#line 1515 "parser.tab.c"
    break;

  case 25: /* funcHead: CONSTRUCTOR LPAREN fParams_opt RPAREN  */
#line 169 "parser.y"
        {
            (yyval.node) = create_node(NODE_FUNC_DEF, "constructor", (yyvsp[-3].tok)->line, (yyvsp[-3].tok)->column);
            if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
        }
#line 1524 "parser.tab.c"
    break;

  case 26: /* funcBody: LBRACE stmt_list_opt RBRACE  */
#line 176 "parser.y"
        {
            (yyval.node) = create_node(NODE_LIST, "funcBody", (yyvsp[-2].tok)->line, (yyvsp[-2].tok)->column);
            if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
        }
#line 1533 "parser.tab.c"
    break;

  case 27: /* stmt_list_opt: varDeclOrStmt stmt_list_opt  */
#line 183 "parser.y"
             {
                 (yyval.node) = create_node(NODE_LIST, "stmts", (yyvsp[-1].node)->line, 1);
                 add_child((yyval.node), (yyvsp[-1].node));
                 if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
             }
#line 1543 "parser.tab.c"
    break;

  case 28: /* stmt_list_opt: %empty  */
#line 188 "parser.y"
                           { (yyval.node) = NULL; }
#line 1549 "parser.tab.c"
    break;

  case 29: /* varDeclOrStmt: localVarDecl  */
#line 191 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1555 "parser.tab.c"
    break;

  case 30: /* varDeclOrStmt: statement  */
#line 192 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1561 "parser.tab.c"
    break;

  case 31: /* attributeDecl: ATTRIBUTE varDecl  */
#line 196 "parser.y"
             {
                 (yyval.node) = (yyvsp[0].node);
                 (yyval.node)->type = NODE_VAR_DECL;
             }
#line 1570 "parser.tab.c"
    break;

  case 32: /* localVarDecl: LOCAL varDecl  */
#line 203 "parser.y"
            {
                (yyval.node) = (yyvsp[0].node);
            }
#line 1578 "parser.tab.c"
    break;

  case 33: /* varDecl: ID COLON type array_list_opt SEMI  */
#line 209 "parser.y"
       {
           (yyval.node) = create_node(NODE_VAR_DECL, "varDecl", (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
           ASTNode* id = create_node(NODE_ID, (yyvsp[-4].tok)->lexeme, (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
           add_child((yyval.node), id);
           add_child((yyval.node), (yyvsp[-2].node));
           if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
       }
#line 1590 "parser.tab.c"
    break;

  case 34: /* array_list_opt: arraySize array_list_opt  */
#line 219 "parser.y"
              {
                  (yyval.node) = create_node(NODE_LIST, "arrays", (yyvsp[-1].node)->line, 1);
                  add_child((yyval.node), (yyvsp[-1].node));
                  if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
              }
#line 1600 "parser.tab.c"
    break;

  case 35: /* array_list_opt: %empty  */
#line 224 "parser.y"
                            { (yyval.node) = NULL; }
#line 1606 "parser.tab.c"
    break;

  case 36: /* statement: assignStat SEMI  */
#line 228 "parser.y"
         { (yyval.node) = (yyvsp[-1].node); }
#line 1612 "parser.tab.c"
    break;

  case 37: /* statement: IF LPAREN expr RPAREN THEN statBlock ELSE statBlock SEMI  */
#line 230 "parser.y"
         {
             (yyval.node) = create_node(NODE_IF_STAT, "if", (yyvsp[-8].tok)->line, (yyvsp[-8].tok)->column);
             add_child((yyval.node), (yyvsp[-6].node));
             add_child((yyval.node), (yyvsp[-3].node));
             add_child((yyval.node), (yyvsp[-1].node));
         }
#line 1623 "parser.tab.c"
    break;

  case 38: /* statement: WHILE LPAREN expr RPAREN statBlock SEMI  */
#line 237 "parser.y"
         {
             (yyval.node) = create_node(NODE_WHILE_STAT, "while", (yyvsp[-5].tok)->line, (yyvsp[-5].tok)->column);
             add_child((yyval.node), (yyvsp[-3].node));
             add_child((yyval.node), (yyvsp[-1].node));
         }
#line 1633 "parser.tab.c"
    break;

  case 39: /* statement: READ LPAREN variable RPAREN SEMI  */
#line 243 "parser.y"
         {
             (yyval.node) = create_node(NODE_READ_STAT, "read", (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
             add_child((yyval.node), (yyvsp[-2].node));
         }
#line 1642 "parser.tab.c"
    break;

  case 40: /* statement: WRITE LPAREN expr RPAREN SEMI  */
#line 248 "parser.y"
         {
             (yyval.node) = create_node(NODE_WRITE_STAT, "write", (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
             add_child((yyval.node), (yyvsp[-2].node));
         }
#line 1651 "parser.tab.c"
    break;

  case 41: /* statement: RETURN LPAREN expr RPAREN SEMI  */
#line 253 "parser.y"
         {
             (yyval.node) = create_node(NODE_RETURN_STAT, "return", (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
             add_child((yyval.node), (yyvsp[-2].node));
         }
#line 1660 "parser.tab.c"
    break;

  case 42: /* statement: functionCall SEMI  */
#line 258 "parser.y"
         { (yyval.node) = (yyvsp[-1].node); }
#line 1666 "parser.tab.c"
    break;

  case 43: /* assignStat: variable ASSIGN expr  */
#line 262 "parser.y"
          {
              (yyval.node) = create_node(NODE_ASSIGN_STAT, ":=", (yyvsp[-2].node)->line, 1);
              add_child((yyval.node), (yyvsp[-2].node));
              add_child((yyval.node), (yyvsp[0].node));
          }
#line 1676 "parser.tab.c"
    break;

  case 44: /* statBlock: LBRACE statement_list_opt RBRACE  */
#line 270 "parser.y"
         { (yyval.node) = (yyvsp[-1].node); }
#line 1682 "parser.tab.c"
    break;

  case 45: /* statBlock: statement  */
#line 272 "parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1688 "parser.tab.c"
    break;

  case 46: /* statBlock: %empty  */
#line 273 "parser.y"
                       { (yyval.node) = NULL; }
#line 1694 "parser.tab.c"
    break;

  case 47: /* statement_list_opt: statement statement_list_opt  */
#line 277 "parser.y"
                  {
                      (yyval.node) = create_node(NODE_LIST, "stat_list", (yyvsp[-1].node)->line, 1);
                      add_child((yyval.node), (yyvsp[-1].node));
                      if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
                  }
#line 1704 "parser.tab.c"
    break;

  case 48: /* statement_list_opt: %empty  */
#line 282 "parser.y"
                                { (yyval.node) = NULL; }
#line 1710 "parser.tab.c"
    break;

  case 49: /* expr: arithExpr rel_expr_opt  */
#line 286 "parser.y"
    {
        if ((yyvsp[0].node)) {
            (yyval.node) = create_node(NODE_REL_EXPR, "relExpr", (yyvsp[-1].node)->line, 1);
            add_child((yyval.node), (yyvsp[-1].node));
            add_child((yyval.node), (yyvsp[0].node));
        } else {
            (yyval.node) = (yyvsp[-1].node);
        }
    }
#line 1724 "parser.tab.c"
    break;

  case 50: /* rel_expr_opt: relOp arithExpr  */
#line 298 "parser.y"
            {
                (yyval.node) = create_node(NODE_EXPR, "rel", (yyvsp[-1].node)->line, 1);
                add_child((yyval.node), (yyvsp[-1].node));
                add_child((yyval.node), (yyvsp[0].node));
            }
#line 1734 "parser.tab.c"
    break;

  case 51: /* rel_expr_opt: %empty  */
#line 303 "parser.y"
                          { (yyval.node) = NULL; }
#line 1740 "parser.tab.c"
    break;

  case 52: /* arithExpr: term arith_expr_tail  */
#line 307 "parser.y"
         {
             if ((yyvsp[0].node)) {
                 (yyval.node) = create_node(NODE_ADD_EXPR, "addExpr", (yyvsp[-1].node)->line, 1);
                 add_child((yyval.node), (yyvsp[-1].node));
                 add_child((yyval.node), (yyvsp[0].node));
             } else {
                 (yyval.node) = (yyvsp[-1].node);
             }
         }
#line 1754 "parser.tab.c"
    break;

  case 53: /* arith_expr_tail: addOp term arith_expr_tail  */
#line 319 "parser.y"
               {
                   (yyval.node) = create_node(NODE_EXPR, "add_tail", (yyvsp[-2].node)->line, 1);
                   add_child((yyval.node), (yyvsp[-2].node));
                   add_child((yyval.node), (yyvsp[-1].node));
                   if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
               }
#line 1765 "parser.tab.c"
    break;

  case 54: /* arith_expr_tail: %empty  */
#line 325 "parser.y"
                             { (yyval.node) = NULL; }
#line 1771 "parser.tab.c"
    break;

  case 55: /* term: factor term_tail  */
#line 329 "parser.y"
    {
        if ((yyvsp[0].node)) {
            (yyval.node) = create_node(NODE_MULT_EXPR, "multExpr", (yyvsp[-1].node)->line, 1);
            add_child((yyval.node), (yyvsp[-1].node));
            add_child((yyval.node), (yyvsp[0].node));
        } else {
            (yyval.node) = (yyvsp[-1].node);
        }
    }
#line 1785 "parser.tab.c"
    break;

  case 56: /* term_tail: multOp factor term_tail  */
#line 341 "parser.y"
         {
             (yyval.node) = create_node(NODE_EXPR, "mult_tail", (yyvsp[-2].node)->line, 1);
             add_child((yyval.node), (yyvsp[-2].node));
             add_child((yyval.node), (yyvsp[-1].node));
             if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
         }
#line 1796 "parser.tab.c"
    break;

  case 57: /* term_tail: %empty  */
#line 347 "parser.y"
                       { (yyval.node) = NULL; }
#line 1802 "parser.tab.c"
    break;

  case 58: /* factor: primary_factor  */
#line 351 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1808 "parser.tab.c"
    break;

  case 59: /* factor: NOT factor  */
#line 353 "parser.y"
      {
          (yyval.node) = create_node(NODE_NOT_EXPR, "not", (yyvsp[0].node)->line, 1);
          add_child((yyval.node), (yyvsp[0].node));
      }
#line 1817 "parser.tab.c"
    break;

  case 60: /* factor: sign factor  */
#line 358 "parser.y"
      {
          (yyval.node) = create_node(NODE_SIGN_EXPR, (yyvsp[-1].node)->value, (yyvsp[0].node)->line, 1);
          add_child((yyval.node), (yyvsp[0].node));
      }
#line 1826 "parser.tab.c"
    break;

  case 61: /* primary_factor: variable  */
#line 365 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1832 "parser.tab.c"
    break;

  case 62: /* primary_factor: functionCall  */
#line 367 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1838 "parser.tab.c"
    break;

  case 63: /* primary_factor: INTLIT  */
#line 369 "parser.y"
              { (yyval.node) = create_node(NODE_INTLIT, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1844 "parser.tab.c"
    break;

  case 64: /* primary_factor: FLOATLIT  */
#line 371 "parser.y"
              { (yyval.node) = create_node(NODE_FLOATLIT, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1850 "parser.tab.c"
    break;

  case 65: /* primary_factor: LPAREN arithExpr RPAREN  */
#line 373 "parser.y"
              { (yyval.node) = (yyvsp[-1].node); }
#line 1856 "parser.tab.c"
    break;

  case 66: /* variable: qualified_id indices_opt  */
#line 377 "parser.y"
        {
            (yyval.node) = create_node(NODE_VARIABLE, "var", (yyvsp[-1].node)->line, 1);
            add_child((yyval.node), (yyvsp[-1].node));
            if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
        }
#line 1866 "parser.tab.c"
    break;

  case 67: /* functionCall: qualified_id LPAREN aParams_opt RPAREN  */
#line 385 "parser.y"
            {
                (yyval.node) = create_node(NODE_FUNC_CALL, "call", (yyvsp[-3].node)->line, 1);
                add_child((yyval.node), (yyvsp[-3].node));
                if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
            }
#line 1876 "parser.tab.c"
    break;

  case 68: /* qualified_id: ID  */
#line 393 "parser.y"
            { (yyval.node) = create_node(NODE_ID, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1882 "parser.tab.c"
    break;

  case 69: /* qualified_id: SELF  */
#line 395 "parser.y"
            { (yyval.node) = create_node(NODE_ID, "self", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1888 "parser.tab.c"
    break;

  case 70: /* qualified_id: qualified_id DOT ID  */
#line 397 "parser.y"
            {
                (yyval.node) = create_node(NODE_EXPR, "member", (yyvsp[-2].node)->line, 1);
                add_child((yyval.node), (yyvsp[-2].node));
                add_child((yyval.node), create_node(NODE_ID, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column));
            }
#line 1898 "parser.tab.c"
    break;

  case 71: /* qualified_id: qualified_id LBRACKET arithExpr RBRACKET DOT ID  */
#line 403 "parser.y"
            {
                (yyval.node) = create_node(NODE_EXPR, "array_member", (yyvsp[-5].node)->line, 1);
                add_child((yyval.node), (yyvsp[-5].node));
                add_child((yyval.node), (yyvsp[-3].node));
                add_child((yyval.node), create_node(NODE_ID, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column));
            }
#line 1909 "parser.tab.c"
    break;

  case 72: /* qualified_id: qualified_id LPAREN aParams_opt RPAREN DOT ID  */
#line 410 "parser.y"
            {
                (yyval.node) = create_node(NODE_EXPR, "call_member", (yyvsp[-5].node)->line, 1);
                add_child((yyval.node), (yyvsp[-5].node));
                if ((yyvsp[-3].node)) add_child((yyval.node), (yyvsp[-3].node));
                add_child((yyval.node), create_node(NODE_ID, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column));
            }
#line 1920 "parser.tab.c"
    break;

  case 73: /* indices_opt: LBRACKET arithExpr RBRACKET indices_opt  */
#line 419 "parser.y"
           {
               (yyval.node) = create_node(NODE_LIST, "indices", (yyvsp[-2].node)->line, 1);
               add_child((yyval.node), (yyvsp[-2].node));
               if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
           }
#line 1930 "parser.tab.c"
    break;

  case 74: /* indices_opt: %empty  */
#line 424 "parser.y"
                         { (yyval.node) = NULL; }
#line 1936 "parser.tab.c"
    break;

  case 75: /* arraySize: LBRACKET INTLIT RBRACKET  */
#line 428 "parser.y"
         {
             (yyval.node) = create_node(NODE_ARRAY_SIZE, (yyvsp[-1].tok)->lexeme, (yyvsp[-1].tok)->line, (yyvsp[-1].tok)->column);
         }
#line 1944 "parser.tab.c"
    break;

  case 76: /* arraySize: LBRACKET RBRACKET  */
#line 432 "parser.y"
         {
             (yyval.node) = create_node(NODE_ARRAY_SIZE, "0", (yyvsp[-1].tok)->line, (yyvsp[-1].tok)->column);
         }
#line 1952 "parser.tab.c"
    break;

  case 77: /* type: INTEGER_TYPE  */
#line 438 "parser.y"
    { (yyval.node) = create_node(NODE_TYPE, "integer", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1958 "parser.tab.c"
    break;

  case 78: /* type: FLOAT_TYPE  */
#line 440 "parser.y"
    { (yyval.node) = create_node(NODE_TYPE, "float", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1964 "parser.tab.c"
    break;

  case 79: /* type: ID  */
#line 442 "parser.y"
    { (yyval.node) = create_node(NODE_TYPE, (yyvsp[0].tok)->lexeme, (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1970 "parser.tab.c"
    break;

  case 80: /* returnType: type  */
#line 446 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1976 "parser.tab.c"
    break;

  case 81: /* returnType: VOID  */
#line 448 "parser.y"
          { (yyval.node) = create_node(NODE_TYPE, "void", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 1982 "parser.tab.c"
    break;

  case 82: /* fParams_opt: ID COLON type array_list_opt fParams_tail_opt  */
#line 452 "parser.y"
           {
               (yyval.node) = create_node(NODE_PARAM, "param", (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
               ASTNode* id = create_node(NODE_ID, (yyvsp[-4].tok)->lexeme, (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
               add_child((yyval.node), id);
               add_child((yyval.node), (yyvsp[-2].node));
               if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
               if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
           }
#line 1995 "parser.tab.c"
    break;

  case 83: /* fParams_opt: %empty  */
#line 460 "parser.y"
                         { (yyval.node) = NULL; }
#line 2001 "parser.tab.c"
    break;

  case 84: /* fParams_tail_opt: COMMA ID COLON type array_list_opt fParams_tail_opt  */
#line 464 "parser.y"
                {
                    (yyval.node) = create_node(NODE_PARAM, "param", (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
                    ASTNode* id = create_node(NODE_ID, (yyvsp[-4].tok)->lexeme, (yyvsp[-4].tok)->line, (yyvsp[-4].tok)->column);
                    add_child((yyval.node), id);
                    add_child((yyval.node), (yyvsp[-2].node));
                    if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
                    if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
                }
#line 2014 "parser.tab.c"
    break;

  case 85: /* fParams_tail_opt: %empty  */
#line 472 "parser.y"
                              { (yyval.node) = NULL; }
#line 2020 "parser.tab.c"
    break;

  case 86: /* aParams_opt: expr aParams_tail_opt  */
#line 476 "parser.y"
           {
               (yyval.node) = create_node(NODE_LIST, "args", (yyvsp[-1].node)->line, 1);
               add_child((yyval.node), (yyvsp[-1].node));
               if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
           }
#line 2030 "parser.tab.c"
    break;

  case 87: /* aParams_opt: %empty  */
#line 481 "parser.y"
                         { (yyval.node) = NULL; }
#line 2036 "parser.tab.c"
    break;

  case 88: /* aParams_tail_opt: COMMA expr aParams_tail_opt  */
#line 485 "parser.y"
                {
                    (yyval.node) = create_node(NODE_LIST, "args", (yyvsp[-1].node)->line, 1);
                    add_child((yyval.node), (yyvsp[-1].node));
                    if ((yyvsp[0].node)) add_child((yyval.node), (yyvsp[0].node));
                }
#line 2046 "parser.tab.c"
    break;

  case 89: /* aParams_tail_opt: %empty  */
#line 490 "parser.y"
                              { (yyval.node) = NULL; }
#line 2052 "parser.tab.c"
    break;

  case 90: /* relOp: EQ  */
#line 493 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, "==", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2058 "parser.tab.c"
    break;

  case 91: /* relOp: NE  */
#line 494 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, "<>", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2064 "parser.tab.c"
    break;

  case 92: /* relOp: LT  */
#line 495 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, "<", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2070 "parser.tab.c"
    break;

  case 93: /* relOp: GT  */
#line 496 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, ">", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2076 "parser.tab.c"
    break;

  case 94: /* relOp: LE  */
#line 497 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, "<=", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2082 "parser.tab.c"
    break;

  case 95: /* relOp: GE  */
#line 498 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, ">=", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2088 "parser.tab.c"
    break;

  case 96: /* addOp: PLUS  */
#line 501 "parser.y"
            { (yyval.node) = create_node(NODE_EXPR, "+", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2094 "parser.tab.c"
    break;

  case 97: /* addOp: MINUS  */
#line 502 "parser.y"
             { (yyval.node) = create_node(NODE_EXPR, "-", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2100 "parser.tab.c"
    break;

  case 98: /* addOp: OR  */
#line 503 "parser.y"
          { (yyval.node) = create_node(NODE_EXPR, "or", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2106 "parser.tab.c"
    break;

  case 99: /* multOp: MULT  */
#line 506 "parser.y"
             { (yyval.node) = create_node(NODE_EXPR, "*", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2112 "parser.tab.c"
    break;

  case 100: /* multOp: DIV  */
#line 507 "parser.y"
            { (yyval.node) = create_node(NODE_EXPR, "/", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2118 "parser.tab.c"
    break;

  case 101: /* multOp: AND  */
#line 508 "parser.y"
            { (yyval.node) = create_node(NODE_EXPR, "and", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2124 "parser.tab.c"
    break;

  case 102: /* sign: PLUS  */
#line 511 "parser.y"
           { (yyval.node) = create_node(NODE_EXPR, "+", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2130 "parser.tab.c"
    break;

  case 103: /* sign: MINUS  */
#line 512 "parser.y"
            { (yyval.node) = create_node(NODE_EXPR, "-", (yyvsp[0].tok)->line, (yyvsp[0].tok)->column); }
#line 2136 "parser.tab.c"
    break;


#line 2140 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 515 "parser.y"


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
